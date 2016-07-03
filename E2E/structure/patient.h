#pragma once

#include <map>

#include "basestructure.h"
#include "series.h"

namespace E2E
{

	class Patient : public BaseStructure
	{

	public:
		typedef std::pair<const int, Series> SeriesPair;
		typedef std::map<int, Series>        SeriesMap;
		typedef SeriesMap::iterator          SeriesIterator;
		typedef SeriesMap::const_iterator    SeriesCIterator;

		Series& getSeries(int seriesId)                         { return seriesMap[seriesId]; }


		      Series& getPatient(int seriesId)                  { return seriesMap[seriesId]   ; }
		const Series& getPatient(int seriesId) const            { return seriesMap.at(seriesId); }

		std::size_t getSeriesSize() const                       { return seriesMap.size(); }

		SeriesCIterator begin() const                           { return seriesMap.begin(); }
		SeriesCIterator end()   const                           { return seriesMap.end(); }


	private:
		std::map<int, Series> seriesMap;
	};


}

