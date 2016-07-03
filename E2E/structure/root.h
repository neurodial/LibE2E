#pragma once

#include <map>

#include "patient.h"
#include "basestructure.h"


namespace E2E
{
	/*
		int32_t   patient    ; // dir + edb
		int32_t   imageScanID; // .edb
		int32_t   imageDirID ; // .sdb
		int32_t   imageID    ;
		int16_t   imageSubID ;
	*/


	class DataRoot : public BaseStructure
	{
	public:
		typedef std::pair<const int, Patient> PatientsPair;
		typedef std::map<int, Patient>        PatientsMap;
		typedef PatientsMap::iterator         PatientsIterator;
		typedef PatientsMap::const_iterator   PatientsCIterator;

		      Patient& getPatient(int patientID)                { return patientsMap[patientID]   ; }
		const Patient& getPatient(int patientID) const          { return patientsMap.at(patientID); }

		std::size_t getPatientsSize() const                     { return patientsMap.size(); }

		PatientsCIterator begin() const                         { return patientsMap.begin(); }
		PatientsCIterator end()   const                         { return patientsMap.end(); }

	private:
		PatientsMap patientsMap;
	};

}
