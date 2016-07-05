#ifndef E2E_IMAGE_H
#define E2E_IMAGE_H

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

		Image(cv::Mat* image, std::istream& stream, MDbData& data);
	public:
		Image(std::istream& stream, MDbData& data);
		~Image();

		static Image* fromJFIF(std::istream& stream, MDbData& data);

		const cv::Mat& getImage() const                         { return *image; }
	};

}

#endif // E2E_IMAGE_H
