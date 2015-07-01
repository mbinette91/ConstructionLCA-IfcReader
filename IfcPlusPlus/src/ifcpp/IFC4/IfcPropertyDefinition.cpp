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
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPropertyDefinition.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcText.h"

// ENTITY IfcPropertyDefinition 
IfcPropertyDefinition::IfcPropertyDefinition() { m_entity_enum = IFCPROPERTYDEFINITION; }
IfcPropertyDefinition::IfcPropertyDefinition( int id ) { m_id = id; m_entity_enum = IFCPROPERTYDEFINITION; }
IfcPropertyDefinition::~IfcPropertyDefinition() {}
shared_ptr<IfcPPObject> IfcPropertyDefinition::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPropertyDefinition> copy_self( new IfcPropertyDefinition() );
	if( m_GlobalId )
	{
		if( options.create_new_IfcGloballyUniqueId ) { copy_self->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId( CreateCompressedGuidString22() ) ); }
		else { copy_self->m_GlobalId = dynamic_pointer_cast<IfcGloballyUniqueId>( m_GlobalId->getDeepCopy(options) ); }
	}
	if( m_OwnerHistory )
	{
		if( options.shallow_copy_IfcOwnerHistory ) { copy_self->m_OwnerHistory = m_OwnerHistory; }
		else { copy_self->m_OwnerHistory = dynamic_pointer_cast<IfcOwnerHistory>( m_OwnerHistory->getDeepCopy(options) ); }
	}
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPropertyDefinition::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPROPERTYDEFINITION" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ");";
}
void IfcPropertyDefinition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPropertyDefinition::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPropertyDefinition, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
}
void IfcPropertyDefinition::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRoot::getAttributes( vec_attributes );
}
void IfcPropertyDefinition::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRoot::getAttributesInverse( vec_attributes_inverse );
	if( m_HasContext_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> HasContext_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_HasContext_inverse.size(); ++i )
		{
			if( !m_HasContext_inverse[i].expired() )
			{
				HasContext_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelDeclares>( m_HasContext_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "HasContext_inverse", HasContext_inverse_vec_obj ) );
	}
	if( m_HasAssociations_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> HasAssociations_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_HasAssociations_inverse.size(); ++i )
		{
			if( !m_HasAssociations_inverse[i].expired() )
			{
				HasAssociations_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelAssociates>( m_HasAssociations_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "HasAssociations_inverse", HasAssociations_inverse_vec_obj ) );
	}
}
void IfcPropertyDefinition::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRoot::setInverseCounterparts( ptr_self_entity );
}
void IfcPropertyDefinition::unlinkFromInverseCounterparts()
{
	IfcRoot::unlinkFromInverseCounterparts();
}
