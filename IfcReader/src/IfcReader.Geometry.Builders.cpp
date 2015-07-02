/*
* This file contains the function `handleGeometry` which handles everything related to the generation of Geometry/3D model files.
*/
#include "IfcReader.hpp"

#include <ifcpp/model/IfcPPModel.h>
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
		mesh_ss = new std::stringstream;
		this->path = path.erase(path.find_last_not_of("/\\") + 1); // Remove trailing (back)slashes
	}

	TreeFileBuilder::~TreeFileBuilder()
	{
		delete file;
		delete mesh_ss;
	}

	void TreeFileBuilder::writeTreeFile()
	{ // tree.json contains information about all the other pieces
		file->open(path + "/" + filename);
		*file << "{\"space\":{\"root\":{\"name\":\"default\",\"i\": [";
		if (count_obj) {
			*file << "{\"object\": 0,\"mtl\":0}";
			for (int j = 1; j < count_obj; j++)
				*file << ",{\"object\":" << j << ",\"mtl\":0}";
		}
		*file << "]},";

		*file << "\"meshes\":[" << mesh_ss->str() << "],";

		*file << "\"materials\":[{\"name\":\"red\",\"diffuse\":{\"color\":[0.8,0.8,0.8]},\"specular\":{\"color\":[0.4,0.4,0.4]},\"phong\":64}],"
			<< "\"lights\":["
			<< "{\"color\":[0.5, 0.5, 0.5], \"dir\" : [-0.784465, -0.588348, -0.196116], \"type\" : 1}, "
			<< "{ \"color\":[0.8, 0.8, 0.9], \"dir\" : [0.590796, 0.324938, -0.738495], \"type\" : 1 }, "
			<< "{ \"color\":[0.9, 0.9, 0.9], \"dir\" : [0.00999937, 0.00499969, 0.999938], \"type\" : 1 }],"
			<< "\"view\" : {\"org\":[-2.39854, -2.18169, 1.21867], \"up\" : [-2.1648, -1.98588, 2.02927], \"target\" : [0, 0, 0], \"fov\" : 52.2338}}}";

		file->close();
	}

	void TreeFileBuilder::closeCurrentMeshSheet()
	{
		if (!hasActiveMeshSheet())
			return;

		if (count_files > 1) { // No comma for the first file!
			*mesh_ss << ",";
		}
		*mesh_ss << "{\"ref\": \"" << msb->filename << "\", \"length\": " << msb->count_obj << "}";

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

	void TreeFileBuilder::startNewProduct()
	{
		if (!hasActiveMeshSheet())
		{
			openNewMeshSheet();
		}
		msb->openNewMesh();
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

	void MeshSheetBuilder::openNewMesh()
	{
		if (count_obj > 0) {
			*file << "," << std::endl;
		}
		*file << "{" << std::endl
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

		//We should really compute those for real....
		*file << "\"vertexNormals\": [";
		if (count_vertex) {
			*file << "1,1,1";
			for (int j = 1; j < count_vertex; j++)
				*file << ",1,1,1";
		}
		*file << "]," << std::endl;

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