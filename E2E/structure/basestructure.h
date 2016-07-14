#pragma once

#include <vector>
#include "../dataelements/stringlistelement.h"


namespace E2E
{
	class BaseElement;

	class BaseStructure
	{
		std::vector<BaseElement*> rawDataVec;
//		std::vector<BaseElement*> allElements;

		std::vector<StringListElement*> unknownStringListElement; // TODO: remove this when all elements are known
	public:
		BaseStructure();
		virtual ~BaseStructure();
		
		BaseStructure(const BaseStructure&)            = delete;
		BaseStructure& operator=(const BaseStructure&) = delete;


		const std::vector<BaseElement*>& getRawDataVec() const  { return rawDataVec ; }
		// const std::vector<BaseElement*>& getAllElements() const { return allElements; }

		void takeRawElement(BaseElement* element)               { rawDataVec.push_back(element); } // allElements.push_back(element); }

		void takeStringListElement(StringListElement* element)  { unknownStringListElement.push_back(element); } // allElements.push_back(element); }
		const std::vector<StringListElement*>& getUnknownStringListElements() const { return unknownStringListElement; }

	protected:
		// void registerElement(BaseElement* element)              { allElements.push_back(element); }

	};


}
