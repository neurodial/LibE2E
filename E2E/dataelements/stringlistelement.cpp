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


#include "stringlistelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include <algorithm>

#include "../e2e_packhelper.h"

#include <iostream>

namespace
{
	PACKSTRUCT(
	struct StringListHeader
	{
		uint32_t stringNumbers;
		uint32_t stringSize;
	});
}


E2E::StringListElement::StringListElement(std::istream& stream, E2E::MDbData& data)
: BaseElement(stream, data)
{
	StringListHeader header;
	StreamHelper::readFStream(stream, &header);

	std::size_t startpos = stream.tellg();

	if(header.stringNumbers*header.stringSize+sizeof(StringListHeader) != data.getDataLength())
		throw "Wrong Element";

	for(uint32_t i = 0; i<header.stringNumbers; ++i)
	{
		stream.seekg(startpos + header.stringSize*i);

		uint16_t ch;
		std::u16string string;
		const std::size_t size = header.stringSize/2; // wchar = 2 bytes
		string.reserve(size);
		for(std::size_t c = 0; c < size; ++c)
		{
			StreamHelper::readFStream(stream, &ch);
			if(ch == 0)
				break;
			string.push_back(ch);
		}

// 		std::cout << std::endl;
// 		std::cout << "StringListElement: ";
// 		for(uint16_t c : string)
// 			std::cout << static_cast<char>(c);

		stringList.push_back(std::move(string));
	}

}

E2E::StringListElement::~StringListElement()
{

}
