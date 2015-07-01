/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com  - Copyright (C) 2011 Fabian Gerold
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/

#include <iostream>

#include <ifcpp/model/IfcPPModel.h>
#include <ifcpp/reader/IfcPPReaderSTEP.h>
#include <ifcpp/IFC4/include/IfcProduct.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcpp/IFC4/include/IfcText.h>

int main(int argc, char *argv[])
{
	std::wstring file_path( L"ExampleModel.ifc" );

	if( argc > 1 )
	{
		std::string arg1 = argv[1];
		if( arg1.length() > 4 )
		{
			std::string ext = arg1.substr( arg1.find_last_of( "." ) + 1 );
			if( boost::iequals( ext, "ifc" ) )
			{
				file_path.assign( arg1.begin(), arg1.end() );
			}
		}
	}

	shared_ptr<IfcPPModel> ifc_model( new IfcPPModel() );
	shared_ptr<IfcPPReaderSTEP> reader( new IfcPPReaderSTEP() );
	reader->loadModelFromFile( file_path, ifc_model );

	const boost::unordered_map<int, shared_ptr<IfcPPEntity> >& map_ifc_entities = ifc_model->getMapIfcEntities();
	for( auto it = map_ifc_entities.begin(); it != map_ifc_entities.end(); ++it )
	{
		int entity_id = it->first;
		const shared_ptr<IfcPPEntity>& ifcpp_entity = it->second;
		shared_ptr<IfcProduct> ifc_product = dynamic_pointer_cast<IfcProduct>( ifcpp_entity );
		if( ifc_product )
		{
			// entity is an IfcProduct, we can access its attributes now:
			if( ifc_product->m_Name )
			{
				std::wcout << "name: " << ifc_product->m_Name->m_value;
			}

			if( ifc_product->m_Description )
			{
				std::wcout << ", description: " << ifc_product->m_Description->m_value;
			}
			
			if( ifc_product->m_GlobalId )
			{
				std::wcout << ", Globally Unique ID: " << ifc_product->m_GlobalId->m_value << std::endl;
			}

			// also inverse attributes can be accessed:
			std::vector<weak_ptr<IfcRelAssigns> >& vec_has_assignments		= ifc_product->m_HasAssignments_inverse;
			std::vector<weak_ptr<IfcRelNests> >& vec_nests					= ifc_product->m_Nests_inverse;
			std::vector<weak_ptr<IfcRelNests> >& vec_is_nested_by			= ifc_product->m_IsNestedBy_inverse;
			std::vector<weak_ptr<IfcRelDeclares> >& vec_has_context			= ifc_product->m_HasContext_inverse;
			std::vector<weak_ptr<IfcRelAggregates> >& vec_is_decomposed		= ifc_product->m_IsDecomposedBy_inverse;
			std::vector<weak_ptr<IfcRelAggregates> >& vec_decomposes		= ifc_product->m_Decomposes_inverse;
			std::vector<weak_ptr<IfcRelAssociates> >& vec_has_associations	= ifc_product->m_HasAssociations_inverse;

		}
	}

	return 0;
}
