#pragma once

#include <map>

#include "series.h"
#include "substructure_template.h"

namespace E2E
{
	class TextElement;

	class Study : public SubstructureTemplate<Series>
	{
		TextElement*        studyUID  = nullptr;
	public:
		virtual ~Study();

		      Series& getCScan(int cscanId)                     { return getAndInsert(cscanId)         ; }
		const Series& getCScan(int cscanId) const               { return *(substructureMap.at(cscanId)); }

		std::size_t getCScanSize() const                        { return substructureMap.size(); }
		
		
		TextElement* getStudyUID() const                        { return studyUID; }
		void takeStudyUID(TextElement* uid);
	};


}
