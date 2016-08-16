
#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class ImageRegistration : public BaseElement
	{
	public:
		ImageRegistration(std::istream& stream, MDbData& data);
		virtual ~ImageRegistration();

		float values[25];

	};

}
