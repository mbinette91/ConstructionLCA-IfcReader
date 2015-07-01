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
#include "include/IfcProperty.h"
#include "include/IfcPropertySet.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByTemplate.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"

// ENTITY IfcPropertySet 
IfcPropertySet::IfcPropertySet() { m_entity_enum = IFCPROPERTYSET; }
IfcPropertySet::IfcPropertySet( int id ) { m_id = id; m_entity_enum = IFCPROPERTYSET; }
IfcPropertySet::~IfcPropertySet() {}
shared_ptr<IfcPPObject> IfcPropertySet::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPropertySet> copy_self( new IfcPropertySet() );
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
	for( size_t ii=0; ii<m_HasProperties.size(); ++ii )
	{
		auto item_ii = m_HasProperties[ii];
		if( item_ii )
		{
			copy_self->m_HasProperties.push_back( dynamic_pointer_cast<IfcProperty>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcPropertySet::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPROPERTYSET" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_HasProperties );
	stream << ");";
}
void IfcPropertySet::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPropertySet::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPropertySet, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReferenceList( args[4], m_HasProperties, map );
}
void IfcPropertySet::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPropertySetDefinition::getAttributes( vec_attributes );
	if( m_HasProperties.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> HasProperties_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_HasProperties.begin(), m_HasProperties.end(), std::back_inserter( HasProperties_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "HasProperties", HasProperties_vec_object ) );
	}
}
void IfcPropertySet::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPropertySetDefinition::getAttributesInverse( vec_attributes_inverse );
}
void IfcPropertySet::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPropertySetDefinition::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcPropertySet> ptr_self = dynamic_pointer_cast<IfcPropertySet>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcPropertySet::setInverseCounterparts: type mismatch" ); }
	for( size_t i=0; i<m_HasProperties.size(); ++i )
	{
		if( m_HasProperties[i] )
		{
			m_HasProperties[i]->m_PartOfPset_inverse.push_back( ptr_self );
		}
	}
}
void IfcPropertySet::unlinkFromInverseCounterparts()
{
	IfcPropertySetDefinition::unlinkFromInverseCounterparts();
	for( size_t i=0; i<m_HasProperties.size(); ++i )
	{
		if( m_HasProperties[i] )
		{
			std::vector<weak_ptr<IfcPropertySet> >& PartOfPset_inverse = m_HasProperties[i]->m_PartOfPset_inverse;
			for( auto it_PartOfPset_inverse = PartOfPset_inverse.begin(); it_PartOfPset_inverse != PartOfPset_inverse.end(); )
			{
				shared_ptr<IfcPropertySet> self_candidate( *it_PartOfPset_inverse );
				if( self_candidate.get() == this )
				{
					it_PartOfPset_inverse= PartOfPset_inverse.erase( it_PartOfPset_inverse );
				}
				else
				{
					++it_PartOfPset_inverse;
				}
			}
		}
	}
}
