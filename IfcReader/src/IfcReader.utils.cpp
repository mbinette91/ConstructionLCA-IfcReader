/*
* This file contains the function `ifcValue2str` which transforms an IfvValue object to it's wstring representation.
* There has to be a better way, but this does the trick for now...
*/
#include <iostream>
#include <ifcpp/IFC4/include/IfcLabel.h>
#include <ifcpp/IFC4/include/IfcValue.h>
#include <ifcpp/IFC4/include/IfcReal.h>
#include <ifcpp/IFC4/include/IfcInteger.h>
#include <ifcpp/IFC4/include/IfcBoolean.h>
#include <ifcpp/IFC4/include/IfcAmountOfSubstanceMeasure.h>
#include <ifcpp/IFC4/include/IfcAreaMeasure.h>
#include <ifcpp/IFC4/include/IfcIdentifier.h>
#include <ifcpp/IFC4/include/IfcComplexNumber.h>
#include <ifcpp/IFC4/include/IfcContextDependentMeasure.h>
#include <ifcpp/IFC4/include/IfcCountMeasure.h>
#include <ifcpp/IFC4/include/IfcDescriptiveMeasure.h>
#include <ifcpp/IFC4/include/IfcElectricCurrentMeasure.h>
#include <ifcpp/IFC4/include/IfcLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcLuminousIntensityMeasure.h>
#include <ifcpp/IFC4/include/IfcMassMeasure.h>
#include <ifcpp/IFC4/include/IfcNonNegativeLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcNormalisedRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcNumericMeasure.h>
#include <ifcpp/IFC4/include/IfcParameterValue.h>
#include <ifcpp/IFC4/include/IfcPlaneAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcPositiveLengthMeasure.h>
#include <ifcpp/IFC4/include/IfcPositivePlaneAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcPositiveRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcRatioMeasure.h>
#include <ifcpp/IFC4/include/IfcSolidAngleMeasure.h>
#include <ifcpp/IFC4/include/IfcThermodynamicTemperatureMeasure.h>
#include <ifcpp/IFC4/include/IfcTimeMeasure.h>
#include <ifcpp/IFC4/include/IfcVolumeMeasure.h>

namespace IfcReader
{ //Anonymous namespace. Thread safe.
#define SEQ_FOR_EACH(D, ...)                                        \
		if(bool c = false) ; else                                       \
			for(boost::remove_reference<boost::function_traits<void(D)> \
					::arg1_type>::type _t[] = __VA_ARGS__;              \
				!c; c = true)                                           \
				BOOST_FOREACH(D, _t)

	std::wstring IfcValue2wstr(shared_ptr<IfcValue> ifc_value){
		std::wstring val = L"";

		if (shared_ptr<IfcLabel> v = dynamic_pointer_cast<IfcLabel>(ifc_value))
			val = v->m_value;
#define CheckTypeWithCast(n) else if (shared_ptr<n> v = dynamic_pointer_cast<n>(ifc_value)) val = std::to_wstring(v->m_value);
#define CheckTypeWithoutCast(n) else if (shared_ptr<n> v = dynamic_pointer_cast<n>(ifc_value)) val = (v->m_value);
		CheckTypeWithCast(IfcReal)
		CheckTypeWithCast(IfcInteger)
		CheckTypeWithCast(IfcBoolean)
		CheckTypeWithCast(IfcAmountOfSubstanceMeasure)
		CheckTypeWithCast(IfcAreaMeasure)
		CheckTypeWithoutCast(IfcIdentifier)
		// CheckType(IfcComplexNumber) //TO-DO: Special case, how to serialize it in the Database ?
		CheckTypeWithCast(IfcContextDependentMeasure)
		CheckTypeWithCast(IfcCountMeasure)
		CheckTypeWithoutCast(IfcDescriptiveMeasure)
		CheckTypeWithCast(IfcElectricCurrentMeasure)
		CheckTypeWithCast(IfcLengthMeasure)
		CheckTypeWithCast(IfcLuminousIntensityMeasure)
		CheckTypeWithCast(IfcMassMeasure)
		CheckTypeWithCast(IfcNonNegativeLengthMeasure)
		CheckTypeWithCast(IfcNormalisedRatioMeasure)
		CheckTypeWithCast(IfcNumericMeasure)
		CheckTypeWithCast(IfcParameterValue)
		CheckTypeWithCast(IfcPlaneAngleMeasure)
		CheckTypeWithCast(IfcPositiveLengthMeasure)
		CheckTypeWithCast(IfcPositivePlaneAngleMeasure)
		CheckTypeWithCast(IfcPositiveRatioMeasure)
		CheckTypeWithCast(IfcRatioMeasure)
		CheckTypeWithCast(IfcSolidAngleMeasure)
		CheckTypeWithCast(IfcThermodynamicTemperatureMeasure)
		CheckTypeWithCast(IfcTimeMeasure)
		CheckTypeWithCast(IfcVolumeMeasure)
		else
			std::cout << "ERROR ([IfcReader.utils.cpp]::IfcValue2wstr): Cannot find suitable conversion for " << ifc_value->className() << std::endl;

		return val;
	}
}