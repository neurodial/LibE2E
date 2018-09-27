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

// #include <map>

#include "patient.h"
#include "substructure_template.h"


namespace E2E
{
	class E2EData;
	/*
		int32_t   patient    ; // dir + edb
		int32_t   imageScanID; // .edb
		int32_t   imageDirID ; // .sdb
		int32_t   imageID    ;
		int16_t   imageSubID ;
	*/


// 	class Patient123 : public SubstructureTemplate<Study>
	class DataRoot : public SubstructureTemplate<Patient>
	{
	public:
		DataRoot(E2EData* parent) : SubstructureTemplate<Patient>(parent) {}

		      Patient& getPatient(int patientID)                { return getAndInsert(patientID)   ; }
		const Patient& getPatient(int patientID) const          { return *(substructureMap.at(patientID)); }

		std::size_t getPatientsSize() const                     { return substructureMap.size(); }
	};

}
