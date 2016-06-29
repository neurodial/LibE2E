#pragma once

#include <vector>
#include <fstream>

#include "../streamhelper.h"

namespace E2E
{
	class MDbDirEntry
	{
		uint32_t foundAddr;
	public:
		MDbDirEntry(uint32_t found, std::ifstream& stream) : foundAddr(found) { StreamHelper::readFStream(stream, &(data)); }

		struct RawData
		{
			uint32_t indexAddress;
			uint32_t dataAddress;
			uint32_t dataLengt;

			// uint8_t  dataBlock[0x16];
			uint32_t  zero       ; // TODO: unknown
			int32_t   patient    ; // dir + edb
			int32_t   imageScanID; // .edb
			int32_t   imageDirID ; // .sdb
			int32_t   imageID    ;
			int16_t   imageSubID ;

			uint8_t  undef[0x0A];
		} __attribute__((packed)) data;

		bool validIndexEntry()
		{
			return foundAddr == data.indexAddress;
		}

		bool isValid()
		{
			return validIndexEntry()
				&& data.dataLengt > 4;
		}

		uint32_t getFoundAddr() const { return foundAddr; }
	};

	class MDbDir
	{
	public:
		void readIndex(std::ifstream& stream, uint32_t linkAddr);
		
		const std::vector<MDbDirEntry>& getIndexVec() const         { return index; };
	private:
		std::vector<MDbDirEntry> index;
	};
	
}