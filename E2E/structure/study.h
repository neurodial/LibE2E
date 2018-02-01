#pragma once

#include <map>

#include "series.h"
#include "substructure_template.h"

namespace E2E
{
	class TextElement;
	class StudyData;
	class EyeData;

	class Study : public SubstructureTemplate<Series>
	{
		TextElement*        studyUID  = nullptr;
		StringListElement*  studyName = nullptr;
		StudyData*          studyData = nullptr;
		EyeData*            eyeDataR  = nullptr;
		EyeData*            eyeDataL  = nullptr;

		void takeEyeData(EyeData* source, EyeData*& dest);
	public:
		Study(E2EData* parent) : SubstructureTemplate(parent) {}
		virtual ~Study();

		      Series& getSeries(int seriesId)                   { return getAndInsert(seriesId)         ; }
		const Series& getSeries(int seriesId) const             { return *(substructureMap.at(seriesId)); }

		std::size_t getCScanSize() const                        { return substructureMap.size(); }
		
		
		TextElement      * getStudyUID() const                  { return studyUID; }
		StringListElement* getStudyName() const                 { return studyName; }
		StudyData        * getStudyData() const                 { return studyData; }
		EyeData          * getEyeDataR () const                 { return eyeDataR ; }
		EyeData          * getEyeDataL () const                 { return eyeDataL ; }


		void takeStudyUID(TextElement* uid);
		void takeStudyName(StringListElement* name);
		void takeStudyData(StudyData* data);
		void takeEyeData(EyeData* eyedata);
	};


}
