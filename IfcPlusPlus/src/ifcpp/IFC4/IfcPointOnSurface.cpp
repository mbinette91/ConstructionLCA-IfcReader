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
#include "include/IfcPointOnSurface.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"
#include "include/IfcSurface.h"

// ENTITY IfcPointOnSurface 
IfcPointOnSurface::IfcPointOnSurface() { m_entity_enum = IFCPOINTONSURFACE; }
IfcPointOnSurface::IfcPointOnSurface( int id ) { m_id = id; m_entity_enum = IFCPOINTONSURFACE; }
IfcPointOnSurface::~IfcPointOnSurface() {}
shared_ptr<IfcPPObject> IfcPointOnSurface::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPointOnSurface> copy_self( new IfcPointOnSurface() );
	if( m_BasisSurface ) { copy_self->m_BasisSurface = dynamic_pointer_cast<IfcSurface>( m_BasisSurface->getDeepCopy(options) ); }
	if( m_PointParameterU ) { copy_self->m_PointParameterU = dynamic_pointer_cast<IfcParameterValue>( m_PointParameterU->getDeepCopy(options) ); }
	if( m_PointParameterV ) { copy_self->m_PointParameterV = dynamic_pointer_cast<IfcParameterValue>( m_PointParameterV->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPointOnSurface::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPOINTONSURFACE" << "(";
	if( m_BasisSurface ) { stream << "#" << m_BasisSurface->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_PointParameterU ) { m_PointParameterU->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_PointParameterV ) { m_PointParameterV->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcPointOnSurface::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPointOnSurface::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPointOnSurface, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_BasisSurface, map );
	m_PointParameterU = IfcParameterValue::createObjectFromSTEP( args[1] );
	m_PointParameterV = IfcParameterValue::createObjectFromSTEP( args[2] );
}
void IfcPointOnSurface::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPoint::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "BasisSurface", m_BasisSurface ) );
	vec_attributes.push_back( std::make_pair( "PointParameterU", m_PointParameterU ) );
	vec_attributes.push_back( std::make_pair( "PointParameterV", m_PointParameterV ) );
}
void IfcPointOnSurface::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPoint::getAttributesInverse( vec_attributes_inverse );
}
void IfcPointOnSurface::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPoint::setInverseCounterparts( ptr_self_entity );
}
void IfcPointOnSurface::unlinkFromInverseCounterparts()
{
	IfcPoint::unlinkFromInverseCounterparts();
}
