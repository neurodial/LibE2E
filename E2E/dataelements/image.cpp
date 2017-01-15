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

/*
	class ufloat16_t
	{
		uint16_t value;
	public:
		ufloat16_t(uint16_t v = 0) : value(v) {}
		operator float() const
		{
			const uint16_t mantise_mask = (1<<10)-1;
			const int mantise  =  value &  mantise_mask;
			const int exponent = (value & ~mantise_mask) >> 10;
			if(exponent == 0)
				return ldexp(static_cast<float>(mantise)/static_cast<float>(1<<10), -62);
			if(exponent == 63)
				return 0.0;
			return ldexp(1.f + static_cast<float>(mantise)/static_cast<float>(1<<10), exponent-63);
		}
	};
	*/
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
			// readConvertCVImage<ufloat16_t, float>(stream, *image);
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


	template<typename Source, typename Dest>
	void Image::readConvertCVImage(std::istream& stream, cv::Mat& image)
	{
		ImageHeader* head = reinterpret_cast<ImageHeader*>(header);
		StreamHelper::readFStream(stream, head);

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
