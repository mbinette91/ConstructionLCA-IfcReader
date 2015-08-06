#pragma once
#include <string>
#include <iosfwd>
#include <ifcpp/model/shared_ptr.h>
#include <ifcpp/model/StatusCallback.h>
class IfcPPModel;
class IfcProduct;
class IfcValue;

namespace IfcReader
{
	std::string w2str(std::wstring str); // Defined in IfcReader.utils.cpp
	std::wstring IfcValue2wstr(shared_ptr<IfcValue> ifc_value); // Defined in IfcReader.utils.cpp

	class IfcReader
	{
	public:
		long project_id = 0;
		static void handleMessageCallBack(void* obj_ptr, shared_ptr<StatusCallback::Message> m);
		shared_ptr<IfcPPModel> loadModelFromFile(std::wstring file_path);
		void handleGeometry(shared_ptr<IfcPPModel> ifc_model, std::string sqlite_db_path, long max_size_bytes);
		void handleData(shared_ptr<IfcPPModel> ifc_model, std::string file_path);
	};

	class MeshSheetBuilder;
	class TreeFileBuilder
	{
	public:
		std::ofstream* file;
		std::stringstream* obj_ss;
		std::stringstream* mesh_ss;
		int count_obj;
		int count_files;
		long max_size_bytes;
		MeshSheetBuilder* msb;
		std::string path;
		std::string filename;

		TreeFileBuilder(std::string path, std::string filename, long max_size_bytes);
		~TreeFileBuilder();
		void writeTreeFile();
		void closeCurrentMeshSheet();
		void openNewMeshSheet();
		bool hasActiveMeshSheet();
		void startNewProduct(shared_ptr<IfcProduct> product);
		void addVertex(double x, double y, double z);
		void closeCurrentProduct();
	};

	class MeshSheetBuilder
	{
		friend class TreeFileBuilder;
	private:
		std::ofstream* file;
		int count_obj;
		int count_vertex;
		std::string path;
		std::string filename;

		MeshSheetBuilder(std::string path, std::string filename);
		~MeshSheetBuilder();
		void openNewMesh(shared_ptr<IfcProduct> product);
		void addVertex(double x, double y, double z);
		void closeCurrentMesh();
	};
}