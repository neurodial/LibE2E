#pragma once

#include <vector>
#include <fstream>


namespace E2E
{
	class MDbDirEntry
	{
		uint32_t foundAddr;
		uint32_t calculatedChecksum;
	public:
		MDbDirEntry(uint32_t found, std::ifstream& stream);

		struct RawData
		{
			uint32_t indexAddress;
			uint32_t dataAddress;
			uint32_t dataLengt;

			// uint8_t  dataBlock[0x16];
			uint32_t  zero       ; // TODO: unknown
			int32_t   patientID  ; // dir + edb
			int32_t   seriesID   ; // .edb
			int32_t   scanID     ; // .sdb
			int32_t   imageID    ;
			int16_t   imageSubID ;

			// uint8_t  undef[0x06];
			uint16_t unknown     ; // not included in checksum, unknown why
			uint32_t type        ;
			uint32_t checksum    ; // sum of block + 0x789ABCDF
		} __attribute__((packed)) data;

		bool validChecksum()                              const  { return (calculatedChecksum - data.checksum) == 0x789ABCDF; }
		bool validIndexEntry()                            const  { return foundAddr == data.indexAddress; }
		bool isValid()                                    const  { return validIndexEntry() && data.dataLengt > 4 && validChecksum(); }

		uint32_t getFoundAddr()                           const  { return foundAddr; }
		uint32_t getCalculatedChecksum()                  const  { return foundAddr; }
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