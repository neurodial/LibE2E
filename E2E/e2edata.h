#pragma once

#include <string>

#include "structure/root.h"

namespace E2E
{
	struct Options
	{
		bool readThumbnails = false;
		bool readRawData    = true;
	};

	class E2EData
	{
		Options options;

		DataRoot dataRoot;

	public:
		E2EData();
		
		bool readE2EFile(const std::string& filename);

		const DataRoot& getDataRoot() const                     { return dataRoot; }
	};


}



