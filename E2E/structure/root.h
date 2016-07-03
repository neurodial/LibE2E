#pragma once

#include <map>

#include "patient.h"
#include "substructure_template.h"


namespace E2E
{
	/*
		int32_t   patient    ; // dir + edb
		int32_t   imageScanID; // .edb
		int32_t   imageDirID ; // .sdb
		int32_t   imageID    ;
		int16_t   imageSubID ;
	*/


	class DataRoot : public SubstructureTemplate<Patient>
	{
	public:
		      Patient& getPatient(int patientID)                { return getAndInsert(patientID)   ; }
		const Patient& getPatient(int patientID) const          { return *(substructureMap.at(patientID)); }

		std::size_t getPatientsSize() const                     { return substructureMap.size(); }
	};

}
