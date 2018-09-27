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


#include "studydata.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	StudyData::StudyData(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		if(91 != data.getDataLength())
			throw "Wrong Element";

		stream.seekg(startpos+6);
		StreamHelper::readFStream(stream, &windowsStudyDate);
		stream.seekg(startpos+16);
		StreamHelper::readString(stream, studyOperator, 16);
	}

	E2E::StudyData::~StudyData()
	{

	}



}
