#pragma once

#include <map>

#include "study.h"
#include "substructure_template.h"

namespace E2E
{
	class TextElement;
	class PatientDataElement;

	class Patient : public SubstructureTemplate<Study>
	{
		PatientDataElement* patientData = nullptr;
		TextElement*        patientUID  = nullptr;
	public:
	    virtual ~Patient();

		      Study& getStudy(int seriesId)                     { return getAndInsert(seriesId)         ; }
		const Study& getStudy(int seriesId) const               { return *(substructureMap.at(seriesId)); }

		std::size_t getSeriesSize() const                       { return substructureMap.size(); }

		PatientDataElement* getPatientData() const              { return patientData;     }
		void takePatientData(PatientDataElement* pat);
		
		TextElement* getPatientUID() const                      { return patientUID; }
		void takePatientUID(TextElement* uid);
	};


}

