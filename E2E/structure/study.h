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

		      Series& getSeries(int seriesId)                   { return getAndInsert(seriesId)         ; }
		const Series& getSeries(int seriesId) const             { return *(substructureMap.at(seriesId)); }

		std::size_t getCScanSize() const                        { return substructureMap.size(); }
		
		
		TextElement* getStudyUID() const                        { return studyUID; }
		void takeStudyUID(TextElement* uid);
	};


}
