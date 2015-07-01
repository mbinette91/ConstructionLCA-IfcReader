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
#include <map>
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterUtil.h"
#include "ifcpp/model/shared_ptr.h"
#include "ifcpp/model/IfcPPException.h"
#include "include/IfcFlowMeterTypeEnum.h"

// TYPE IfcFlowMeterTypeEnum = ENUMERATION OF	(ENERGYMETER	,GASMETER	,OILMETER	,WATERMETER	,USERDEFINED	,NOTDEFINED);
IfcFlowMeterTypeEnum::IfcFlowMeterTypeEnum() {}
IfcFlowMeterTypeEnum::~IfcFlowMeterTypeEnum() {}
shared_ptr<IfcPPObject> IfcFlowMeterTypeEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcFlowMeterTypeEnum> copy_self( new IfcFlowMeterTypeEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcFlowMeterTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCFLOWMETERTYPEENUM("; }
	if( m_enum == ENUM_ENERGYMETER )
	{
		stream << ".ENERGYMETER.";
	}
	else if( m_enum == ENUM_GASMETER )
	{
		stream << ".GASMETER.";
	}
	else if( m_enum == ENUM_OILMETER )
	{
		stream << ".OILMETER.";
	}
	else if( m_enum == ENUM_WATERMETER )
	{
		stream << ".WATERMETER.";
	}
	else if( m_enum == ENUM_USERDEFINED )
	{
		stream << ".USERDEFINED.";
	}
	else if( m_enum == ENUM_NOTDEFINED )
	{
		stream << ".NOTDEFINED.";
	}
	if( is_select_type ) { stream << ")"; }
}
shared_ptr<IfcFlowMeterTypeEnum> IfcFlowMeterTypeEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcFlowMeterTypeEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcFlowMeterTypeEnum>(); }
	shared_ptr<IfcFlowMeterTypeEnum> type_object( new IfcFlowMeterTypeEnum() );
	if( boost::iequals( arg, L".ENERGYMETER." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_ENERGYMETER;
	}
	else if( boost::iequals( arg, L".GASMETER." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_GASMETER;
	}
	else if( boost::iequals( arg, L".OILMETER." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_OILMETER;
	}
	else if( boost::iequals( arg, L".WATERMETER." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_WATERMETER;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcFlowMeterTypeEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
