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
#include "include/IfcCartesianPoint.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcCartesianPoint 
IfcCartesianPoint::IfcCartesianPoint() { m_entity_enum = IFCCARTESIANPOINT; }
IfcCartesianPoint::IfcCartesianPoint( int id ) { m_id = id; m_entity_enum = IFCCARTESIANPOINT; }
IfcCartesianPoint::~IfcCartesianPoint() {}
shared_ptr<IfcPPObject> IfcCartesianPoint::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcCartesianPoint> copy_self( new IfcCartesianPoint() );
	for( size_t ii=0; ii<m_Coordinates.size(); ++ii )
	{
		auto item_ii = m_Coordinates[ii];
		if( item_ii )
		{
			copy_self->m_Coordinates.push_back( dynamic_pointer_cast<IfcLengthMeasure>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcCartesianPoint::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCARTESIANPOINT" << "(";
	writeNumericTypeList( stream, m_Coordinates );
	stream << ");";
}
void IfcCartesianPoint::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcCartesianPoint::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcCartesianPoint, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readTypeOfRealList( args[0], m_Coordinates );
}
void IfcCartesianPoint::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPoint::getAttributes( vec_attributes );
	if( m_Coordinates.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> Coordinates_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_Coordinates.begin(), m_Coordinates.end(), std::back_inserter( Coordinates_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "Coordinates", Coordinates_vec_object ) );
	}
}
void IfcCartesianPoint::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPoint::getAttributesInverse( vec_attributes_inverse );
}
void IfcCartesianPoint::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPoint::setInverseCounterparts( ptr_self_entity );
}
void IfcCartesianPoint::unlinkFromInverseCounterparts()
{
	IfcPoint::unlinkFromInverseCounterparts();
}
