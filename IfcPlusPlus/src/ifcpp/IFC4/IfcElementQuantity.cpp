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
#include "include/IfcElementQuantity.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPhysicalQuantity.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByTemplate.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"

// ENTITY IfcElementQuantity 
IfcElementQuantity::IfcElementQuantity() { m_entity_enum = IFCELEMENTQUANTITY; }
IfcElementQuantity::IfcElementQuantity( int id ) { m_id = id; m_entity_enum = IFCELEMENTQUANTITY; }
IfcElementQuantity::~IfcElementQuantity() {}
shared_ptr<IfcPPObject> IfcElementQuantity::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcElementQuantity> copy_self( new IfcElementQuantity() );
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
	if( m_MethodOfMeasurement ) { copy_self->m_MethodOfMeasurement = dynamic_pointer_cast<IfcLabel>( m_MethodOfMeasurement->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_Quantities.size(); ++ii )
	{
		auto item_ii = m_Quantities[ii];
		if( item_ii )
		{
			copy_self->m_Quantities.push_back( dynamic_pointer_cast<IfcPhysicalQuantity>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcElementQuantity::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCELEMENTQUANTITY" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_MethodOfMeasurement ) { m_MethodOfMeasurement->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	writeEntityList( stream, m_Quantities );
	stream << ");";
}
void IfcElementQuantity::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcElementQuantity::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 6 ){ std::stringstream err; err << "Wrong parameter count for entity IfcElementQuantity, expecting 6, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_MethodOfMeasurement = IfcLabel::createObjectFromSTEP( args[4] );
	readEntityReferenceList( args[5], m_Quantities, map );
}
void IfcElementQuantity::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcQuantitySet::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "MethodOfMeasurement", m_MethodOfMeasurement ) );
	if( m_Quantities.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> Quantities_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_Quantities.begin(), m_Quantities.end(), std::back_inserter( Quantities_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "Quantities", Quantities_vec_object ) );
	}
}
void IfcElementQuantity::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcQuantitySet::getAttributesInverse( vec_attributes_inverse );
}
void IfcElementQuantity::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcQuantitySet::setInverseCounterparts( ptr_self_entity );
}
void IfcElementQuantity::unlinkFromInverseCounterparts()
{
	IfcQuantitySet::unlinkFromInverseCounterparts();
}
