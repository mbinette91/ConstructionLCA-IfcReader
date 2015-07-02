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

	void HandleProduct(DatabaseConfig dbc, shared_ptr<IfcProduct> ifc_product){
		std::wstring wguid = ifc_product->m_GlobalId->m_value;
		std::wstring wname = ifc_product->m_Name->m_value;
		std::wstring wdescription;
		if (ifc_product->m_Description)
			wdescription = ifc_product->m_Description->m_value;
		std::string	guid(wguid.begin(), wguid.end());
		std::string	name(wname.begin(), wname.end());
		std::string	description(wdescription.begin(), wdescription.end());

		SQLite::Statement   query(*dbc.db, "INSERT INTO products VALUES(NULL, ?, ?, ?, ?)");
		query.bind(1, dbc.ifc_reader->project_id);
		query.bind(2, guid);
		query.bind(3, name);
		query.bind(4, description);

		int nb = query.exec();
		if (nb != 0 && nb != 1) // TO-DO: Not sure why valid INSERTs return 1 (SQLITE_ERROR)... ?!
		{
			std::cout << "ERROR (IfcReader::handleDataProduct): " << query.getQuery() << " returned " << nb << "(" << query.errmsg() << ")" << std::endl;
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
}

namespace IfcReader
{
	void IfcReader::handleData(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path){
		const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_entities = ifc_model->getMapIfcEntities();
		try
		{
			SQLite::Database db(sqlite_db_path, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
			SQLite::Transaction transaction(db);

			db.exec("CREATE TABLE IF NOT EXISTS products(id INTEGER PRIMARY KEY, project_id INTEGER, GUID TEXT, name TEXT, description TEXT)");

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