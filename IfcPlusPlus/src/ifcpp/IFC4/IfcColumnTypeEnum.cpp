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
#include "include/IfcColumnTypeEnum.h"

// TYPE IfcColumnTypeEnum = ENUMERATION OF	(COLUMN	,PILASTER	,USERDEFINED	,NOTDEFINED);
IfcColumnTypeEnum::IfcColumnTypeEnum() {}
IfcColumnTypeEnum::~IfcColumnTypeEnum() {}
shared_ptr<IfcPPObject> IfcColumnTypeEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcColumnTypeEnum> copy_self( new IfcColumnTypeEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcColumnTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCCOLUMNTYPEENUM("; }
	if( m_enum == ENUM_COLUMN )
	{
		stream << ".COLUMN.";
	}
	else if( m_enum == ENUM_PILASTER )
	{
		stream << ".PILASTER.";
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
shared_ptr<IfcColumnTypeEnum> IfcColumnTypeEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcColumnTypeEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcColumnTypeEnum>(); }
	shared_ptr<IfcColumnTypeEnum> type_object( new IfcColumnTypeEnum() );
	if( boost::iequals( arg, L".COLUMN." ) )
	{
		type_object->m_enum = IfcColumnTypeEnum::ENUM_COLUMN;
	}
	else if( boost::iequals( arg, L".PILASTER." ) )
	{
		type_object->m_enum = IfcColumnTypeEnum::ENUM_PILASTER;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcColumnTypeEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcColumnTypeEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
