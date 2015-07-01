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
#include "include/IfcBoundaryFaceCondition.h"
#include "include/IfcLabel.h"
#include "include/IfcModulusOfSubgradeReactionSelect.h"

// ENTITY IfcBoundaryFaceCondition 
IfcBoundaryFaceCondition::IfcBoundaryFaceCondition() { m_entity_enum = IFCBOUNDARYFACECONDITION; }
IfcBoundaryFaceCondition::IfcBoundaryFaceCondition( int id ) { m_id = id; m_entity_enum = IFCBOUNDARYFACECONDITION; }
IfcBoundaryFaceCondition::~IfcBoundaryFaceCondition() {}
shared_ptr<IfcPPObject> IfcBoundaryFaceCondition::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBoundaryFaceCondition> copy_self( new IfcBoundaryFaceCondition() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_TranslationalStiffnessByAreaX ) { copy_self->m_TranslationalStiffnessByAreaX = dynamic_pointer_cast<IfcModulusOfSubgradeReactionSelect>( m_TranslationalStiffnessByAreaX->getDeepCopy(options) ); }
	if( m_TranslationalStiffnessByAreaY ) { copy_self->m_TranslationalStiffnessByAreaY = dynamic_pointer_cast<IfcModulusOfSubgradeReactionSelect>( m_TranslationalStiffnessByAreaY->getDeepCopy(options) ); }
	if( m_TranslationalStiffnessByAreaZ ) { copy_self->m_TranslationalStiffnessByAreaZ = dynamic_pointer_cast<IfcModulusOfSubgradeReactionSelect>( m_TranslationalStiffnessByAreaZ->getDeepCopy(options) ); }
	return copy_self;
}
void IfcBoundaryFaceCondition::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCBOUNDARYFACECONDITION" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_TranslationalStiffnessByAreaX ) { m_TranslationalStiffnessByAreaX->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_TranslationalStiffnessByAreaY ) { m_TranslationalStiffnessByAreaY->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ",";
	if( m_TranslationalStiffnessByAreaZ ) { m_TranslationalStiffnessByAreaZ->getStepParameter( stream, true ); } else { stream << "$" ; }
	stream << ");";
}
void IfcBoundaryFaceCondition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBoundaryFaceCondition::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcBoundaryFaceCondition, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_TranslationalStiffnessByAreaX = IfcModulusOfSubgradeReactionSelect::createObjectFromSTEP( args[1], map );
	m_TranslationalStiffnessByAreaY = IfcModulusOfSubgradeReactionSelect::createObjectFromSTEP( args[2], map );
	m_TranslationalStiffnessByAreaZ = IfcModulusOfSubgradeReactionSelect::createObjectFromSTEP( args[3], map );
}
void IfcBoundaryFaceCondition::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcBoundaryCondition::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "TranslationalStiffnessByAreaX", m_TranslationalStiffnessByAreaX ) );
	vec_attributes.push_back( std::make_pair( "TranslationalStiffnessByAreaY", m_TranslationalStiffnessByAreaY ) );
	vec_attributes.push_back( std::make_pair( "TranslationalStiffnessByAreaZ", m_TranslationalStiffnessByAreaZ ) );
}
void IfcBoundaryFaceCondition::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcBoundaryCondition::getAttributesInverse( vec_attributes_inverse );
}
void IfcBoundaryFaceCondition::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcBoundaryCondition::setInverseCounterparts( ptr_self_entity );
}
void IfcBoundaryFaceCondition::unlinkFromInverseCounterparts()
{
	IfcBoundaryCondition::unlinkFromInverseCounterparts();
}
