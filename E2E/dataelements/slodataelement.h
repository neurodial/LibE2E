#pragma once

#include <istream>

#include "baseelement.h"

namespace cv { class Mat; }

namespace E2E
{
	class MDbData;

	class SloDataElement : public BaseElement
	{
		uint64_t                             winDate;
		float                                transform[6];

	public:
		SloDataElement(std::istream& stream, MDbData& data);
		~SloDataElement();


		uint64_t getDate()        const                          { return winDate;   }
		const float* getTransformData() const                    { return transform; }
	};

}

