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
#include "include/IfcBendingParameterSelect.h"
#include "include/IfcMeasureValue.h"
#include "include/IfcSizeSelect.h"
#include "include/IfcLengthMeasure.h"

// TYPE IfcLengthMeasure = REAL;
IfcLengthMeasure::IfcLengthMeasure() {}
IfcLengthMeasure::IfcLengthMeasure( double value ) { m_value = value; }
IfcLengthMeasure::~IfcLengthMeasure() {}
shared_ptr<IfcPPObject> IfcLengthMeasure::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcLengthMeasure> copy_self( new IfcLengthMeasure() );
	copy_self->m_value = m_value;
	return copy_self;
}
void IfcLengthMeasure::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCLENGTHMEASURE("; }
	stream << m_value;
	if( is_select_type ) { stream << ")"; }
}
shared_ptr<IfcLengthMeasure> IfcLengthMeasure::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcLengthMeasure>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcLengthMeasure>(); }
	shared_ptr<IfcLengthMeasure> type_object( new IfcLengthMeasure() );
	readReal( arg, type_object->m_value );
	return type_object;
}
