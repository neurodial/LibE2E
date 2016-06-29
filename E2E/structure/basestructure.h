#pragma once

#include <vector>


namespace E2E
{
	class BaseElement;

	class BaseStructure
	{
		std::vector<BaseElement*> rawDataVec;
		std::vector<BaseElement*> allElements;
	public:
		BaseStructure();
		virtual ~BaseStructure();


		BaseStructure(const BaseStructure&)            = delete;
		BaseStructure& operator=(const BaseStructure&) = delete;


		const std::vector<BaseElement*>& getRawDataVec() const  { return rawDataVec ; }
		const std::vector<BaseElement*>& getAllElements() const { return allElements; }

		void takeRawElement(BaseElement* element)               { rawDataVec.push_back(element); allElements.push_back(element); }

	protected:
		void addElement(BaseElement* element)                   { allElements.push_back(element); }

	};


}
