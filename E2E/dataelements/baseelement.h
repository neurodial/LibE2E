#pragma once

#include <istream>

namespace E2E
{
	class MDbData;

	class BaseElement
	{
		char*                               rawData       = nullptr;
		std::size_t                         rawDataLength = 0      ;

		// TODO
		int type       = 0;
		int interpret  = 0;
		int address    = 0;
		int length     = 0;

		int subID      = 0;

	public:
		BaseElement(std::istream& stream, MDbData& data);
		virtual ~BaseElement();

		std::size_t getRawDataLength() const                    { return rawDataLength; }
		const char* getRawData()       const                    { return rawData;       }

		int getAddress()               const                    { return address; }
		int getNumBytes()              const                    { return length; }
		int getType()                  const                    { return type;   }

		int getSubID()                 const                    { return subID;  }
	};
}

