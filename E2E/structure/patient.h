#pragma once

#include <map>

#include "basestructure.h"
#include "series.h"

namespace E2E
{

	class Patient : public BaseStructure
	{
		std::map<int, Series> seriesMap;
	public:

		Series& getSeries(int seriesId)                         { return seriesMap[seriesId]; }
	};


}
