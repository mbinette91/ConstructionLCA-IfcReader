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
#include "include/IfcPreDefinedCurveFont.h"

// ENTITY IfcPreDefinedCurveFont 
IfcPreDefinedCurveFont::IfcPreDefinedCurveFont() { m_entity_enum = IFCPREDEFINEDCURVEFONT; }
IfcPreDefinedCurveFont::IfcPreDefinedCurveFont( int id ) { m_id = id; m_entity_enum = IFCPREDEFINEDCURVEFONT; }
IfcPreDefinedCurveFont::~IfcPreDefinedCurveFont() {}
shared_ptr<IfcPPObject> IfcPreDefinedCurveFont::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcPreDefinedCurveFont> copy_self( new IfcPreDefinedCurveFont() );
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	return copy_self;
}
void IfcPreDefinedCurveFont::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCPREDEFINEDCURVEFONT" << "(";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ");";
}
void IfcPreDefinedCurveFont::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcPreDefinedCurveFont::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 1 ){ std::stringstream err; err << "Wrong parameter count for entity IfcPreDefinedCurveFont, expecting 1, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_Name = IfcLabel::createObjectFromSTEP( args[0] );
}
void IfcPreDefinedCurveFont::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcPreDefinedItem::getAttributes( vec_attributes );
}
void IfcPreDefinedCurveFont::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcPreDefinedItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcPreDefinedCurveFont::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcPreDefinedItem::setInverseCounterparts( ptr_self_entity );
}
void IfcPreDefinedCurveFont::unlinkFromInverseCounterparts()
{
	IfcPreDefinedItem::unlinkFromInverseCounterparts();
}
