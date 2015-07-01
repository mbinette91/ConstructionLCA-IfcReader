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
#include "include/IfcLengthMeasure.h"
#include "include/IfcPlanarExtent.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcPlanarExtent 
IfcPlanarExtent::IfcPlanarExtent() { m_entity_enum = IFCPLANAREXTENT; }
IfcPlanarExtent::IfcPlanarExtent( int id ) { m_id = id; m_entity_enum = IFCPLANAREXTENT; }
IfcPlanarExtent::~IfcPlanarExtent() {}
shared_ptr<IfcPPObject> IfcPlanarExtent::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPlanarExtent> copy_self( new IfcPlanarExtent() );
	if( m_SizeInX ) { copy_self->m_SizeInX = dynamic_pointer_cast<IfcLengthMeasure>( m_SizeInX->getDeepCopy(options) ); }
	if( m_SizeInY ) { copy_self->m_SizeInY = dynamic_pointer_cast<IfcLengthMeasure>( m_SizeInY->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPlanarExtent::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPLANAREXTENT" << "(";
	if( m_SizeInX ) { m_SizeInX->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_SizeInY ) { m_SizeInY->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcPlanarExtent::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPlanarExtent::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPlanarExtent, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_SizeInX = IfcLengthMeasure::createObjectFromSTEP( args[0] );
	m_SizeInY = IfcLengthMeasure::createObjectFromSTEP( args[1] );
}
void IfcPlanarExtent::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricRepresentationItem::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "SizeInX", m_SizeInX ) );
	vec_attributes.push_back( std::make_pair( "SizeInY", m_SizeInY ) );
}
void IfcPlanarExtent::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcPlanarExtent::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcPlanarExtent::unlinkFromInverseCounterparts()
{
	IfcGeometricRepresentationItem::unlinkFromInverseCounterparts();
}
