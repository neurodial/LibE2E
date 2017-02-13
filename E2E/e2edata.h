#pragma once

#include <string>

#include "structure/root.h"

namespace CppFW { class Callback; }

namespace E2E
{
	struct Options
	{
		bool readThumbnails = false;
		bool readRawData    = false;
	};

	class E2EData
	{

		DataRoot dataRoot;

	public:
		E2EData();
		
		bool readE2EFile(const std::string& filename, CppFW::Callback* callback = nullptr);

		const DataRoot& getDataRoot() const                     { return dataRoot; }

		Options options;
	};


}
