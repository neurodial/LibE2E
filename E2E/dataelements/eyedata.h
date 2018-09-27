/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
