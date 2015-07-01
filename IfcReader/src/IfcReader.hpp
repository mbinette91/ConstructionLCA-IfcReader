#pragma once

#include <string>
#include <xstring>
#include <ifcpp/model/shared_ptr.h>
#include <ifcpp/model/StatusCallback.h>
#include <ifcpp/model/IfcPPModel.h>

class IfcReader
{
public:
	long project_id = 0;
	static void handleMessageCallBack(void* obj_ptr, shared_ptr<StatusCallback::Message> m);
	shared_ptr<IfcPPModel> loadModelFromFile(std::wstring file_path);
	void handleGeometry(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path);
	void handleData(shared_ptr<IfcPPModel> ifc_model, std::string file_path);
};