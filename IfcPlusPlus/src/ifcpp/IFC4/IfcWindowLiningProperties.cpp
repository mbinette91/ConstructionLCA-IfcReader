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
#include "include/IfcLengthMeasure.h"
#include "include/IfcNonNegativeLengthMeasure.h"
#include "include/IfcNormalisedRatioMeasure.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByTemplate.h"
#include "include/IfcShapeAspect.h"
#include "include/IfcText.h"
#include "include/IfcTypeObject.h"
#include "include/IfcWindowLiningProperties.h"

// ENTITY IfcWindowLiningProperties 
IfcWindowLiningProperties::IfcWindowLiningProperties() { m_entity_enum = IFCWINDOWLININGPROPERTIES; }
IfcWindowLiningProperties::IfcWindowLiningProperties( int id ) { m_id = id; m_entity_enum = IFCWINDOWLININGPROPERTIES; }
IfcWindowLiningProperties::~IfcWindowLiningProperties() {}
shared_ptr<IfcPPObject> IfcWindowLiningProperties::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcWindowLiningProperties> copy_self( new IfcWindowLiningProperties() );
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
	if( m_LiningDepth ) { copy_self->m_LiningDepth = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_LiningDepth->getDeepCopy(options) ); }
	if( m_LiningThickness ) { copy_self->m_LiningThickness = dynamic_pointer_cast<IfcNonNegativeLengthMeasure>( m_LiningThickness->getDeepCopy(options) ); }
	if( m_TransomThickness ) { copy_self->m_TransomThickness = dynamic_pointer_cast<IfcNonNegativeLengthMeasure>( m_TransomThickness->getDeepCopy(options) ); }
	if( m_MullionThickness ) { copy_self->m_MullionThickness = dynamic_pointer_cast<IfcNonNegativeLengthMeasure>( m_MullionThickness->getDeepCopy(options) ); }
	if( m_FirstTransomOffset ) { copy_self->m_FirstTransomOffset = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_FirstTransomOffset->getDeepCopy(options) ); }
	if( m_SecondTransomOffset ) { copy_self->m_SecondTransomOffset = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_SecondTransomOffset->getDeepCopy(options) ); }
	if( m_FirstMullionOffset ) { copy_self->m_FirstMullionOffset = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_FirstMullionOffset->getDeepCopy(options) ); }
	if( m_SecondMullionOffset ) { copy_self->m_SecondMullionOffset = dynamic_pointer_cast<IfcNormalisedRatioMeasure>( m_SecondMullionOffset->getDeepCopy(options) ); }
	if( m_ShapeAspectStyle ) { copy_self->m_ShapeAspectStyle = dynamic_pointer_cast<IfcShapeAspect>( m_ShapeAspectStyle->getDeepCopy(options) ); }
	if( m_LiningOffset ) { copy_self->m_LiningOffset = dynamic_pointer_cast<IfcLengthMeasure>( m_LiningOffset->getDeepCopy(options) ); }
	if( m_LiningToPanelOffsetX ) { copy_self->m_LiningToPanelOffsetX = dynamic_pointer_cast<IfcLengthMeasure>( m_LiningToPanelOffsetX->getDeepCopy(options) ); }
	if( m_LiningToPanelOffsetY ) { copy_self->m_LiningToPanelOffsetY = dynamic_pointer_cast<IfcLengthMeasure>( m_LiningToPanelOffsetY->getDeepCopy(options) ); }
	return copy_self;
}
void IfcWindowLiningProperties::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCWINDOWLININGPROPERTIES" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_LiningDepth ) { m_LiningDepth->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LiningThickness ) { m_LiningThickness->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_TransomThickness ) { m_TransomThickness->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_MullionThickness ) { m_MullionThickness->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_FirstTransomOffset ) { m_FirstTransomOffset->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_SecondTransomOffset ) { m_SecondTransomOffset->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_FirstMullionOffset ) { m_FirstMullionOffset->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_SecondMullionOffset ) { m_SecondMullionOffset->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ShapeAspectStyle ) { stream << "#" << m_ShapeAspectStyle->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_LiningOffset ) { m_LiningOffset->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LiningToPanelOffsetX ) { m_LiningToPanelOffsetX->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LiningToPanelOffsetY ) { m_LiningToPanelOffsetY->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcWindowLiningProperties::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcWindowLiningProperties::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 16 ){ std::stringstream err; err << "Wrong parameter count for entity IfcWindowLiningProperties, expecting 16, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_LiningDepth = IfcPositiveLengthMeasure::createObjectFromSTEP( args[4] );
	m_LiningThickness = IfcNonNegativeLengthMeasure::createObjectFromSTEP( args[5] );
	m_TransomThickness = IfcNonNegativeLengthMeasure::createObjectFromSTEP( args[6] );
	m_MullionThickness = IfcNonNegativeLengthMeasure::createObjectFromSTEP( args[7] );
	m_FirstTransomOffset = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[8] );
	m_SecondTransomOffset = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[9] );
	m_FirstMullionOffset = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[10] );
	m_SecondMullionOffset = IfcNormalisedRatioMeasure::createObjectFromSTEP( args[11] );
	readEntityReference( args[12], m_ShapeAspectStyle, map );
	m_LiningOffset = IfcLengthMeasure::createObjectFromSTEP( args[13] );
	m_LiningToPanelOffsetX = IfcLengthMeasure::createObjectFromSTEP( args[14] );
	m_LiningToPanelOffsetY = IfcLengthMeasure::createObjectFromSTEP( args[15] );
}
void IfcWindowLiningProperties::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPreDefinedPropertySet::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "LiningDepth", m_LiningDepth ) );
	vec_attributes.push_back( std::make_pair( "LiningThickness", m_LiningThickness ) );
	vec_attributes.push_back( std::make_pair( "TransomThickness", m_TransomThickness ) );
	vec_attributes.push_back( std::make_pair( "MullionThickness", m_MullionThickness ) );
	vec_attributes.push_back( std::make_pair( "FirstTransomOffset", m_FirstTransomOffset ) );
	vec_attributes.push_back( std::make_pair( "SecondTransomOffset", m_SecondTransomOffset ) );
	vec_attributes.push_back( std::make_pair( "FirstMullionOffset", m_FirstMullionOffset ) );
	vec_attributes.push_back( std::make_pair( "SecondMullionOffset", m_SecondMullionOffset ) );
	vec_attributes.push_back( std::make_pair( "ShapeAspectStyle", m_ShapeAspectStyle ) );
	vec_attributes.push_back( std::make_pair( "LiningOffset", m_LiningOffset ) );
	vec_attributes.push_back( std::make_pair( "LiningToPanelOffsetX", m_LiningToPanelOffsetX ) );
	vec_attributes.push_back( std::make_pair( "LiningToPanelOffsetY", m_LiningToPanelOffsetY ) );
}
void IfcWindowLiningProperties::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPreDefinedPropertySet::getAttributesInverse( vec_attributes_inverse );
}
void IfcWindowLiningProperties::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPreDefinedPropertySet::setInverseCounterparts( ptr_self_entity );
}
void IfcWindowLiningProperties::unlinkFromInverseCounterparts()
{
	IfcPreDefinedPropertySet::unlinkFromInverseCounterparts();
}
