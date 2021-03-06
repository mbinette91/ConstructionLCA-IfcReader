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
#include "include/IfcBoundedSurface.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcBoundedSurface 
IfcBoundedSurface::IfcBoundedSurface() { m_entity_enum = IFCBOUNDEDSURFACE; }
IfcBoundedSurface::IfcBoundedSurface( int id ) { m_id = id; m_entity_enum = IFCBOUNDEDSURFACE; }
IfcBoundedSurface::~IfcBoundedSurface() {}
shared_ptr<IfcPPObject> IfcBoundedSurface::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBoundedSurface> copy_self( new IfcBoundedSurface() );
	return copy_self;
}
void IfcBoundedSurface::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCBOUNDEDSURFACE" << "(";
	stream << ");";
}
void IfcBoundedSurface::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBoundedSurface::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
}
void IfcBoundedSurface::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcSurface::getAttributes( vec_attributes );
}
void IfcBoundedSurface::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcSurface::getAttributesInverse( vec_attributes_inverse );
}
void IfcBoundedSurface::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcSurface::setInverseCounterparts( ptr_self_entity );
}
void IfcBoundedSurface::unlinkFromInverseCounterparts()
{
	IfcSurface::unlinkFromInverseCounterparts();
}
