#pragma once

#include <map>
#include "basestructure.h"


namespace E2E
{

	class Image;

	struct BScan : public BaseStructure
	{
		Image* bscanImage = nullptr;
		
		// std::vector<Segmentierungsdaten>

	public:
		~BScan();

		const Image* getImage() const                           { return bscanImage; }
		void setImage(Image* image);
	};


}
