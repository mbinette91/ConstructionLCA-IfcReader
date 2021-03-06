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
#include "include/IfcFanTypeEnum.h"

// TYPE IfcFanTypeEnum = ENUMERATION OF	(CENTRIFUGALFORWARDCURVED	,CENTRIFUGALRADIAL	,CENTRIFUGALBACKWARDINCLINEDCURVED	,CENTRIFUGALAIRFOIL	,TUBEAXIAL	,VANEAXIAL	,PROPELLORAXIAL	,USERDEFINED	,NOTDEFINED);
IfcFanTypeEnum::IfcFanTypeEnum() {}
IfcFanTypeEnum::~IfcFanTypeEnum() {}
shared_ptr<IfcPPObject> IfcFanTypeEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcFanTypeEnum> copy_self( new IfcFanTypeEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcFanTypeEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCFANTYPEENUM("; }
	if( m_enum == ENUM_CENTRIFUGALFORWARDCURVED )
	{
		stream << ".CENTRIFUGALFORWARDCURVED.";
	}
	else if( m_enum == ENUM_CENTRIFUGALRADIAL )
	{
		stream << ".CENTRIFUGALRADIAL.";
	}
	else if( m_enum == ENUM_CENTRIFUGALBACKWARDINCLINEDCURVED )
	{
		stream << ".CENTRIFUGALBACKWARDINCLINEDCURVED.";
	}
	else if( m_enum == ENUM_CENTRIFUGALAIRFOIL )
	{
		stream << ".CENTRIFUGALAIRFOIL.";
	}
	else if( m_enum == ENUM_TUBEAXIAL )
	{
		stream << ".TUBEAXIAL.";
	}
	else if( m_enum == ENUM_VANEAXIAL )
	{
		stream << ".VANEAXIAL.";
	}
	else if( m_enum == ENUM_PROPELLORAXIAL )
	{
		stream << ".PROPELLORAXIAL.";
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
shared_ptr<IfcFanTypeEnum> IfcFanTypeEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcFanTypeEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcFanTypeEnum>(); }
	shared_ptr<IfcFanTypeEnum> type_object( new IfcFanTypeEnum() );
	if( boost::iequals( arg, L".CENTRIFUGALFORWARDCURVED." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_CENTRIFUGALFORWARDCURVED;
	}
	else if( boost::iequals( arg, L".CENTRIFUGALRADIAL." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_CENTRIFUGALRADIAL;
	}
	else if( boost::iequals( arg, L".CENTRIFUGALBACKWARDINCLINEDCURVED." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_CENTRIFUGALBACKWARDINCLINEDCURVED;
	}
	else if( boost::iequals( arg, L".CENTRIFUGALAIRFOIL." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_CENTRIFUGALAIRFOIL;
	}
	else if( boost::iequals( arg, L".TUBEAXIAL." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_TUBEAXIAL;
	}
	else if( boost::iequals( arg, L".VANEAXIAL." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_VANEAXIAL;
	}
	else if( boost::iequals( arg, L".PROPELLORAXIAL." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_PROPELLORAXIAL;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcFanTypeEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
