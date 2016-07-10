#pragma once

#include <istream>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class SegmentationData : public BaseElement
	{
		void*                               header = nullptr;

		std::size_t numElements = 0;
		float*      segmentationData = nullptr;
		int         type = -1;


	public:
		SegmentationData(std::istream& stream, MDbData& data);
		~SegmentationData();

		const float* begin() const                              { return segmentationData; }
		const float* end() const                                { return segmentationData+numElements; }

		std::size_t size() const                                { return numElements; }

		int getType() const                                     { return type; }

	};

}
