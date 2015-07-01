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
#include "include/IfcCompoundPlaneAngleMeasure.h"
#include "include/IfcElementCompositionEnum.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcObjectPlacement.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPostalAddress.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelContainedInSpatialStructure.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcRelReferencedInSpatialStructure.h"
#include "include/IfcRelServicesBuildings.h"
#include "include/IfcSite.h"
#include "include/IfcText.h"

// ENTITY IfcSite 
IfcSite::IfcSite() { m_entity_enum = IFCSITE; }
IfcSite::IfcSite( int id ) { m_id = id; m_entity_enum = IFCSITE; }
IfcSite::~IfcSite() {}
shared_ptr<IfcPPObject> IfcSite::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSite> copy_self( new IfcSite() );
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
	if( m_LongName ) { copy_self->m_LongName = dynamic_pointer_cast<IfcLabel>( m_LongName->getDeepCopy(options) ); }
	if( m_CompositionType ) { copy_self->m_CompositionType = dynamic_pointer_cast<IfcElementCompositionEnum>( m_CompositionType->getDeepCopy(options) ); }
	if( m_RefLatitude ) { copy_self->m_RefLatitude = dynamic_pointer_cast<IfcCompoundPlaneAngleMeasure>( m_RefLatitude->getDeepCopy(options) ); }
	if( m_RefLongitude ) { copy_self->m_RefLongitude = dynamic_pointer_cast<IfcCompoundPlaneAngleMeasure>( m_RefLongitude->getDeepCopy(options) ); }
	if( m_RefElevation ) { copy_self->m_RefElevation = dynamic_pointer_cast<IfcLengthMeasure>( m_RefElevation->getDeepCopy(options) ); }
	if( m_LandTitleNumber ) { copy_self->m_LandTitleNumber = dynamic_pointer_cast<IfcLabel>( m_LandTitleNumber->getDeepCopy(options) ); }
	if( m_SiteAddress ) { copy_self->m_SiteAddress = dynamic_pointer_cast<IfcPostalAddress>( m_SiteAddress->getDeepCopy(options) ); }
	return copy_self;
}
void IfcSite::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSITE" << "(";
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
	stream << ",";
	if( m_LongName ) { m_LongName->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_CompositionType ) { m_CompositionType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RefLatitude ) { m_RefLatitude->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_RefLongitude ) { m_RefLongitude->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_RefElevation ) { m_RefElevation->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LandTitleNumber ) { m_LandTitleNumber->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_SiteAddress ) { stream << "#" << m_SiteAddress->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcSite::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSite::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 14 ){ std::stringstream err; err << "Wrong parameter count for entity IfcSite, expecting 14, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	readEntityReference( args[5], m_ObjectPlacement, map );
	readEntityReference( args[6], m_Representation, map );
	m_LongName = IfcLabel::createObjectFromSTEP( args[7] );
	m_CompositionType = IfcElementCompositionEnum::createObjectFromSTEP( args[8] );
	m_RefLatitude = IfcCompoundPlaneAngleMeasure::createObjectFromSTEP( args[9] );
	m_RefLongitude = IfcCompoundPlaneAngleMeasure::createObjectFromSTEP( args[10] );
	m_RefElevation = IfcLengthMeasure::createObjectFromSTEP( args[11] );
	m_LandTitleNumber = IfcLabel::createObjectFromSTEP( args[12] );
	readEntityReference( args[13], m_SiteAddress, map );
}
void IfcSite::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcSpatialStructureElement::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "RefLatitude", m_RefLatitude ) );
	vec_attributes.push_back( std::make_pair( "RefLongitude", m_RefLongitude ) );
	vec_attributes.push_back( std::make_pair( "RefElevation", m_RefElevation ) );
	vec_attributes.push_back( std::make_pair( "LandTitleNumber", m_LandTitleNumber ) );
	vec_attributes.push_back( std::make_pair( "SiteAddress", m_SiteAddress ) );
}
void IfcSite::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcSpatialStructureElement::getAttributesInverse( vec_attributes_inverse );
}
void IfcSite::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcSpatialStructureElement::setInverseCounterparts( ptr_self_entity );
}
void IfcSite::unlinkFromInverseCounterparts()
{
	IfcSpatialStructureElement::unlinkFromInverseCounterparts();
}
