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
#include "include/IfcParameterValue.h"
#include "include/IfcTextureVertexList.h"

// ENTITY IfcTextureVertexList 
IfcTextureVertexList::IfcTextureVertexList() { m_entity_enum = IFCTEXTUREVERTEXLIST; }
IfcTextureVertexList::IfcTextureVertexList( int id ) { m_id = id; m_entity_enum = IFCTEXTUREVERTEXLIST; }
IfcTextureVertexList::~IfcTextureVertexList() {}
shared_ptr<IfcPPObject> IfcTextureVertexList::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcTextureVertexList> copy_self( new IfcTextureVertexList() );
	copy_self->m_TexCoordsList.resize( m_TexCoordsList.size() );
	for( size_t ii=0; ii<m_TexCoordsList.size(); ++ii )
	{
		std::vector<shared_ptr<IfcParameterValue> >& vec_ii = m_TexCoordsList[ii];
		std::vector<shared_ptr<IfcParameterValue> >& vec_ii_target = copy_self->m_TexCoordsList[ii];
		for( size_t jj=0; jj<vec_ii.size(); ++jj )
		{
			shared_ptr<IfcParameterValue>& item_jj = vec_ii[jj];
			if( item_jj )
			{
				vec_ii_target.push_back( dynamic_pointer_cast<IfcParameterValue>( item_jj->getDeepCopy(options) ) );
			}
		}
	}
	return copy_self;
}
void IfcTextureVertexList::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCTEXTUREVERTEXLIST" << "(";
	writeNumericTypeList2D( stream, m_TexCoordsList );
	stream << ");";
}
void IfcTextureVertexList::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcTextureVertexList::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcTextureVertexList, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readTypeOfRealList2D( args[0], m_TexCoordsList );
}
void IfcTextureVertexList::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPresentationItem::getAttributes( vec_attributes );
}
void IfcTextureVertexList::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcTextureVertexList::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcTextureVertexList::unlinkFromInverseCounterparts()
{
	IfcPresentationItem::unlinkFromInverseCounterparts();
}
