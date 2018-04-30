#ifndef E2EMDBDATA_H
#define E2EMDBDATA_H

#include<fstream>
#include<cassert>
#include<memory>

namespace E2E
{

	struct Options;

	class DataRoot;
	class Patient;
	class Series;
	class BScan;
	class Study;

	class StringListElement;

	class DictEntryRawData;

	class MDbData
	{
// 		DictEntryRawData*                    dictRawData = nullptr;
		std::unique_ptr<DictEntryRawData>    dictRawData;
		const DictEntryRawData&              mdbDirEntry;
		E2E::DataRoot&                       e2edata;

		void addUnknow2Structure(std::ifstream& stream, const std::string& name);
		bool addUnknowStringList2Structure(std::ifstream& stream);
		bool addUnknowStringList2Structure(StringListElement* baseElement);

		const Options& options;

		MDbData(const E2E::Options& options, std::ifstream& stream, E2E::DataRoot& e2edata, const E2E::DictEntryRawData& mdbDirEntry);
		~MDbData();

		bool isValid(const DictEntryRawData& mdbDirEntry);


		Patient&  getPatient();
		Study  &  getStudy  ();
		Series &  getSeries ();
		BScan  &  getBScan  ();

		void validOrThrow(std::ifstream& stream);
		void readDictRawData(std::ifstream& stream);

	public:
		enum class DataClass { General, Patient, Study, Series, Image };

		static bool evaluate(std::ifstream& stream, E2E::DataRoot& e2edata, const E2E::DictEntryRawData& mdbDirEntry, const E2E::Options& options);

		std::size_t getDataLength() const;
		std::size_t getDataAdress() const;
		int getTypeValue() const;


		DataClass getDataClass() const;
		int getSubId()      const;
		int getImageId()    const;
		int getSeriesId()   const;
		int getStudyId()    const;
		int getPatientId()  const;

		const E2E::DictEntryRawData& getDirEntry()               { return mdbDirEntry; }
		const E2E::DictEntryRawData& getDataHeader()             { assert(dictRawData); return *dictRawData; }

		const Options& getOptions() const                        { return options; }
	};
	
};

#endif // E2EMDBDATA_H
