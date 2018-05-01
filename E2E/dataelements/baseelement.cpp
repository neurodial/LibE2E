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
