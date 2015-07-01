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
#include "include/IfcLagTime.h"
#include "include/IfcTaskDurationEnum.h"
#include "include/IfcTimeOrRatioSelect.h"

// ENTITY IfcLagTime 
IfcLagTime::IfcLagTime() { m_entity_enum = IFCLAGTIME; }
IfcLagTime::IfcLagTime( int id ) { m_id = id; m_entity_enum = IFCLAGTIME; }
IfcLagTime::~IfcLagTime() {}
shared_ptr<IfcPPObject> IfcLagTime::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcLagTime> copy_self( new IfcLagTime() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_DataOrigin ) { copy_self->m_DataOrigin = dynamic_pointer_cast<IfcDataOriginEnum>( m_DataOrigin->getDeepCopy(options) ); }
	if( m_UserDefinedDataOrigin ) { copy_self->m_UserDefinedDataOrigin = dynamic_pointer_cast<IfcLabel>( m_UserDefinedDataOrigin->getDeepCopy(options) ); }
	if( m_LagValue ) { copy_self->m_LagValue = dynamic_pointer_cast<IfcTimeOrRatioSelect>( m_LagValue->getDeepCopy(options) ); }
	if( m_DurationType ) { copy_self->m_DurationType = dynamic_pointer_cast<IfcTaskDurationEnum>( m_DurationType->getDeepCopy(options) ); }
	return copy_self;
}
void IfcLagTime::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCLAGTIME" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_DataOrigin ) { m_DataOrigin->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_UserDefinedDataOrigin ) { m_UserDefinedDataOrigin->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_LagValue ) { m_LagValue->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_DurationType ) { m_DurationType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcLagTime::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcLagTime::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcLagTime, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_DataOrigin = IfcDataOriginEnum::createObjectFromSTEP( args[1] );
	m_UserDefinedDataOrigin = IfcLabel::createObjectFromSTEP( args[2] );
	m_LagValue = IfcTimeOrRatioSelect::createObjectFromSTEP( args[3], map );
	m_DurationType = IfcTaskDurationEnum::createObjectFromSTEP( args[4] );
}
void IfcLagTime::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcSchedulingTime::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "LagValue", m_LagValue ) );
	vec_attributes.push_back( std::make_pair( "DurationType", m_DurationType ) );
}
void IfcLagTime::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcSchedulingTime::getAttributesInverse( vec_attributes_inverse );
}
void IfcLagTime::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcSchedulingTime::setInverseCounterparts( ptr_self_entity );
}
void IfcLagTime::unlinkFromInverseCounterparts()
{
	IfcSchedulingTime::unlinkFromInverseCounterparts();
}
