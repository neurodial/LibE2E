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


#include "image.h"

// #include <ostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>
// #include <opencv2/imgcodecs.hpp>

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"
#include "../datadict/dictentryrawdata.h"

#include "../e2e_packhelper.h"

#include<iostream>
#include<memory>

namespace
{
	PACKSTRUCT(struct ImageHeader
	{
		uint8_t  undef[0x40 - E2E::DictEntryRawData::dataEntryHeaderSize];
		uint8_t  u1;
		uint8_t  u2;
		uint8_t  type;
		uint8_t  u4;
		uint32_t u5;
		uint32_t breite;
		uint32_t hoehe;
	});
}

namespace E2E
{

	Image::Image(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(new ImageHeader)
	, image (new cv::Mat)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);
		StreamHelper::readFStream(stream, head);

		switch(head->type)
		{
			case 1:
				readCVImage(stream, *image, CV_8UC1);
				break;
			case 32:
				readCVImage(stream, *image, CV_16UC1);
				break;
			default:
				if(data.getSubId() == 0) // SLO
					readCVImage(stream, *image, CV_8UC1);
				else // BScan
					readCVImage(stream, *image, CV_16UC1);
					// readConvertCVImage<ufloat16_t, float>(stream, *image);
		}

	}

	Image::Image(cv::Mat* image, std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(nullptr)
	, image(image)
	{

	}


	Image::~Image()
	{
		delete reinterpret_cast<ImageHeader*>(header);
		delete image;
	}


	void Image::readCVImage(std::istream& stream, cv::Mat& image, int cvFormat)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);

		image = cv::Mat(head->breite, head->hoehe, cvFormat);

		std::size_t num = head->breite*head->hoehe;
		std::size_t pixelBytes = num*image.elemSize();
		std::size_t bytes = getNumBytes() - sizeof(ImageHeader);

		if(pixelBytes != bytes)
		{
			std::cerr << "Image::readCVImage: pixelBytes != bytes\n";
			pixelBytes = std::min(pixelBytes, bytes);
		}

		stream.read(reinterpret_cast<char*>(image.data), pixelBytes);
	}


	template<typename Source, typename Dest>
	void Image::readConvertCVImage(std::istream& stream, cv::Mat& image)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);

		image = cv::Mat(head->breite, head->hoehe, cv::DataType<Dest>::type);

		std::size_t sizeField = head->breite *head->hoehe;
		std::unique_ptr<Source> tempImage(new Source[sizeField]);  // p1 owns Foo

		Dest*   imgIt  = image.ptr<Dest>();
		Source* tempIt = tempImage.get();
		StreamHelper::readFStream(stream, tempIt, sizeField);

		for(std::size_t i = 0; i<sizeField; ++i)
		{
			*imgIt = static_cast<Dest>(*tempIt);
			++imgIt;
			++tempIt;
		}
	}


	Image* Image::fromJFIF(std::istream& stream, MDbData& data)
	{
		int         readLength = static_cast<int>(data.getDataLength()); // TODO
		std::size_t readAdress = data.getDataAdress() + 60 + 0x10;

		cv::Mat inputArray(readLength, 1, CV_8UC1);

		stream.seekg(readAdress);
		stream.read(reinterpret_cast<char*>(inputArray.data), readLength);

		cv::Mat* image = new cv::Mat;
		*image = cv::imdecode(inputArray, cv::IMREAD_ANYDEPTH);
		return new Image(image, stream, data);
	}


	std::size_t Image::getImageCols() const
	{
		return image->cols;
	}

	std::size_t Image::getImageRows() const
	{
		return image->rows;
	}

}
