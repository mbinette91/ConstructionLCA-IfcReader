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
#include "include/IfcMonetaryUnit.h"

// ENTITY IfcMonetaryUnit 
IfcMonetaryUnit::IfcMonetaryUnit() { m_entity_enum = IFCMONETARYUNIT; }
IfcMonetaryUnit::IfcMonetaryUnit( int id ) { m_id = id; m_entity_enum = IFCMONETARYUNIT; }
IfcMonetaryUnit::~IfcMonetaryUnit() {}
shared_ptr<IfcPPObject> IfcMonetaryUnit::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcMonetaryUnit> copy_self( new IfcMonetaryUnit() );
	if( m_Currency ) { copy_self->m_Currency = dynamic_pointer_cast<IfcLabel>( m_Currency->getDeepCopy(options) ); }
	return copy_self;
}
void IfcMonetaryUnit::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCMONETARYUNIT" << "(";
	if( m_Currency ) { m_Currency->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcMonetaryUnit::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcMonetaryUnit::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcMonetaryUnit, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Currency = IfcLabel::createObjectFromSTEP( args[0] );
}
void IfcMonetaryUnit::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "Currency", m_Currency ) );
}
void IfcMonetaryUnit::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
}
void IfcMonetaryUnit::setInverseCounterparts( shared_ptr<IfcPPEntity> )
{
}
void IfcMonetaryUnit::unlinkFromInverseCounterparts()
{
}
