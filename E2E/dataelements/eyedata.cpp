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


#include "eyedata.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include<iostream>

namespace E2E
{
	EyeData::EyeData(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		if(67 != data.getDataLength() && 68 != data.getDataLength())
		{
			std::cerr << "EyeData: wrong element size " << data.getDataLength() << " != " << "67 || 68\n";
			throw "Wrong Element (Size)";
		}


		StreamHelper::readFStream(stream, &eyeSide       );  // Element 0
		StreamHelper::readFStream(stream, &iop_mmHg      );  // Element 1
		StreamHelper::readFStream(stream, &refraction_dpt);  // Element 2
		StreamHelper::readFStream(stream, &c_curve_mm    );  // Element 3
		StreamHelper::readFStream(stream, &vfieldMean    );  // Element 4
		StreamHelper::readFStream(stream, &vfieldVar     );  // Element 5
		StreamHelper::readFStream(stream, &cylinder_dpt  );  // Element 6
		StreamHelper::readFStream(stream, &axis_deg      );  // Element 7
		StreamHelper::readFStream(stream, &correctiveLens);  // Element 8
		StreamHelper::readFStream(stream, &pupilSize_mm  );  // Element 9

	}

	E2E::EyeData::~EyeData()
	{

	}



}
