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
#include "include/IfcExternalReferenceRelationship.h"
#include "include/IfcLabel.h"
#include "include/IfcPhysicalComplexQuantity.h"
#include "include/IfcPhysicalQuantity.h"
#include "include/IfcText.h"

// ENTITY IfcPhysicalComplexQuantity 
IfcPhysicalComplexQuantity::IfcPhysicalComplexQuantity() { m_entity_enum = IFCPHYSICALCOMPLEXQUANTITY; }
IfcPhysicalComplexQuantity::IfcPhysicalComplexQuantity( int id ) { m_id = id; m_entity_enum = IFCPHYSICALCOMPLEXQUANTITY; }
IfcPhysicalComplexQuantity::~IfcPhysicalComplexQuantity() {}
shared_ptr<IfcPPObject> IfcPhysicalComplexQuantity::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPhysicalComplexQuantity> copy_self( new IfcPhysicalComplexQuantity() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_HasQuantities.size(); ++ii )
	{
		auto item_ii = m_HasQuantities[ii];
		if( item_ii )
		{
			copy_self->m_HasQuantities.push_back( dynamic_pointer_cast<IfcPhysicalQuantity>(item_ii->getDeepCopy(options) ) );
		}
	}
	if( m_Discrimination ) { copy_self->m_Discrimination = dynamic_pointer_cast<IfcLabel>( m_Discrimination->getDeepCopy(options) ); }
	if( m_Quality ) { copy_self->m_Quality = dynamic_pointer_cast<IfcLabel>( m_Quality->getDeepCopy(options) ); }
	if( m_Usage ) { copy_self->m_Usage = dynamic_pointer_cast<IfcLabel>( m_Usage->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPhysicalComplexQuantity::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPHYSICALCOMPLEXQUANTITY" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	writeEntityList( stream, m_HasQuantities );
	stream << ",";
	if( m_Discrimination ) { m_Discrimination->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Quality ) { m_Quality->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	if( m_Usage ) { m_Usage->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcPhysicalComplexQuantity::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPhysicalComplexQuantity::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 6 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPhysicalComplexQuantity, expecting 6, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	m_Description = IfcText::createObjectFromSTEP( args[1] );
	readEntityReferenceList( args[2], m_HasQuantities, map );
	m_Discrimination = IfcLabel::createObjectFromSTEP( args[3] );
	m_Quality = IfcLabel::createObjectFromSTEP( args[4] );
	m_Usage = IfcLabel::createObjectFromSTEP( args[5] );
}
void IfcPhysicalComplexQuantity::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPhysicalQuantity::getAttributes( vec_attributes );
	if( m_HasQuantities.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> HasQuantities_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_HasQuantities.begin(), m_HasQuantities.end(), std::back_inserter( HasQuantities_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "HasQuantities", HasQuantities_vec_object ) );
	}
	vec_attributes.push_back( std::make_pair( "Discrimination", m_Discrimination ) );
	vec_attributes.push_back( std::make_pair( "Quality", m_Quality ) );
	vec_attributes.push_back( std::make_pair( "Usage", m_Usage ) );
}
void IfcPhysicalComplexQuantity::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPhysicalQuantity::getAttributesInverse( vec_attributes_inverse );
}
void IfcPhysicalComplexQuantity::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPhysicalQuantity::setInverseCounterparts( ptr_self_entity );
	shared_ptr<IfcPhysicalComplexQuantity> ptr_self = dynamic_pointer_cast<IfcPhysicalComplexQuantity>( ptr_self_entity );
	if( !ptr_self ) { throw IfcPPException( "IfcPhysicalComplexQuantity::setInverseCounterparts: type mismatch" ); }
	for( size_t i=0; i<m_HasQuantities.size(); ++i )
	{
		if( m_HasQuantities[i] )
		{
			m_HasQuantities[i]->m_PartOfComplex_inverse.push_back( ptr_self );
		}
	}
}
void IfcPhysicalComplexQuantity::unlinkFromInverseCounterparts()
{
	IfcPhysicalQuantity::unlinkFromInverseCounterparts();
	for( size_t i=0; i<m_HasQuantities.size(); ++i )
	{
		if( m_HasQuantities[i] )
		{
			std::vector<weak_ptr<IfcPhysicalComplexQuantity> >& PartOfComplex_inverse = m_HasQuantities[i]->m_PartOfComplex_inverse;
			for( auto it_PartOfComplex_inverse = PartOfComplex_inverse.begin(); it_PartOfComplex_inverse != PartOfComplex_inverse.end(); )
			{
				shared_ptr<IfcPhysicalComplexQuantity> self_candidate( *it_PartOfComplex_inverse );
				if( self_candidate.get() == this )
				{
					it_PartOfComplex_inverse= PartOfComplex_inverse.erase( it_PartOfComplex_inverse );
				}
				else
				{
					++it_PartOfComplex_inverse;
				}
			}
		}
	}
}
