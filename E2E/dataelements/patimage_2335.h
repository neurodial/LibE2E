#pragma once

#include <istream>

#include "baseelement.h"

namespace cv { class Mat; }

namespace E2E
{
	class MDbData;

	class PatImage_2335 : public BaseElement
	{
		void*                               header = nullptr;
		cv::Mat*                            image  = nullptr;

	public:
		PatImage_2335(std::istream& stream, MDbData& data);
		~PatImage_2335();

		const cv::Mat& getImage() const                         { return *image; }

		char getType() const;

		std::size_t getImageCols() const;
		std::size_t getImageRows() const;
	};

}

