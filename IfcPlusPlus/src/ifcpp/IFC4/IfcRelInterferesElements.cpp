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
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelInterferesElements.h"
#include "include/IfcText.h"

// ENTITY IfcRelInterferesElements 
IfcRelInterferesElements::IfcRelInterferesElements() { m_entity_enum = IFCRELINTERFERESELEMENTS; }
IfcRelInterferesElements::IfcRelInterferesElements( int id ) { m_id = id; m_entity_enum = IFCRELINTERFERESELEMENTS; }
IfcRelInterferesElements::~IfcRelInterferesElements() {}
shared_ptr<IfcPPObject> IfcRelInterferesElements::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelInterferesElements> copy_self( new IfcRelInterferesElements() );
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
	if( m_RelatingElement ) { copy_self->m_RelatingElement = dynamic_pointer_cast<IfcElement>( m_RelatingElement->getDeepCopy(options) ); }
	if( m_RelatedElement ) { copy_self->m_RelatedElement = dynamic_pointer_cast<IfcElement>( m_RelatedElement->getDeepCopy(options) ); }
	if( m_InterferenceGeometry ) { copy_self->m_InterferenceGeometry = dynamic_pointer_cast<IfcConnectionGeometry>( m_InterferenceGeometry->getDeepCopy(options) ); }
	if( m_InterferenceType ) { copy_self->m_InterferenceType = dynamic_pointer_cast<IfcIdentifier>( m_InterferenceType->getDeepCopy(options) ); }
	if( m_ImpliedOrder ) { copy_self->m_ImpliedOrder = m_ImpliedOrder; }
	return copy_self;
}
void IfcRelInterferesElements::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELINTERFERESELEMENTS" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RelatingElement ) { stream << "#" << m_RelatingElement->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_RelatedElement ) { stream << "#" << m_RelatedElement->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_InterferenceGeometry ) { stream << "#" << m_InterferenceGeometry->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_InterferenceType ) { m_InterferenceType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ImpliedOrder == LOGICAL_FALSE ) { stream << ".F."; }
	else if( m_ImpliedOrder == LOGICAL_TRUE ) { stream << ".T."; }
	else { stream << ".U."; } // LOGICAL_UNKNOWN
	stream << ");";
}
void IfcRelInterferesElements::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelInterferesElements::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 9 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelInterferesElements, expecting 9, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReference( args[4], m_RelatingElement, map );
	readEntityReference( args[5], m_RelatedElement, map );
	readEntityReference( args[6], m_InterferenceGeometry, map );
	m_InterferenceType = IfcIdentifier::createObjectFromSTEP( args[7] );
	if( boost::iequals( args[8], L".F." ) ) { m_ImpliedOrder = LOGICAL_FALSE; }
	else if( boost::iequals( args[8], L".T." ) ) { m_ImpliedOrder = LOGICAL_TRUE; }
	else if( boost::iequals( args[8], L".U." ) ) { m_ImpliedOrder = LOGICAL_UNKNOWN; }
}
void IfcRelInterferesElements::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelConnects::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RelatingElement", m_RelatingElement ) );
	vec_attributes.push_back( std::make_pair( "RelatedElement", m_RelatedElement ) );
	vec_attributes.push_back( std::make_pair( "InterferenceGeometry", m_InterferenceGeometry ) );
	vec_attributes.push_back( std::make_pair( "InterferenceType", m_InterferenceType ) );
	vec_attributes.push_back( std::make_pair( "ImpliedOrder", shared_ptr<IfcPPLogicalAttribute>( new IfcPPLogicalAttribute( m_ImpliedOrder ) ) ) );
}
void IfcRelInterferesElements::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelConnects::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelInterferesElements::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelConnects::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelInterferesElements> ptr_self = dynamic_pointer_cast<IfcRelInterferesElements>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelInterferesElements::setInverseCounterparts: type mismatch" ); }
	if( m_RelatedElement )
	{
		m_RelatedElement->m_IsInterferedByElements_inverse.push_back( ptr_self );
	}
	if( m_RelatingElement )
	{
		m_RelatingElement->m_InterferesElements_inverse.push_back( ptr_self );
	}
}
void IfcRelInterferesElements::unlinkFromInverseCounterparts()
{
	IfcRelConnects::unlinkFromInverseCounterparts();
	if( m_RelatedElement )
	{
		std::vector<weak_ptr<IfcRelInterferesElements> >& IsInterferedByElements_inverse = m_RelatedElement->m_IsInterferedByElements_inverse;
		for( auto it_IsInterferedByElements_inverse = IsInterferedByElements_inverse.begin(); it_IsInterferedByElements_inverse != IsInterferedByElements_inverse.end(); )
		{
			shared_ptr<IfcRelInterferesElements> self_candidate( *it_IsInterferedByElements_inverse );
			if( self_candidate.get() == this )
			{
				it_IsInterferedByElements_inverse= IsInterferedByElements_inverse.erase( it_IsInterferedByElements_inverse );
			}
			else
			{
				++it_IsInterferedByElements_inverse;
			}
		}
	}
	if( m_RelatingElement )
	{
		std::vector<weak_ptr<IfcRelInterferesElements> >& InterferesElements_inverse = m_RelatingElement->m_InterferesElements_inverse;
		for( auto it_InterferesElements_inverse = InterferesElements_inverse.begin(); it_InterferesElements_inverse != InterferesElements_inverse.end(); )
		{
			shared_ptr<IfcRelInterferesElements> self_candidate( *it_InterferesElements_inverse );
			if( self_candidate.get() == this )
			{
				it_InterferesElements_inverse= InterferesElements_inverse.erase( it_InterferesElements_inverse );
			}
			else
			{
				++it_InterferesElements_inverse;
			}
		}
	}
}
