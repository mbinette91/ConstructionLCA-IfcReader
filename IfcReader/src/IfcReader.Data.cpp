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
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcpp/IFC4/include/IfcText.h>
#include <ifcpp/IFC4/include/IfcRelAssociates.h>
#include <ifcpp/IFC4/include/IfcRelAssociatesMaterial.h>
#include <ifcpp/IFC4/include/IfcMaterialSelect.h>
#include <ifcpp/IFC4/include/IfcMaterial.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSetUsage.h>
#include <ifcpp/IFC4/include/IfcMaterialLayerSet.h>
#include <ifcpp/IFC4/include/IfcMaterialLayer.h>
#include <ifcpp/IFC4/include/IfcNonNegativeLengthMeasure.h>

namespace 
{ //Anonymous namespace. Thread safe.
	class DatabaseConfig {
	public:
		IfcReader::IfcReader* ifc_reader;
		SQLite::Database *db;
		DatabaseConfig(IfcReader::IfcReader* ifc_reader, SQLite::Database *db)
		{
			this->ifc_reader = ifc_reader;
			this->db = db;
		};
	};

	void HandleMaterial(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id);
	void InsertMaterial(DatabaseConfig dbc, int product_id, std::string name, double thickness, std::string layer_name);
	int GetLastInsertedProductId(DatabaseConfig dbc);

	void HandleProduct(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product){
		std::wstring wguid = ifc_product->m_GlobalId->m_value;
		std::wstring wname = ifc_product->m_Name->m_value;
		std::wstring wdescription;
		if (ifc_product->m_Description)
			wdescription = ifc_product->m_Description->m_value;
		std::string	guid(wguid.begin(), wguid.end());
		std::string	name(wname.begin(), wname.end());
		std::string	description(wdescription.begin(), wdescription.end());

		SQLite::Statement query(*dbc.db, "INSERT INTO products VALUES(NULL, ?, ?, ?, ?, ?)");
		query.bind(1, dbc.ifc_reader->project_id);
		query.bind(2, guid);
		query.bind(3, name);
		query.bind(4, description);
		query.bind(5, ifc_product->className());

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::HandleProduct): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;

		int product_id = GetLastInsertedProductId(dbc);

		if (product_id != 0)
		{
			HandleMaterial(dbc, ifc_product, product_id);
		}

		/*// also inverse attributes can be accessed:
		std::vector<weak_ptr<IfcRelAssigns> >& vec_has_assignments = ifc_product->m_HasAssignments_inverse;
		std::vector<weak_ptr<IfcRelNests> >& vec_nests = ifc_product->m_Nests_inverse;
		std::vector<weak_ptr<IfcRelNests> >& vec_is_nested_by = ifc_product->m_IsNestedBy_inverse;
		std::vector<weak_ptr<IfcRelDeclares> >& vec_has_context = ifc_product->m_HasContext_inverse;
		std::vector<weak_ptr<IfcRelAggregates> >& vec_is_decomposed = ifc_product->m_IsDecomposedBy_inverse;
		std::vector<weak_ptr<IfcRelAggregates> >& vec_decomposes = ifc_product->m_Decomposes_inverse;
		std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations = ifc_product->m_HasAssociations_inverse;
		//*/
	}

	/* Example of an IFC material association:
		#606= IFCMATERIAL('Leichtbeton');
		#756= IFCMATERIALLAYER(#606,0.3,.U.);
		#758= IFCMATERIALLAYERSET((#756),'Leichtbeton 300');
		#9791= IFCMATERIALLAYERSETUSAGE(#758,.AXIS2.,.NEGATIVE.,0.);
		#9880= IFCRELASSOCIATESMATERIAL('0SGYIDeQf6d84TJ9vXtUZL',#13,$,$,(#9806),#9791);
		#9806= IFCWALLSTANDARDCASE('16DNNqzfP2thtfaOflvsKA',#13,'Wand-Ext-ERDG-4',$,$,#9803,#9876,'A6C3DE63-3731-4F6A-94-7E-DE8A8295779F');
	*/
	void HandleMaterial(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product, int product_id){
		std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations = ifc_product->m_HasAssociations_inverse;
		if (vec_has_associations.size() > 0){
			std::vector<weak_ptr<IfcRelAssociates> >::iterator it;
			for (it = vec_has_associations.begin(); it != vec_has_associations.end(); ++it)
			{
				shared_ptr<IfcRelAssociates> rel(*it);
				if (rel->className() == "IfcRelAssociatesMaterial"){
					shared_ptr<IfcRelAssociatesMaterial> rel_mat = dynamic_pointer_cast<IfcRelAssociatesMaterial>(rel);
					if (rel_mat->m_RelatingMaterial->className() == "IfcMaterial")
					{
						shared_ptr<IfcMaterial> mat = dynamic_pointer_cast<IfcMaterial>(rel_mat->m_RelatingMaterial);
						std::string name = mat->m_Name ? IfcReader::w2str(mat->m_Name->m_value) : "";
						InsertMaterial(dbc, product_id, name, 0, "");
					}
					else if (rel_mat->m_RelatingMaterial->className() == "IfcMaterialLayerSetUsage")
					{
						shared_ptr<IfcMaterialLayerSetUsage> matlsu = dynamic_pointer_cast<IfcMaterialLayerSetUsage>(rel_mat->m_RelatingMaterial);
						shared_ptr<IfcMaterialLayerSet> matls = dynamic_pointer_cast<IfcMaterialLayerSet>(matlsu->m_ForLayerSet);
						std::string layer_name = matls->m_LayerSetName ? IfcReader::w2str(matls->m_LayerSetName->m_value) : "";
						std::vector<shared_ptr<IfcMaterialLayer> >::iterator it_mat;
						for (it_mat = matls->m_MaterialLayers.begin(); it_mat != matls->m_MaterialLayers.end(); ++it_mat)
						{
							shared_ptr<IfcMaterialLayer> mat(*it_mat);
							if (rel->className() == "IfcRelAssociatesMaterial"){
								std::string name = mat->m_Material && mat->m_Material->m_Name ? IfcReader::w2str(mat->m_Material->m_Name->m_value) : "";
								double thickness = mat->m_LayerThickness ? mat->m_LayerThickness->m_value : 0;
								InsertMaterial(dbc, product_id, name, thickness, layer_name);
							}
						}
					}
				}
			}
		}
	}

	void InsertMaterial(DatabaseConfig dbc, int product_id, std::string name, double thickness, std::string layer_name){
		SQLite::Statement query(*dbc.db, "INSERT INTO materials VALUES(NULL, ?, ?, ?, ?)");
		query.bind(1, product_id);
		query.bind(2, name);
		query.bind(3, thickness);
		query.bind(4, layer_name);

		int nb = query.exec();
		if (nb != 1) //If this did not insert 1 row, something went wrong..!
			std::cout << "ERROR ([IfcReader.Data.cpp]::InsertMaterial): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
	}

	int GetLastInsertedProductId(DatabaseConfig dbc){
		int product_id = 0;
		SQLite::Statement query(*dbc.db, "SELECT id FROM products ORDER BY id DESC LIMIT 1");
		if (query.executeStep())
			product_id = query.getColumn(0);
		return product_id;
	}
}

namespace IfcReader
{
	void IfcReader::handleData(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path){
		const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_entities = ifc_model->getMapIfcEntities();
		try
		{
			SQLite::Database db(sqlite_db_path, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
			SQLite::Transaction transaction(db);

			db.exec("CREATE TABLE IF NOT EXISTS products(id INTEGER PRIMARY KEY, project_id INTEGER, GUID TEXT, name TEXT, description TEXT, class_name TEXT)");
			db.exec("CREATE TABLE IF NOT EXISTS materials(id INTEGER PRIMARY KEY, product_id INTEGER, name TEXT, thickness REAL, layer_name TEXT)");

			DatabaseConfig dbc(this, &db);
			for (auto it = map_ifc_entities.begin(); it != map_ifc_entities.end(); ++it)
			{
				int entity_id = it->first;
				const shared_ptr<IfcPPEntity>& ifcpp_entity = it->second;
				shared_ptr<IfcProduct> ifc_product = dynamic_pointer_cast<IfcProduct>(ifcpp_entity);
				if (ifc_product)
				{
					if (ifc_product->m_GlobalId && ifc_product->m_Name)
					{
						HandleProduct(dbc, ifc_product); //TO-DO: Should this be in the main `if(ifc_product)` block ?
					}
				}
			}

			transaction.commit(); // Don't forget to commit !
		}
		catch (std::exception& e)
		{
			std::wcout << "ERROR (IfcReader::handleData): " << e.what() << std::endl;
		}

	};
};