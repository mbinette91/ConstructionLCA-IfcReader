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
#include "include/IfcPresentationLayerAssignment.h"
#include "include/IfcSolidModel.h"
#include "include/IfcStyledItem.h"

// ENTITY IfcSolidModel 
IfcSolidModel::IfcSolidModel() { m_entity_enum = IFCSOLIDMODEL; }
IfcSolidModel::IfcSolidModel( int id ) { m_id = id; m_entity_enum = IFCSOLIDMODEL; }
IfcSolidModel::~IfcSolidModel() {}
shared_ptr<IfcPPObject> IfcSolidModel::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSolidModel> copy_self( new IfcSolidModel() );
	return copy_self;
}
void IfcSolidModel::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSOLIDMODEL" << "(";
	stream << ");";
}
void IfcSolidModel::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSolidModel::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
}
void IfcSolidModel::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcGeometricRepresentationItem::getAttributes( vec_attributes );
}
void IfcSolidModel::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcGeometricRepresentationItem::getAttributesInverse( vec_attributes_inverse );
}
void IfcSolidModel::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcGeometricRepresentationItem::setInverseCounterparts( ptr_self_entity );
}
void IfcSolidModel::unlinkFromInverseCounterparts()
{
	IfcGeometricRepresentationItem::unlinkFromInverseCounterparts();
}
