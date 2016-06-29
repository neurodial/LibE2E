#pragma once

#include <map>

#include "bscann.h"
#include "basestructure.h"

namespace E2E
{

	class Image;

	class CScann : public BaseStructure
	{
		std::map<int, BScan> bscans;
		Image* sloImage;
		// image
	public:

		BScan& getBScan(int id)                                 { return bscans[id]; }
		Image& getSloImage()                                    { return *sloImage;  }
	};


}
