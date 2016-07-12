#include "bscan.h"


#include "../dataelements/image.h"
#include "../dataelements/segmentationdata.h"

E2E::BScan::~BScan()
{
	delete bscanImage;
}


void E2E::BScan::takeImage(E2E::Image* image)
{
	delete bscanImage;
	bscanImage = image;
}

void E2E::BScan::takeSegmentationData(E2E::SegmentationData* data)
{
	segmentationMap.emplace(data->getType(), data);

}

std::size_t E2E::BScan::getImageCols() const
{
	if(bscanImage)
		return bscanImage->getImageCols();
	return 0;
}

std::size_t E2E::BScan::getImageRows() const
{
	if(bscanImage)
		return bscanImage->getImageRows();
	return 0;
}