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
#include "include/IfcSurfaceStyleLighting.h"

// ENTITY IfcSurfaceStyleLighting 
IfcSurfaceStyleLighting::IfcSurfaceStyleLighting() { m_entity_enum = IFCSURFACESTYLELIGHTING; }
IfcSurfaceStyleLighting::IfcSurfaceStyleLighting( int id ) { m_id = id; m_entity_enum = IFCSURFACESTYLELIGHTING; }
IfcSurfaceStyleLighting::~IfcSurfaceStyleLighting() {}
shared_ptr<IfcPPObject> IfcSurfaceStyleLighting::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSurfaceStyleLighting> copy_self( new IfcSurfaceStyleLighting() );
	if( m_DiffuseTransmissionColour ) { copy_self->m_DiffuseTransmissionColour = dynamic_pointer_cast<IfcColourRgb>( m_DiffuseTransmissionColour->getDeepCopy(options) ); }
	if( m_DiffuseReflectionColour ) { copy_self->m_DiffuseReflectionColour = dynamic_pointer_cast<IfcColourRgb>( m_DiffuseReflectionColour->getDeepCopy(options) ); }
	if( m_TransmissionColour ) { copy_self->m_TransmissionColour = dynamic_pointer_cast<IfcColourRgb>( m_TransmissionColour->getDeepCopy(options) ); }
	if( m_ReflectanceColour ) { copy_self->m_ReflectanceColour = dynamic_pointer_cast<IfcColourRgb>( m_ReflectanceColour->getDeepCopy(options) ); }
	return copy_self;
}
void IfcSurfaceStyleLighting::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSURFACESTYLELIGHTING" << "(";
	if( m_DiffuseTransmissionColour ) { stream << "#" << m_DiffuseTransmissionColour->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_DiffuseReflectionColour ) { stream << "#" << m_DiffuseReflectionColour->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_TransmissionColour ) { stream << "#" << m_TransmissionColour->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_ReflectanceColour ) { stream << "#" << m_ReflectanceColour->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcSurfaceStyleLighting::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSurfaceStyleLighting::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcSurfaceStyleLighting, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_DiffuseTransmissionColour, map );
	readEntityReference( args[1], m_DiffuseReflectionColour, map );
	readEntityReference( args[2], m_TransmissionColour, map );
	readEntityReference( args[3], m_ReflectanceColour, map );
}
void IfcSurfaceStyleLighting::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPresentationItem::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "DiffuseTransmissionColour", m_DiffuseTransmissionColour ) );
	vec_attributes.push_back( std::make_pair( "DiffuseReflectionColour", m_DiffuseReflectionColour ) );
	vec_attributes.push_back( std::make_pair( "TransmissionColour", m_TransmissionColour ) );
	vec_attributes.push_back( std::make_pair( "ReflectanceColour", m_ReflectanceColour ) );
}
void IfcSurfaceStyleLighting::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcSurfaceStyleLighting::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcSurfaceStyleLighting::unlinkFromInverseCounterparts()
{
	IfcPresentationItem::unlinkFromInverseCounterparts();
}
