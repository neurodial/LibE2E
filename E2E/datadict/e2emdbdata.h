#ifndef E2EMDBDATA_H
#define E2EMDBDATA_H

#include <fstream>

namespace E2E
{

	class DataRoot;
	class Patient;
	class CScann;
	class BScan;

	class MDbDirEntry;

	class MDbData
	{
		void*                               rawData = nullptr;

		void addUnknow2Structure(std::ifstream& stream, E2E::DataRoot& e2edata);
	public:
		enum class DataClass { General, Patient, Series, Scann, Image  };

		MDbData();
		~MDbData();

		static const std::size_t headerSize = 50;

		bool isValid(const MDbDirEntry& mdbDirEntry);
		
		bool evaluate(std::ifstream& stream, DataRoot& data, const MDbDirEntry& mdbDirEntry);

		DataClass getDataClass() const;
		int getImageSubId() const;
		int getImageId()    const;
		int getScannId()    const;
		int getSeriesId()   const;
		int getPatientId()  const;


		DataRoot* getDataRoot();
		Patient*  getPatient ();
		CScann*   getCScann  ();
		BScan*    getBScan   ();



		std::size_t getDataLength() const;
		std::size_t getDataAdress() const;

	};
	
};

#endif // E2EMDBDATA_H
