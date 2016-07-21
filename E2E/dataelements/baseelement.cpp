#include "baseelement.h"

#include "../datadict/e2emdbdata.h"
#include "../datadict/dictentryrawdata.h"
#include "../e2edata.h"

#include <iostream>

namespace E2E
{

	E2E::BaseElement::BaseElement(std::istream& stream, E2E::MDbData& data)
	{
		if(data.getOptions().readRawData)
		{
			std::size_t pos    = stream.tellg();
			std::size_t readLengt  = data.getDataLength();
			std::size_t readAdress = data.getDataAdress() + 60;

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

		address = data.getDataAdress();
		length  = data.getDataLength();
		type    = data.getTypeValue();
		subID   = data.getSubId();
	}

	BaseElement::~BaseElement()
	{
		delete[] rawData;

		delete dictEntry;
		delete dataHeader;
	}



}