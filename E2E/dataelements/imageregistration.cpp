#include "imageregistration.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	ImageRegistration::ImageRegistration(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		if(100 != data.getDataLength())
			throw "Wrong Element";

		StreamHelper::readFStream(stream, values, sizeof(values)/sizeof(values[0]));

	}

	ImageRegistration::~ImageRegistration()
	{

	}



}