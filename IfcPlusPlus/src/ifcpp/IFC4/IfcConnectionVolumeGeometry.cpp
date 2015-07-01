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
#include "include/IfcConnectionVolumeGeometry.h"
#include "include/IfcSolidOrShell.h"

// ENTITY IfcConnectionVolumeGeometry 
IfcConnectionVolumeGeometry::IfcConnectionVolumeGeometry() { m_entity_enum = IFCCONNECTIONVOLUMEGEOMETRY; }
IfcConnectionVolumeGeometry::IfcConnectionVolumeGeometry( int id ) { m_id = id; m_entity_enum = IFCCONNECTIONVOLUMEGEOMETRY; }
IfcConnectionVolumeGeometry::~IfcConnectionVolumeGeometry() {}
shared_ptr<IfcPPObject> IfcConnectionVolumeGeometry::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcConnectionVolumeGeometry> copy_self( new IfcConnectionVolumeGeometry() );
	if( m_VolumeOnRelatingElement ) { copy_self->m_VolumeOnRelatingElement = dynamic_pointer_cast<IfcSolidOrShell>( m_VolumeOnRelatingElement->getDeepCopy(options) ); }
	if( m_VolumeOnRelatedElement ) { copy_self->m_VolumeOnRelatedElement = dynamic_pointer_cast<IfcSolidOrShell>( m_VolumeOnRelatedElement->getDeepCopy(options) ); }
	return copy_self;
}
void IfcConnectionVolumeGeometry::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCONNECTIONVOLUMEGEOMETRY" << "(";
	if( m_VolumeOnRelatingElement ) { m_VolumeOnRelatingElement->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_VolumeOnRelatedElement ) { m_VolumeOnRelatedElement->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ");";
}
void IfcConnectionVolumeGeometry::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcConnectionVolumeGeometry::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcConnectionVolumeGeometry, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_VolumeOnRelatingElement = IfcSolidOrShell::createObjectFromSTEP( args[0], map );
	m_VolumeOnRelatedElement = IfcSolidOrShell::createObjectFromSTEP( args[1], map );
}
void IfcConnectionVolumeGeometry::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcConnectionGeometry::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "VolumeOnRelatingElement", m_VolumeOnRelatingElement ) );
	vec_attributes.push_back( std::make_pair( "VolumeOnRelatedElement", m_VolumeOnRelatedElement ) );
}
void IfcConnectionVolumeGeometry::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcConnectionGeometry::getAttributesInverse( vec_attributes_inverse );
}
void IfcConnectionVolumeGeometry::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcConnectionGeometry::setInverseCounterparts( ptr_self_entity );
}
void IfcConnectionVolumeGeometry::unlinkFromInverseCounterparts()
{
	IfcConnectionGeometry::unlinkFromInverseCounterparts();
}
