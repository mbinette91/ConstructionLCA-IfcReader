/*
* This file contains the function `handleData` which handles everything related to the persistance of useful information for later LCA computing.
* It is expected this is the module that is going to change the most often.
*/
#include "IfcReader.hpp"

#include <iostream>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Transaction.h>
#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcPropertySet.h>
#include <ifcpp/IFC4/include/IfcRelDefinesByProperties.h>
#include <ifcpp/IFC4/include/IfcRelAssociatesMaterial.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSetUsage.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSet.h>
#include <ifcpp/IFC4/include/IfcMaterialLayer.h>
#include <ifcpp/IFC4/include/IfcMaterial.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcpp/IFC4/include/IfcText.h>
#include <ifcpp/IFC4/include/IfcIdentifier.h>
#include <ifcpp/IFC4/include/IfcNonNegativeLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcPropertySingleValue.h>
#include "SQLiteDataHandler.hpp"

namespace IfcReader
{
	SQLiteDataHandler::SQLiteDataHandler(std::string path) : closed(false)
	{
		db = new SQLite::Database(path, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		transaction = new SQLite::Transaction(*db);
	}

	SQLiteDataHandler::~SQLiteDataHandler()
	{
		if (!closed)
			this->close();
		delete transaction;
		delete db;
	}

	void SQLiteDataHandler::initialize(){
		db->exec("CREATE TABLE IF NOT EXISTS products(id INTEGER PRIMARY KEY, project_id INTEGER, GUID TEXT, name TEXT, description TEXT, class_name TEXT)");
		db->exec("CREATE TABLE IF NOT EXISTS materials(id INTEGER PRIMARY KEY, product_id INTEGER, name TEXT, thickness REAL, layer_name TEXT)");
		db->exec("CREATE TABLE IF NOT EXISTS property_set(id INTEGER PRIMARY KEY, product_id INTEGER, name TEXT)");
		db->exec("CREATE TABLE IF NOT EXISTS property(id INTEGER PRIMARY KEY, property_set_id INTEGER, name TEXT, value TEXT)");
	}

	void SQLiteDataHandler::close(){
		closed = true;
		transaction->commit(); // Don't forget to commit !
	}

	int SQLiteDataHandler::handleProduct(shared_ptr<IfcProduct> ifc_product){
		std::string guid = w2str(ifc_product->m_GlobalId->m_value);
		std::string name = w2str(ifc_product->m_Name->m_value);
		std::string description;
		if (ifc_product->m_Description)
			description = w2str(ifc_product->m_Description->m_value);

		SQLite::Statement query(*db, "INSERT INTO products VALUES(NULL, ?, ?, ?, ?, ?)");
		query.bind(1, project_id);
		query.bind(2, guid);
		query.bind(3, name);
		query.bind(4, description);
		query.bind(5, ifc_product->className());

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR (SQLiteDataHandler::handleProduct): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;

		return getLastInsertedProductId();
	}

	void SQLiteDataHandler::handleMaterial(int product_id, shared_ptr<IfcMaterialLayerSet> matls, shared_ptr<IfcMaterialLayer> matl, shared_ptr<IfcMaterial> mat){
		std::string layer_name = matls && matls->m_LayerSetName ? w2str(matls->m_LayerSetName->m_value) : "";
		std::string name = mat && mat->m_Name ? w2str(mat->m_Name->m_value) : "";
		double thickness = matl && matl->m_LayerThickness ? matl->m_LayerThickness->m_value : 0;

		SQLite::Statement query(*db, "INSERT INTO materials VALUES(NULL, ?, ?, ?, ?)");
		query.bind(1, product_id);
		query.bind(2, name);
		query.bind(3, thickness);
		query.bind(4, layer_name);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR (SQLiteDataHandler::handleMaterial): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
	}

	int SQLiteDataHandler::handlePropertySet(int product_id, shared_ptr<IfcPropertySet> prop_set){
		std::string name = w2str(prop_set->m_Name->m_value);
		SQLite::Statement query(*db, "INSERT INTO property_set VALUES(NULL, ?, ?)");
		query.bind(1, product_id);
		query.bind(2, name);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR (SQLiteDataHandler::handlePropertySet): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;

		return getLastInsertedPropertySetId();
	}

	void SQLiteDataHandler::handleProperty(int property_set_id, shared_ptr<IfcPropertySingleValue> prop_single_value){
		std::string name = w2str(prop_single_value->m_Name->m_value);
		std::string value = w2str(IfcValue2wstr(prop_single_value->m_NominalValue));

		SQLite::Statement query(*db, "INSERT INTO property VALUES(NULL, ?, ?, ?)");
		query.bind(1, property_set_id);
		query.bind(2, name);
		query.bind(3, value);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR (SQLiteDataHandler::handleProperty): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
	}

	int SQLiteDataHandler::getLastInsertedProductId(){
		int product_id = 0;
		SQLite::Statement query(*db, "SELECT id FROM products ORDER BY id DESC LIMIT 1");
		if (query.executeStep())
			product_id = query.getColumn(0);
		return product_id;
	}

	int SQLiteDataHandler::getLastInsertedPropertySetId(){
		int id = 0;
		SQLite::Statement query(*db, "SELECT id FROM property_set ORDER BY id DESC LIMIT 1");
		if (query.executeStep())
			id = query.getColumn(0);
		return id;
	}
}