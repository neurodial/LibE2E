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
