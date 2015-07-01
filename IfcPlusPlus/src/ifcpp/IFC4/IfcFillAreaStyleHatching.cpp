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
#include "include/IfcCurveStyle.h"
#include "include/IfcFillAreaStyleHatching.h"
#include "include/IfcHatchLineDistanceSelect.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcFillAreaStyleHatching 
IfcFillAreaStyleHatching::IfcFillAreaStyleHatching() { m_entity_enum = IFCFILLAREASTYLEHATCHING; }
IfcFillAreaStyleHatching::IfcFillAreaStyleHatching( int id ) { m_id = id; m_entity_enum = IFCFILLAREASTYLEHATCHING; }
IfcFillAreaStyleHatching::~IfcFillAreaStyleHatching() {}
shared_ptr<IfcPPObject> IfcFillAreaStyleHatching::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcFillAreaStyleHatching> copy_self( new IfcFillAreaStyleHatching() );
	if( m_HatchLineAppearance ) { copy_self->m_HatchLineAppearance = dynamic_pointer_cast<IfcCurveStyle>( m_HatchLineAppearance->getDeepCopy(options) ); }
	if( m_StartOfNextHatchLine ) { copy_self->m_StartOfNextHatchLine = dynamic_pointer_cast<IfcHatchLineDistanceSelect>( m_StartOfNextHatchLine->getDeepCopy(options) ); }
	if( m_PointOfReferenceHatchLine ) { copy_self->m_PointOfReferenceHatchLine = dynamic_pointer_cast<IfcCartesianPoint>( m_PointOfReferenceHatchLine->getDeepCopy(options) ); }
	if( m_PatternStart ) { copy_self->m_PatternStart = dynamic_pointer_cast<IfcCartesianPoint>( m_PatternStart->getDeepCopy(options) ); }
	if( m_HatchLineAngle ) { copy_self->m_HatchLineAngle = dynamic_pointer_cast<IfcPlaneAngleMeasure>( m_HatchLineAngle->getDeepCopy(options) ); }
	return copy_self;
}
void IfcFillAreaStyleHatching::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCFILLAREASTYLEHATCHING" << "(";
	if( m_HatchLineAppearance ) { stream << "#" << m_HatchLineAppearance->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_StartOfNextHatchLine ) { m_StartOfNextHatchLine->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_PointOfReferenceHatchLine ) { stream << "#" << m_PointOfReferenceHatchLine->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_PatternStart ) { stream << "#" << m_PatternStart->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_HatchLineAngle ) { m_HatchLineAngle->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcFillAreaStyleHatching::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcFillAreaStyleHatching::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcFillAreaStyleHatching, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_HatchLineAppearance, map );
	m_StartOfNextHatchLine = IfcHatchLineDistanceSelect::createObjectFromSTEP( args[1], map );
	readEntityReference( args[2], m_PointOfReferenceHatchLine, map );
	readEntityReference( args[3], m_PatternStart, map );
	m_HatchLineAngle = IfcPlaneAngleMeasure::createObjectFromSTEP( args[4] );
}
void IfcFillAreaStyleHatching::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricRepresentationItem::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "HatchLineAppearance", m_HatchLineAppearance ) );
	vec_attributes.push_back( std::make_pair( "StartOfNextHatchLine", m_StartOfNextHatchLine ) );
	vec_attributes.push_back( std::make_pair( "PointOfReferenceHatchLine", m_PointOfReferenceHatchLine ) );
	vec_attributes.push_back( std::make_pair( "PatternStart", m_PatternStart ) );
	vec_attributes.push_back( std::make_pair( "HatchLineAngle", m_HatchLineAngle ) );
}
void IfcFillAreaStyleHatching::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcFillAreaStyleHatching::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcFillAreaStyleHatching::unlinkFromInverseCounterparts()
{
	IfcGeometricRepresentationItem::unlinkFromInverseCounterparts();
}
