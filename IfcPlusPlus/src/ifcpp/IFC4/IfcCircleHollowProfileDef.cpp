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
#include "include/IfcCircleHollowProfileDef.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileProperties.h"
#include "include/IfcProfileTypeEnum.h"

// ENTITY IfcCircleHollowProfileDef 
IfcCircleHollowProfileDef::IfcCircleHollowProfileDef() { m_entity_enum = IFCCIRCLEHOLLOWPROFILEDEF; }
IfcCircleHollowProfileDef::IfcCircleHollowProfileDef( int id ) { m_id = id; m_entity_enum = IFCCIRCLEHOLLOWPROFILEDEF; }
IfcCircleHollowProfileDef::~IfcCircleHollowProfileDef() {}
shared_ptr<IfcPPObject> IfcCircleHollowProfileDef::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcCircleHollowProfileDef> copy_self( new IfcCircleHollowProfileDef() );
	if( m_ProfileType ) { copy_self->m_ProfileType = dynamic_pointer_cast<IfcProfileTypeEnum>( m_ProfileType->getDeepCopy(options) ); }
	if( m_ProfileName ) { copy_self->m_ProfileName = dynamic_pointer_cast<IfcLabel>( m_ProfileName->getDeepCopy(options) ); }
	if( m_Position ) { copy_self->m_Position = dynamic_pointer_cast<IfcAxis2Placement2D>( m_Position->getDeepCopy(options) ); }
	if( m_Radius ) { copy_self->m_Radius = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_Radius->getDeepCopy(options) ); }
	if( m_WallThickness ) { copy_self->m_WallThickness = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_WallThickness->getDeepCopy(options) ); }
	return copy_self;
}
void IfcCircleHollowProfileDef::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCIRCLEHOLLOWPROFILEDEF" << "(";
	if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Position ) { stream << "#" << m_Position->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Radius ) { m_Radius->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_WallThickness ) { m_WallThickness->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcCircleHollowProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcCircleHollowProfileDef::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcCircleHollowProfileDef, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_ProfileType = IfcProfileTypeEnum::createObjectFromSTEP( args[0] );
	m_ProfileName = IfcLabel::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_Position, map );
	m_Radius = IfcPositiveLengthMeasure::createObjectFromSTEP( args[3] );
	m_WallThickness = IfcPositiveLengthMeasure::createObjectFromSTEP( args[4] );
}
void IfcCircleHollowProfileDef::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcCircleProfileDef::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "WallThickness", m_WallThickness ) );
}
void IfcCircleHollowProfileDef::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcCircleProfileDef::getAttributesInverse( vec_attributes_inverse );
}
void IfcCircleHollowProfileDef::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcCircleProfileDef::setInverseCounterparts( ptr_self_entity );
}
void IfcCircleHollowProfileDef::unlinkFromInverseCounterparts()
{
	IfcCircleProfileDef::unlinkFromInverseCounterparts();
}
