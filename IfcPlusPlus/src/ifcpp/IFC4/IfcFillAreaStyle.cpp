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
#include "include/IfcFillAreaStyle.h"
#include "include/IfcFillStyleSelect.h"
#include "include/IfcLabel.h"

// ENTITY IfcFillAreaStyle 
IfcFillAreaStyle::IfcFillAreaStyle() { m_entity_enum = IFCFILLAREASTYLE; }
IfcFillAreaStyle::IfcFillAreaStyle( int id ) { m_id = id; m_entity_enum = IFCFILLAREASTYLE; }
IfcFillAreaStyle::~IfcFillAreaStyle() {}
shared_ptr<IfcPPObject> IfcFillAreaStyle::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcFillAreaStyle> copy_self( new IfcFillAreaStyle() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_FillStyles.size(); ++ii )
	{
		auto item_ii = m_FillStyles[ii];
		if( item_ii )
		{
			copy_self->m_FillStyles.push_back( dynamic_pointer_cast<IfcFillStyleSelect>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_ModelorDraughting ) { copy_self->m_ModelorDraughting = m_ModelorDraughting; }
	return copy_self;
}
void IfcFillAreaStyle::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCFILLAREASTYLE" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeTypeList( stream, m_FillStyles, true );
	stream << ",";
	if( m_ModelorDraughting == false ) { stream << ".F."; }
	else if( m_ModelorDraughting == true ) { stream << ".T."; }
	stream << ");";
}
void IfcFillAreaStyle::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcFillAreaStyle::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcFillAreaStyle, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	readSelectList( args[1], m_FillStyles, map );
	if( boost::iequals( args[2], L".F." ) ) { m_ModelorDraughting = false; }
	else if( boost::iequals( args[2], L".T." ) ) { m_ModelorDraughting = true; }
}
void IfcFillAreaStyle::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPresentationStyle::getAttributes( vec_attributes );
	if( m_FillStyles.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> FillStyles_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_FillStyles.begin(), m_FillStyles.end(), std::back_inserter( FillStyles_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "FillStyles", FillStyles_vec_object ) );
	}
	if( m_ModelorDraughting )
	{
		vec_attributes.push_back( std::make_pair( "ModelorDraughting", shared_ptr<IfcPPBoolAttribute>( new IfcPPBoolAttribute( m_ModelorDraughting.get() ) ) ) );
	}
	else
	{
		vec_attributes.push_back( std::make_pair( "ModelorDraughting", shared_ptr<IfcPPBoolAttribute>() ) );	 // empty shared_ptr
	}
}
void IfcFillAreaStyle::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPresentationStyle::getAttributesInverse( vec_attributes_inverse );
}
void IfcFillAreaStyle::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPresentationStyle::setInverseCounterparts( ptr_self_entity );
}
void IfcFillAreaStyle::unlinkFromInverseCounterparts()
{
	IfcPresentationStyle::unlinkFromInverseCounterparts();
}
