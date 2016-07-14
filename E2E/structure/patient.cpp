#include "patient.h"

#include "../dataelements/patientdataelement.h"
#include "../dataelements/textelement.h"


namespace E2E
{

	Patient::~Patient()
	{
		delete patientData;
		delete patientUID;
	}


	void Patient::takePatientData(PatientDataElement* pat)
	{
		if(patientData)
			throw "multible PatientData";
		patientData = pat;
	}

	void Patient::takePatientUID(TextElement* uid)
	{
		if(patientUID)
			throw "multible PatientUID";
		patientUID = uid;
	}


}