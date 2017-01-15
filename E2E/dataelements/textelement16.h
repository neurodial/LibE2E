#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class TextElement16 : public BaseElement
	{
		std::u16string text;
	public:
		TextElement16(std::istream& stream, MDbData& data);
		virtual ~TextElement16();

		const std::u16string& getText() const                          { return text; }
	};


};
