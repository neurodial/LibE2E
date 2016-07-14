#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class TextElement : public BaseElement
	{
		std::string text;
	public:
		TextElement(std::istream& stream, MDbData& data);
		virtual ~TextElement();
		
		const std::string& getText() const                       { return text; }
	};
	
	
};
