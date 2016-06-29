#pragma once

#include <istream>

namespace cv { class Mat; }

namespace E2E
{
	class MDbData;

	class BaseElement
	{
		char*                               rawData       = nullptr;
		std::size_t                         rawDataLength = 0      ;

	public:
		BaseElement(std::istream& stream, MDbData& data);
		virtual ~BaseElement();

		std::size_t getRawDataLength() const                    { return rawDataLength; }
		const char* getRawData()       const                    { return rawData;       }
	};
}

