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
#include "include/IfcDateTime.h"
#include "include/IfcEventTime.h"
#include "include/IfcLabel.h"

// ENTITY IfcEventTime 
IfcEventTime::IfcEventTime() { m_entity_enum = IFCEVENTTIME; }
IfcEventTime::IfcEventTime( int id ) { m_id = id; m_entity_enum = IFCEVENTTIME; }
IfcEventTime::~IfcEventTime() {}
shared_ptr<IfcPPObject> IfcEventTime::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcEventTime> copy_self( new IfcEventTime() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_DataOrigin ) { copy_self->m_DataOrigin = dynamic_pointer_cast<IfcDataOriginEnum>( m_DataOrigin->getDeepCopy(options) ); }
	if( m_UserDefinedDataOrigin ) { copy_self->m_UserDefinedDataOrigin = dynamic_pointer_cast<IfcLabel>( m_UserDefinedDataOrigin->getDeepCopy(options) ); }
	if( m_ActualDate ) { copy_self->m_ActualDate = dynamic_pointer_cast<IfcDateTime>( m_ActualDate->getDeepCopy(options) ); }
	if( m_EarlyDate ) { copy_self->m_EarlyDate = dynamic_pointer_cast<IfcDateTime>( m_EarlyDate->getDeepCopy(options) ); }
	if( m_LateDate ) { copy_self->m_LateDate = dynamic_pointer_cast<IfcDateTime>( m_LateDate->getDeepCopy(options) ); }
	if( m_ScheduleDate ) { copy_self->m_ScheduleDate = dynamic_pointer_cast<IfcDateTime>( m_ScheduleDate->getDeepCopy(options) ); }
	return copy_self;
}
void IfcEventTime::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCEVENTTIME" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_DataOrigin ) { m_DataOrigin->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_UserDefinedDataOrigin ) { m_UserDefinedDataOrigin->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ActualDate ) { m_ActualDate->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_EarlyDate ) { m_EarlyDate->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_LateDate ) { m_LateDate->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ScheduleDate ) { m_ScheduleDate->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcEventTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcEventTime::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 7 ){ std::stringstream err; err << "Wrong parameter count for entity IfcEventTime, expecting 7, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_DataOrigin = IfcDataOriginEnum::createObjectFromSTEP( args[1] );
	m_UserDefinedDataOrigin = IfcLabel::createObjectFromSTEP( args[2] );
	m_ActualDate = IfcDateTime::createObjectFromSTEP( args[3] );
	m_EarlyDate = IfcDateTime::createObjectFromSTEP( args[4] );
	m_LateDate = IfcDateTime::createObjectFromSTEP( args[5] );
	m_ScheduleDate = IfcDateTime::createObjectFromSTEP( args[6] );
}
void IfcEventTime::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcSchedulingTime::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "ActualDate", m_ActualDate ) );
	vec_attributes.push_back( std::make_pair( "EarlyDate", m_EarlyDate ) );
	vec_attributes.push_back( std::make_pair( "LateDate", m_LateDate ) );
	vec_attributes.push_back( std::make_pair( "ScheduleDate", m_ScheduleDate ) );
}
void IfcEventTime::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcSchedulingTime::getAttributesInverse( vec_attributes_inverse );
}
void IfcEventTime::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcSchedulingTime::setInverseCounterparts( ptr_self_entity );
}
void IfcEventTime::unlinkFromInverseCounterparts()
{
	IfcSchedulingTime::unlinkFromInverseCounterparts();
}
