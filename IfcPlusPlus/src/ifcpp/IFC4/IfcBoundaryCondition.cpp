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
#include "include/IfcBoundaryCondition.h"
#include "include/IfcLabel.h"

// ENTITY IfcBoundaryCondition 
IfcBoundaryCondition::IfcBoundaryCondition() { m_entity_enum = IFCBOUNDARYCONDITION; }
IfcBoundaryCondition::IfcBoundaryCondition( int id ) { m_id = id; m_entity_enum = IFCBOUNDARYCONDITION; }
IfcBoundaryCondition::~IfcBoundaryCondition() {}
shared_ptr<IfcPPObject> IfcBoundaryCondition::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcBoundaryCondition> copy_self( new IfcBoundaryCondition() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	return copy_self;
}
void IfcBoundaryCondition::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCBOUNDARYCONDITION" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcBoundaryCondition::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcBoundaryCondition::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcBoundaryCondition, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
}
void IfcBoundaryCondition::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
}
void IfcBoundaryCondition::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
}
void IfcBoundaryCondition::setInverseCounterparts( shared_ptr<IfcPPEntity> )
{
}
void IfcBoundaryCondition::unlinkFromInverseCounterparts()
{
}
