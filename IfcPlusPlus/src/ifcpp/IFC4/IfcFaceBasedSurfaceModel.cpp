/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
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
#include <sstream>
#include <limits>

#include "ifcpp/model/IfcPPException.h"
#include "ifcpp/model/IfcPPAttributeObject.h"
#include "ifcpp/model/IfcPPGuid.h"
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterUtil.h"
#include "ifcpp/IfcPPEntityEnums.h"
#include "include/IfcConnectedFaceSet.h"
#include "include/IfcFaceBasedSurfaceModel.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcFaceBasedSurfaceModel 
IfcFaceBasedSurfaceModel::IfcFaceBasedSurfaceModel() { m_entity_enum = IFCFACEBASEDSURFACEMODEL; }
IfcFaceBasedSurfaceModel::IfcFaceBasedSurfaceModel( int id ) { m_id = id; m_entity_enum = IFCFACEBASEDSURFACEMODEL; }
IfcFaceBasedSurfaceModel::~IfcFaceBasedSurfaceModel() {}
shared_ptr<IfcPPObject> IfcFaceBasedSurfaceModel::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcFaceBasedSurfaceModel> copy_self( new IfcFaceBasedSurfaceModel() );
	for( size_t ii=0; ii<m_FbsmFaces.size(); ++ii )
	{
		auto item_ii = m_FbsmFaces[ii];
		if( item_ii )
		{
			copy_self->m_FbsmFaces.push_back( dynamic_pointer_cast<IfcConnectedFaceSet>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcFaceBasedSurfaceModel::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCFACEBASEDSURFACEMODEL" << "(";
	writeEntityList( stream, m_FbsmFaces );
	stream << ");";
}
void IfcFaceBasedSurfaceModel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcFaceBasedSurfaceModel::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcFaceBasedSurfaceModel, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReferenceList( args[0], m_FbsmFaces, map );
}
void IfcFaceBasedSurfaceModel::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricRepresentationItem::getAttributes( vec_attributes );
	if( m_FbsmFaces.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> FbsmFaces_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_FbsmFaces.begin(), m_FbsmFaces.end(), std::back_inserter( FbsmFaces_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "FbsmFaces", FbsmFaces_vec_object ) );
	}
}
void IfcFaceBasedSurfaceModel::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcFaceBasedSurfaceModel::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcFaceBasedSurfaceModel::unlinkFromInverseCounterparts()
{
	IfcGeometricRepresentationItem::unlinkFromInverseCounterparts();
}
