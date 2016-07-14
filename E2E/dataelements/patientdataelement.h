#pragma once

#include <string>

#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class PatientDataElement : public BaseElement
	{
	public:
		enum class Sex { Unknown, Female = 0x46, Male = 0x4d};
		
		PatientDataElement(std::istream& stream, MDbData& data);
		virtual ~PatientDataElement();

		std::string getForename() const                          { return forename; }
		std::string getSurname () const                          { return surname ; }
		std::string getTitle   () const                          { return title   ; }
		std::string getId      () const                          { return id      ; }
		Sex         getSex     () const                          { return sex     ; }
		
		
	private:
		std::string forename;
		std::string surname ;
		std::string title   ;
		std::string id      ;

		Sex sex = Sex::Unknown;

	};

}

