#include "stringlistelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include <algorithm>

#include <iostream>

namespace
{
	struct StringListHeader
	{
		uint8_t  undef[0x3c - E2E::MDbData::headerSize];
		uint32_t stringNumbers;
		uint32_t stringSize;
	} __attribute__((packed));
}


E2E::StringListElement::StringListElement(std::istream& stream, E2E::MDbData& data)
{
	StringListHeader header;
	StreamHelper::readFStream(stream, &header);

	for(uint32_t i = 0; i<header.stringNumbers; ++i)
	{
		wchar_t ch;
		std::wstring string;
		const std::size_t size = header.stringSize/2;
		string.reserve(size);
		for(std::size_t c = 0; c < size; ++c)
		{
			StreamHelper::readFStream(stream, &ch);
			string.push_back(ch);
		}

		std::wcout << "StringListElement: " << string << std::endl;

		stringList.push_back(std::move(string));
	}

}

E2E::StringListElement::~StringListElement()
{

}
