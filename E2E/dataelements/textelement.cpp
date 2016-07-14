#include "textelement.h"
#include "../datadict/e2emdbdata.h"
#include "../streamhelper.h"

namespace E2E
{

	TextElement::TextElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		StreamHelper::readString(stream, text, data.getDataLength());
	}


	TextElement::~TextElement()
	{

	}

}