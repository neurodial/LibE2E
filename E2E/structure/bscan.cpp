#include "bscan.h"


#include "../dataelements/image.h"


E2E::BScan::~BScan()
{
	delete bscanImage;
}


void E2E::BScan::takeImage(E2E::Image* image)
{
	delete bscanImage;
	bscanImage = image;
}
