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
#include "include/IfcOwnerHistory.h"
#include "include/IfcProjectLibrary.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelNests.h"
#include "include/IfcRepresentationContext.h"
#include "include/IfcText.h"
#include "include/IfcUnitAssignment.h"

// ENTITY IfcProjectLibrary 
IfcProjectLibrary::IfcProjectLibrary() { m_entity_enum = IFCPROJECTLIBRARY; }
IfcProjectLibrary::IfcProjectLibrary( int id ) { m_id = id; m_entity_enum = IFCPROJECTLIBRARY; }
IfcProjectLibrary::~IfcProjectLibrary() {}
shared_ptr<IfcPPObject> IfcProjectLibrary::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcProjectLibrary> copy_self( new IfcProjectLibrary() );
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
	if( m_LongName ) { copy_self->m_LongName = dynamic_pointer_cast<IfcLabel>( m_LongName->getDeepCopy(options) ); }
	if( m_Phase ) { copy_self->m_Phase = dynamic_pointer_cast<IfcLabel>( m_Phase->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_RepresentationContexts.size(); ++ii )
	{
		auto item_ii = m_RepresentationContexts[ii];
		if( item_ii )
		{
			copy_self->m_RepresentationContexts.push_back( dynamic_pointer_cast<IfcRepresentationContext>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_UnitsInContext ) { copy_self->m_UnitsInContext = dynamic_pointer_cast<IfcUnitAssignment>( m_UnitsInContext->getDeepCopy(options) ); }
	return copy_self;
}
void IfcProjectLibrary::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPROJECTLIBRARY" << "(";
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
	if( m_LongName ) { m_LongName->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Phase ) { m_Phase->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_RepresentationContexts );
	stream << ",";
	if( m_UnitsInContext ) { stream << "#" << m_UnitsInContext->m_id; } else { stream << "*"; }
	stream << ");";
}
void IfcProjectLibrary::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcProjectLibrary::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 9 ){ std::stringstream err; err << "Wrong parameter count for entity IfcProjectLibrary, expecting 9, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	m_LongName = IfcLabel::createObjectFromSTEP( args[5] );
	m_Phase = IfcLabel::createObjectFromSTEP( args[6] );
	readEntityReferenceList( args[7], m_RepresentationContexts, map );
	readEntityReference( args[8], m_UnitsInContext, map );
}
void IfcProjectLibrary::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcContext::getAttributes( vec_attributes );
}
void IfcProjectLibrary::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcContext::getAttributesInverse( vec_attributes_inverse );
}
void IfcProjectLibrary::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcContext::setInverseCounterparts( ptr_self_entity );
}
void IfcProjectLibrary::unlinkFromInverseCounterparts()
{
	IfcContext::unlinkFromInverseCounterparts();
}
