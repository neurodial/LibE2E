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


#include "baseelement.h"

#include "../datadict/e2emdbdata.h"
#include "../datadict/dictentryrawdata.h"
#include "../e2edata.h"

#include <iostream>

namespace E2E
{
	BaseElement::BaseElement(std::istream& stream, E2E::MDbData& data, const std::string& name)
	: BaseElement(stream, data)
	{
		this->name = name;
	}


	E2E::BaseElement::BaseElement(std::istream& stream, E2E::MDbData& data)
	{
		if(data.getOptions().readRawData)
		{
			std::size_t pos        = stream.tellg();
			std::size_t readLengt  = data.getDataLength();
			std::size_t readAdress = data.getDataAdress() + DictEntryRawData::dataEntryHeaderSize;

			rawData = new char[readLengt];

			stream.seekg(readAdress);
			stream.read(rawData, readLengt);
			rawDataLength = readLengt; // data.getDataLength(); //

			stream.seekg(pos);

			dictEntry  = new DictEntryRawData(data.getDirEntry());
			dataHeader = new DictEntryRawData(data.getDataHeader());
			
			/*
			uint32_t checksum = 0;
			for(char* it = rawData; it<rawData+readLengt; ++it)
				checksum += *it;
			
			std::cout << '\t' << checksum << '\t' << (checksum - dataHeader->getDataRawHeader().undef - 0xedb9a879);
			*/
		}
		// interpret = data.

		blockHeaderAddress = data.getDataAdress();
		blockDataAddress   = data.getDataAdress() + DictEntryRawData::dataEntryHeaderSize;
		length             = data.getDataLength();
		type               = data.getTypeValue();
		subID              = data.getSubId();
	}

	BaseElement::~BaseElement()
	{
		delete[] rawData;

		delete dictEntry;
		delete dataHeader;
	}


	uint32_t BaseElement::calcDataCheckSum(const char* data, const std::size_t length)
	{
		if(!data)
			return 0;

		uint32_t checksum = 0;
		for(std::size_t i=0; i<length; ++i)
		{
			checksum += *reinterpret_cast<const uint8_t*>(data);
// 			checksum += static_cast<uint32_t>(*data)<<8;
			++data;
		}

		return checksum + checksumMagic;
	}


	std::size_t BaseElement::getEntryID() const
	{
		if(dictEntry)
			return dictEntry->getEntryId();
		return 0;
	}


}
