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
#include "include/IfcVibrationIsolatorTypeEnum.h"

// TYPE IfcVibrationIsolatorTypeEnum = ENUMERATION OF	(COMPRESSION	,SPRING	,USERDEFINED	,NOTDEFINED);
IfcVibrationIsolatorTypeEnum::IfcVibrationIsolatorTypeEnum() {}
IfcVibrationIsolatorTypeEnum::~IfcVibrationIsolatorTypeEnum() {}
shared_ptr<IfcPPObject> IfcVibrationIsolatorTypeEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcVibrationIsolatorTypeEnum> copy_self( new IfcVibrationIsolatorTypeEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcVibrationIsolatorTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCVIBRATIONISOLATORTYPEENUM("; }
	if( m_enum == ENUM_COMPRESSION )
	{
		stream << ".COMPRESSION.";
	}
	else if( m_enum == ENUM_SPRING )
	{
		stream << ".SPRING.";
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
shared_ptr<IfcVibrationIsolatorTypeEnum> IfcVibrationIsolatorTypeEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcVibrationIsolatorTypeEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcVibrationIsolatorTypeEnum>(); }
	shared_ptr<IfcVibrationIsolatorTypeEnum> type_object( new IfcVibrationIsolatorTypeEnum() );
	if( boost::iequals( arg, L".COMPRESSION." ) )
	{
		type_object->m_enum = IfcVibrationIsolatorTypeEnum::ENUM_COMPRESSION;
	}
	else if( boost::iequals( arg, L".SPRING." ) )
	{
		type_object->m_enum = IfcVibrationIsolatorTypeEnum::ENUM_SPRING;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcVibrationIsolatorTypeEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcVibrationIsolatorTypeEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
