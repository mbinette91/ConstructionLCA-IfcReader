/*
* This file contains the function `handleGeometry` which handles everything related to the generation of Geometry/3D model files.
*/
#include <fstream>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcppgeometry/GeometryConverter.h>
#include "IfcReader.hpp"

void IfcReader::handleGeometry(shared_ptr<IfcPPModel> ifc_model, std::string output_folder)
{
	output_folder = output_folder.erase(output_folder.find_last_not_of("/\\") + 1); // Remove trailing (back)slashes

	shared_ptr<GeometryConverter> geometry_converter(new GeometryConverter(ifc_model));

	geometry_converter->setMessageCallBack(this, &IfcReader::handleMessageCallBack);

	osg::ref_ptr<osg::Switch> model_switch = new osg::Switch();
	geometry_converter->createGeometryOSG(model_switch);

	// contains the VEF graph for each IfcProduct:
	std::map<int, shared_ptr<ProductShapeInputData> >& map_vef_data = geometry_converter->getShapeInputData();

	int count_obj = 0;
	for (auto it = map_vef_data.begin(); it != map_vef_data.end(); ++it)
	{
		int entity_id = it->first; // STEP entity id

		shared_ptr<ProductShapeInputData>& shape_data = it->second;
		shared_ptr<IfcProduct> ifc_product(shape_data->m_ifc_product);

		if (!ifc_product->m_GlobalId || !ifc_product->m_Name)
			continue; //Skip.
		std::wstring wguid = ifc_product->m_GlobalId->m_value;
		std::wstring wname = ifc_product->m_Name->m_value;
		std::string	guid(wguid.begin(), wguid.end());
		std::string	name(wname.begin(), wname.end());

		std::ofstream model_file;
		std::string filename = output_folder + "/obj" + std::to_string(count_obj) + ".json";
		model_file.open(filename);
		count_obj++;
		model_file << "{" << std::endl
			<< "\"vertexPositions\": [" << std::endl;
		int countVertex = 0;
		bool first_point = true;
		// for each IfcProduct, there can be mulitple geometric representation items:
		std::vector<shared_ptr<ItemShapeInputData> >& vec_item_data = shape_data->m_vec_item_data;
		for (size_t i_item = 0; i_item < vec_item_data.size(); ++i_item)
		{
			shared_ptr<ItemShapeInputData>& item_data = vec_item_data[i_item];

			// every item can have several meshsets:
			std::vector<shared_ptr<carve::mesh::MeshSet<3> > >& vec_item_meshsets = item_data->m_meshsets;
			for (size_t i_meshset = 0; i_meshset < vec_item_meshsets.size(); ++i_meshset)
			{
				shared_ptr<carve::mesh::MeshSet<3> >& meshset = vec_item_meshsets[i_meshset];

				// vertices of the meshset:
				std::vector<carve::mesh::Vertex<3> >& vec_vertices = meshset->vertex_storage;

				std::vector<carve::mesh::Mesh<3>* >& vec_meshes = meshset->meshes;
				for (size_t i_mesh = 0; i_mesh < vec_meshes.size(); ++i_mesh)
				{
					carve::mesh::Mesh<3>* mesh = vec_meshes[i_mesh];

					// closed edges of the vef graph:
					std::vector<carve::mesh::Edge<3>* >& vec_closed_edges = mesh->closed_edges;

					// faces:
					std::vector<carve::mesh::Face<3>* >& vec_faces = mesh->faces;
					for (size_t i_face = 0; i_face < vec_faces.size(); ++i_face)
					{
						carve::mesh::Face<3>* face = vec_faces[i_face];

						// iterate through edges:
						carve::mesh::Edge<3>* edge = face->edge;
						do
						{
							if (!first_point) {
								model_file << "," << std::endl;
							}
							else
								first_point = false;

							carve::mesh::Vertex<3>* vertex_begin = edge->v1();
							carve::mesh::Vertex<3>* vertex_end = edge->v2();

							// coordinates of vertex:
							carve::geom::vector<3>& vertex_begin_coords = vertex_begin->v;
							double x = vertex_begin_coords.x;
							double y = vertex_begin_coords.y;
							double z = vertex_begin_coords.z;

							model_file << x << "," << y << "," << z;
							countVertex++;

							edge = edge->next;
						} while (edge != face->edge);
					}
				}
			}
		}
		model_file << std::endl << "]," << std::endl;

		//We should really compute those for real....
		model_file << "\"vertexNormals\": [";
		if (countVertex) {
			model_file << "1,1,1";
			for (int j = 1; j < countVertex; j++)
				model_file << ",1,1,1";
		}
		model_file << "]," << std::endl;

		model_file << std::endl << "\"indices\": [";
		if (countVertex) {
			model_file << "0";
			for (int j = 1; j < countVertex; j++)
				model_file << "," << j;
		}
		model_file << "]" << std::endl << "}";
		model_file.close();
	}

	// tree.json contains information about all the other pieces
	std::ofstream model_file;
	model_file.open(output_folder + "/tree.json");
	model_file << "{\"space\":{\"root\":{\"name\":\"default\",\"i\": [";
	if (count_obj) {
		model_file << "{\"object\": 0,\"mtl\":0}";
		for (int j = 1; j < count_obj; j++)
			model_file << ",{\"object\":" << j << ",\"mtl\":0}";
	}
	model_file << "]},";
	// Meshes
	model_file << "\"meshes\":[";
	if (count_obj) {
		model_file << "{\"ref\": \"obj0.json\"}";
		for (int j = 1; j < count_obj; j++)
			model_file << ",{\"ref\": \"obj" << j << ".json\"}";
	}
	model_file << "],";

	model_file << "\"materials\":[{\"name\":\"red\",\"diffuse\":{\"color\":[0.8,0.8,0.8]},\"specular\":{\"color\":[0.4,0.4,0.4]},\"phong\":64}],"
		<< "\"lights\":["
		<< "{\"color\":[0.5, 0.5, 0.5], \"dir\" : [-0.784465, -0.588348, -0.196116], \"type\" : 1}, "
		<< "{ \"color\":[0.8, 0.8, 0.9], \"dir\" : [0.590796, 0.324938, -0.738495], \"type\" : 1 }, "
		<< "{ \"color\":[0.9, 0.9, 0.9], \"dir\" : [0.00999937, 0.00499969, 0.999938], \"type\" : 1 }],"
		<< "\"view\" : {\"org\":[-2.39854, -2.18169, 1.21867], \"up\" : [-2.1648, -1.98588, 2.02927], \"target\" : [0, 0, 0], \"fov\" : 52.2338}}}";

	model_file.close();
}
