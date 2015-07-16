/*
* This file contains generic IfcReader functions such as the function: 
*	`handleMessageCallBack`:	Handles (error/warning/other) messages from the IfcPPReader and the GeometryConverter.
*	`loadModelFromFile`:		Loads an IfcPPModel from the file_path passed as parameter.
* Those functions will likely not change often.
*/
#include "IfcReader.hpp"

#include <iostream>
#include <ifcpp/reader/IfcPPReaderSTEP.h>
#include <ifcpp/model/IfcPPModel.h>

namespace IfcReader
{
	std::string w2str(std::wstring wstr)
	{
		return std::string(wstr.begin(), wstr.end());
	}

	void IfcReader::handleMessageCallBack(void* obj_ptr, shared_ptr<StatusCallback::Message> m)
	{
		if (m && m->m_message_type != StatusCallback::MESSAGE_TYPE_PROGRESS_VALUE && m->m_message_type != StatusCallback::MESSAGE_TYPE_PROGRESS_TEXT)
		{
			// std::wcout << m->m_message_text << std::endl;
		}
	}

	shared_ptr<IfcPPModel> IfcReader::loadModelFromFile(std::wstring file_path)
	{
		shared_ptr<IfcPPModel> ifc_model(new IfcPPModel());
		shared_ptr<IfcPPReaderSTEP> reader(new IfcPPReaderSTEP());

		reader->setMessageCallBack(this, &IfcReader::handleMessageCallBack);
	
		reader->loadModelFromFile(file_path, ifc_model);

		return ifc_model;
	}
};