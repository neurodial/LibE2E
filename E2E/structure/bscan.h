#pragma once

#include <map>
#include "basestructure.h"


namespace E2E
{

class BScanMetaDataElement;

	class SegmentationData;
	class Image;

	class BScan : public BaseStructure
	{
	public:
		struct SegPair
		{
			SegPair() = default;
			SegPair(int index, int type) : index(index), type(type) {}
			bool operator<(const SegPair& other) const
			{
				if(index == other.index)
					return type < other.type;
				return index < other.index;
			}

			int index = 0;
			int type  = 0;
		};

		typedef std::pair<const SegPair, SegmentationData*>  SegmentationPair;
		typedef std::map<SegPair, SegmentationData*>         SegmentationMap;
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

		const BScanMetaDataElement* getBScanMetaDataElement() const { return bScanMetaDataElement; }
		void takeBScanMetaDataElement(BScanMetaDataElement* metaData);
	private:
		Image* bscanImage = nullptr;
		std::vector<Image*> pixmaps;
		
		SegmentationMap segmentationMap;
		BScanMetaDataElement* bScanMetaDataElement = nullptr;
		// std::vector<Segmentierungsdaten>

	};


}
