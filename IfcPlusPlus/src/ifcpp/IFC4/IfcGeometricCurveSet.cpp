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

#include "ifcpp/model/IfcPPException.h"
#include "ifcpp/model/IfcPPAttributeObject.h"
#include "ifcpp/model/IfcPPGuid.h"
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterUtil.h"
#include "ifcpp/IfcPPEntityEnums.h"
#include "include/IfcGeometricCurveSet.h"
#include "include/IfcGeometricSetSelect.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcGeometricCurveSet 
IfcGeometricCurveSet::IfcGeometricCurveSet() { m_entity_enum = IFCGEOMETRICCURVESET; }
IfcGeometricCurveSet::IfcGeometricCurveSet( int id ) { m_id = id; m_entity_enum = IFCGEOMETRICCURVESET; }
IfcGeometricCurveSet::~IfcGeometricCurveSet() {}
shared_ptr<IfcPPObject> IfcGeometricCurveSet::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcGeometricCurveSet> copy_self( new IfcGeometricCurveSet() );
	for( size_t ii=0; ii<m_Elements.size(); ++ii )
	{
		auto item_ii = m_Elements[ii];
		if( item_ii )
		{
			copy_self->m_Elements.push_back( dynamic_pointer_cast<IfcGeometricSetSelect>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcGeometricCurveSet::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCGEOMETRICCURVESET" << "(";
	writeTypeList( stream, m_Elements, true );
	stream << ");";
}
void IfcGeometricCurveSet::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcGeometricCurveSet::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcGeometricCurveSet, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readSelectList( args[0], m_Elements, map );
}
void IfcGeometricCurveSet::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricSet::getAttributes( vec_attributes );
}
void IfcGeometricCurveSet::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricSet::getAttributesInverse( vec_attributes_inverse );
}
void IfcGeometricCurveSet::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricSet::setInverseCounterparts( ptr_self_entity );
}
void IfcGeometricCurveSet::unlinkFromInverseCounterparts()
{
	IfcGeometricSet::unlinkFromInverseCounterparts();
}
