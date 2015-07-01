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
#include "include/IfcRailingTypeEnum.h"

// TYPE IfcRailingTypeEnum = ENUMERATION OF	(HANDRAIL	,GUARDRAIL	,BALUSTRADE	,USERDEFINED	,NOTDEFINED);
IfcRailingTypeEnum::IfcRailingTypeEnum() {}
IfcRailingTypeEnum::~IfcRailingTypeEnum() {}
shared_ptr<IfcPPObject> IfcRailingTypeEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRailingTypeEnum> copy_self( new IfcRailingTypeEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcRailingTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCRAILINGTYPEENUM("; }
	if( m_enum == ENUM_HANDRAIL )
	{
		stream << ".HANDRAIL.";
	}
	else if( m_enum == ENUM_GUARDRAIL )
	{
		stream << ".GUARDRAIL.";
	}
	else if( m_enum == ENUM_BALUSTRADE )
	{
		stream << ".BALUSTRADE.";
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
shared_ptr<IfcRailingTypeEnum> IfcRailingTypeEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcRailingTypeEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcRailingTypeEnum>(); }
	shared_ptr<IfcRailingTypeEnum> type_object( new IfcRailingTypeEnum() );
	if( boost::iequals( arg, L".HANDRAIL." ) )
	{
		type_object->m_enum = IfcRailingTypeEnum::ENUM_HANDRAIL;
	}
	else if( boost::iequals( arg, L".GUARDRAIL." ) )
	{
		type_object->m_enum = IfcRailingTypeEnum::ENUM_GUARDRAIL;
	}
	else if( boost::iequals( arg, L".BALUSTRADE." ) )
	{
		type_object->m_enum = IfcRailingTypeEnum::ENUM_BALUSTRADE;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcRailingTypeEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcRailingTypeEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
