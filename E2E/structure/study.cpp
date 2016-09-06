#include "study.h"


#include "../dataelements/textelement.h"
#include "../dataelements/studydata.h"

namespace E2E
{
	Study::~Study()
	{
		delete studyUID;
		delete studyData;
	}

	void Study::takeStudyUID(TextElement* uid)
	{
		if(studyUID)
			throw "mutlible StudyID";
		// delete studyUID;
		studyUID = uid;
	}

	void Study::takeStudyData(StudyData* data)
	{
		if(studyData)
			throw "mutlible StudyID";
		// delete studyUID;
		studyData = data;

	}

}