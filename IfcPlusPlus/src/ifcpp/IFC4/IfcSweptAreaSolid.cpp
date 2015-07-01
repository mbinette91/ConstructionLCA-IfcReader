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
#include "include/IfcAxis2Placement3D.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcProfileDef.h"
#include "include/IfcStyledItem.h"
#include "include/IfcSweptAreaSolid.h"

// ENTITY IfcSweptAreaSolid 
IfcSweptAreaSolid::IfcSweptAreaSolid() { m_entity_enum = IFCSWEPTAREASOLID; }
IfcSweptAreaSolid::IfcSweptAreaSolid( int id ) { m_id = id; m_entity_enum = IFCSWEPTAREASOLID; }
IfcSweptAreaSolid::~IfcSweptAreaSolid() {}
shared_ptr<IfcPPObject> IfcSweptAreaSolid::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSweptAreaSolid> copy_self( new IfcSweptAreaSolid() );
	if( m_SweptArea )
	{
		if( options.shallow_copy_IfcProfileDef ) { copy_self->m_SweptArea = m_SweptArea; }
		else { copy_self->m_SweptArea = dynamic_pointer_cast<IfcProfileDef>( m_SweptArea->getDeepCopy(options) ); }
	}
	if( m_Position ) { copy_self->m_Position = dynamic_pointer_cast<IfcAxis2Placement3D>( m_Position->getDeepCopy(options) ); }
	return copy_self;
}
void IfcSweptAreaSolid::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSWEPTAREASOLID" << "(";
	if( m_SweptArea ) { stream << "#" << m_SweptArea->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_Position ) { stream << "#" << m_Position->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcSweptAreaSolid::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSweptAreaSolid::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcSweptAreaSolid, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_SweptArea, map );
	readEntityReference( args[1], m_Position, map );
}
void IfcSweptAreaSolid::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcSolidModel::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "SweptArea", m_SweptArea ) );
	vec_attributes.push_back( std::make_pair( "Position", m_Position ) );
}
void IfcSweptAreaSolid::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcSolidModel::getAttributesInverse( vec_attributes_inverse );
}
void IfcSweptAreaSolid::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcSolidModel::setInverseCounterparts( ptr_self_entity );
}
void IfcSweptAreaSolid::unlinkFromInverseCounterparts()
{
	IfcSolidModel::unlinkFromInverseCounterparts();
}
