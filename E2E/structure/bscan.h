#pragma once

#include <map>
#include "basestructure.h"


namespace E2E
{

	class Image;

	struct BScan : public BaseStructure
	{
		Image* bscanImage = nullptr;
		std::vector<Image*> pixmaps;
		
		// std::vector<Segmentierungsdaten>

	public:
		~BScan();

		const Image* getImage() const                           { return bscanImage; }
		void takeImage(Image* image);

		const std::vector<Image*>& getPixmaps() const           { return pixmaps; }
		void takePixmap(Image* img)                             { pixmaps.push_back(img); }
	};


}
