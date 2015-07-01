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
#include "include/IfcEvent.h"
#include "include/IfcEventTime.h"
#include "include/IfcEventTriggerTypeEnum.h"
#include "include/IfcEventTypeEnum.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProcess.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcRelSequence.h"
#include "include/IfcText.h"

// ENTITY IfcEvent 
IfcEvent::IfcEvent() { m_entity_enum = IFCEVENT; }
IfcEvent::IfcEvent( int id ) { m_id = id; m_entity_enum = IFCEVENT; }
IfcEvent::~IfcEvent() {}
shared_ptr<IfcPPObject> IfcEvent::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcEvent> copy_self( new IfcEvent() );
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
	if( m_Identification ) { copy_self->m_Identification = dynamic_pointer_cast<IfcIdentifier>( m_Identification->getDeepCopy(options) ); }
	if( m_LongDescription ) { copy_self->m_LongDescription = dynamic_pointer_cast<IfcText>( m_LongDescription->getDeepCopy(options) ); }
	if( m_PredefinedType ) { copy_self->m_PredefinedType = dynamic_pointer_cast<IfcEventTypeEnum>( m_PredefinedType->getDeepCopy(options) ); }
	if( m_EventTriggerType ) { copy_self->m_EventTriggerType = dynamic_pointer_cast<IfcEventTriggerTypeEnum>( m_EventTriggerType->getDeepCopy(options) ); }
	if( m_UserDefinedEventTriggerType ) { copy_self->m_UserDefinedEventTriggerType = dynamic_pointer_cast<IfcLabel>( m_UserDefinedEventTriggerType->getDeepCopy(options) ); }
	if( m_EventOccurenceTime ) { copy_self->m_EventOccurenceTime = dynamic_pointer_cast<IfcEventTime>( m_EventOccurenceTime->getDeepCopy(options) ); }
	return copy_self;
}
void IfcEvent::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCEVENT" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ObjectType ) { m_ObjectType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_LongDescription ) { m_LongDescription->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_PredefinedType ) { m_PredefinedType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_EventTriggerType ) { m_EventTriggerType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_UserDefinedEventTriggerType ) { m_UserDefinedEventTriggerType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_EventOccurenceTime ) { stream << "#" << m_EventOccurenceTime->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcEvent::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcEvent::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 11 ){ std::stringstream err; err << "Wrong parameter count for entity IfcEvent, expecting 11, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	m_Identification = IfcIdentifier::createObjectFromSTEP( args[5] );
	m_LongDescription = IfcText::createObjectFromSTEP( args[6] );
	m_PredefinedType = IfcEventTypeEnum::createObjectFromSTEP( args[7] );
	m_EventTriggerType = IfcEventTriggerTypeEnum::createObjectFromSTEP( args[8] );
	m_UserDefinedEventTriggerType = IfcLabel::createObjectFromSTEP( args[9] );
	readEntityReference( args[10], m_EventOccurenceTime, map );
}
void IfcEvent::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcProcess::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "PredefinedType", m_PredefinedType ) );
	vec_attributes.push_back( std::make_pair( "EventTriggerType", m_EventTriggerType ) );
	vec_attributes.push_back( std::make_pair( "UserDefinedEventTriggerType", m_UserDefinedEventTriggerType ) );
	vec_attributes.push_back( std::make_pair( "EventOccurenceTime", m_EventOccurenceTime ) );
}
void IfcEvent::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcProcess::getAttributesInverse( vec_attributes_inverse );
}
void IfcEvent::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcProcess::setInverseCounterparts( ptr_self_entity );
}
void IfcEvent::unlinkFromInverseCounterparts()
{
	IfcProcess::unlinkFromInverseCounterparts();
}
