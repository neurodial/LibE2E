#include "series.h"

#include "../dataelements/image.h"
#include "../dataelements/textelement.h"
#include "../dataelements/bscansmetadataelement.h"


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
		delete metaDataElement;
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

	void Series::takeBScansMetaData(BScansMetaDataElement* ele)
	{
		if(metaDataElement)
			throw "mutlible BScansMetaDataElement";
		metaDataElement = ele;
	}

	void Series::takeSloDataElement(SloDataElement* data)
	{
		if(sloDataElement)
			throw "mutlible SloDataElement";
		sloDataElement = data;
	}

	void Series::takeExaminedStructure(StringListElement* textEle)
	{
		if(examinedStructure)
			throw "mutlible StudyID";
		// delete studyUID;
		examinedStructure = textEle;
	}

	void Series::takeScanPattern(StringListElement* textEle)
	{
		if(scanPattern)
			throw "mutlible StudyID";
		// delete studyUID;
		scanPattern = textEle;
	}


}
