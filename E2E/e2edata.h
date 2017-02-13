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
		std::size_t filesLoaded;
		DataRoot dataRoot;

		E2EData(const E2EData&)            = delete;
		E2EData& operator=(const E2EData&) = delete;

	public:
		E2EData();
		
		bool readE2EFile(const std::string& filename, CppFW::Callback* callback = nullptr);

		const DataRoot& getDataRoot() const                            { return dataRoot; }

		Options options;


		std::size_t getFilesLoaded()                             const { return filesLoaded; }
	};


}
