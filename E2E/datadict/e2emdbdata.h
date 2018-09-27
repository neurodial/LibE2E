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

		const E2E::DictEntryRawData& getDirEntry()               const { return mdbDirEntry; }
		const E2E::DictEntryRawData& getDataHeader()             const { assert(dictRawData); return *dictRawData; }

		const Options& getOptions()                              const { return options; }
	};
	
};

#endif // E2EMDBDATA_H
