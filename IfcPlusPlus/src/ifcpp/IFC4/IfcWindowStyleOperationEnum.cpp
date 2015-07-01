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
#include "include/IfcWindowStyleOperationEnum.h"

// TYPE IfcWindowStyleOperationEnum = ENUMERATION OF	(SINGLE_PANEL	,DOUBLE_PANEL_VERTICAL	,DOUBLE_PANEL_HORIZONTAL	,TRIPLE_PANEL_VERTICAL	,TRIPLE_PANEL_BOTTOM	,TRIPLE_PANEL_TOP	,TRIPLE_PANEL_LEFT	,TRIPLE_PANEL_RIGHT	,TRIPLE_PANEL_HORIZONTAL	,USERDEFINED	,NOTDEFINED);
IfcWindowStyleOperationEnum::IfcWindowStyleOperationEnum() {}
IfcWindowStyleOperationEnum::~IfcWindowStyleOperationEnum() {}
shared_ptr<IfcPPObject> IfcWindowStyleOperationEnum::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcWindowStyleOperationEnum> copy_self( new IfcWindowStyleOperationEnum() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcWindowStyleOperationEnum::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCWINDOWSTYLEOPERATIONENUM("; }
	if( m_enum == ENUM_SINGLE_PANEL )
	{
		stream << ".SINGLE_PANEL.";
	}
	else if( m_enum == ENUM_DOUBLE_PANEL_VERTICAL )
	{
		stream << ".DOUBLE_PANEL_VERTICAL.";
	}
	else if( m_enum == ENUM_DOUBLE_PANEL_HORIZONTAL )
	{
		stream << ".DOUBLE_PANEL_HORIZONTAL.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_VERTICAL )
	{
		stream << ".TRIPLE_PANEL_VERTICAL.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_BOTTOM )
	{
		stream << ".TRIPLE_PANEL_BOTTOM.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_TOP )
	{
		stream << ".TRIPLE_PANEL_TOP.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_LEFT )
	{
		stream << ".TRIPLE_PANEL_LEFT.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_RIGHT )
	{
		stream << ".TRIPLE_PANEL_RIGHT.";
	}
	else if( m_enum == ENUM_TRIPLE_PANEL_HORIZONTAL )
	{
		stream << ".TRIPLE_PANEL_HORIZONTAL.";
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
shared_ptr<IfcWindowStyleOperationEnum> IfcWindowStyleOperationEnum::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcWindowStyleOperationEnum>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcWindowStyleOperationEnum>(); }
	shared_ptr<IfcWindowStyleOperationEnum> type_object( new IfcWindowStyleOperationEnum() );
	if( boost::iequals( arg, L".SINGLE_PANEL." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_SINGLE_PANEL;
	}
	else if( boost::iequals( arg, L".DOUBLE_PANEL_VERTICAL." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_DOUBLE_PANEL_VERTICAL;
	}
	else if( boost::iequals( arg, L".DOUBLE_PANEL_HORIZONTAL." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_DOUBLE_PANEL_HORIZONTAL;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_VERTICAL." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_VERTICAL;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_BOTTOM." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_BOTTOM;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_TOP." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_TOP;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_LEFT." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_LEFT;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_RIGHT." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_RIGHT;
	}
	else if( boost::iequals( arg, L".TRIPLE_PANEL_HORIZONTAL." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_TRIPLE_PANEL_HORIZONTAL;
	}
	else if( boost::iequals( arg, L".USERDEFINED." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_USERDEFINED;
	}
	else if( boost::iequals( arg, L".NOTDEFINED." ) )
	{
		type_object->m_enum = IfcWindowStyleOperationEnum::ENUM_NOTDEFINED;
	}
	return type_object;
}
