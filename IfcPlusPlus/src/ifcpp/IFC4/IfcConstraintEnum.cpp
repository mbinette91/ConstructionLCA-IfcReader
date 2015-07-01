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
#include "include/IfcConstraintEnum.h"

// TYPE IfcConstraintEnum = ENUMERATION OF	(HARD	,SOFT	,ADVISORY	,USERDEFINED	,NOTDEFINED);
IfcConstraintEnum::IfcConstraintEnum() {}
IfcConstraintEnum::~IfcConstraintEnum() {}
shared_ptr<IfcPPObject> IfcConstraintEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcConstraintEnum> copy_self( new IfcConstraintEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcConstraintEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCCONSTRAINTENUM("; }
	if( m_enum == ENUM_HARD )
	{
		stream << ".HARD.";
	}
	else if( m_enum == ENUM_SOFT )
	{
		stream << ".SOFT.";
	}
	else if( m_enum == ENUM_ADVISORY )
	{
		stream << ".ADVISORY.";
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
shared_ptr<IfcConstraintEnum> IfcConstraintEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcConstraintEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcConstraintEnum>(); }
	shared_ptr<IfcConstraintEnum> type_object( new IfcConstraintEnum() );
	if( boost::iequals( arg, L".HARD." ) )
	{
		type_object->m_enum = IfcConstraintEnum::ENUM_HARD;
	}
	else if( boost::iequals( arg, L".SOFT." ) )
	{
		type_object->m_enum = IfcConstraintEnum::ENUM_SOFT;
	}
	else if( boost::iequals( arg, L".ADVISORY." ) )
	{
		type_object->m_enum = IfcConstraintEnum::ENUM_ADVISORY;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcConstraintEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcConstraintEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
