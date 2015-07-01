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
#include "include/IfcAxis2Placement2D.h"
#include "include/IfcCartesianPoint.h"
#include "include/IfcDirection.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcAxis2Placement2D 
IfcAxis2Placement2D::IfcAxis2Placement2D() { m_entity_enum = IFCAXIS2PLACEMENT2D; }
IfcAxis2Placement2D::IfcAxis2Placement2D( int id ) { m_id = id; m_entity_enum = IFCAXIS2PLACEMENT2D; }
IfcAxis2Placement2D::~IfcAxis2Placement2D() {}
shared_ptr<IfcPPObject> IfcAxis2Placement2D::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcAxis2Placement2D> copy_self( new IfcAxis2Placement2D() );
	if( m_Location ) { copy_self->m_Location = dynamic_pointer_cast<IfcCartesianPoint>( m_Location->getDeepCopy(options) ); }
	if( m_RefDirection ) { copy_self->m_RefDirection = dynamic_pointer_cast<IfcDirection>( m_RefDirection->getDeepCopy(options) ); }
	return copy_self;
}
void IfcAxis2Placement2D::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCAXIS2PLACEMENT2D" << "(";
	if( m_Location ) { stream << "#" << m_Location->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_RefDirection ) { stream << "#" << m_RefDirection->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcAxis2Placement2D::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcAxis2Placement2D::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcAxis2Placement2D, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_Location, map );
	readEntityReference( args[1], m_RefDirection, map );
}
void IfcAxis2Placement2D::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPlacement::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RefDirection", m_RefDirection ) );
}
void IfcAxis2Placement2D::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPlacement::getAttributesInverse( vec_attributes_inverse );
}
void IfcAxis2Placement2D::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPlacement::setInverseCounterparts( ptr_self_entity );
}
void IfcAxis2Placement2D::unlinkFromInverseCounterparts()
{
	IfcPlacement::unlinkFromInverseCounterparts();
}
