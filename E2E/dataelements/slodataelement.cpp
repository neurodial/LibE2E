#include "slodataelement.h"

#include "../streamhelper.h"

namespace E2E
{
	SloDataElement::SloDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		stream.seekg(startpos+24);
		StreamHelper::readFStream(stream, &winDate);
		StreamHelper::readFStream(stream, transform, sizeof(transform)/sizeof(transform[0]));
	}


	SloDataElement::~SloDataElement()
	{

	}

}