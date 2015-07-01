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
#include "include/IfcDocumentInformation.h"
#include "include/IfcDocumentInformationRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcText.h"

// ENTITY IfcDocumentInformationRelationship 
IfcDocumentInformationRelationship::IfcDocumentInformationRelationship() { m_entity_enum = IFCDOCUMENTINFORMATIONRELATIONSHIP; }
IfcDocumentInformationRelationship::IfcDocumentInformationRelationship( int id ) { m_id = id; m_entity_enum = IFCDOCUMENTINFORMATIONRELATIONSHIP; }
IfcDocumentInformationRelationship::~IfcDocumentInformationRelationship() {}
shared_ptr<IfcPPObject> IfcDocumentInformationRelationship::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcDocumentInformationRelationship> copy_self( new IfcDocumentInformationRelationship() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	if( m_RelatingDocument ) { copy_self->m_RelatingDocument = dynamic_pointer_cast<IfcDocumentInformation>( m_RelatingDocument->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_RelatedDocuments.size(); ++ii )
	{
		auto item_ii = m_RelatedDocuments[ii];
		if( item_ii )
		{
			copy_self->m_RelatedDocuments.push_back( dynamic_pointer_cast<IfcDocumentInformation>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_RelationshipType ) { copy_self->m_RelationshipType = dynamic_pointer_cast<IfcLabel>( m_RelationshipType->getDeepCopy(options) ); }
	return copy_self;
}
void IfcDocumentInformationRelationship::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCDOCUMENTINFORMATIONRELATIONSHIP" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RelatingDocument ) { stream << "#" << m_RelatingDocument->m_id; } else { stream << "$"; }
	stream << ",";
	writeEntityList( stream, m_RelatedDocuments );
	stream << ",";
	if( m_RelationshipType ) { m_RelationshipType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcDocumentInformationRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcDocumentInformationRelationship::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcDocumentInformationRelationship, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_Description = IfcText::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_RelatingDocument, map );
	readEntityReferenceList( args[3], m_RelatedDocuments, map );
	m_RelationshipType = IfcLabel::createObjectFromSTEP( args[4] );
}
void IfcDocumentInformationRelationship::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcResourceLevelRelationship::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RelatingDocument", m_RelatingDocument ) );
	if( m_RelatedDocuments.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> RelatedDocuments_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_RelatedDocuments.begin(), m_RelatedDocuments.end(), std::back_inserter( RelatedDocuments_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "RelatedDocuments", RelatedDocuments_vec_object ) );
	}
	vec_attributes.push_back( std::make_pair( "RelationshipType", m_RelationshipType ) );
}
void IfcDocumentInformationRelationship::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcResourceLevelRelationship::getAttributesInverse( vec_attributes_inverse );
}
void IfcDocumentInformationRelationship::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcResourceLevelRelationship::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcDocumentInformationRelationship> ptr_self = dynamic_pointer_cast<IfcDocumentInformationRelationship>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcDocumentInformationRelationship::setInverseCounterparts: type mismatch" ); }
	for( size_t i=0; i<m_RelatedDocuments.size(); ++i )
	{
		if( m_RelatedDocuments[i] )
		{
			m_RelatedDocuments[i]->m_IsPointedTo_inverse.push_back( ptr_self );
		}
	}
	if( m_RelatingDocument )
	{
		m_RelatingDocument->m_IsPointer_inverse.push_back( ptr_self );
	}
}
void IfcDocumentInformationRelationship::unlinkFromInverseCounterparts()
{
	IfcResourceLevelRelationship::unlinkFromInverseCounterparts();
	for( size_t i=0; i<m_RelatedDocuments.size(); ++i )
	{
		if( m_RelatedDocuments[i] )
		{
			std::vector<weak_ptr<IfcDocumentInformationRelationship> >& IsPointedTo_inverse = m_RelatedDocuments[i]->m_IsPointedTo_inverse;
			for( auto it_IsPointedTo_inverse = IsPointedTo_inverse.begin(); it_IsPointedTo_inverse != IsPointedTo_inverse.end(); )
			{
				shared_ptr<IfcDocumentInformationRelationship> self_candidate( *it_IsPointedTo_inverse );
				if( self_candidate.get() == this )
				{
					it_IsPointedTo_inverse= IsPointedTo_inverse.erase( it_IsPointedTo_inverse );
				}
				else
				{
					++it_IsPointedTo_inverse;
				}
			}
		}
	}
	if( m_RelatingDocument )
	{
		std::vector<weak_ptr<IfcDocumentInformationRelationship> >& IsPointer_inverse = m_RelatingDocument->m_IsPointer_inverse;
		for( auto it_IsPointer_inverse = IsPointer_inverse.begin(); it_IsPointer_inverse != IsPointer_inverse.end(); )
		{
			shared_ptr<IfcDocumentInformationRelationship> self_candidate( *it_IsPointer_inverse );
			if( self_candidate.get() == this )
			{
				it_IsPointer_inverse= IsPointer_inverse.erase( it_IsPointer_inverse );
			}
			else
			{
				++it_IsPointer_inverse;
			}
		}
	}
}
