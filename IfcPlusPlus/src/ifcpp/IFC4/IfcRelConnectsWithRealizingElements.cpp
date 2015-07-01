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
#include "include/IfcConnectionGeometry.h"
#include "include/IfcElement.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelConnectsWithRealizingElements.h"
#include "include/IfcText.h"

// ENTITY IfcRelConnectsWithRealizingElements 
IfcRelConnectsWithRealizingElements::IfcRelConnectsWithRealizingElements() { m_entity_enum = IFCRELCONNECTSWITHREALIZINGELEMENTS; }
IfcRelConnectsWithRealizingElements::IfcRelConnectsWithRealizingElements( int id ) { m_id = id; m_entity_enum = IFCRELCONNECTSWITHREALIZINGELEMENTS; }
IfcRelConnectsWithRealizingElements::~IfcRelConnectsWithRealizingElements() {}
shared_ptr<IfcPPObject> IfcRelConnectsWithRealizingElements::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelConnectsWithRealizingElements> copy_self( new IfcRelConnectsWithRealizingElements() );
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
	if( m_ConnectionGeometry ) { copy_self->m_ConnectionGeometry = dynamic_pointer_cast<IfcConnectionGeometry>( m_ConnectionGeometry->getDeepCopy(options) ); }
	if( m_RelatingElement ) { copy_self->m_RelatingElement = dynamic_pointer_cast<IfcElement>( m_RelatingElement->getDeepCopy(options) ); }
	if( m_RelatedElement ) { copy_self->m_RelatedElement = dynamic_pointer_cast<IfcElement>( m_RelatedElement->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_RealizingElements.size(); ++ii )
	{
		auto item_ii = m_RealizingElements[ii];
		if( item_ii )
		{
			copy_self->m_RealizingElements.push_back( dynamic_pointer_cast<IfcElement>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_ConnectionType ) { copy_self->m_ConnectionType = dynamic_pointer_cast<IfcLabel>( m_ConnectionType->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRelConnectsWithRealizingElements::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELCONNECTSWITHREALIZINGELEMENTS" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ConnectionGeometry ) { stream << "#" << m_ConnectionGeometry->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_RelatingElement ) { stream << "#" << m_RelatingElement->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_RelatedElement ) { stream << "#" << m_RelatedElement->m_id; } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_RealizingElements );
	stream << ",";
	if( m_ConnectionType ) { m_ConnectionType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcRelConnectsWithRealizingElements::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelConnectsWithRealizingElements::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 9 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelConnectsWithRealizingElements, expecting 9, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReference( args[4], m_ConnectionGeometry, map );
	readEntityReference( args[5], m_RelatingElement, map );
	readEntityReference( args[6], m_RelatedElement, map );
	readEntityReferenceList( args[7], m_RealizingElements, map );
	m_ConnectionType = IfcLabel::createObjectFromSTEP( args[8] );
}
void IfcRelConnectsWithRealizingElements::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelConnectsElements::getAttributes( vec_attributes );
	if( m_RealizingElements.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> RealizingElements_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_RealizingElements.begin(), m_RealizingElements.end(), std::back_inserter( RealizingElements_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "RealizingElements", RealizingElements_vec_object ) );
	}
	vec_attributes.push_back( std::make_pair( "ConnectionType", m_ConnectionType ) );
}
void IfcRelConnectsWithRealizingElements::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelConnectsElements::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelConnectsWithRealizingElements::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelConnectsElements::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelConnectsWithRealizingElements> ptr_self = dynamic_pointer_cast<IfcRelConnectsWithRealizingElements>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelConnectsWithRealizingElements::setInverseCounterparts: type mismatch" ); }
	for( size_t i=0; i<m_RealizingElements.size(); ++i )
	{
		if( m_RealizingElements[i] )
		{
			m_RealizingElements[i]->m_IsConnectionRealization_inverse.push_back( ptr_self );
		}
	}
}
void IfcRelConnectsWithRealizingElements::unlinkFromInverseCounterparts()
{
	IfcRelConnectsElements::unlinkFromInverseCounterparts();
	for( size_t i=0; i<m_RealizingElements.size(); ++i )
	{
		if( m_RealizingElements[i] )
		{
			std::vector<weak_ptr<IfcRelConnectsWithRealizingElements> >& IsConnectionRealization_inverse = m_RealizingElements[i]->m_IsConnectionRealization_inverse;
			for( auto it_IsConnectionRealization_inverse = IsConnectionRealization_inverse.begin(); it_IsConnectionRealization_inverse != IsConnectionRealization_inverse.end(); )
			{
				shared_ptr<IfcRelConnectsWithRealizingElements> self_candidate( *it_IsConnectionRealization_inverse );
				if( self_candidate.get() == this )
				{
					it_IsConnectionRealization_inverse= IsConnectionRealization_inverse.erase( it_IsConnectionRealization_inverse );
				}
				else
				{
					++it_IsConnectionRealization_inverse;
				}
			}
		}
	}
}
