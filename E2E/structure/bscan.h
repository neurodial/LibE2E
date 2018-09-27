/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include <map>
#include "basestructure.h"


namespace E2E
{

	class BScanMetaDataElement;

	class ImageRegistration;
	class SegmentationData;
	class Image;

	class BScan : public BaseStructure
	{
	public:
		BScan(E2EData* parent) : BaseStructure(parent) {}

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

		const Image* getAngioImage() const                      { return angioImage; }
		void takeAngioImage(Image* image);

		const std::vector<Image*>& getPixmaps() const           { return pixmaps; }
		void takePixmap(Image* img)                             { pixmaps.push_back(img); }

		std::size_t getImageCols() const;
		std::size_t getImageRows() const;


		const SegmentationMap& getSegmentationMap() const       { return segmentationMap; }
		void takeSegmentationData(SegmentationData* data);

		const BScanMetaDataElement* getBScanMetaDataElement() const { return bScanMetaDataElement; }
		void takeBScanMetaDataElement(BScanMetaDataElement* metaData);



		const ImageRegistration* getImageRegistrationData() const { return imageRegistrationData; }
		void takeImageRegistrationData(ImageRegistration* ele);
	private:
		Image* bscanImage = nullptr;
		Image* angioImage = nullptr;
		std::vector<Image*> pixmaps;
		
		SegmentationMap segmentationMap;
		BScanMetaDataElement* bScanMetaDataElement = nullptr;
		// std::vector<Segmentierungsdaten>
		ImageRegistration*     imageRegistrationData = nullptr;

	};


}
