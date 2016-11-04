#include "studydata.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	StudyData::StudyData(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		if(91 != data.getDataLength())
			throw "Wrong Element";

		stream.seekg(startpos+6);
		StreamHelper::readFStream(stream, &windowsStudyDate);
		stream.seekg(startpos+16);
		StreamHelper::readString(stream, studyOperator, 16);
	}

	E2E::StudyData::~StudyData()
	{

	}



}
