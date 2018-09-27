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


#include "bscan.h"


#include "../dataelements/image.h"
#include "../dataelements/segmentationdata.h"
#include "../dataelements/bscanmetadataelement.h"

#include "../dataelements/imageregistration.h"


namespace E2E
{
	BScan::~BScan()
	{
		delete bscanImage;

		for(SegmentationPair data : segmentationMap)
			delete data.second;

		for(Image* data : pixmaps)
			delete data;

		delete imageRegistrationData;
		delete bScanMetaDataElement;
	}


	void BScan::takeImage(Image* image)
	{
		if(bscanImage)
			throw "double BScan-Image";
		bscanImage = image;
	}

	void BScan::takeAngioImage(Image* image)
	{
		if(angioImage)
			throw "double BScan-Angio-Image";
		angioImage = image;
	}


	void BScan::takeSegmentationData(SegmentationData* data)
	{
		segmentationMap.emplace(SegPair(data->getSegIndex(), data->getSegType()), data);

	}

	std::size_t BScan::getImageCols() const
	{
		if(bscanImage)
			return bscanImage->getImageCols();
		return 0;
	}

	std::size_t BScan::getImageRows() const
	{
		if(bscanImage)
			return bscanImage->getImageRows();
		return 0;
	}

	void BScan::takeBScanMetaDataElement(BScanMetaDataElement* metaData)
	{
		delete bScanMetaDataElement;
		bScanMetaDataElement = metaData;
	}

	void BScan::takeImageRegistrationData(ImageRegistration* ele)
	{
		if(imageRegistrationData)
			throw "mutlible ImageRegistrationData";
		imageRegistrationData = ele;
	}
}
