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


#pragma once

#include <istream>

namespace E2E
{

	class DictEntryRawData;
	class MDbData;

	class BaseElement
	{
		char*                               rawData       = nullptr;
		std::size_t                         rawDataLength = 0      ;

		const DictEntryRawData*             dictEntry  = nullptr;
		const DictEntryRawData*             dataHeader = nullptr;

		// TODO
		int         type               = 0;
		int         interpret          = 0;
		std::size_t blockHeaderAddress = 0;
		std::size_t blockDataAddress   = 0;
		std::size_t length             = 0;

		int         subID              = 0;

		static const uint32_t checksumMagic = 0x12435687;

		std::string name;
	public:
		BaseElement(std::istream& stream, MDbData& data);
		BaseElement(std::istream& stream, MDbData& data, const std::string& name);
		virtual ~BaseElement();

		std::size_t getRawDataLength() const                    { return rawDataLength; }
		const char* getRawData()       const                    { return rawData;       }

		std::size_t getBlockHeaderAddress()    const            { return blockHeaderAddress; }
		std::size_t getBlockDataAddress()      const            { return blockDataAddress  ; }
		std::size_t getNumBytes()              const            { return length; }
		int getType()                  const                    { return type;   }

		int getSubID()                 const                    { return subID;  }

		const DictEntryRawData* getDictEntry () const           { return dictEntry ; }
		const DictEntryRawData* getDataHeader() const           { return dataHeader; }

		static uint32_t calcDataCheckSum(const char* data, const std::size_t length);
		uint32_t getRawDataChecksum()           const           { return calcDataCheckSum(rawData, length); }

		const std::string& getName()            const           { return name; }

		std::size_t getEntryID() const;
	};
}

