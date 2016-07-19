#pragma once

#include <vector>
#include <fstream>

#include "dictentryrawdata.h"


namespace E2E
{
	class MDbDir
	{
	public:
		void readIndex(std::ifstream& stream, uint32_t linkAddr);
		
		const std::vector<DictEntryRawData>& getIndexVec() const         { return index; };
	private:
		std::vector<DictEntryRawData> index;
	};
	
}