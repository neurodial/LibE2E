#pragma once

#include <fstream>
#include <ostream>

namespace E2E
{

	class DictEntryRawData
	{
	public:
		enum class EntryType { Dir, Data};
		struct DataRawHeader
		{
			uint8_t  mdbdataStr[0x08]; // MDbData + \0
			uint32_t zero1;
			uint32_t undef;
		};

		struct Raw
		{
			uint32_t indexAddress;
			uint32_t dataAddress ;
			uint32_t dataLengt   ;

			uint32_t zero        ; // TODO: unknown
			int32_t  patientID   ; // dir + edb
			int32_t  studyID     ; // .edb
			int32_t  seriesID    ; // .sdb
			int32_t  imageID     ;
			int16_t  imageSubID  ;

			uint16_t unknown     ; // not included in checksum, unknown why
			uint32_t type        ;
			uint32_t checksum    ; // sum of block + 0x789ABCDF
		} __attribute__((packed));


		DictEntryRawData(std::ifstream& stream, uint32_t linkAddr, EntryType t);
		DictEntryRawData(const DictEntryRawData& other) = default;

		void print(std::ostream& stream) const;

		bool validChecksum()                              const  { return (calculatedChecksum - rawdata.checksum) == 0; }
		bool validIndexEntry()                            const;
		bool isValid()                                    const  { return validIndexEntry() && validChecksum(); }

		uint32_t getFoundAddr()                           const  { return foundAddr; }
		uint32_t getCalculatedChecksum()                  const  { return calculatedChecksum; }

		const Raw& getRaw()                               const  { return rawdata; }
		const DataRawHeader& getDataRawHeader()           const  { return dataRawHeader; }

	private:
		Raw       rawdata           ;
		DataRawHeader dataRawHeader ;
		EntryType type              ;
		uint32_t  foundAddr         ;
		uint32_t  calculatedChecksum;

		void calcChecksumDir();
		void calcChecksumData();

		void copyFrom(const DictEntryRawData& other);
	};

	inline std::ostream& operator<<(std::ostream& stream, const DictEntryRawData& ob) { ob.print(stream); return stream; }


}
