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
#include "include/IfcAreaMeasure.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcNamedUnit.h"
#include "include/IfcPhysicalComplexQuantity.h"
#include "include/IfcQuantityArea.h"
#include "include/IfcText.h"

// ENTITY IfcQuantityArea 
IfcQuantityArea::IfcQuantityArea() { m_entity_enum = IFCQUANTITYAREA; }
IfcQuantityArea::IfcQuantityArea( int id ) { m_id = id; m_entity_enum = IFCQUANTITYAREA; }
IfcQuantityArea::~IfcQuantityArea() {}
shared_ptr<IfcPPObject> IfcQuantityArea::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcQuantityArea> copy_self( new IfcQuantityArea() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	if( m_Unit ) { copy_self->m_Unit = dynamic_pointer_cast<IfcNamedUnit>( m_Unit->getDeepCopy(options) ); }
	if( m_AreaValue ) { copy_self->m_AreaValue = dynamic_pointer_cast<IfcAreaMeasure>( m_AreaValue->getDeepCopy(options) ); }
	if( m_Formula ) { copy_self->m_Formula = dynamic_pointer_cast<IfcLabel>( m_Formula->getDeepCopy(options) ); }
	return copy_self;
}
void IfcQuantityArea::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCQUANTITYAREA" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Unit ) { stream << "#" << m_Unit->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_AreaValue ) { m_AreaValue->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Formula ) { m_Formula->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcQuantityArea::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcQuantityArea::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcQuantityArea, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_Description = IfcText::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_Unit, map );
	m_AreaValue = IfcAreaMeasure::createObjectFromSTEP( args[3] );
	m_Formula = IfcLabel::createObjectFromSTEP( args[4] );
}
void IfcQuantityArea::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPhysicalSimpleQuantity::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "AreaValue", m_AreaValue ) );
	vec_attributes.push_back( std::make_pair( "Formula", m_Formula ) );
}
void IfcQuantityArea::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPhysicalSimpleQuantity::getAttributesInverse( vec_attributes_inverse );
}
void IfcQuantityArea::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPhysicalSimpleQuantity::setInverseCounterparts( ptr_self_entity );
}
void IfcQuantityArea::unlinkFromInverseCounterparts()
{
	IfcPhysicalSimpleQuantity::unlinkFromInverseCounterparts();
}
