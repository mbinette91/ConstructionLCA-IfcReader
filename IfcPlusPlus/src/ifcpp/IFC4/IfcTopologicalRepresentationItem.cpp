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
#include "include/IfcTopologicalRepresentationItem.h"

// ENTITY IfcTopologicalRepresentationItem 
IfcTopologicalRepresentationItem::IfcTopologicalRepresentationItem() { m_entity_enum = IFCTOPOLOGICALREPRESENTATIONITEM; }
IfcTopologicalRepresentationItem::IfcTopologicalRepresentationItem( int id ) { m_id = id; m_entity_enum = IFCTOPOLOGICALREPRESENTATIONITEM; }
IfcTopologicalRepresentationItem::~IfcTopologicalRepresentationItem() {}
shared_ptr<IfcPPObject> IfcTopologicalRepresentationItem::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcTopologicalRepresentationItem> copy_self( new IfcTopologicalRepresentationItem() );
	return copy_self;
}
void IfcTopologicalRepresentationItem::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCTOPOLOGICALREPRESENTATIONITEM" << "(";
	stream << ");";
}
void IfcTopologicalRepresentationItem::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcTopologicalRepresentationItem::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
}
void IfcTopologicalRepresentationItem::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRepresentationItem::getAttributes( vec_attributes );
}
void IfcTopologicalRepresentationItem::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcTopologicalRepresentationItem::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcTopologicalRepresentationItem::unlinkFromInverseCounterparts()
{
	IfcRepresentationItem::unlinkFromInverseCounterparts();
}
