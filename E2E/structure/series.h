#pragma once

#include <map>

#include "bscan.h"
#include "substructure_template.h"

namespace E2E
{


	class BScansMetaDataElement;
	class Image;
	class TextElement;
	class SloDataElement;

	class Series : public SubstructureTemplate<BScan>
	{
		Image* sloImage = nullptr;
		std::vector<Image*> pixmaps;
		
		TextElement*        seriesUID          = nullptr;
		StringListElement*  examinedStructure  = nullptr;
		StringListElement*  scanPattern        = nullptr;

		BScansMetaDataElement* metaDataElement = nullptr;
		SloDataElement*        sloDataElement  = nullptr;
		// image
	public:
		Series(E2EData* parent) : SubstructureTemplate(parent) {}
		virtual ~Series();

		      BScan& getBScan(int bscanId)                      { return getAndInsert(bscanId)         ; }
		const BScan& getBScan(int bscanId) const                { return *(substructureMap.at(bscanId)); }

		std::size_t getBScanSize() const                        { return substructureMap.size(); }


		const Image* getSloImage() const                        { return sloImage; }
		void   takeSloImage(Image* img);

		const std::vector<Image*>& getPixmaps() const           { return pixmaps; }
		void takePixmap(Image* img)                             { pixmaps.push_back(img); }
		
		const BScansMetaDataElement* getBScanMetaData() const          { return metaDataElement; }
		void takeBScansMetaData(BScansMetaDataElement* ele);
		
		TextElement* getSeriesUID() const                              { return seriesUID; }
		void takeSeriesUID(TextElement* uid);

		StringListElement* getExaminedStructure() const                { return examinedStructure; }
		void takeExaminedStructure(StringListElement* textEle);

		StringListElement* getScanPattern() const                      { return scanPattern; }
		void takeScanPattern(StringListElement* textEle);

		SloDataElement* getSloDataElement() const                      { return sloDataElement; }
		void takeSloDataElement(SloDataElement* data);
	};


}
