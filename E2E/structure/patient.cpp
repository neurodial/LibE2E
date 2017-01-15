#include "patient.h"

#include "../dataelements/patientdataelement.h"
#include "../dataelements/textelement.h"
#include "../dataelements/textelement16.h"
#include <E2E/dataelements/patimage_2335.h>


namespace E2E
{

	Patient::~Patient()
	{
		delete patientData;
		delete patientUID;

		delete patImageL;
		delete patImageR;

		delete diagnose;
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

	void Patient::takePatImage_2335(PatImage_2335* img)
	{
		switch(img->getType())
		{
			case 'L':
				if(!patImageL)
					patImageL = img;
				else
					throw "mutible patImageL";
				break;
			case 'R':
				if(!patImageR)
					patImageR = img;
				else
					throw "mutible patImageR";
				break;
			default:
				throw "unknown patImage Type";
		}

	}

	void Patient::takeDiagnose(TextElement16* diag)
	{
		if(diagnose)
			throw "multible diagnose";
		diagnose = diag;
	}

}
