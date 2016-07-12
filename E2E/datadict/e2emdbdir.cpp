
#include "e2emdbdir.h"

#include <iostream>
#include "../streamhelper.h"

namespace E2E
{

	MDbDirEntry::MDbDirEntry(uint32_t found, std::ifstream& stream)
	: foundAddr(found)
	{
		StreamHelper::readFStream(stream, &(data));
		
		calculatedChecksum = 0;
		calculatedChecksum += data.indexAddress;
		calculatedChecksum += data.dataAddress;
		calculatedChecksum += data.dataLengt;
		calculatedChecksum += data.zero       ; // TODO: unknown
		calculatedChecksum += data.patientID  ; // dir + edb
		calculatedChecksum += data.seriesID   ; // .edb
		calculatedChecksum += data.scanID     ; // .sdb
		calculatedChecksum += data.imageID    ;
		calculatedChecksum += data.imageSubID ;
		
		// calculatedChecksum += data.unknown    ;
		calculatedChecksum += data.type;
		
// 		int16_t* ptr = reinterpret_cast<int16_t*>(&data.undef);
// 		for(int i = 0; i < sizeof(data.undef); i+=sizeof(uint16_t))
// 		{
// 			sum += *ptr;
// 			++ptr;
// 		}

		if(!validIndexEntry())
			std::cerr << "MDbDirEntry: IndexEntry is invalid\n";


		if(!validChecksum())
			std::cerr << "MDbDirEntry: Checksum is invalid\n";
	}


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

		while(true)
		{
			MDbDirEntry set(stream.tellg(), stream);

			if(set.isValid())
				index.push_back(set);

			if(!set.validIndexEntry())
				break;
		};
	}
}