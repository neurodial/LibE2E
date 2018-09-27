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

#include <istream>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class SegmentationData : public BaseElement
	{
		void*                               header = nullptr;

		float*      segmentationData = nullptr;
		int         type = -1;
		std::size_t numElements = 0;
		int         index = -1;


	public:
		typedef const float* pointer;

		SegmentationData(std::istream& stream, MDbData& data);
		~SegmentationData();

		pointer begin() const                              { return segmentationData; }
		pointer end() const                                { return segmentationData+numElements; }

		std::size_t size() const                                { return numElements; }

		int getSegType() const                                  { return type; }
		int getSegIndex() const                                 { return index; }

	};

}
