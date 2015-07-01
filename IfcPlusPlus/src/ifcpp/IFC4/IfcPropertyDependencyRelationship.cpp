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
#include "include/IfcProperty.h"
#include "include/IfcPropertyDependencyRelationship.h"
#include "include/IfcText.h"

// ENTITY IfcPropertyDependencyRelationship 
IfcPropertyDependencyRelationship::IfcPropertyDependencyRelationship() { m_entity_enum = IFCPROPERTYDEPENDENCYRELATIONSHIP; }
IfcPropertyDependencyRelationship::IfcPropertyDependencyRelationship( int id ) { m_id = id; m_entity_enum = IFCPROPERTYDEPENDENCYRELATIONSHIP; }
IfcPropertyDependencyRelationship::~IfcPropertyDependencyRelationship() {}
shared_ptr<IfcPPObject> IfcPropertyDependencyRelationship::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPropertyDependencyRelationship> copy_self( new IfcPropertyDependencyRelationship() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	if( m_DependingProperty ) { copy_self->m_DependingProperty = dynamic_pointer_cast<IfcProperty>( m_DependingProperty->getDeepCopy(options) ); }
	if( m_DependantProperty ) { copy_self->m_DependantProperty = dynamic_pointer_cast<IfcProperty>( m_DependantProperty->getDeepCopy(options) ); }
	if( m_Expression ) { copy_self->m_Expression = dynamic_pointer_cast<IfcText>( m_Expression->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPropertyDependencyRelationship::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPROPERTYDEPENDENCYRELATIONSHIP" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_DependingProperty ) { stream << "#" << m_DependingProperty->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_DependantProperty ) { stream << "#" << m_DependantProperty->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_Expression ) { m_Expression->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcPropertyDependencyRelationship::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPropertyDependencyRelationship::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 5 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPropertyDependencyRelationship, expecting 5, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_Description = IfcText::createObjectFromSTEP( args[1] );
	readEntityReference( args[2], m_DependingProperty, map );
	readEntityReference( args[3], m_DependantProperty, map );
	m_Expression = IfcText::createObjectFromSTEP( args[4] );
}
void IfcPropertyDependencyRelationship::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcResourceLevelRelationship::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "DependingProperty", m_DependingProperty ) );
	vec_attributes.push_back( std::make_pair( "DependantProperty", m_DependantProperty ) );
	vec_attributes.push_back( std::make_pair( "Expression", m_Expression ) );
}
void IfcPropertyDependencyRelationship::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcResourceLevelRelationship::getAttributesInverse( vec_attributes_inverse );
}
void IfcPropertyDependencyRelationship::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcResourceLevelRelationship::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcPropertyDependencyRelationship> ptr_self = dynamic_pointer_cast<IfcPropertyDependencyRelationship>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcPropertyDependencyRelationship::setInverseCounterparts: type mismatch" ); }
	if( m_DependantProperty )
	{
		m_DependantProperty->m_PropertyDependsOn_inverse.push_back( ptr_self );
	}
	if( m_DependingProperty )
	{
		m_DependingProperty->m_PropertyForDependance_inverse.push_back( ptr_self );
	}
}
void IfcPropertyDependencyRelationship::unlinkFromInverseCounterparts()
{
	IfcResourceLevelRelationship::unlinkFromInverseCounterparts();
	if( m_DependantProperty )
	{
		std::vector<weak_ptr<IfcPropertyDependencyRelationship> >& PropertyDependsOn_inverse = m_DependantProperty->m_PropertyDependsOn_inverse;
		for( auto it_PropertyDependsOn_inverse = PropertyDependsOn_inverse.begin(); it_PropertyDependsOn_inverse != PropertyDependsOn_inverse.end(); )
		{
			shared_ptr<IfcPropertyDependencyRelationship> self_candidate( *it_PropertyDependsOn_inverse );
			if( self_candidate.get() == this )
			{
				it_PropertyDependsOn_inverse= PropertyDependsOn_inverse.erase( it_PropertyDependsOn_inverse );
			}
			else
			{
				++it_PropertyDependsOn_inverse;
			}
		}
	}
	if( m_DependingProperty )
	{
		std::vector<weak_ptr<IfcPropertyDependencyRelationship> >& PropertyForDependance_inverse = m_DependingProperty->m_PropertyForDependance_inverse;
		for( auto it_PropertyForDependance_inverse = PropertyForDependance_inverse.begin(); it_PropertyForDependance_inverse != PropertyForDependance_inverse.end(); )
		{
			shared_ptr<IfcPropertyDependencyRelationship> self_candidate( *it_PropertyForDependance_inverse );
			if( self_candidate.get() == this )
			{
				it_PropertyForDependance_inverse= PropertyForDependance_inverse.erase( it_PropertyForDependance_inverse );
			}
			else
			{
				++it_PropertyForDependance_inverse;
			}
		}
	}
}
