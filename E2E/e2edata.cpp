#include "e2edata.h"

#include <fstream>
#include <iomanip>

#include "datadict/e2emdbdir.h"
#include "datadict/e2emdbdata.h"
#include "streamhelper.h"

#include <cpp_framework/callback.h>


namespace E2E
{

	E2EData::E2EData()
	{

	}




	bool E2EData::readE2EFile(const std::string& filename, CppFW::Callback* callback)
	{
		std::ifstream stream(filename, std::ios::binary | std::ios::in);

		if(!StreamHelper::testString(stream, "CMDb", 4))
			return false;

		stream.seekg(0x20, std::ios_base::cur);

		if(!StreamHelper::testString(stream, "MDbMDir", 7))
			return false;



		MDbDir dir;

		dir.readIndex(stream, 0x4c);

		CppFW::Callback callb;
		if(callback)
		{
			callback->callback(0.1);
			callb = callback->createSubTask(0.9, 0.1);
		}

		const std::vector<DictEntryRawData>& vec = dir.getIndexVec();

		double numEntries  = static_cast<double>(vec.size());
		double countEntrie = 0;
		for(const DictEntryRawData& dirEntry : vec)
		{
			MDbData::evaluate(stream, dataRoot, dirEntry, options);
			callb.callback(countEntrie/numEntries);
			countEntrie += 1.0;
		}

		return true;
	}

}
