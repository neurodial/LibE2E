#include "patient.h"

namespace E2E
{

	Patient::~Patient()
	{
		delete patientName;
	}


	void Patient::takePatientName(PatientNameElement* pat)
	{
		delete patientName;
		patientName = pat;
	}


}