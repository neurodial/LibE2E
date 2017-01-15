#include "textelement16.h"
#include "../datadict/e2emdbdata.h"
#include "../streamhelper.h"

namespace E2E
{

	TextElement16::TextElement16(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		StreamHelper::readString(stream, text, data.getDataLength());
	}


	TextElement16::~TextElement16()
	{

	}

}
