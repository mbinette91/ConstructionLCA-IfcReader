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
#include "include/IfcLabel.h"
#include "include/IfcLengthMeasure.h"
#include "include/IfcPlaneAngleMeasure.h"
#include "include/IfcStructuralLoadSingleDisplacement.h"

// ENTITY IfcStructuralLoadSingleDisplacement 
IfcStructuralLoadSingleDisplacement::IfcStructuralLoadSingleDisplacement() { m_entity_enum = IFCSTRUCTURALLOADSINGLEDISPLACEMENT; }
IfcStructuralLoadSingleDisplacement::IfcStructuralLoadSingleDisplacement( int id ) { m_id = id; m_entity_enum = IFCSTRUCTURALLOADSINGLEDISPLACEMENT; }
IfcStructuralLoadSingleDisplacement::~IfcStructuralLoadSingleDisplacement() {}
shared_ptr<IfcPPObject> IfcStructuralLoadSingleDisplacement::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcStructuralLoadSingleDisplacement> copy_self( new IfcStructuralLoadSingleDisplacement() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_DisplacementX ) { copy_self->m_DisplacementX = dynamic_pointer_cast<IfcLengthMeasure>( m_DisplacementX->getDeepCopy(options) ); }
	if( m_DisplacementY ) { copy_self->m_DisplacementY = dynamic_pointer_cast<IfcLengthMeasure>( m_DisplacementY->getDeepCopy(options) ); }
	if( m_DisplacementZ ) { copy_self->m_DisplacementZ = dynamic_pointer_cast<IfcLengthMeasure>( m_DisplacementZ->getDeepCopy(options) ); }
	if( m_RotationalDisplacementRX ) { copy_self->m_RotationalDisplacementRX = dynamic_pointer_cast<IfcPlaneAngleMeasure>( m_RotationalDisplacementRX->getDeepCopy(options) ); }
	if( m_RotationalDisplacementRY ) { copy_self->m_RotationalDisplacementRY = dynamic_pointer_cast<IfcPlaneAngleMeasure>( m_RotationalDisplacementRY->getDeepCopy(options) ); }
	if( m_RotationalDisplacementRZ ) { copy_self->m_RotationalDisplacementRZ = dynamic_pointer_cast<IfcPlaneAngleMeasure>( m_RotationalDisplacementRZ->getDeepCopy(options) ); }
	return copy_self;
}
void IfcStructuralLoadSingleDisplacement::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSTRUCTURALLOADSINGLEDISPLACEMENT" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_DisplacementX ) { m_DisplacementX->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_DisplacementY ) { m_DisplacementY->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_DisplacementZ ) { m_DisplacementZ->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_RotationalDisplacementRX ) { m_RotationalDisplacementRX->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_RotationalDisplacementRY ) { m_RotationalDisplacementRY->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_RotationalDisplacementRZ ) { m_RotationalDisplacementRZ->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcStructuralLoadSingleDisplacement::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcStructuralLoadSingleDisplacement::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 7 ){ std::stringstream err; err << "Wrong parameter count for entity IfcStructuralLoadSingleDisplacement, expecting 7, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_DisplacementX = IfcLengthMeasure::createObjectFromSTEP( args[1] );
	m_DisplacementY = IfcLengthMeasure::createObjectFromSTEP( args[2] );
	m_DisplacementZ = IfcLengthMeasure::createObjectFromSTEP( args[3] );
	m_RotationalDisplacementRX = IfcPlaneAngleMeasure::createObjectFromSTEP( args[4] );
	m_RotationalDisplacementRY = IfcPlaneAngleMeasure::createObjectFromSTEP( args[5] );
	m_RotationalDisplacementRZ = IfcPlaneAngleMeasure::createObjectFromSTEP( args[6] );
}
void IfcStructuralLoadSingleDisplacement::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcStructuralLoadStatic::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "DisplacementX", m_DisplacementX ) );
	vec_attributes.push_back( std::make_pair( "DisplacementY", m_DisplacementY ) );
	vec_attributes.push_back( std::make_pair( "DisplacementZ", m_DisplacementZ ) );
	vec_attributes.push_back( std::make_pair( "RotationalDisplacementRX", m_RotationalDisplacementRX ) );
	vec_attributes.push_back( std::make_pair( "RotationalDisplacementRY", m_RotationalDisplacementRY ) );
	vec_attributes.push_back( std::make_pair( "RotationalDisplacementRZ", m_RotationalDisplacementRZ ) );
}
void IfcStructuralLoadSingleDisplacement::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcStructuralLoadStatic::getAttributesInverse( vec_attributes_inverse );
}
void IfcStructuralLoadSingleDisplacement::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcStructuralLoadStatic::setInverseCounterparts( ptr_self_entity );
}
void IfcStructuralLoadSingleDisplacement::unlinkFromInverseCounterparts()
{
	IfcStructuralLoadStatic::unlinkFromInverseCounterparts();
}
