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
#include "include/IfcCartesianPoint.h"
#include "include/IfcColourRgb.h"
#include "include/IfcLabel.h"
#include "include/IfcLightSourcePositional.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcReal.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcLightSourcePositional 
IfcLightSourcePositional::IfcLightSourcePositional() { m_entity_enum = IFCLIGHTSOURCEPOSITIONAL; }
IfcLightSourcePositional::IfcLightSourcePositional( int id ) { m_id = id; m_entity_enum = IFCLIGHTSOURCEPOSITIONAL; }
IfcLightSourcePositional::~IfcLightSourcePositional() {}
shared_ptr<IfcPPObject> IfcLightSourcePositional::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcLightSourcePositional> copy_self( new IfcLightSourcePositional() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_LightColour ) { copy_self->m_LightColour = dynamic_pointer_cast<IfcColourRgb>( m_LightColour->getDeepCopy(options) ); }
	if( m_AmbientIntensity ) { copy_self->m_AmbientIntensity = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_AmbientIntensity->getDeepCopy(options) ); }
	if( m_Intensity ) { copy_self->m_Intensity = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_Intensity->getDeepCopy(options) ); }
	if( m_Position ) { copy_self->m_Position = dynamic_pointer_cast<IfcCartesianPoint>( m_Position->getDeepCopy(options) ); }
	if( m_Radius ) { copy_self->m_Radius = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_Radius->getDeepCopy(options) ); }
	if( m_ConstantAttenuation ) { copy_self->m_ConstantAttenuation = dynamic_pointer_cast<IfcReal>( m_ConstantAttenuation->getDeepCopy(options) ); }
	if( m_DistanceAttenuation ) { copy_self->m_DistanceAttenuation = dynamic_pointer_cast<IfcReal>( m_DistanceAttenuation->getDeepCopy(options) ); }
	if( m_QuadricAttenuation ) { copy_self->m_QuadricAttenuation = dynamic_pointer_cast<IfcReal>( m_QuadricAttenuation->getDeepCopy(options) ); }
	return copy_self;
}
void IfcLightSourcePositional::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCLIGHTSOURCEPOSITIONAL" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_LightColour ) { stream << "#" << m_LightColour->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_AmbientIntensity ) { m_AmbientIntensity->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Intensity ) { m_Intensity->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Position ) { stream << "#" << m_Position->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_Radius ) { m_Radius->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ConstantAttenuation ) { m_ConstantAttenuation->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_DistanceAttenuation ) { m_DistanceAttenuation->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_QuadricAttenuation ) { m_QuadricAttenuation->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcLightSourcePositional::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcLightSourcePositional::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 9 ){ std::stringstream err; err << "Wrong parameter count for entity IfcLightSourcePositional, expecting 9, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_LightColour, map );
	m_AmbientIntensity = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[2] );
	m_Intensity = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[3] );
	readEntityReference( args[4], m_Position, map );
	m_Radius = IfcPositiveLengthMeasure::createObjectFromSTEP( args[5] );
	m_ConstantAttenuation = IfcReal::createObjectFromSTEP( args[6] );
	m_DistanceAttenuation = IfcReal::createObjectFromSTEP( args[7] );
	m_QuadricAttenuation = IfcReal::createObjectFromSTEP( args[8] );
}
void IfcLightSourcePositional::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcLightSource::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Position", m_Position ) );
	vec_attributes.push_back( std::make_pair( "Radius", m_Radius ) );
	vec_attributes.push_back( std::make_pair( "ConstantAttenuation", m_ConstantAttenuation ) );
	vec_attributes.push_back( std::make_pair( "DistanceAttenuation", m_DistanceAttenuation ) );
	vec_attributes.push_back( std::make_pair( "QuadricAttenuation", m_QuadricAttenuation ) );
}
void IfcLightSourcePositional::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcLightSource::getAttributesInverse( vec_attributes_inverse );
}
void IfcLightSourcePositional::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcLightSource::setInverseCounterparts( ptr_self_entity );
}
void IfcLightSourcePositional::unlinkFromInverseCounterparts()
{
	IfcLightSource::unlinkFromInverseCounterparts();
}
