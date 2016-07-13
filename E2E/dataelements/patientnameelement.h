#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class PatientNameElement : public BaseElement
	{
		std::string forename;
		std::string surname ;
		std::string id      ;

	public:
		PatientNameElement(std::istream& stream, MDbData& data);
		virtual ~PatientNameElement();

		std::string getForename() const                          { return forename; }
		std::string getSurname () const                          { return surname ; }
		std::string getId      () const                          { return id      ; }

	};

}

