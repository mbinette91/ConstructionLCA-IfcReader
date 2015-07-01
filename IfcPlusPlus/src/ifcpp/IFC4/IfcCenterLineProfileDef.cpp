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
#include "include/IfcCenterLineProfileDef.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcProfileProperties.h"
#include "include/IfcProfileTypeEnum.h"

// ENTITY IfcCenterLineProfileDef 
IfcCenterLineProfileDef::IfcCenterLineProfileDef() { m_entity_enum = IFCCENTERLINEPROFILEDEF; }
IfcCenterLineProfileDef::IfcCenterLineProfileDef( int id ) { m_id = id; m_entity_enum = IFCCENTERLINEPROFILEDEF; }
IfcCenterLineProfileDef::~IfcCenterLineProfileDef() {}
shared_ptr<IfcPPObject> IfcCenterLineProfileDef::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcCenterLineProfileDef> copy_self( new IfcCenterLineProfileDef() );
	if( m_ProfileType ) { copy_self->m_ProfileType = dynamic_pointer_cast<IfcProfileTypeEnum>( m_ProfileType->getDeepCopy(options) ); }
	if( m_ProfileName ) { copy_self->m_ProfileName = dynamic_pointer_cast<IfcLabel>( m_ProfileName->getDeepCopy(options) ); }
	if( m_Curve ) { copy_self->m_Curve = dynamic_pointer_cast<IfcBoundedCurve>( m_Curve->getDeepCopy(options) ); }
	if( m_Thickness ) { copy_self->m_Thickness = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_Thickness->getDeepCopy(options) ); }
	return copy_self;
}
void IfcCenterLineProfileDef::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCENTERLINEPROFILEDEF" << "(";
	if( m_ProfileType ) { m_ProfileType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ProfileName ) { m_ProfileName->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Curve ) { stream << "#" << m_Curve->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Thickness ) { m_Thickness->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcCenterLineProfileDef::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcCenterLineProfileDef::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcCenterLineProfileDef, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_ProfileType = IfcProfileTypeEnum::createObjectFromSTEP( args[0] );
	m_ProfileName = IfcLabel::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_Curve, map );
	m_Thickness = IfcPositiveLengthMeasure::createObjectFromSTEP( args[3] );
}
void IfcCenterLineProfileDef::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcArbitraryOpenProfileDef::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Thickness", m_Thickness ) );
}
void IfcCenterLineProfileDef::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcArbitraryOpenProfileDef::getAttributesInverse( vec_attributes_inverse );
}
void IfcCenterLineProfileDef::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcArbitraryOpenProfileDef::setInverseCounterparts( ptr_self_entity );
}
void IfcCenterLineProfileDef::unlinkFromInverseCounterparts()
{
	IfcArbitraryOpenProfileDef::unlinkFromInverseCounterparts();
}
