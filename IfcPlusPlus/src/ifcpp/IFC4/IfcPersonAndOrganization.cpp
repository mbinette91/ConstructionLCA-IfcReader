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
#include "include/IfcActorRole.h"
#include "include/IfcOrganization.h"
#include "include/IfcPerson.h"
#include "include/IfcPersonAndOrganization.h"

// ENTITY IfcPersonAndOrganization 
IfcPersonAndOrganization::IfcPersonAndOrganization() { m_entity_enum = IFCPERSONANDORGANIZATION; }
IfcPersonAndOrganization::IfcPersonAndOrganization( int id ) { m_id = id; m_entity_enum = IFCPERSONANDORGANIZATION; }
IfcPersonAndOrganization::~IfcPersonAndOrganization() {}
shared_ptr<IfcPPObject> IfcPersonAndOrganization::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPersonAndOrganization> copy_self( new IfcPersonAndOrganization() );
	if( m_ThePerson ) { copy_self->m_ThePerson = dynamic_pointer_cast<IfcPerson>( m_ThePerson->getDeepCopy(options) ); }
	if( m_TheOrganization ) { copy_self->m_TheOrganization = dynamic_pointer_cast<IfcOrganization>( m_TheOrganization->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_Roles.size(); ++ii )
	{
		auto item_ii = m_Roles[ii];
		if( item_ii )
		{
			copy_self->m_Roles.push_back( dynamic_pointer_cast<IfcActorRole>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcPersonAndOrganization::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPERSONANDORGANIZATION" << "(";
	if( m_ThePerson ) { stream << "#" << m_ThePerson->m_id; } else { stream << "$"; }
	stream << ",";
	if( m_TheOrganization ) { stream << "#" << m_TheOrganization->m_id; } else { stream << "$"; }
	stream << ",";
	writeEntityList( stream, m_Roles );
	stream << ");";
}
void IfcPersonAndOrganization::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPersonAndOrganization::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPersonAndOrganization, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_ThePerson, map );
	readEntityReference( args[1], m_TheOrganization, map );
	readEntityReferenceList( args[2], m_Roles, map );
}
void IfcPersonAndOrganization::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "ThePerson", m_ThePerson ) );
	vec_attributes.push_back( std::make_pair( "TheOrganization", m_TheOrganization ) );
	if( m_Roles.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> Roles_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_Roles.begin(), m_Roles.end(), std::back_inserter( Roles_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "Roles", Roles_vec_object ) );
	}
}
void IfcPersonAndOrganization::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
}
void IfcPersonAndOrganization::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	shared_ptr<IfcPersonAndOrganization> ptr_self = dynamic_pointer_cast<IfcPersonAndOrganization>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcPersonAndOrganization::setInverseCounterparts: type mismatch" ); }
	if( m_TheOrganization )
	{
		m_TheOrganization->m_Engages_inverse.push_back( ptr_self );
	}
	if( m_ThePerson )
	{
		m_ThePerson->m_EngagedIn_inverse.push_back( ptr_self );
	}
}
void IfcPersonAndOrganization::unlinkFromInverseCounterparts()
{
	if( m_TheOrganization )
	{
		std::vector<weak_ptr<IfcPersonAndOrganization> >& Engages_inverse = m_TheOrganization->m_Engages_inverse;
		for( auto it_Engages_inverse = Engages_inverse.begin(); it_Engages_inverse != Engages_inverse.end(); )
		{
			shared_ptr<IfcPersonAndOrganization> self_candidate( *it_Engages_inverse );
			if( self_candidate.get() == this )
			{
				it_Engages_inverse= Engages_inverse.erase( it_Engages_inverse );
			}
			else
			{
				++it_Engages_inverse;
			}
		}
	}
	if( m_ThePerson )
	{
		std::vector<weak_ptr<IfcPersonAndOrganization> >& EngagedIn_inverse = m_ThePerson->m_EngagedIn_inverse;
		for( auto it_EngagedIn_inverse = EngagedIn_inverse.begin(); it_EngagedIn_inverse != EngagedIn_inverse.end(); )
		{
			shared_ptr<IfcPersonAndOrganization> self_candidate( *it_EngagedIn_inverse );
			if( self_candidate.get() == this )
			{
				it_EngagedIn_inverse= EngagedIn_inverse.erase( it_EngagedIn_inverse );
			}
			else
			{
				++it_EngagedIn_inverse;
			}
		}
	}
}
