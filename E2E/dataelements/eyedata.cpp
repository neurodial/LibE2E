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
