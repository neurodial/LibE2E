#ifndef E2EMDBDATA_H
#define E2EMDBDATA_H

#include <fstream>

namespace E2E
{

	struct Options;

	class DataRoot;
	class Patient;
	class CScan;
	class BScan;
	class Series;

	class MDbDirEntry;

	class MDbData
	{
		void*                               rawData = nullptr;

		void addUnknow2Structure(std::ifstream& stream, E2E::DataRoot& e2edata);
		bool addUnknowStringList2Structure(std::ifstream& stream, DataRoot& e2edata);

		const Options& options;
	public:
		enum class DataClass { General, Patient, Series, Scann, Image  };

		MDbData(const E2E::Options& options);
		~MDbData();

		static const std::size_t headerSize = 60;

		bool isValid(const MDbDirEntry& mdbDirEntry);
		
		bool evaluate( std::ifstream& stream, E2E::DataRoot& e2edata, const E2E::MDbDirEntry& mdbDirEntry);

		DataClass getDataClass() const;
		int getImageSubId() const;
		int getImageId()    const;
		int getScanId()     const;
		int getSeriesId()   const;
		int getPatientId()  const;


		Patient&  getPatient(DataRoot& e2edata);
		Series &  getSeries (DataRoot& e2edata);
		CScan  &  getCScan  (DataRoot& e2edata);
		BScan  &  getBScan  (DataRoot& e2edata);

		const Options& getOptions() const                        { return options; }


		std::size_t getDataLength() const;
		std::size_t getDataAdress() const;

		int getTypeValue() const;
	};
	
};

#endif // E2EMDBDATA_H
