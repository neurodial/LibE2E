#include "study.h"


#include "../dataelements/textelement.h"
#include "../dataelements/studydata.h"
#include "../dataelements/eyedata.h"

namespace E2E
{
	Study::~Study()
	{
		delete studyUID;
		delete studyData;
		delete eyeDataL;
		delete eyeDataR;
		delete studyName;
	}

	void Study::takeStudyUID(TextElement* uid)
	{
		if(studyUID)
			throw "mutlible StudyID";
		// delete studyUID;
		studyUID = uid;
	}

	void Study::takeStudyName(StringListElement* uid)
	{
		if(studyName)
			throw "mutlible StudyName";
		// delete studyUID;
		studyName = uid;
	}

	void Study::takeStudyData(StudyData* data)
	{
		if(studyData)
			throw "mutlible StudyID";
		// delete studyUID;
		studyData = data;

	}

	void Study::takeEyeData(EyeData* source, EyeData*& dest)
	{
		if(dest)
			throw "mutlible eye data";
		dest = source;
	}



	void Study::takeEyeData(E2E::EyeData* eyedata)
	{
		if(!eyedata)
			return;
		switch(eyedata->getEyeSide())
		{
			case 'L':
				takeEyeData(eyedata, eyeDataL);
				break;
			case 'R':
				takeEyeData(eyedata, eyeDataR);
				break;
			default:
				throw("undef eye side");
		}
	}


}
