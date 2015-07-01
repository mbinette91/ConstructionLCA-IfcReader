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
#include "include/IfcGridPlacement.h"
#include "include/IfcGridPlacementDirectionSelect.h"
#include "include/IfcLocalPlacement.h"
#include "include/IfcProduct.h"
#include "include/IfcVirtualGridIntersection.h"

// ENTITY IfcGridPlacement 
IfcGridPlacement::IfcGridPlacement() { m_entity_enum = IFCGRIDPLACEMENT; }
IfcGridPlacement::IfcGridPlacement( int id ) { m_id = id; m_entity_enum = IFCGRIDPLACEMENT; }
IfcGridPlacement::~IfcGridPlacement() {}
shared_ptr<IfcPPObject> IfcGridPlacement::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcGridPlacement> copy_self( new IfcGridPlacement() );
	if( m_PlacementLocation ) { copy_self->m_PlacementLocation = dynamic_pointer_cast<IfcVirtualGridIntersection>( m_PlacementLocation->getDeepCopy(options) ); }
	if( m_PlacementRefDirection ) { copy_self->m_PlacementRefDirection = dynamic_pointer_cast<IfcGridPlacementDirectionSelect>( m_PlacementRefDirection->getDeepCopy(options) ); }
	return copy_self;
}
void IfcGridPlacement::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCGRIDPLACEMENT" << "(";
	if( m_PlacementLocation ) { stream << "#" << m_PlacementLocation->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_PlacementRefDirection ) { m_PlacementRefDirection->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ");";
}
void IfcGridPlacement::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcGridPlacement::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcGridPlacement, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_PlacementLocation, map );
	m_PlacementRefDirection = IfcGridPlacementDirectionSelect::createObjectFromSTEP( args[1], map );
}
void IfcGridPlacement::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcObjectPlacement::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "PlacementLocation", m_PlacementLocation ) );
	vec_attributes.push_back( std::make_pair( "PlacementRefDirection", m_PlacementRefDirection ) );
}
void IfcGridPlacement::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcObjectPlacement::getAttributesInverse( vec_attributes_inverse );
}
void IfcGridPlacement::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcObjectPlacement::setInverseCounterparts( ptr_self_entity );
}
void IfcGridPlacement::unlinkFromInverseCounterparts()
{
	IfcObjectPlacement::unlinkFromInverseCounterparts();
}
