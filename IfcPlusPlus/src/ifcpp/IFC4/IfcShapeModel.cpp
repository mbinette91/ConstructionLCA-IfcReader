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
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcRepresentationContext.h"
#include "include/IfcRepresentationItem.h"
#include "include/IfcRepresentationMap.h"
#include "include/IfcShapeAspect.h"
#include "include/IfcShapeModel.h"

// ENTITY IfcShapeModel 
IfcShapeModel::IfcShapeModel() { m_entity_enum = IFCSHAPEMODEL; }
IfcShapeModel::IfcShapeModel( int id ) { m_id = id; m_entity_enum = IFCSHAPEMODEL; }
IfcShapeModel::~IfcShapeModel() {}
shared_ptr<IfcPPObject> IfcShapeModel::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcShapeModel> copy_self( new IfcShapeModel() );
	if( m_ContextOfItems )
	{
		if( options.shallow_copy_IfcRepresentationContext ) { copy_self->m_ContextOfItems = m_ContextOfItems; }
		else { copy_self->m_ContextOfItems = dynamic_pointer_cast<IfcRepresentationContext>( m_ContextOfItems->getDeepCopy(options) ); }
	}
	if( m_RepresentationIdentifier ) { copy_self->m_RepresentationIdentifier = dynamic_pointer_cast<IfcLabel>( m_RepresentationIdentifier->getDeepCopy(options) ); }
	if( m_RepresentationType ) { copy_self->m_RepresentationType = dynamic_pointer_cast<IfcLabel>( m_RepresentationType->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_Items.size(); ++ii )
	{
		auto item_ii = m_Items[ii];
		if( item_ii )
		{
			copy_self->m_Items.push_back( dynamic_pointer_cast<IfcRepresentationItem>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcShapeModel::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSHAPEMODEL" << "(";
	if( m_ContextOfItems ) { stream << "#" << m_ContextOfItems->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_RepresentationIdentifier ) { m_RepresentationIdentifier->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_RepresentationType ) { m_RepresentationType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_Items );
	stream << ");";
}
void IfcShapeModel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcShapeModel::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 4 ){ std::stringstream err; err << "Wrong parameter count for entity IfcShapeModel, expecting 4, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	readEntityReference( args[0], m_ContextOfItems, map );
	m_RepresentationIdentifier = IfcLabel::createObjectFromSTEP( args[1] );
	m_RepresentationType = IfcLabel::createObjectFromSTEP( args[2] );
	readEntityReferenceList( args[3], m_Items, map );
}
void IfcShapeModel::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcRepresentation::getAttributes( vec_attributes );
}
void IfcShapeModel::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcRepresentation::getAttributesInverse( vec_attributes_inverse );
	if( m_OfShapeAspect_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> OfShapeAspect_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_OfShapeAspect_inverse.size(); ++i )
		{
			if( !m_OfShapeAspect_inverse[i].expired() )
			{
				OfShapeAspect_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcShapeAspect>( m_OfShapeAspect_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "OfShapeAspect_inverse", OfShapeAspect_inverse_vec_obj ) );
	}
}
void IfcShapeModel::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcRepresentation::setInverseCounterparts( ptr_self_entity );
}
void IfcShapeModel::unlinkFromInverseCounterparts()
{
	IfcRepresentation::unlinkFromInverseCounterparts();
}
