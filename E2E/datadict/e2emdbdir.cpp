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



#include "e2emdbdir.h"

#include <iostream>
#include "../streamhelper.h"

namespace E2E
{

	void MDbDir::readIndex(std::ifstream& stream, uint32_t linkAddr)
	{
		// read adress from MDbDir
		stream.seekg(linkAddr);
		uint32_t actDirAddr;
		StreamHelper::readFStream(stream, &actDirAddr);

		// test MDbDir adress
		if(actDirAddr == 0)
			return;
		stream.seekg(actDirAddr);
		if(!StreamHelper::testString(stream, "MDbDir", 6))
			return;

		// test success -> read dir
		// std::cout << "Read MDbDir: " << std::hex << actDirAddr << std::dec << std::endl;

		// read next linked MDbDir
		readIndex(stream, actDirAddr+0x2c);

		// go back to adress
		stream.seekg(actDirAddr + 0x40-12);

		// read all valid dataset

		DictEntryRawData::resetEntryCounter();
		while(true)
		{
			DictEntryRawData set(stream, stream.tellg(), DictEntryRawData::EntryType::Dir);

			if(!set.validIndexEntry())
				break;

			if(set.isValid())
				index.push_back(set);
		};
	}
}
