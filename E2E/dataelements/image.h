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

namespace cv { class Mat; }

namespace E2E
{
	class MDbData;

	class Image : public BaseElement
	{
		void*                               header = nullptr;
		cv::Mat*                            image  = nullptr;

		void readCVImage(std::istream& stream, cv::Mat& image, int cvFormat);

		template<typename Source, typename Dest>
		void readConvertCVImage(std::istream& stream, cv::Mat& image);

		Image(cv::Mat* image, std::istream& stream, MDbData& data);
	public:
		Image(std::istream& stream, MDbData& data);
		~Image();

		static Image* fromJFIF(std::istream& stream, MDbData& data);

		const cv::Mat& getImage() const                         { return *image; }


		std::size_t getImageCols() const;
		std::size_t getImageRows() const;
	};

}

