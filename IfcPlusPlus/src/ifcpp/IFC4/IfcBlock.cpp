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
#include "include/IfcAxis2Placement3D.h"
#include "include/IfcBlock.h"
#include "include/IfcPositiveLengthMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcBlock 
IfcBlock::IfcBlock() { m_entity_enum = IFCBLOCK; }
IfcBlock::IfcBlock( int id ) { m_id = id; m_entity_enum = IFCBLOCK; }
IfcBlock::~IfcBlock() {}
shared_ptr<IfcPPObject> IfcBlock::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBlock> copy_self( new IfcBlock() );
	if( m_Position ) { copy_self->m_Position = dynamic_pointer_cast<IfcAxis2Placement3D>( m_Position->getDeepCopy(options) ); }
	if( m_XLength ) { copy_self->m_XLength = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_XLength->getDeepCopy(options) ); }
	if( m_YLength ) { copy_self->m_YLength = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_YLength->getDeepCopy(options) ); }
	if( m_ZLength ) { copy_self->m_ZLength = dynamic_pointer_cast<IfcPositiveLengthMeasure>( m_ZLength->getDeepCopy(options) ); }
	return copy_self;
}
void IfcBlock::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCBLOCK" << "(";
	if( m_Position ) { stream << "#" << m_Position->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_XLength ) { m_XLength->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_YLength ) { m_YLength->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ZLength ) { m_ZLength->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcBlock::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBlock::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcBlock, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_Position, map );
	m_XLength = IfcPositiveLengthMeasure::createObjectFromSTEP( args[1] );
	m_YLength = IfcPositiveLengthMeasure::createObjectFromSTEP( args[2] );
	m_ZLength = IfcPositiveLengthMeasure::createObjectFromSTEP( args[3] );
}
void IfcBlock::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcCsgPrimitive3D::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "XLength", m_XLength ) );
	vec_attributes.push_back( std::make_pair( "YLength", m_YLength ) );
	vec_attributes.push_back( std::make_pair( "ZLength", m_ZLength ) );
}
void IfcBlock::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcCsgPrimitive3D::getAttributesInverse( vec_attributes_inverse );
}
void IfcBlock::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcCsgPrimitive3D::setInverseCounterparts( ptr_self_entity );
}
void IfcBlock::unlinkFromInverseCounterparts()
{
	IfcCsgPrimitive3D::unlinkFromInverseCounterparts();
}
