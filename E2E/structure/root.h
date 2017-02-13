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
