#pragma once

#include <map>

#include "cscan.h"
#include "substructure_template.h"

namespace E2E
{


	class Series : public SubstructureTemplate<CScan>
	{
	public:

		      CScan& getCScan(int cscanId)                      { return getAndInsert(cscanId)         ; }
		const CScan& getCScan(int cscanId) const                { return *(substructureMap.at(cscanId)); }

		std::size_t getCScanSize() const                        { return substructureMap.size(); }
	};


}
