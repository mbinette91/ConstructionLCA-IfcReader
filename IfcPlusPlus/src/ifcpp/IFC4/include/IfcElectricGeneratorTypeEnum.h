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

// TYPE IfcElectricGeneratorTypeEnum = ENUMERATION OF	(CHP	,ENGINEGENERATOR	,STANDALONE	,USERDEFINED	,NOTDEFINED);
class IFCPP_EXPORT IfcElectricGeneratorTypeEnum : virtual public IfcPPObject
{
public:
	enum IfcElectricGeneratorTypeEnumEnum
	{
		ENUM_CHP,
		ENUM_ENGINEGENERATOR,
		ENUM_STANDALONE,
		ENUM_USERDEFINED,
		ENUM_NOTDEFINED
	};

	IfcElectricGeneratorTypeEnum();
	IfcElectricGeneratorTypeEnum( IfcElectricGeneratorTypeEnumEnum e ) { m_enum = e; }
	~IfcElectricGeneratorTypeEnum();
	virtual const char* className() const { return "IfcElectricGeneratorTypeEnum"; }
	virtual shared_ptr<IfcPPObject> getDeepCopy( IfcPPCopyOptions& options );
	virtual void getStepParameter( std::stringstream& stream, bool is_select_type = false ) const;
	static shared_ptr<IfcElectricGeneratorTypeEnum> createObjectFromSTEP( const std::wstring& arg );
	IfcElectricGeneratorTypeEnumEnum m_enum;
};

