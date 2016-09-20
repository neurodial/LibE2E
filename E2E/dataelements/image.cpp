#include "image.h"

// #include <ostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"
#include "../datadict/dictentryrawdata.h"

#include "../e2e_packhelper.h"

namespace
{
	PACKSTRUCT(struct ImageHeader
	{
		uint8_t  undef[0x40 - E2E::DictEntryRawData::dataEntryHeaderSize];
		uint32_t u1;
		uint32_t u2;
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
		if(data.getSubId() == 0) // SLO
			readCVImage(stream, *image, CV_8UC1);
		else // BScan
			readCVImage(stream, *image, CV_16UC1);
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
		StreamHelper::readFStream(stream, head);

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

	Image* Image::fromJFIF(std::istream& stream, MDbData& data)
	{
		int         readLengt  = static_cast<int>(data.getDataLength()); // TODO
		std::size_t readAdress = data.getDataAdress() + 60 + 0x10;

		cv::Mat inputArray(readLengt, 1, CV_8UC1);

		stream.seekg(readAdress);
		stream.read(reinterpret_cast<char*>(inputArray.data), readLengt);

		cv::Mat* image = new cv::Mat;
		*image = cv::imdecode(inputArray, CV_LOAD_IMAGE_ANYDEPTH);
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
