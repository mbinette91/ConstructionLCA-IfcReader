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
#include "include/IfcBoundedCurve.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcBoundedCurve 
IfcBoundedCurve::IfcBoundedCurve() { m_entity_enum = IFCBOUNDEDCURVE; }
IfcBoundedCurve::IfcBoundedCurve( int id ) { m_id = id; m_entity_enum = IFCBOUNDEDCURVE; }
IfcBoundedCurve::~IfcBoundedCurve() {}
shared_ptr<IfcPPObject> IfcBoundedCurve::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBoundedCurve> copy_self( new IfcBoundedCurve() );
	return copy_self;
}
void IfcBoundedCurve::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCBOUNDEDCURVE" << "(";
	stream << ");";
}
void IfcBoundedCurve::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBoundedCurve::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
}
void IfcBoundedCurve::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcCurve::getAttributes( vec_attributes );
}
void IfcBoundedCurve::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcCurve::getAttributesInverse( vec_attributes_inverse );
}
void IfcBoundedCurve::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcCurve::setInverseCounterparts( ptr_self_entity );
}
void IfcBoundedCurve::unlinkFromInverseCounterparts()
{
	IfcCurve::unlinkFromInverseCounterparts();
}
