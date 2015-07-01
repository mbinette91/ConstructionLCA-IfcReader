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
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"
#include "include/IfcVertex.h"
#include "include/IfcVertexLoop.h"

// ENTITY IfcVertexLoop 
IfcVertexLoop::IfcVertexLoop() { m_entity_enum = IFCVERTEXLOOP; }
IfcVertexLoop::IfcVertexLoop( int id ) { m_id = id; m_entity_enum = IFCVERTEXLOOP; }
IfcVertexLoop::~IfcVertexLoop() {}
shared_ptr<IfcPPObject> IfcVertexLoop::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcVertexLoop> copy_self( new IfcVertexLoop() );
	if( m_LoopVertex ) { copy_self->m_LoopVertex = dynamic_pointer_cast<IfcVertex>( m_LoopVertex->getDeepCopy(options) ); }
	return copy_self;
}
void IfcVertexLoop::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCVERTEXLOOP" << "(";
	if( m_LoopVertex ) { stream << "#" << m_LoopVertex->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcVertexLoop::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcVertexLoop::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcVertexLoop, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_LoopVertex, map );
}
void IfcVertexLoop::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcLoop::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "LoopVertex", m_LoopVertex ) );
}
void IfcVertexLoop::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcLoop::getAttributesInverse( vec_attributes_inverse );
}
void IfcVertexLoop::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcLoop::setInverseCounterparts( ptr_self_entity );
}
void IfcVertexLoop::unlinkFromInverseCounterparts()
{
	IfcLoop::unlinkFromInverseCounterparts();
}
