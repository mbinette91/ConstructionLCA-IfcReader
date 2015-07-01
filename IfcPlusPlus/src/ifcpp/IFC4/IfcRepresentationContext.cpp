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
#include "include/IfcRepresentation.h"
#include "include/IfcRepresentationContext.h"

// ENTITY IfcRepresentationContext 
IfcRepresentationContext::IfcRepresentationContext() { m_entity_enum = IFCREPRESENTATIONCONTEXT; }
IfcRepresentationContext::IfcRepresentationContext( int id ) { m_id = id; m_entity_enum = IFCREPRESENTATIONCONTEXT; }
IfcRepresentationContext::~IfcRepresentationContext() {}
shared_ptr<IfcPPObject> IfcRepresentationContext::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcRepresentationContext> copy_self( new IfcRepresentationContext() );
	if( m_ContextIdentifier ) { copy_self->m_ContextIdentifier = dynamic_pointer_cast<IfcLabel>( m_ContextIdentifier->getDeepCopy(options) ); }
	if( m_ContextType ) { copy_self->m_ContextType = dynamic_pointer_cast<IfcLabel>( m_ContextType->getDeepCopy(options) ); }
	return copy_self;
}
void IfcRepresentationContext::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCREPRESENTATIONCONTEXT" << "(";
	if( m_ContextIdentifier ) { m_ContextIdentifier->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_ContextType ) { m_ContextType->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcRepresentationContext::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcRepresentationContext::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcRepresentationContext, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_ContextIdentifier = IfcLabel::createObjectFromSTEP( args[0] );
	m_ContextType = IfcLabel::createObjectFromSTEP( args[1] );
}
void IfcRepresentationContext::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	vec_attributes.push_back( std::make_pair( "ContextIdentifier", m_ContextIdentifier ) );
	vec_attributes.push_back( std::make_pair( "ContextType", m_ContextType ) );
}
void IfcRepresentationContext::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	if( m_RepresentationsInContext_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> RepresentationsInContext_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_RepresentationsInContext_inverse.size(); ++i )
		{
			if( !m_RepresentationsInContext_inverse[i].expired() )
			{
				RepresentationsInContext_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRepresentation>( m_RepresentationsInContext_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "RepresentationsInContext_inverse", RepresentationsInContext_inverse_vec_obj ) );
	}
}
void IfcRepresentationContext::setInverseCounterparts( shared_ptr<IfcPPEntity> )
{
}
void IfcRepresentationContext::unlinkFromInverseCounterparts()
{
}
