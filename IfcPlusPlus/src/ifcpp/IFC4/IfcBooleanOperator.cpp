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
#include "include/IfcBooleanOperator.h"

// TYPE IfcBooleanOperator = ENUMERATION OF	(UNION	,INTERSECTION	,DIFFERENCE);
IfcBooleanOperator::IfcBooleanOperator() {}
IfcBooleanOperator::~IfcBooleanOperator() {}
shared_ptr<IfcPPObject> IfcBooleanOperator::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBooleanOperator> copy_self( new IfcBooleanOperator() );
	copy_self->m_enum = m_enum;
	return copy_self;
}
void IfcBooleanOperator::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCBOOLEANOPERATOR("; }
	if( m_enum == ENUM_UNION )
	{
		stream << ".UNION.";
	}
	else if( m_enum == ENUM_INTERSECTION )
	{
		stream << ".INTERSECTION.";
	}
	else if( m_enum == ENUM_DIFFERENCE )
	{
		stream << ".DIFFERENCE.";
	}
	if( is_select_type ) { stream << ")"; }
}
shared_ptr<IfcBooleanOperator> IfcBooleanOperator::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcBooleanOperator>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcBooleanOperator>(); }
	shared_ptr<IfcBooleanOperator> type_object( new IfcBooleanOperator() );
	if( boost::iequals( arg, L".UNION." ) )
	{
		type_object->m_enum = IfcBooleanOperator::ENUM_UNION;
	}
	else if( boost::iequals( arg, L".INTERSECTION." ) )
	{
		type_object->m_enum = IfcBooleanOperator::ENUM_INTERSECTION;
	}
	else if( boost::iequals( arg, L".DIFFERENCE." ) )
	{
		type_object->m_enum = IfcBooleanOperator::ENUM_DIFFERENCE;
	}
	return type_object;
}
