#pragma once

#include <map>

#include "cscann.h"
#include "basestructure.h"

namespace E2E
{


	class Series : public BaseStructure
	{
		std::map<int, CScann> cscans;
	public:

		CScann& getCScan(int id)                                 { return cscans[id]; }
	};


}
