#pragma once

#include <map>
#include "basestructure.h"


namespace E2E
{

	class SegmentationData;
	class Image;

	class BScan : public BaseStructure
	{
	public:
		typedef std::pair<const int, SegmentationData*>  SegmentationPair;
		typedef std::map<int, SegmentationData*>         SegmentationMap;
		typedef typename SegmentationMap::iterator       SubstructureIterator;
		typedef typename SegmentationMap::const_iterator SubstructureCIterator;

		~BScan();

		const Image* getImage() const                           { return bscanImage; }
		void takeImage(Image* image);

		const std::vector<Image*>& getPixmaps() const           { return pixmaps; }
		void takePixmap(Image* img)                             { pixmaps.push_back(img); }

		std::size_t getImageCols() const;
		std::size_t getImageRows() const;


		const SegmentationMap& getSegmentationMap() const       { return segmentationMap; }
		void takeSegmentationData(SegmentationData* data);
	private:
		Image* bscanImage = nullptr;
		std::vector<Image*> pixmaps;
		
		SegmentationMap segmentationMap;
		// std::vector<Segmentierungsdaten>

	};


}
