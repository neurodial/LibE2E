#include "series.h"

#include "../dataelements/image.h"
#include "../dataelements/textelement.h"


namespace E2E
{

	Series::Series()
	{

	}


	Series::~Series()
	{
		delete sloImage;

		for(Image* data : pixmaps)
			delete data;
		
		delete seriesUID;
	}


	void Series::takeSloImage(Image* img)
	{
		delete sloImage;
		sloImage = img;
	}

	void Series::takeSeriesUID(TextElement* uid)
	{
		if(seriesUID)
			throw "mutlible StudyID";
		// delete studyUID;
		seriesUID = uid;
	}

}
