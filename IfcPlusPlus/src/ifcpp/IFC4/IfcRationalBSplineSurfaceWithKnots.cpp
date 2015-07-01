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
#include "include/IfcBSplineSurfaceForm.h"
#include "include/IfcCartesianPoint.h"
#include "include/IfcKnotType.h"
#include "include/IfcParameterValue.h"
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcRationalBSplineSurfaceWithKnots.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcRationalBSplineSurfaceWithKnots 
IfcRationalBSplineSurfaceWithKnots::IfcRationalBSplineSurfaceWithKnots() { m_entity_enum = IFCRATIONALBSPLINESURFACEWITHKNOTS; }
IfcRationalBSplineSurfaceWithKnots::IfcRationalBSplineSurfaceWithKnots( int id ) { m_id = id; m_entity_enum = IFCRATIONALBSPLINESURFACEWITHKNOTS; }
IfcRationalBSplineSurfaceWithKnots::~IfcRationalBSplineSurfaceWithKnots() {}
shared_ptr<IfcPPObject> IfcRationalBSplineSurfaceWithKnots::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRationalBSplineSurfaceWithKnots> copy_self( new IfcRationalBSplineSurfaceWithKnots() );
	if( m_UDegree ) { copy_self->m_UDegree = m_UDegree; }
	if( m_VDegree ) { copy_self->m_VDegree = m_VDegree; }
	copy_self->m_ControlPointsList.resize( m_ControlPointsList.size() );
	for( size_t ii=0; ii<m_ControlPointsList.size(); ++ii )
	{
		std::vector<shared_ptr<IfcCartesianPoint> >& vec_ii = m_ControlPointsList[ii];
		std::vector<shared_ptr<IfcCartesianPoint> >& vec_ii_target = copy_self->m_ControlPointsList[ii];
		for( size_t jj=0; jj<vec_ii.size(); ++jj )
		{
			shared_ptr<IfcCartesianPoint>& item_jj = vec_ii[jj];
			if( item_jj )
			{
				vec_ii_target.push_back( dynamic_pointer_cast<IfcCartesianPoint>( item_jj->getDeepCopy(options) ) );
			}
		}
	}
	if( m_SurfaceForm ) { copy_self->m_SurfaceForm = dynamic_pointer_cast<IfcBSplineSurfaceForm>( m_SurfaceForm->getDeepCopy(options) ); }
	if( m_UClosed ) { copy_self->m_UClosed = m_UClosed; }
	if( m_VClosed ) { copy_self->m_VClosed = m_VClosed; }
	if( m_SelfIntersect ) { copy_self->m_SelfIntersect = m_SelfIntersect; }
	if( m_UMultiplicities.size() > 0 ) { std::copy( m_UMultiplicities.begin(), m_UMultiplicities.end(), std::back_inserter( copy_self->m_UMultiplicities ) ); }
	if( m_VMultiplicities.size() > 0 ) { std::copy( m_VMultiplicities.begin(), m_VMultiplicities.end(), std::back_inserter( copy_self->m_VMultiplicities ) ); }
	for( size_t ii=0; ii<m_UKnots.size(); ++ii )
	{
		auto item_ii = m_UKnots[ii];
		if( item_ii )
		{
			copy_self->m_UKnots.push_back( dynamic_pointer_cast<IfcParameterValue>(item_ii->getDeepCopy(options) ) );
		}
	}
	for( size_t ii=0; ii<m_VKnots.size(); ++ii )
	{
		auto item_ii = m_VKnots[ii];
		if( item_ii )
		{
			copy_self->m_VKnots.push_back( dynamic_pointer_cast<IfcParameterValue>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_KnotSpec ) { copy_self->m_KnotSpec = dynamic_pointer_cast<IfcKnotType>( m_KnotSpec->getDeepCopy(options) ); }
	if( m_WeightsData.size() > 0 )
	{
		copy_self->m_WeightsData.resize( m_WeightsData.size() );
		for( size_t i = 0; i < m_WeightsData.size(); ++i )
		{
			std::copy( m_WeightsData[i].begin(), m_WeightsData[i].end(), std::back_inserter( copy_self->m_WeightsData[i] ) );
		}
	}
	return copy_self;
}
void IfcRationalBSplineSurfaceWithKnots::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCRATIONALBSPLINESURFACEWITHKNOTS" << "(";
	if( m_UDegree ){ stream << m_UDegree; } else { stream << "*"; }
	stream << ",";
	if( m_VDegree ){ stream << m_VDegree; } else { stream << "*"; }
	stream << ",";
	writeEntityList2D( stream, m_ControlPointsList );
	stream << ",";
	if( m_SurfaceForm ) { m_SurfaceForm->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_UClosed == LOGICAL_FALSE ) { stream << ".F."; }
	else if( m_UClosed == LOGICAL_TRUE ) { stream << ".T."; }
	else { stream << ".U."; } // LOGICAL_UNKNOWN
	stream << ",";
	if( m_VClosed == LOGICAL_FALSE ) { stream << ".F."; }
	else if( m_VClosed == LOGICAL_TRUE ) { stream << ".T."; }
	else { stream << ".U."; } // LOGICAL_UNKNOWN
	stream << ",";
	if( m_SelfIntersect == LOGICAL_FALSE ) { stream << ".F."; }
	else if( m_SelfIntersect == LOGICAL_TRUE ) { stream << ".T."; }
	else { stream << ".U."; } // LOGICAL_UNKNOWN
	stream << ",";
	writeNumericList( stream, m_UMultiplicities );
	stream << ",";
	writeNumericList( stream, m_VMultiplicities );
	stream << ",";
	writeNumericTypeList( stream, m_UKnots );
	stream << ",";
	writeNumericTypeList( stream, m_VKnots );
	stream << ",";
	if( m_KnotSpec ) { m_KnotSpec->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeNumericList2D( stream, m_WeightsData );
	stream << ");";
}
void IfcRationalBSplineSurfaceWithKnots::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRationalBSplineSurfaceWithKnots::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 13 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRationalBSplineSurfaceWithKnots, expecting 13, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readIntValue( args[0], m_UDegree );
	readIntValue( args[1], m_VDegree );
	readEntityReferenceList2D( args[2], m_ControlPointsList, map );
	m_SurfaceForm = IfcBSplineSurfaceForm::createObjectFromSTEP( args[3] );
	if( boost::iequals( args[4], L".F." ) ) { m_UClosed = LOGICAL_FALSE; }
	else if( boost::iequals( args[4], L".T." ) ) { m_UClosed = LOGICAL_TRUE; }
	else if( boost::iequals( args[4], L".U." ) ) { m_UClosed = LOGICAL_UNKNOWN; }
	if( boost::iequals( args[5], L".F." ) ) { m_VClosed = LOGICAL_FALSE; }
	else if( boost::iequals( args[5], L".T." ) ) { m_VClosed = LOGICAL_TRUE; }
	else if( boost::iequals( args[5], L".U." ) ) { m_VClosed = LOGICAL_UNKNOWN; }
	if( boost::iequals( args[6], L".F." ) ) { m_SelfIntersect = LOGICAL_FALSE; }
	else if( boost::iequals( args[6], L".T." ) ) { m_SelfIntersect = LOGICAL_TRUE; }
	else if( boost::iequals( args[6], L".U." ) ) { m_SelfIntersect = LOGICAL_UNKNOWN; }
	readIntList(  args[7], m_UMultiplicities );
	readIntList(  args[8], m_VMultiplicities );
	readTypeOfRealList( args[9], m_UKnots );
	readTypeOfRealList( args[10], m_VKnots );
	m_KnotSpec = IfcKnotType::createObjectFromSTEP( args[11] );
	readRealList2D( args[12], m_WeightsData );
}
void IfcRationalBSplineSurfaceWithKnots::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcBSplineSurfaceWithKnots::getAttributes( vec_attributes );
}
void IfcRationalBSplineSurfaceWithKnots::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcBSplineSurfaceWithKnots::getAttributesInverse( vec_attributes_inverse );
}
void IfcRationalBSplineSurfaceWithKnots::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcBSplineSurfaceWithKnots::setInverseCounterparts( ptr_self_entity );
}
void IfcRationalBSplineSurfaceWithKnots::unlinkFromInverseCounterparts()
{
	IfcBSplineSurfaceWithKnots::unlinkFromInverseCounterparts();
}
