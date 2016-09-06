#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class StudyData : public BaseElement
	{
	public:
		StudyData(std::istream& stream, MDbData& data);
		virtual ~StudyData();

		std::string getOperator() const                          { return studyOperator; }
		double getWindowsStudyDate() const                       { return windowsStudyDate; }


	private:
		std::string studyOperator;

		double windowsStudyDate;


	};

}

