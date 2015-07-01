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
#include "include/IfcConversionBasedUnit.h"
#include "include/IfcDimensionalExponents.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcMeasureWithUnit.h"
#include "include/IfcUnitEnum.h"

// ENTITY IfcConversionBasedUnit 
IfcConversionBasedUnit::IfcConversionBasedUnit() { m_entity_enum = IFCCONVERSIONBASEDUNIT; }
IfcConversionBasedUnit::IfcConversionBasedUnit( int id ) { m_id = id; m_entity_enum = IFCCONVERSIONBASEDUNIT; }
IfcConversionBasedUnit::~IfcConversionBasedUnit() {}
shared_ptr<IfcPPObject> IfcConversionBasedUnit::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcConversionBasedUnit> copy_self( new IfcConversionBasedUnit() );
	if( m_Dimensions ) { copy_self->m_Dimensions = dynamic_pointer_cast<IfcDimensionalExponents>( m_Dimensions->getDeepCopy(options) ); }
	if( m_UnitType ) { copy_self->m_UnitType = dynamic_pointer_cast<IfcUnitEnum>( m_UnitType->getDeepCopy(options) ); }
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_ConversionFactor ) { copy_self->m_ConversionFactor = dynamic_pointer_cast<IfcMeasureWithUnit>( m_ConversionFactor->getDeepCopy(options) ); }
	return copy_self;
}
void IfcConversionBasedUnit::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCONVERSIONBASEDUNIT" << "(";
	if( m_Dimensions ) { stream << "#" << m_Dimensions->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_UnitType ) { m_UnitType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ConversionFactor ) { stream << "#" << m_ConversionFactor->m_id; } else { stream << "$"; }
	stream << ");";
}
void IfcConversionBasedUnit::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcConversionBasedUnit::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcConversionBasedUnit, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_Dimensions, map );
	m_UnitType = IfcUnitEnum::createObjectFromSTEP( args[1] );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	readEntityReference( args[3], m_ConversionFactor, map );
}
void IfcConversionBasedUnit::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcNamedUnit::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
	vec_attributes.push_back( std::make_pair( "ConversionFactor", m_ConversionFactor ) );
}
void IfcConversionBasedUnit::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcNamedUnit::getAttributesInverse( vec_attributes_inverse );
	if( m_HasExternalReference_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> HasExternalReference_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_HasExternalReference_inverse.size(); ++i )
		{
			if( !m_HasExternalReference_inverse[i].expired() )
			{
				HasExternalReference_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcExternalReferenceRelationship>( m_HasExternalReference_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "HasExternalReference_inverse", HasExternalReference_inverse_vec_obj ) );
	}
}
void IfcConversionBasedUnit::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcNamedUnit::setInverseCounterparts( ptr_self_entity );
}
void IfcConversionBasedUnit::unlinkFromInverseCounterparts()
{
	IfcNamedUnit::unlinkFromInverseCounterparts();
}
