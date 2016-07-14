#include "study.h"


#include "../dataelements/textelement.h"

namespace E2E
{
	Study::~Study()
	{
		delete studyUID;
	}

	void Study::takeStudyUID(TextElement* uid)
	{
		if(studyUID)
			throw "mutlible StudyID";
		// delete studyUID;
		studyUID = uid;
	}

}