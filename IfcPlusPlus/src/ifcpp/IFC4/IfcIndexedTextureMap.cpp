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
#include "include/IfcIndexedTextureMap.h"
#include "include/IfcSurfaceTexture.h"
#include "include/IfcTessellatedFaceSet.h"
#include "include/IfcTextureVertexList.h"

// ENTITY IfcIndexedTextureMap 
IfcIndexedTextureMap::IfcIndexedTextureMap() { m_entity_enum = IFCINDEXEDTEXTUREMAP; }
IfcIndexedTextureMap::IfcIndexedTextureMap( int id ) { m_id = id; m_entity_enum = IFCINDEXEDTEXTUREMAP; }
IfcIndexedTextureMap::~IfcIndexedTextureMap() {}
shared_ptr<IfcPPObject> IfcIndexedTextureMap::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcIndexedTextureMap> copy_self( new IfcIndexedTextureMap() );
	for( size_t ii=0; ii<m_Maps.size(); ++ii )
	{
		auto item_ii = m_Maps[ii];
		if( item_ii )
		{
			copy_self->m_Maps.push_back( dynamic_pointer_cast<IfcSurfaceTexture>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_MappedTo ) { copy_self->m_MappedTo = dynamic_pointer_cast<IfcTessellatedFaceSet>( m_MappedTo->getDeepCopy(options) ); }
	if( m_TexCoords ) { copy_self->m_TexCoords = dynamic_pointer_cast<IfcTextureVertexList>( m_TexCoords->getDeepCopy(options) ); }
	return copy_self;
}
void IfcIndexedTextureMap::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCINDEXEDTEXTUREMAP" << "(";
	writeEntityList( stream, m_Maps );
	stream << ",";
	if( m_MappedTo ) { stream << "#" << m_MappedTo->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_TexCoords ) { stream << "#" << m_TexCoords->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcIndexedTextureMap::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcIndexedTextureMap::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcIndexedTextureMap, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReferenceList( args[0], m_Maps, map );
	readEntityReference( args[1], m_MappedTo, map );
	readEntityReference( args[2], m_TexCoords, map );
}
void IfcIndexedTextureMap::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcTextureCoordinate::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "MappedTo", m_MappedTo ) );
	vec_attributes.push_back( std::make_pair( "TexCoords", m_TexCoords ) );
}
void IfcIndexedTextureMap::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcTextureCoordinate::getAttributesInverse( vec_attributes_inverse );
}
void IfcIndexedTextureMap::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcTextureCoordinate::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcIndexedTextureMap> ptr_self = dynamic_pointer_cast<IfcIndexedTextureMap>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcIndexedTextureMap::setInverseCounterparts: type mismatch" ); }
	if( m_MappedTo )
	{
		m_MappedTo->m_HasTextures_inverse.push_back( ptr_self );
	}
}
void IfcIndexedTextureMap::unlinkFromInverseCounterparts()
{
	IfcTextureCoordinate::unlinkFromInverseCounterparts();
	if( m_MappedTo )
	{
		std::vector<weak_ptr<IfcIndexedTextureMap> >& HasTextures_inverse = m_MappedTo->m_HasTextures_inverse;
		for( auto it_HasTextures_inverse = HasTextures_inverse.begin(); it_HasTextures_inverse != HasTextures_inverse.end(); )
		{
			shared_ptr<IfcIndexedTextureMap> self_candidate( *it_HasTextures_inverse );
			if( self_candidate.get() == this )
			{
				it_HasTextures_inverse= HasTextures_inverse.erase( it_HasTextures_inverse );
			}
			else
			{
				++it_HasTextures_inverse;
			}
		}
	}
}
