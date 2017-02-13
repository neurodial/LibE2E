#pragma once

#include "study.h"
#include "substructure_template.h"

namespace E2E
{
	class TextElement;
	class TextElement16;
	class PatientDataElement;
	class PatImage_2335;

	class Patient : public SubstructureTemplate<Study>
	{
		PatientDataElement* patientData = nullptr;
		TextElement*        patientUID  = nullptr;
		TextElement16*      diagnose    = nullptr;

		PatImage_2335*      patImageL   = nullptr;
		PatImage_2335*      patImageR   = nullptr;
	public:
		Patient(E2EData* parent) : SubstructureTemplate(parent) {}
	    virtual ~Patient();

		      Study& getStudy(int studyId)                      { return getAndInsert(studyId)         ; }
		const Study& getStudy(int studyId) const                { return *(substructureMap.at(studyId)); }

		std::size_t getSeriesSize() const                       { return substructureMap.size(); }

		PatientDataElement* getPatientData() const              { return patientData;     }
		void takePatientData(PatientDataElement* pat);
		
		TextElement* getPatientUID() const                      { return patientUID; }
		void takePatientUID(TextElement* uid);

		void takePatImage_2335(PatImage_2335* img);
		PatImage_2335* getPatImageR() const                     { return patImageR; }
		PatImage_2335* getPatImageL() const                     { return patImageL; }


		TextElement16* getDiagnose() const                        { return diagnose; }
		void takeDiagnose(TextElement16* diag);
	};


}

