#include "e2edata.h"

#include <fstream>
#include <iomanip>

#include "datadict/e2emdbdir.h"
#include "datadict/e2emdbdata.h"
#include "streamhelper.h"


namespace E2E
{

	E2EData::E2EData()
	{

	}




	bool E2EData::readE2EFile(const std::string& filename)
	{
		std::ifstream stream(filename, std::ios::binary | std::ios::in);

		if(!StreamHelper::testString(stream, "CMDb", 4))
			return false;

		stream.seekg(0x20, std::ios_base::cur);

		if(!StreamHelper::testString(stream, "MDbMDir", 7))
			return false;


		MDbDir dir;

		dir.readIndex(stream, 0x4c);

		const std::vector<MDbDirEntry>& vec = dir.getIndexVec();

		for(const MDbDirEntry& dirEntry : vec)
		{
			MDbData data(options);
			data.evaluate(stream, dataRoot, dirEntry);
		}

		return true;
	}


}