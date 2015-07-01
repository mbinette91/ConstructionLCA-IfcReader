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
#include "include/IfcGroup.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToGroup.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcText.h"

// ENTITY IfcGroup 
IfcGroup::IfcGroup() { m_entity_enum = IFCGROUP; }
IfcGroup::IfcGroup( int id ) { m_id = id; m_entity_enum = IFCGROUP; }
IfcGroup::~IfcGroup() {}
shared_ptr<IfcPPObject> IfcGroup::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcGroup> copy_self( new IfcGroup() );
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
	if( m_ObjectType ) { copy_self->m_ObjectType = dynamic_pointer_cast<IfcLabel>( m_ObjectType->getDeepCopy(options) ); }
	return copy_self;
}
void IfcGroup::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCGROUP" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ObjectType ) { m_ObjectType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ");";
}
void IfcGroup::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcGroup::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcGroup, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
}
void IfcGroup::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcObject::getAttributes( vec_attributes );
}
void IfcGroup::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcObject::getAttributesInverse( vec_attributes_inverse );
	if( m_IsGroupedBy_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> IsGroupedBy_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_IsGroupedBy_inverse.size(); ++i )
		{
			if( !m_IsGroupedBy_inverse[i].expired() )
			{
				IsGroupedBy_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelAssignsToGroup>( m_IsGroupedBy_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "IsGroupedBy_inverse", IsGroupedBy_inverse_vec_obj ) );
	}
}
void IfcGroup::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcObject::setInverseCounterparts( ptr_self_entity );
}
void IfcGroup::unlinkFromInverseCounterparts()
{
	IfcObject::unlinkFromInverseCounterparts();
}
