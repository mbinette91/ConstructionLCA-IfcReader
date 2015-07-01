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
#include "include/IfcColourRgb.h"
#include "include/IfcLabel.h"
#include "include/IfcLightSource.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcLightSource 
IfcLightSource::IfcLightSource() { m_entity_enum = IFCLIGHTSOURCE; }
IfcLightSource::IfcLightSource( int id ) { m_id = id; m_entity_enum = IFCLIGHTSOURCE; }
IfcLightSource::~IfcLightSource() {}
shared_ptr<IfcPPObject> IfcLightSource::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcLightSource> copy_self( new IfcLightSource() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_LightColour ) { copy_self->m_LightColour = dynamic_pointer_cast<IfcColourRgb>( m_LightColour->getDeepCopy(options) ); }
	if( m_AmbientIntensity ) { copy_self->m_AmbientIntensity = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_AmbientIntensity->getDeepCopy(options) ); }
	if( m_Intensity ) { copy_self->m_Intensity = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_Intensity->getDeepCopy(options) ); }
	return copy_self;
}
void IfcLightSource::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCLIGHTSOURCE" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LightColour ) { stream << "#" << m_LightColour->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_AmbientIntensity ) { m_AmbientIntensity->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Intensity ) { m_Intensity->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcLightSource::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcLightSource::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcLightSource, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_LightColour, map );
	m_AmbientIntensity = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[2] );
	m_Intensity = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[3] );
}
void IfcLightSource::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricRepresentationItem::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
	vec_attributes.push_back( std::make_pair( "LightColour", m_LightColour ) );
	vec_attributes.push_back( std::make_pair( "AmbientIntensity", m_AmbientIntensity ) );
	vec_attributes.push_back( std::make_pair( "Intensity", m_Intensity ) );
}
void IfcLightSource::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcLightSource::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcLightSource::unlinkFromInverseCounterparts()
{
	IfcGeometricRepresentationItem::unlinkFromInverseCounterparts();
}
