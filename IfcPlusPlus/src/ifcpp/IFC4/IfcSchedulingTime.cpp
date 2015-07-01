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
#include "include/IfcDataOriginEnum.h"
#include "include/IfcLabel.h"
#include "include/IfcSchedulingTime.h"

// ENTITY IfcSchedulingTime 
IfcSchedulingTime::IfcSchedulingTime() { m_entity_enum = IFCSCHEDULINGTIME; }
IfcSchedulingTime::IfcSchedulingTime( int id ) { m_id = id; m_entity_enum = IFCSCHEDULINGTIME; }
IfcSchedulingTime::~IfcSchedulingTime() {}
shared_ptr<IfcPPObject> IfcSchedulingTime::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSchedulingTime> copy_self( new IfcSchedulingTime() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_DataOrigin ) { copy_self->m_DataOrigin = dynamic_pointer_cast<IfcDataOriginEnum>( m_DataOrigin->getDeepCopy(options) ); }
	if( m_UserDefinedDataOrigin ) { copy_self->m_UserDefinedDataOrigin = dynamic_pointer_cast<IfcLabel>( m_UserDefinedDataOrigin->getDeepCopy(options) ); }
	return copy_self;
}
void IfcSchedulingTime::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSCHEDULINGTIME" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_DataOrigin ) { m_DataOrigin->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_UserDefinedDataOrigin ) { m_UserDefinedDataOrigin->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcSchedulingTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSchedulingTime::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcSchedulingTime, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_DataOrigin = IfcDataOriginEnum::createObjectFromSTEP( args[1] );
	m_UserDefinedDataOrigin = IfcLabel::createObjectFromSTEP( args[2] );
}
void IfcSchedulingTime::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
	vec_attributes.push_back( std::make_pair( "DataOrigin", m_DataOrigin ) );
	vec_attributes.push_back( std::make_pair( "UserDefinedDataOrigin", m_UserDefinedDataOrigin ) );
}
void IfcSchedulingTime::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
}
void IfcSchedulingTime::setInverseCounterparts( shared_ptr<IfcPPEntity> )
{
}
void IfcSchedulingTime::unlinkFromInverseCounterparts()
{
}
