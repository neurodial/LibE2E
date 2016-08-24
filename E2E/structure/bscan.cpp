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
