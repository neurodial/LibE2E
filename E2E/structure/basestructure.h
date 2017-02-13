#pragma once

#include <vector>
#include "../dataelements/stringlistelement.h"


namespace E2E
{
	class E2EData;
	class BaseElement;

	class BaseStructure
	{
		std::vector<BaseElement*> rawDataVec;
//		std::vector<BaseElement*> allElements;

		std::vector<StringListElement*> unknownStringListElement; // TODO: remove this when all elements are known
	public:
		BaseStructure();
		BaseStructure(E2EData* parentData);
		virtual ~BaseStructure();
		
		BaseStructure(const BaseStructure&)            = delete;
		BaseStructure& operator=(const BaseStructure&) = delete;


		const std::vector<BaseElement*>& getRawDataVec() const         { return rawDataVec ; }
		// const std::vector<BaseElement*>& getAllElements() const { return allElements; }

		void takeRawElement(BaseElement* element)                      { rawDataVec.push_back(element); } // allElements.push_back(element); }

		void takeStringListElement(StringListElement* element)         { unknownStringListElement.push_back(element); } // allElements.push_back(element); }
		const std::vector<StringListElement*>& getUnknownStringListElements() const { return unknownStringListElement; }


		std::size_t getCreateFromLoadedFileNum()                 const { return createFromLoadedFileNum;  }

	protected:
		// void registerElement(BaseElement* element)              { allElements.push_back(element); }

		E2EData* getParentData()                                 const { return parentData; }

	private:
		E2EData* parentData                 = nullptr;
		std::size_t createFromLoadedFileNum = 0;

	};


}
