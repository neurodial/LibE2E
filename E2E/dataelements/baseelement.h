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

	public:
		BaseElement(std::istream& stream, MDbData& data);
		virtual ~BaseElement();

		std::size_t getRawDataLength() const                    { return rawDataLength; }
		const char* getRawData()       const                    { return rawData;       }

		int getBlockHeaderAddress()    const                    { return blockHeaderAddress; }
		int getBlockDataAddress()      const                    { return blockDataAddress  ; }
		int getNumBytes()              const                    { return length; }
		int getType()                  const                    { return type;   }

		int getSubID()                 const                    { return subID;  }

		const DictEntryRawData* getDictEntry () const           { return dictEntry ; }
		const DictEntryRawData* getDataHeader() const           { return dataHeader; }
	};
}

