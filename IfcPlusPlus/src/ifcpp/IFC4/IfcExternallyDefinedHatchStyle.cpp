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
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcExternallyDefinedHatchStyle.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcURIReference.h"

// ENTITY IfcExternallyDefinedHatchStyle 
IfcExternallyDefinedHatchStyle::IfcExternallyDefinedHatchStyle() { m_entity_enum = IFCEXTERNALLYDEFINEDHATCHSTYLE; }
IfcExternallyDefinedHatchStyle::IfcExternallyDefinedHatchStyle( int id ) { m_id = id; m_entity_enum = IFCEXTERNALLYDEFINEDHATCHSTYLE; }
IfcExternallyDefinedHatchStyle::~IfcExternallyDefinedHatchStyle() {}
shared_ptr<IfcPPObject> IfcExternallyDefinedHatchStyle::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcExternallyDefinedHatchStyle> copy_self( new IfcExternallyDefinedHatchStyle() );
	if( m_Location ) { copy_self->m_Location = dynamic_pointer_cast<IfcURIReference>( m_Location->getDeepCopy(options) ); }
	if( m_Identification ) { copy_self->m_Identification = dynamic_pointer_cast<IfcIdentifier>( m_Identification->getDeepCopy(options) ); }
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	return copy_self;
}
void IfcExternallyDefinedHatchStyle::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCEXTERNALLYDEFINEDHATCHSTYLE" << "(";
	if( m_Location ) { m_Location->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ");";
}
void IfcExternallyDefinedHatchStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcExternallyDefinedHatchStyle::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcExternallyDefinedHatchStyle, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Location = IfcURIReference::createObjectFromSTEP( args[0] );
	m_Identification = IfcIdentifier::createObjectFromSTEP( args[1] );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
}
void IfcExternallyDefinedHatchStyle::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcExternalReference::getAttributes( vec_attributes );
}
void IfcExternallyDefinedHatchStyle::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcExternalReference::getAttributesInverse( vec_attributes_inverse );
}
void IfcExternallyDefinedHatchStyle::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcExternalReference::setInverseCounterparts( ptr_self_entity );
}
void IfcExternallyDefinedHatchStyle::unlinkFromInverseCounterparts()
{
	IfcExternalReference::unlinkFromInverseCounterparts();
}
