/*
* Written by: Mathieu Binette
*/
#include <time.h>
#include <iostream>
#include "IfcReader.hpp"

int main(int argc, char *argv[])
{
	std::wstring file_path;

	if (argc != 6)
	{
		std::wcout << "Usage: " << argv[0] << " IFC_PATH GEOMETRY_OUTPUT_FOLDER SQLITE_DB_PATH MAX_SIZE_BYTES PROJECT_ID" << std::endl;
		std::wcout << "\tIFC_PATH : Must exist." << std::endl;
		std::wcout << "\tGEOMETRY_OUTPUT_FOLDER : Folder has to exist." << std::endl;
		std::wcout << "\tSQLITE_DB_PATH : Will be created if it doesn't exist." << std::endl;
		return -1;
	}

	std::string argv1 = argv[1];
	file_path.assign(argv1.begin(), argv1.end());

	time_t time_start;
	shared_ptr<IfcReader::IfcReader> ifc_reader(new IfcReader::IfcReader());
	ifc_reader->project_id = atoi(argv[5]);
	std::wcout << "Preparing to parse " << file_path << "." << std::endl;

	time(&time_start);
	shared_ptr<IfcPPModel> ifc_model = ifc_reader->loadModelFromFile(file_path);
	std::wcout << "Time to load model: " << difftime(time(NULL), time_start) << "s" << std::endl;

	time(&time_start);
	ifc_reader->handleGeometry(ifc_model, argv[2], atoi(argv[4]));
	std::wcout << "Time to handle geometry: " << difftime(time(NULL), time_start) << "s" << std::endl;

	time(&time_start);
	ifc_reader->handleData(ifc_model, argv[3]);
	std::wcout << "Time to handle data: " << difftime(time(NULL), time_start) << "s" << std::endl;

	return 0;
}
