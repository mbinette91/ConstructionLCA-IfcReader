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

#pragma once
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include "ifcpp/model/shared_ptr.h"
#include "ifcpp/model/IfcPPObject.h"
#include "ifcpp/model/IfcPPGlobal.h"

// TYPE IfcWallTypeEnum = ENUMERATION OF	(MOVABLE	,PARAPET	,PARTITIONING	,PLUMBINGWALL	,SHEAR	,SOLIDWALL	,STANDARD	,POLYGONAL	,ELEMENTEDWALL	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcWallTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcWallTypeEnumEnum
	{
		ENUM_MOVABLE,
		ENUM_PARAPET,
		ENUM_PARTITIONING,
		ENUM_PLUMBINGWALL,
		ENUM_SHEAR,
		ENUM_SOLIDWALL,
		ENUM_STANDARD,
		ENUM_POLYGONAL,
		ENUM_ELEMENTEDWALL,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcWallTypeEnum();
	IfcWallTypeEnum( IfcWallTypeEnumEnum e ) { m_enum = e; }
	~IfcWallTypeEnum();
	virtual const char* className() const { return "IfcWallTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcWallTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcWallTypeEnumEnum m_enum;
};

