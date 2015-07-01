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
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcObjectDefinition.h"
#include "include/IfcObjectTypeEnum.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProcess.h"
#include "include/IfcProcessSelect.h"
#include "include/IfcRelAssignsToProcess.h"
#include "include/IfcText.h"
#include "include/IfcTypeProcess.h"

// ENTITY IfcRelAssignsToProcess 
IfcRelAssignsToProcess::IfcRelAssignsToProcess() { m_entity_enum = IFCRELASSIGNSTOPROCESS; }
IfcRelAssignsToProcess::IfcRelAssignsToProcess( int id ) { m_id = id; m_entity_enum = IFCRELASSIGNSTOPROCESS; }
IfcRelAssignsToProcess::~IfcRelAssignsToProcess() {}
shared_ptr<IfcPPObject> IfcRelAssignsToProcess::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelAssignsToProcess> copy_self( new IfcRelAssignsToProcess() );
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
	for( size_t ii=0; ii<m_RelatedObjects.size(); ++ii )
	{
		auto item_ii = m_RelatedObjects[ii];
		if( item_ii )
		{
			copy_self->m_RelatedObjects.push_back( dynamic_pointer_cast<IfcObjectDefinition>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_RelatedObjectsType ) { copy_self->m_RelatedObjectsType = dynamic_pointer_cast<IfcObjectTypeEnum>( m_RelatedObjectsType->getDeepCopy(options) ); }
	if( m_RelatingProcess ) { copy_self->m_RelatingProcess = dynamic_pointer_cast<IfcProcessSelect>( m_RelatingProcess->getDeepCopy(options) ); }
	if( m_QuantityInProcess ) { copy_self->m_QuantityInProcess = dynamic_pointer_cast<IfcMeasureWithUnit>( m_QuantityInProcess->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRelAssignsToProcess::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELASSIGNSTOPROCESS" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_RelatedObjects );
	stream << ",";
	if( m_RelatedObjectsType ) { m_RelatedObjectsType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RelatingProcess ) { m_RelatingProcess->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_QuantityInProcess ) { stream << "#" << m_QuantityInProcess->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcRelAssignsToProcess::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelAssignsToProcess::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 8 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelAssignsToProcess, expecting 8, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReferenceList( args[4], m_RelatedObjects, map );
	m_RelatedObjectsType = IfcObjectTypeEnum::createObjectFromSTEP( args[5] );
	m_RelatingProcess = IfcProcessSelect::createObjectFromSTEP( args[6], map );
	readEntityReference( args[7], m_QuantityInProcess, map );
}
void IfcRelAssignsToProcess::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelAssigns::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RelatingProcess", m_RelatingProcess ) );
	vec_attributes.push_back( std::make_pair( "QuantityInProcess", m_QuantityInProcess ) );
}
void IfcRelAssignsToProcess::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelAssigns::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelAssignsToProcess::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelAssigns::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelAssignsToProcess> ptr_self = dynamic_pointer_cast<IfcRelAssignsToProcess>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelAssignsToProcess::setInverseCounterparts: type mismatch" ); }
	shared_ptr<IfcProcess>  RelatingProcess_IfcProcess = dynamic_pointer_cast<IfcProcess>( m_RelatingProcess );
	if( RelatingProcess_IfcProcess )
	{
		RelatingProcess_IfcProcess->m_OperatesOn_inverse.push_back( ptr_self );
	}
	shared_ptr<IfcTypeProcess>  RelatingProcess_IfcTypeProcess = dynamic_pointer_cast<IfcTypeProcess>( m_RelatingProcess );
	if( RelatingProcess_IfcTypeProcess )
	{
		RelatingProcess_IfcTypeProcess->m_OperatesOn_inverse.push_back( ptr_self );
	}
}
void IfcRelAssignsToProcess::unlinkFromInverseCounterparts()
{
	IfcRelAssigns::unlinkFromInverseCounterparts();
	shared_ptr<IfcProcess>  RelatingProcess_IfcProcess = dynamic_pointer_cast<IfcProcess>( m_RelatingProcess );
	if( RelatingProcess_IfcProcess )
	{
		std::vector<weak_ptr<IfcRelAssignsToProcess> >& OperatesOn_inverse = RelatingProcess_IfcProcess->m_OperatesOn_inverse;
		for( auto it_OperatesOn_inverse = OperatesOn_inverse.begin(); it_OperatesOn_inverse != OperatesOn_inverse.end(); )
		{
			shared_ptr<IfcRelAssignsToProcess> self_candidate( *it_OperatesOn_inverse );
			if( self_candidate.get() == this )
			{
				it_OperatesOn_inverse= OperatesOn_inverse.erase( it_OperatesOn_inverse );
			}
			else
			{
				++it_OperatesOn_inverse;
			}
		}
	}
	shared_ptr<IfcTypeProcess>  RelatingProcess_IfcTypeProcess = dynamic_pointer_cast<IfcTypeProcess>( m_RelatingProcess );
	if( RelatingProcess_IfcTypeProcess )
	{
		std::vector<weak_ptr<IfcRelAssignsToProcess> >& OperatesOn_inverse = RelatingProcess_IfcTypeProcess->m_OperatesOn_inverse;
		for( auto it_OperatesOn_inverse = OperatesOn_inverse.begin(); it_OperatesOn_inverse != OperatesOn_inverse.end(); )
		{
			shared_ptr<IfcRelAssignsToProcess> self_candidate( *it_OperatesOn_inverse );
			if( self_candidate.get() == this )
			{
				it_OperatesOn_inverse= OperatesOn_inverse.erase( it_OperatesOn_inverse );
			}
			else
			{
				++it_OperatesOn_inverse;
			}
		}
	}
}
