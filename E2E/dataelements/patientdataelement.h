/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


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
		double      getWinBDate() const                          { return windowsBirthDate; }
		
		
	private:
		std::string forename;
		std::string surname ;
		std::string title   ;
		std::string id      ;

		double windowsBirthDate;

		Sex sex = Sex::Unknown;

	};

}

