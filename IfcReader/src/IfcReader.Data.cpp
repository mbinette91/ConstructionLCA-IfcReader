/*
* This file contains the function `handleData` which handles everything related to the persistance of useful information for later LCA computing.
* It is expected this is the module that is going to change the most often.
*/
#include "IfcReader.hpp"

#include <iostream>
#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include "IfcReader.Data.Handler.SQLite.hpp"

namespace IfcReader
{
	void IfcReader::handleData(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path){
		try
		{
			DataHandler *handler = new SQLiteDataHandler(sqlite_db_path);
			handler->setProjectId(this->project_id);

			handler->initialize();

			handler->handleModel(ifc_model);

			handler->close();
			delete handler;
		}
		catch (std::exception& e)
		{
			std::wcout << "ERROR (IfcReader::handleData): " << e.what() << std::endl;
		}
	};
};