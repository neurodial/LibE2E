#pragma once

#include <map>

#include "series.h"
#include "substructure_template.h"

namespace E2E
{

	class PatientNameElement;

	class Patient : public SubstructureTemplate<Series>
	{
		PatientNameElement* patientName = nullptr;
	public:
	    virtual ~Patient();

		      Series& getSeries(int seriesId)                   { return getAndInsert(seriesId)         ; }
		const Series& getSeries(int seriesId) const             { return *(substructureMap.at(seriesId)); }

		std::size_t getSeriesSize() const                       { return substructureMap.size(); }

		PatientNameElement* getPatientName() const              { return patientName;     }
		void takePatientName(PatientNameElement* pat);
	};


}

