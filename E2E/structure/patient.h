#pragma once

#include <map>

#include "series.h"
#include "substructure_template.h"

namespace E2E
{

	class Patient : public SubstructureTemplate<Series>
	{

	public:

		      Series& getSeries(int seriesId)                   { return getAndInsert(seriesId)         ; }
		const Series& getSeries(int seriesId) const             { return *(substructureMap.at(seriesId)); }

		std::size_t getSeriesSize() const                       { return substructureMap.size(); }

	};


}

