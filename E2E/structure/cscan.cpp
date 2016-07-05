#include "cscan.h"


E2E::CScan::CScan()
{

}


E2E::CScan::~CScan()
{
	delete sloImage;

}


void E2E::CScan::takeSloImage(E2E::Image* img)
{
	delete sloImage;
	sloImage = img;
}
