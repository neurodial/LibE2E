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


#include "series.h"

#include "../dataelements/image.h"
#include "../dataelements/textelement.h"
#include "../dataelements/bscansmetadataelement.h"
#include "../dataelements/slodataelement.h"


namespace E2E
{

	Series::~Series()
	{
		delete sloImage;

		for(Image* data : pixmaps)
			delete data;
		
		delete seriesUID;
		delete metaDataElement;
		delete examinedStructure;
		delete scanPattern;
		delete sloDataElement;
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
