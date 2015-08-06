/*
* This file contains the function `handleGeometry` which handles everything related to the generation of Geometry/3D model files.
*/
#include "IfcReader.hpp"

#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <fstream>
#include <sstream>

namespace IfcReader
{
	TreeFileBuilder::TreeFileBuilder(std::string path, std::string filename, long max_size_bytes)
		: filename(filename)
		, count_obj(0)
		, count_files(0)
		, max_size_bytes(max_size_bytes)
		, msb(NULL)
	{
		file = new std::ofstream;
		obj_ss = new std::stringstream;
		mesh_ss = new std::stringstream;
		this->path = path.erase(path.find_last_not_of("/\\") + 1); // Remove trailing (back)slashes
	}

	TreeFileBuilder::~TreeFileBuilder()
	{
		delete file;
		delete obj_ss;
		delete mesh_ss;
	}

	void TreeFileBuilder::writeTreeFile()
	{ // tree.json contains information about all the other pieces
		file->open(path + "/" + filename);
		*file << "{\"objects\": [" << obj_ss->str() << "],";
		*file << "\"meshes\":[" << mesh_ss->str() << "],";
		*file << "\"materials\":\"IFC\" }";
		file->close();
	}

	void TreeFileBuilder::closeCurrentMeshSheet()
	{
		if (!hasActiveMeshSheet())
			return;

		if (count_files > 1) { // No comma for the first file!
			*mesh_ss << ",";
		}
		*mesh_ss << "{\"ref\": \"" << msb->filename << "\"}";

		delete msb;
		msb = NULL;
	}

	void TreeFileBuilder::openNewMeshSheet()
	{
		if (hasActiveMeshSheet())
			throw "ERROR (): Cannot open new MeshSheet - current one hasn't been closed!";

		msb = new MeshSheetBuilder(path, "obj" + std::to_string(count_files) + ".json");
		count_files++;
	}

	bool TreeFileBuilder::hasActiveMeshSheet()
	{
		return (msb != NULL);
	}

	void TreeFileBuilder::startNewProduct(shared_ptr<IfcProduct> product)
	{
		if (count_obj > 0) { // No comma for the first obj!
			*obj_ss << ",";
		}
		*obj_ss << "{\"guid\": \"" << w2str(product->m_GlobalId->m_value) << "\"}";

		if (!hasActiveMeshSheet())
		{
			openNewMeshSheet();
		}
		msb->openNewMesh(product);
	}

	void TreeFileBuilder::addVertex(double x, double y, double z)
	{
		msb->addVertex(x, y, z);
	}

	void TreeFileBuilder::closeCurrentProduct()
	{
		msb->closeCurrentMesh();
		count_obj++;

		if (msb->file->tellp() >= max_size_bytes)
		{
			closeCurrentMeshSheet();
		}
	}

	MeshSheetBuilder::MeshSheetBuilder(std::string path, std::string filename)
		: path(path)
		, filename(filename)
		, count_obj(0)
		, count_vertex(0)
	{
		file = new std::ofstream;
		file->open(path + "/" + filename);
		*file << "[" << std::endl;
	}

	MeshSheetBuilder::~MeshSheetBuilder()
	{
		*file << std::endl << "]";
		file->close();
		file->clear();
		delete file;
	}

	void MeshSheetBuilder::openNewMesh(shared_ptr<IfcProduct> product)
	{
		if (count_obj > 0) {
			*file << "," << std::endl;
		}
		*file << "{" << std::endl
			<< "\"guid\": \"" << w2str(product->m_GlobalId->m_value) << "\"," << std::endl
			<< "\"vertexPositions\": [" << std::endl;
		int countVertex = 0;
		bool first_point = true;
	}

	void MeshSheetBuilder::addVertex(double x, double y, double z)
	{
		if (count_vertex > 0) {
			*file << "," << std::endl;
		}
		*file << x << "," << y << "," << z;
		count_vertex++;
	}

	void MeshSheetBuilder::closeCurrentMesh()
	{
		*file << std::endl << "]," << std::endl;

		// For now, let's not reuse the same vertex.
		*file << std::endl << "\"indices\": [";
		if (count_vertex) {
			*file << "0";
			for (int j = 1; j < count_vertex; j++)
				*file << "," << j;
		}
		*file << "]" << std::endl << "}";
		count_obj++;
		count_vertex = 0;
	}
}