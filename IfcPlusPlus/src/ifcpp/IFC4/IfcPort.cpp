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
#include "include/IfcObjectPlacement.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPort.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelConnectsPortToElement.h"
#include "include/IfcRelConnectsPorts.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcText.h"

// ENTITY IfcPort 
IfcPort::IfcPort() { m_entity_enum = IFCPORT; }
IfcPort::IfcPort( int id ) { m_id = id; m_entity_enum = IFCPORT; }
IfcPort::~IfcPort() {}
shared_ptr<IfcPPObject> IfcPort::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPort> copy_self( new IfcPort() );
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
	if( m_ObjectPlacement ) { copy_self->m_ObjectPlacement = dynamic_pointer_cast<IfcObjectPlacement>( m_ObjectPlacement->getDeepCopy(options) ); }
	if( m_Representation ) { copy_self->m_Representation = dynamic_pointer_cast<IfcProductRepresentation>( m_Representation->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPort::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPORT" << "(";
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
	if( m_ObjectPlacement ) { stream << "#" << m_ObjectPlacement->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Representation ) { stream << "#" << m_Representation->m_id; } else { stream << "*"; }
	stream << ");";
}
void IfcPort::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPort::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 7 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPort, expecting 7, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	readEntityReference( args[5], m_ObjectPlacement, map );
	readEntityReference( args[6], m_Representation, map );
}
void IfcPort::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcProduct::getAttributes( vec_attributes );
}
void IfcPort::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcProduct::getAttributesInverse( vec_attributes_inverse );
	if( m_ContainedIn_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ContainedIn_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ContainedIn_inverse.size(); ++i )
		{
			if( !m_ContainedIn_inverse[i].expired() )
			{
				ContainedIn_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelConnectsPortToElement>( m_ContainedIn_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ContainedIn_inverse", ContainedIn_inverse_vec_obj ) );
	}
	if( m_ConnectedFrom_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ConnectedFrom_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ConnectedFrom_inverse.size(); ++i )
		{
			if( !m_ConnectedFrom_inverse[i].expired() )
			{
				ConnectedFrom_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelConnectsPorts>( m_ConnectedFrom_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ConnectedFrom_inverse", ConnectedFrom_inverse_vec_obj ) );
	}
	if( m_ConnectedTo_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ConnectedTo_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ConnectedTo_inverse.size(); ++i )
		{
			if( !m_ConnectedTo_inverse[i].expired() )
			{
				ConnectedTo_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelConnectsPorts>( m_ConnectedTo_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ConnectedTo_inverse", ConnectedTo_inverse_vec_obj ) );
	}
}
void IfcPort::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcProduct::setInverseCounterparts( ptr_self_entity );
}
void IfcPort::unlinkFromInverseCounterparts()
{
	IfcProduct::unlinkFromInverseCounterparts();
}
