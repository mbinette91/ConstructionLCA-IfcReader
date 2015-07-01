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
#include "include/IfcElement.h"
#include "include/IfcFeatureElementSubtraction.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcRelVoidsElement.h"
#include "include/IfcText.h"

// ENTITY IfcRelVoidsElement 
IfcRelVoidsElement::IfcRelVoidsElement() { m_entity_enum = IFCRELVOIDSELEMENT; }
IfcRelVoidsElement::IfcRelVoidsElement( int id ) { m_id = id; m_entity_enum = IFCRELVOIDSELEMENT; }
IfcRelVoidsElement::~IfcRelVoidsElement() {}
shared_ptr<IfcPPObject> IfcRelVoidsElement::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelVoidsElement> copy_self( new IfcRelVoidsElement() );
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
	if( m_RelatingBuildingElement ) { copy_self->m_RelatingBuildingElement = dynamic_pointer_cast<IfcElement>( m_RelatingBuildingElement->getDeepCopy(options) ); }
	if( m_RelatedOpeningElement ) { copy_self->m_RelatedOpeningElement = dynamic_pointer_cast<IfcFeatureElementSubtraction>( m_RelatedOpeningElement->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRelVoidsElement::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELVOIDSELEMENT" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RelatingBuildingElement ) { stream << "#" << m_RelatingBuildingElement->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_RelatedOpeningElement ) { stream << "#" << m_RelatedOpeningElement->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcRelVoidsElement::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelVoidsElement::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 6 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelVoidsElement, expecting 6, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReference( args[4], m_RelatingBuildingElement, map );
	readEntityReference( args[5], m_RelatedOpeningElement, map );
}
void IfcRelVoidsElement::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelDecomposes::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RelatingBuildingElement", m_RelatingBuildingElement ) );
	vec_attributes.push_back( std::make_pair( "RelatedOpeningElement", m_RelatedOpeningElement ) );
}
void IfcRelVoidsElement::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelDecomposes::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelVoidsElement::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelDecomposes::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelVoidsElement> ptr_self = dynamic_pointer_cast<IfcRelVoidsElement>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelVoidsElement::setInverseCounterparts: type mismatch" ); }
	if( m_RelatedOpeningElement )
	{
		m_RelatedOpeningElement->m_VoidsElements_inverse = ptr_self;
	}
	if( m_RelatingBuildingElement )
	{
		m_RelatingBuildingElement->m_HasOpenings_inverse.push_back( ptr_self );
	}
}
void IfcRelVoidsElement::unlinkFromInverseCounterparts()
{
	IfcRelDecomposes::unlinkFromInverseCounterparts();
	if( m_RelatedOpeningElement )
	{
		shared_ptr<IfcRelVoidsElement> self_candidate( m_RelatedOpeningElement->m_VoidsElements_inverse );
		if( self_candidate.get() == this )
		{
			weak_ptr<IfcRelVoidsElement>& self_candidate_weak = m_RelatedOpeningElement->m_VoidsElements_inverse;
			self_candidate_weak.reset();
		}
	}
	if( m_RelatingBuildingElement )
	{
		std::vector<weak_ptr<IfcRelVoidsElement> >& HasOpenings_inverse = m_RelatingBuildingElement->m_HasOpenings_inverse;
		for( auto it_HasOpenings_inverse = HasOpenings_inverse.begin(); it_HasOpenings_inverse != HasOpenings_inverse.end(); )
		{
			shared_ptr<IfcRelVoidsElement> self_candidate( *it_HasOpenings_inverse );
			if( self_candidate.get() == this )
			{
				it_HasOpenings_inverse= HasOpenings_inverse.erase( it_HasOpenings_inverse );
			}
			else
			{
				++it_HasOpenings_inverse;
			}
		}
	}
}
