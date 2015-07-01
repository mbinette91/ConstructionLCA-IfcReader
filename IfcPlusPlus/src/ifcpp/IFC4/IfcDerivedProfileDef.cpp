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
#include "include/IfcCartesianTransformationOperator2D.h"
#include "include/IfcDerivedProfileDef.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcProfileDef.h"
#include "include/IfcProfileProperties.h"
#include "include/IfcProfileTypeEnum.h"

// ENTITY IfcDerivedProfileDef 
IfcDerivedProfileDef::IfcDerivedProfileDef() { m_entity_enum = IFCDERIVEDPROFILEDEF; }
IfcDerivedProfileDef::IfcDerivedProfileDef( int id ) { m_id = id; m_entity_enum = IFCDERIVEDPROFILEDEF; }
IfcDerivedProfileDef::~IfcDerivedProfileDef() {}
shared_ptr<IfcPPObject> IfcDerivedProfileDef::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcDerivedProfileDef> copy_self( new IfcDerivedProfileDef() );
	if( m_ProfileType ) { copy_self->m_ProfileType = dynamic_pointer_cast<IfcProfileTypeEnum>( m_ProfileType->getDeepCopy(options) ); }
	if( m_ProfileName ) { copy_self->m_ProfileName = dynamic_pointer_cast<IfcLabel>( m_ProfileName->getDeepCopy(options) ); }
	if( m_ParentProfile )
	{
		if( options.shallow_copy_IfcProfileDef ) { copy_self->m_ParentProfile = m_ParentProfile; }
		else { copy_self->m_ParentProfile = dynamic_pointer_cast<IfcProfileDef>( m_ParentProfile->getDeepCopy(options) ); }
	}
	if( m_Operator ) { copy_self->m_Operator = dynamic_pointer_cast<IfcCartesianTransformationOperator2D>( m_Operator->getDeepCopy(options) ); }
	if( m_Label ) { copy_self->m_Label = dynamic_pointer_cast<IfcLabel>( m_Label->getDeepCopy(options) ); }
	return copy_self;
}
void IfcDerivedProfileDef::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCDERIVEDPROFILEDEF" << "(";
	if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ParentProfile ) { stream << "#" << m_ParentProfile->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_Operator ) { stream << "#" << m_Operator->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_Label ) { m_Label->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcDerivedProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcDerivedProfileDef::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcDerivedProfileDef, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_ProfileType = IfcProfileTypeEnum::createObjectFromSTEP( args[0] );
	m_ProfileName = IfcLabel::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_ParentProfile, map );
	readEntityReference( args[3], m_Operator, map );
	m_Label = IfcLabel::createObjectFromSTEP( args[4] );
}
void IfcDerivedProfileDef::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcProfileDef::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "ParentProfile", m_ParentProfile ) );
	vec_attributes.push_back( std::make_pair( "Operator", m_Operator ) );
	vec_attributes.push_back( std::make_pair( "Label", m_Label ) );
}
void IfcDerivedProfileDef::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcProfileDef::getAttributesInverse( vec_attributes_inverse );
}
void IfcDerivedProfileDef::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcProfileDef::setInverseCounterparts( ptr_self_entity );
}
void IfcDerivedProfileDef::unlinkFromInverseCounterparts()
{
	IfcProfileDef::unlinkFromInverseCounterparts();
}
