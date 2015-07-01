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
#include "include/IfcCurve.h"
#include "include/IfcPcurve.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"
#include "include/IfcSurface.h"

// ENTITY IfcPcurve 
IfcPcurve::IfcPcurve() { m_entity_enum = IFCPCURVE; }
IfcPcurve::IfcPcurve( int id ) { m_id = id; m_entity_enum = IFCPCURVE; }
IfcPcurve::~IfcPcurve() {}
shared_ptr<IfcPPObject> IfcPcurve::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPcurve> copy_self( new IfcPcurve() );
	if( m_BasisSurface ) { copy_self->m_BasisSurface = dynamic_pointer_cast<IfcSurface>( m_BasisSurface->getDeepCopy(options) ); }
	if( m_ReferenceCurve ) { copy_self->m_ReferenceCurve = dynamic_pointer_cast<IfcCurve>( m_ReferenceCurve->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPcurve::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPCURVE" << "(";
	if( m_BasisSurface ) { stream << "#" << m_BasisSurface->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_ReferenceCurve ) { stream << "#" << m_ReferenceCurve->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcPcurve::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPcurve::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPcurve, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_BasisSurface, map );
	readEntityReference( args[1], m_ReferenceCurve, map );
}
void IfcPcurve::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcCurve::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "BasisSurface", m_BasisSurface ) );
	vec_attributes.push_back( std::make_pair( "ReferenceCurve", m_ReferenceCurve ) );
}
void IfcPcurve::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcCurve::getAttributesInverse( vec_attributes_inverse );
}
void IfcPcurve::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcCurve::setInverseCounterparts( ptr_self_entity );
}
void IfcPcurve::unlinkFromInverseCounterparts()
{
	IfcCurve::unlinkFromInverseCounterparts();
}
