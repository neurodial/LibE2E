#pragma once

#include <map>

#include "bscan.h"
#include "substructure_template.h"

namespace E2E
{

	class Image;

	class CScan : public SubstructureTemplate<BScan>
	{
		Image* sloImage;
		// image
	public:

		      BScan& getBScan(int bscanId)                      { return getAndInsert(bscanId)         ; }
		const BScan& getBScan(int bscanId) const                { return *(substructureMap.at(bscanId)); }

		std::size_t getBScanSize() const                        { return substructureMap.size(); }


		Image& getSloImage()                                    { return *sloImage;  }
	};


}
