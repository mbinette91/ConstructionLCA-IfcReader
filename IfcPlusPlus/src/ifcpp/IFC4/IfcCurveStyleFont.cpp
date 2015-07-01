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
#include "include/IfcCurveStyleFont.h"
#include "include/IfcCurveStyleFontPattern.h"
#include "include/IfcLabel.h"

// ENTITY IfcCurveStyleFont 
IfcCurveStyleFont::IfcCurveStyleFont() { m_entity_enum = IFCCURVESTYLEFONT; }
IfcCurveStyleFont::IfcCurveStyleFont( int id ) { m_id = id; m_entity_enum = IFCCURVESTYLEFONT; }
IfcCurveStyleFont::~IfcCurveStyleFont() {}
shared_ptr<IfcPPObject> IfcCurveStyleFont::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcCurveStyleFont> copy_self( new IfcCurveStyleFont() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	for( size_t ii=0; ii<m_PatternList.size(); ++ii )
	{
		auto item_ii = m_PatternList[ii];
		if( item_ii )
		{
			copy_self->m_PatternList.push_back( dynamic_pointer_cast<IfcCurveStyleFontPattern>(item_ii->getDeepCopy(options) ) );
		}
	}
	return copy_self;
}
void IfcCurveStyleFont::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCCURVESTYLEFONT" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "$"; }
	stream << ",";
	writeEntityList( stream, m_PatternList );
	stream << ");";
}
void IfcCurveStyleFont::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcCurveStyleFont::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 2 ){ std::stringstream err; err << "Wrong parameter count for entity IfcCurveStyleFont, expecting 2, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
	readEntityReferenceList( args[1], m_PatternList, map );
}
void IfcCurveStyleFont::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPresentationItem::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "Name", m_Name ) );
	if( m_PatternList.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> PatternList_vec_object( new  IfcPPAttributeObjectVector() );
		std::copy( m_PatternList.begin(), m_PatternList.end(), std::back_inserter( PatternList_vec_object->m_vec ) );
		vec_attributes.push_back( std::make_pair( "PatternList", PatternList_vec_object ) );
	}
}
void IfcCurveStyleFont::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcCurveStyleFont::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcCurveStyleFont::unlinkFromInverseCounterparts()
{
	IfcPresentationItem::unlinkFromInverseCounterparts();
}
