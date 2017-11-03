#include "patimage_2335.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"
#include "../datadict/dictentryrawdata.h"

#include "../e2e_packhelper.h"

#include<iostream>

namespace
{
	PACKSTRUCT(struct ImageHeader
	{
		uint8_t  undef1[0x1C];
		uint8_t  type;
		uint8_t  undef2[0x23];
		uint32_t breite   ;
		uint32_t hoehe    ;
		uint32_t imgOffset;
	});
}

namespace E2E
{

	PatImage_2335::PatImage_2335(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	, header(new ImageHeader)
	, image (new cv::Mat)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);
		StreamHelper::readFStream(stream, head);

		std::size_t num = head->breite*head->hoehe;
		std::size_t pixelBytes = num*sizeof(uint8_t);
		std::size_t bytes = getNumBytes() - head->imgOffset;


		*image = cv::Mat(head->breite, head->hoehe, cv::DataType<uint8_t>::type);


		if(pixelBytes != bytes)
		{
			std::cerr << "Image::readCVImage: pixelBytes != bytes\n";
			pixelBytes = std::min(pixelBytes, bytes);
		}

		stream.seekg(getBlockDataAddress()+head->imgOffset);
		stream.read(reinterpret_cast<char*>(image->data), pixelBytes);
	}


	PatImage_2335::~PatImage_2335()
	{
		delete reinterpret_cast<ImageHeader*>(header);
		delete image;
	}

	char PatImage_2335::getType() const
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);
		return head->type;
	}





	std::size_t PatImage_2335::getImageCols() const
	{
		return image->cols;
	}

	std::size_t PatImage_2335::getImageRows() const
	{
		return image->rows;
	}

}
