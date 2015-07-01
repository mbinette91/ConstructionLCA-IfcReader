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
#include "include/IfcDerivedMeasureValue.h"
#include "include/IfcThermalAdmittanceMeasure.h"

// TYPE IfcThermalAdmittanceMeasure = REAL;
IfcThermalAdmittanceMeasure::IfcThermalAdmittanceMeasure() {}
IfcThermalAdmittanceMeasure::IfcThermalAdmittanceMeasure( double value ) { m_value = value; }
IfcThermalAdmittanceMeasure::~IfcThermalAdmittanceMeasure() {}
shared_ptr<IfcPPObject> IfcThermalAdmittanceMeasure::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcThermalAdmittanceMeasure> copy_self( new IfcThermalAdmittanceMeasure() );
	copy_self->m_value = m_value;
	return copy_self;
}
void IfcThermalAdmittanceMeasure::getStepParameter( std::stringstream& stream, bool is_select_type ) const
{
	if( is_select_type ) { stream << "IFCTHERMALADMITTANCEMEASURE("; }
	stream << m_value;
	if( is_select_type ) { stream << ")"; }
}
shared_ptr<IfcThermalAdmittanceMeasure> IfcThermalAdmittanceMeasure::createObjectFromSTEP( const std::wstring& arg )
{
	// read TYPE
	if( arg.compare( L"$" ) == 0 ) { return shared_ptr<IfcThermalAdmittanceMeasure>(); }
	else if( arg.compare( L"*" ) == 0 ) { return shared_ptr<IfcThermalAdmittanceMeasure>(); }
	shared_ptr<IfcThermalAdmittanceMeasure> type_object( new IfcThermalAdmittanceMeasure() );
	readReal( arg, type_object->m_value );
	return type_object;
}
