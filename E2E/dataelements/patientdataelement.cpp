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


#include "patientdataelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	PatientDataElement::PatientDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		if(131 != data.getDataLength())
			throw "Wrong Element";

		StreamHelper::readString(stream, forename, 30);
		stream.seekg(startpos+31);
		StreamHelper::readString(stream, surname, 50);
		stream.seekg(startpos+82);
		StreamHelper::readString(stream, title, 10);
		
		char sexChar;
		stream.seekg(startpos+93);
		StreamHelper::readFStream(stream, &windowsBirthDate);
		// stream.seekg(startpos+101);
		StreamHelper::readFStream(stream, &sexChar);
		// stream.seekg(startpos+102);
		StreamHelper::readString(stream, id, 20);
		
		
		switch(sexChar)
		{
			case 'F':
				sex = Sex::Female;
				break;
			case 'M':
				sex = Sex::Male;
				break;
			default:
				// TODO:
				break;
		}
	}

	E2E::PatientDataElement::~PatientDataElement()
	{

	}



}
