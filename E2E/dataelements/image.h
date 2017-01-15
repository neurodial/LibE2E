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

