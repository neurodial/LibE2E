/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
