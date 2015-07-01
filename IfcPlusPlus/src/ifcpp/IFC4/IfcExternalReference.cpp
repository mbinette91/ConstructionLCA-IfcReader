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
#include "include/IfcExternalReference.h"
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcIdentifier.h"
#include "include/IfcLabel.h"
#include "include/IfcURIReference.h"

// ENTITY IfcExternalReference 
IfcExternalReference::IfcExternalReference() { m_entity_enum = IFCEXTERNALREFERENCE; }
IfcExternalReference::IfcExternalReference( int id ) { m_id = id; m_entity_enum = IFCEXTERNALREFERENCE; }
IfcExternalReference::~IfcExternalReference() {}
shared_ptr<IfcPPObject> IfcExternalReference::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcExternalReference> copy_self( new IfcExternalReference() );
	if( m_Location ) { copy_self->m_Location = dynamic_pointer_cast<IfcURIReference>( m_Location->getDeepCopy(options) ); }
	if( m_Identification ) { copy_self->m_Identification = dynamic_pointer_cast<IfcIdentifier>( m_Identification->getDeepCopy(options) ); }
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	return copy_self;
}
void IfcExternalReference::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCEXTERNALREFERENCE" << "(";
	if( m_Location ) { m_Location->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Identification ) { m_Identification->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcExternalReference::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcExternalReference::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 3 ){ std::stringstream err; err << "Wrong parameter count for entity IfcExternalReference, expecting 3, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Location = IfcURIReference::createObjectFromSTEP( args[0] );
	m_Identification = IfcIdentifier::createObjectFromSTEP( args[1] );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
}
void IfcExternalReference::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "Location", m_Location ) );
	vec_attributes.push_back( std::make_pair( "Identification", m_Identification ) );
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
}
void IfcExternalReference::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	if( m_ExternalReferenceForResources_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ExternalReferenceForResources_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ExternalReferenceForResources_inverse.size(); ++i )
		{
			if( !m_ExternalReferenceForResources_inverse[i].expired() )
			{
				ExternalReferenceForResources_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcExternalReferenceRelationship>( m_ExternalReferenceForResources_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ExternalReferenceForResources_inverse", ExternalReferenceForResources_inverse_vec_obj ) );
	}
}
void IfcExternalReference::setInverseCounterparts( shared_ptr<IfcPPEntity> )
{
}
void IfcExternalReference::unlinkFromInverseCounterparts()
{
}
