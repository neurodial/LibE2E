#include "stringlistelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include <algorithm>

#include <iostream>

namespace
{
	struct StringListHeader
	{
		uint32_t stringNumbers;
		uint32_t stringSize;
	} __attribute__((packed));
}


E2E::StringListElement::StringListElement(std::istream& stream, E2E::MDbData& data)
: BaseElement(stream, data)
{
	StringListHeader header;
	StreamHelper::readFStream(stream, &header);

	std::size_t startpos = stream.tellg();

	if(header.stringNumbers*header.stringSize+sizeof(StringListHeader) != data.getDataLength())
		throw "Wrong Element";

	for(uint32_t i = 0; i<header.stringNumbers; ++i)
	{
		stream.seekg(startpos + header.stringSize*i);

		uint16_t ch;
		std::u16string string;
		const std::size_t size = header.stringSize/2; // wchar = 2 bytes
		string.reserve(size);
		for(std::size_t c = 0; c < size; ++c)
		{
			StreamHelper::readFStream(stream, &ch);
			if(ch == 0)
				break;
			string.push_back(ch);
		}

		std::cout << std::endl;
		std::cout << "StringListElement: ";
		for(uint16_t c : string)
			std::cout << static_cast<char>(c);

		stringList.push_back(std::move(string));
	}

}

E2E::StringListElement::~StringListElement()
{

}
