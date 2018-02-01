#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class EyeData : public BaseElement
	{
		char     eyeSide;
		double   c_curve_mm;
		double   refraction_dpt;
		double   cylinder_dpt;
		double   axis_deg;
		double   pupilSize_mm;
		double   iop_mmHg;
		double   vfieldMean;
		double   vfieldVar;
		uint16_t correctiveLens;

	public:
		EyeData(std::istream& stream, MDbData& data);
		virtual ~EyeData();

		char     getEyeSide       ()                              const { return eyeSide       ; }
		double   getC_curve_mm    ()                              const { return c_curve_mm    ; }
		double   getRefraction_dpt()                              const { return refraction_dpt; }
		double   getCylinder_dpt  ()                              const { return cylinder_dpt  ; }
		double   getAxis_deg      ()                              const { return axis_deg      ; }
		double   getPupilSize_mm  ()                              const { return pupilSize_mm  ; }
		double   getIop_mmHg      ()                              const { return iop_mmHg      ; }
		double   getVfieldMean    ()                              const { return vfieldMean    ; }
		double   getVfieldVar     ()                              const { return vfieldVar     ; }
		uint16_t getCorrectiveLens()                              const { return correctiveLens; }

	};

}
