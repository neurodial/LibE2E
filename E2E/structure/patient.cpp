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
		delete ancestry;
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

	void Patient::takeAncestry(StringListElement* anc)
	{
		if(ancestry)
			throw "multible ancestry";
		ancestry = anc;
	}
}
