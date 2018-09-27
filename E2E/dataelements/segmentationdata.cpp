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


#include "segmentationdata.h"


#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include <iostream>
#include <algorithm>

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
