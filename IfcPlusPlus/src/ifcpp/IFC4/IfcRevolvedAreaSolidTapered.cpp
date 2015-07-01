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
#include "include/IfcAxis1Placement.h"
#include "include/IfcAxis2Placement3D.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcProfileDef.h"
#include "include/IfcRevolvedAreaSolidTapered.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcRevolvedAreaSolidTapered 
IfcRevolvedAreaSolidTapered::IfcRevolvedAreaSolidTapered() { m_entity_enum = IFCREVOLVEDAREASOLIDTAPERED; }
IfcRevolvedAreaSolidTapered::IfcRevolvedAreaSolidTapered( int id ) { m_id = id; m_entity_enum = IFCREVOLVEDAREASOLIDTAPERED; }
IfcRevolvedAreaSolidTapered::~IfcRevolvedAreaSolidTapered() {}
shared_ptr<IfcPPObject> IfcRevolvedAreaSolidTapered::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRevolvedAreaSolidTapered> copy_self( new IfcRevolvedAreaSolidTapered() );
	if( m_SweptArea )
	{
		if( options.shallow_copy_IfcProfileDef ) { copy_self->m_SweptArea = m_SweptArea; }
		else { copy_self->m_SweptArea = dynamic_pointer_cast<IfcProfileDef>( m_SweptArea->getDeepCopy(options) ); }
	}
	if( m_Position ) { copy_self->m_Position = dynamic_pointer_cast<IfcAxis2Placement3D>( m_Position->getDeepCopy(options) ); }
	if( m_Axis ) { copy_self->m_Axis = dynamic_pointer_cast<IfcAxis1Placement>( m_Axis->getDeepCopy(options) ); }
	if( m_Angle ) { copy_self->m_Angle = dynamic_pointer_cast<IfcPlaneAngleMeasure>( m_Angle->getDeepCopy(options) ); }
	if( m_EndSweptArea )
	{
		if( options.shallow_copy_IfcProfileDef ) { copy_self->m_EndSweptArea = m_EndSweptArea; }
		else { copy_self->m_EndSweptArea = dynamic_pointer_cast<IfcProfileDef>( m_EndSweptArea->getDeepCopy(options) ); }
	}
	return copy_self;
}
void IfcRevolvedAreaSolidTapered::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCREVOLVEDAREASOLIDTAPERED" << "(";
	if( m_SweptArea ) { stream << "#" << m_SweptArea->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Position ) { stream << "#" << m_Position->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Axis ) { stream << "#" << m_Axis->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Angle ) { m_Angle->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_EndSweptArea ) { stream << "#" << m_EndSweptArea->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcRevolvedAreaSolidTapered::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRevolvedAreaSolidTapered::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRevolvedAreaSolidTapered, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_SweptArea, map );
	readEntityReference( args[1], m_Position, map );
	readEntityReference( args[2], m_Axis, map );
	m_Angle = IfcPlaneAngleMeasure::createObjectFromSTEP( args[3] );
	readEntityReference( args[4], m_EndSweptArea, map );
}
void IfcRevolvedAreaSolidTapered::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRevolvedAreaSolid::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "EndSweptArea", m_EndSweptArea ) );
}
void IfcRevolvedAreaSolidTapered::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRevolvedAreaSolid::getAttributesInverse( vec_attributes_inverse );
}
void IfcRevolvedAreaSolidTapered::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRevolvedAreaSolid::setInverseCounterparts( ptr_self_entity );
}
void IfcRevolvedAreaSolidTapered::unlinkFromInverseCounterparts()
{
	IfcRevolvedAreaSolid::unlinkFromInverseCounterparts();
}
