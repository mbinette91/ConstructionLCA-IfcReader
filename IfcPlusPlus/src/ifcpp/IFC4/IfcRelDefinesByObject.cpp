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
#include "include/IfcObject.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcText.h"

// ENTITY IfcRelDefinesByObject 
IfcRelDefinesByObject::IfcRelDefinesByObject() { m_entity_enum = IFCRELDEFINESBYOBJECT; }
IfcRelDefinesByObject::IfcRelDefinesByObject( int id ) { m_id = id; m_entity_enum = IFCRELDEFINESBYOBJECT; }
IfcRelDefinesByObject::~IfcRelDefinesByObject() {}
shared_ptr<IfcPPObject> IfcRelDefinesByObject::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelDefinesByObject> copy_self( new IfcRelDefinesByObject() );
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
			copy_self->m_RelatedObjects.push_back( dynamic_pointer_cast<IfcObject>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_RelatingObject ) { copy_self->m_RelatingObject = dynamic_pointer_cast<IfcObject>( m_RelatingObject->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRelDefinesByObject::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELDEFINESBYOBJECT" << "(";
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
	if( m_RelatingObject ) { stream << "#" << m_RelatingObject->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcRelDefinesByObject::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelDefinesByObject::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 6 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelDefinesByObject, expecting 6, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReferenceList( args[4], m_RelatedObjects, map );
	readEntityReference( args[5], m_RelatingObject, map );
}
void IfcRelDefinesByObject::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelDefines::getAttributes( vec_attributes );
	if( m_RelatedObjects.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> RelatedObjects_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_RelatedObjects.begin(), m_RelatedObjects.end(), std::back_inserter( RelatedObjects_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "RelatedObjects", RelatedObjects_vec_object ) );
	}
	vec_attributes.push_back( std::make_pair( "RelatingObject", m_RelatingObject ) );
}
void IfcRelDefinesByObject::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelDefines::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelDefinesByObject::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelDefines::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelDefinesByObject> ptr_self = dynamic_pointer_cast<IfcRelDefinesByObject>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelDefinesByObject::setInverseCounterparts: type mismatch" ); }
	for( size_t i=0; i<m_RelatedObjects.size(); ++i )
	{
		if( m_RelatedObjects[i] )
		{
			m_RelatedObjects[i]->m_IsDeclaredBy_inverse.push_back( ptr_self );
		}
	}
	if( m_RelatingObject )
	{
		m_RelatingObject->m_Declares_inverse.push_back( ptr_self );
	}
}
void IfcRelDefinesByObject::unlinkFromInverseCounterparts()
{
	IfcRelDefines::unlinkFromInverseCounterparts();
	for( size_t i=0; i<m_RelatedObjects.size(); ++i )
	{
		if( m_RelatedObjects[i] )
		{
			std::vector<weak_ptr<IfcRelDefinesByObject> >& IsDeclaredBy_inverse = m_RelatedObjects[i]->m_IsDeclaredBy_inverse;
			for( auto it_IsDeclaredBy_inverse = IsDeclaredBy_inverse.begin(); it_IsDeclaredBy_inverse != IsDeclaredBy_inverse.end(); )
			{
				shared_ptr<IfcRelDefinesByObject> self_candidate( *it_IsDeclaredBy_inverse );
				if( self_candidate.get() == this )
				{
					it_IsDeclaredBy_inverse= IsDeclaredBy_inverse.erase( it_IsDeclaredBy_inverse );
				}
				else
				{
					++it_IsDeclaredBy_inverse;
				}
			}
		}
	}
	if( m_RelatingObject )
	{
		std::vector<weak_ptr<IfcRelDefinesByObject> >& Declares_inverse = m_RelatingObject->m_Declares_inverse;
		for( auto it_Declares_inverse = Declares_inverse.begin(); it_Declares_inverse != Declares_inverse.end(); )
		{
			shared_ptr<IfcRelDefinesByObject> self_candidate( *it_Declares_inverse );
			if( self_candidate.get() == this )
			{
				it_Declares_inverse= Declares_inverse.erase( it_Declares_inverse );
			}
			else
			{
				++it_Declares_inverse;
			}
		}
	}
}
