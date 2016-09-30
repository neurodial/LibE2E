#include "segmentationdata.h"


#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include <iostream>

#include "../e2e_packhelper.h"

namespace
{
	PACKSTRUCT(struct SegHeader
	{
		// uint8_t  undef[0x40 - E2E::MDbData::headerSize];
		uint32_t u0; // always 0
		uint32_t index; // ?
		uint32_t type;  // ?
		uint32_t size;
		uint32_t zeros[5]; // unknow, always zero
	});

}



namespace E2E
{

	SegmentationData::SegmentationData(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(new SegHeader)
	{
		SegHeader* head = reinterpret_cast<SegHeader*>(header);
		StreamHelper::readFStream(stream, head);

		std::size_t numElementsHeader = head->size;
		std::size_t maxElements = (data.getDataLength() - sizeof(SegHeader))/sizeof(float);

		if(numElementsHeader != maxElements)
			std::cerr << "SegmentationData: numElements != maxElements (" << numElementsHeader << " != " << maxElements << ")\n";

		numElements = std::min(numElementsHeader, maxElements);
		type  = head->type;
		index = head->index;

		segmentationData = new float[numElements];
		StreamHelper::readFStream(stream, segmentationData, numElements);

	}

	E2E::SegmentationData::~SegmentationData()
	{
		delete reinterpret_cast<SegHeader*>(header);
		delete[] segmentationData;
	}

}
