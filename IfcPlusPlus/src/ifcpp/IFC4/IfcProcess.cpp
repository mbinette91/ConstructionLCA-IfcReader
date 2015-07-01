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
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProcess.h"
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

// ENTITY IfcProcess 
IfcProcess::IfcProcess() { m_entity_enum = IFCPROCESS; }
IfcProcess::IfcProcess( int id ) { m_id = id; m_entity_enum = IFCPROCESS; }
IfcProcess::~IfcProcess() {}
shared_ptr<IfcPPObject> IfcProcess::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcProcess> copy_self( new IfcProcess() );
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
	return copy_self;
}
void IfcProcess::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPROCESS" << "(";
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
	if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LongDescription ) { m_LongDescription->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcProcess::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcProcess::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 7 ){ std::stringstream err; err << "Wrong parameter count for entity IfcProcess, expecting 7, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	m_Identification = IfcIdentifier::createObjectFromSTEP( args[5] );
	m_LongDescription = IfcText::createObjectFromSTEP( args[6] );
}
void IfcProcess::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcObject::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Identification", m_Identification ) );
	vec_attributes.push_back( std::make_pair( "LongDescription", m_LongDescription ) );
}
void IfcProcess::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcObject::getAttributesInverse( vec_attributes_inverse );
	if( m_IsPredecessorTo_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> IsPredecessorTo_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_IsPredecessorTo_inverse.size(); ++i )
		{
			if( !m_IsPredecessorTo_inverse[i].expired() )
			{
				IsPredecessorTo_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelSequence>( m_IsPredecessorTo_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "IsPredecessorTo_inverse", IsPredecessorTo_inverse_vec_obj ) );
	}
	if( m_IsSuccessorFrom_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> IsSuccessorFrom_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_IsSuccessorFrom_inverse.size(); ++i )
		{
			if( !m_IsSuccessorFrom_inverse[i].expired() )
			{
				IsSuccessorFrom_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelSequence>( m_IsSuccessorFrom_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "IsSuccessorFrom_inverse", IsSuccessorFrom_inverse_vec_obj ) );
	}
	if( m_OperatesOn_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> OperatesOn_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_OperatesOn_inverse.size(); ++i )
		{
			if( !m_OperatesOn_inverse[i].expired() )
			{
				OperatesOn_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelAssignsToProcess>( m_OperatesOn_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "OperatesOn_inverse", OperatesOn_inverse_vec_obj ) );
	}
}
void IfcProcess::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcObject::setInverseCounterparts( ptr_self_entity );
}
void IfcProcess::unlinkFromInverseCounterparts()
{
	IfcObject::unlinkFromInverseCounterparts();
}
