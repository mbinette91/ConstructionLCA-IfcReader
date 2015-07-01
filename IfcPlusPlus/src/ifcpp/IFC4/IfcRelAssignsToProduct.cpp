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
#include "include/IfcObjectDefinition.h"
#include "include/IfcObjectTypeEnum.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProduct.h"
#include "include/IfcProductSelect.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcText.h"
#include "include/IfcTypeProduct.h"

// ENTITY IfcRelAssignsToProduct 
IfcRelAssignsToProduct::IfcRelAssignsToProduct() { m_entity_enum = IFCRELASSIGNSTOPRODUCT; }
IfcRelAssignsToProduct::IfcRelAssignsToProduct( int id ) { m_id = id; m_entity_enum = IFCRELASSIGNSTOPRODUCT; }
IfcRelAssignsToProduct::~IfcRelAssignsToProduct() {}
shared_ptr<IfcPPObject> IfcRelAssignsToProduct::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRelAssignsToProduct> copy_self( new IfcRelAssignsToProduct() );
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
	if( m_RelatingProduct ) { copy_self->m_RelatingProduct = dynamic_pointer_cast<IfcProductSelect>( m_RelatingProduct->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRelAssignsToProduct::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRELASSIGNSTOPRODUCT" << "(";
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
	if( m_RelatingProduct ) { m_RelatingProduct->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ");";
}
void IfcRelAssignsToProduct::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRelAssignsToProduct::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 7 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRelAssignsToProduct, expecting 7, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	readEntityReferenceList( args[4], m_RelatedObjects, map );
	m_RelatedObjectsType = IfcObjectTypeEnum::createObjectFromSTEP( args[5] );
	m_RelatingProduct = IfcProductSelect::createObjectFromSTEP( args[6], map );
}
void IfcRelAssignsToProduct::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRelAssigns::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RelatingProduct", m_RelatingProduct ) );
}
void IfcRelAssignsToProduct::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRelAssigns::getAttributesInverse( vec_attributes_inverse );
}
void IfcRelAssignsToProduct::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRelAssigns::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcRelAssignsToProduct> ptr_self = dynamic_pointer_cast<IfcRelAssignsToProduct>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcRelAssignsToProduct::setInverseCounterparts: type mismatch" ); }
	shared_ptr<IfcProduct>  RelatingProduct_IfcProduct = dynamic_pointer_cast<IfcProduct>( m_RelatingProduct );
	if( RelatingProduct_IfcProduct )
	{
		RelatingProduct_IfcProduct->m_ReferencedBy_inverse.push_back( ptr_self );
	}
	shared_ptr<IfcTypeProduct>  RelatingProduct_IfcTypeProduct = dynamic_pointer_cast<IfcTypeProduct>( m_RelatingProduct );
	if( RelatingProduct_IfcTypeProduct )
	{
		RelatingProduct_IfcTypeProduct->m_ReferencedBy_inverse.push_back( ptr_self );
	}
}
void IfcRelAssignsToProduct::unlinkFromInverseCounterparts()
{
	IfcRelAssigns::unlinkFromInverseCounterparts();
	shared_ptr<IfcProduct>  RelatingProduct_IfcProduct = dynamic_pointer_cast<IfcProduct>( m_RelatingProduct );
	if( RelatingProduct_IfcProduct )
	{
		std::vector<weak_ptr<IfcRelAssignsToProduct> >& ReferencedBy_inverse = RelatingProduct_IfcProduct->m_ReferencedBy_inverse;
		for( auto it_ReferencedBy_inverse = ReferencedBy_inverse.begin(); it_ReferencedBy_inverse != ReferencedBy_inverse.end(); )
		{
			shared_ptr<IfcRelAssignsToProduct> self_candidate( *it_ReferencedBy_inverse );
			if( self_candidate.get() == this )
			{
				it_ReferencedBy_inverse= ReferencedBy_inverse.erase( it_ReferencedBy_inverse );
			}
			else
			{
				++it_ReferencedBy_inverse;
			}
		}
	}
	shared_ptr<IfcTypeProduct>  RelatingProduct_IfcTypeProduct = dynamic_pointer_cast<IfcTypeProduct>( m_RelatingProduct );
	if( RelatingProduct_IfcTypeProduct )
	{
		std::vector<weak_ptr<IfcRelAssignsToProduct> >& ReferencedBy_inverse = RelatingProduct_IfcTypeProduct->m_ReferencedBy_inverse;
		for( auto it_ReferencedBy_inverse = ReferencedBy_inverse.begin(); it_ReferencedBy_inverse != ReferencedBy_inverse.end(); )
		{
			shared_ptr<IfcRelAssignsToProduct> self_candidate( *it_ReferencedBy_inverse );
			if( self_candidate.get() == this )
			{
				it_ReferencedBy_inverse= ReferencedBy_inverse.erase( it_ReferencedBy_inverse );
			}
			else
			{
				++it_ReferencedBy_inverse;
			}
		}
	}
}
