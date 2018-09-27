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


#include "dictentryrawdata.h"

#include "../streamhelper.h"
#include <cassert>
#include <cstring>


namespace E2E
{
	std::size_t DictEntryRawData::idCounter = 0;

	DictEntryRawData::DictEntryRawData(std::ifstream& stream, std::size_t addr, E2E::DictEntryRawData::EntryType t)
	: type(t)
	, foundAddr(addr)
	{
		id = idCounter;
		++idCounter;

		switch(type)
		{
			case EntryType::Data:
				StreamHelper::readFStream(stream, &(dataRawHeader));
				StreamHelper::readFStream(stream, &(rawdata));
				calcChecksumData();
				break;
			case EntryType::Dir:
				StreamHelper::readFStream(stream, &(rawdata));
				calcChecksumDir();
				break;
		}
	}


	void DictEntryRawData::calcChecksumData()
	{
		calculatedChecksum = 0x8765431C + rawdata.indexAddress;
	}

	void DictEntryRawData::calcChecksumDir()
	{
		calculatedChecksum = 0;
		calculatedChecksum += rawdata.indexAddress;
		calculatedChecksum += rawdata.dataAddress;
		calculatedChecksum += rawdata.dataLengt;
		calculatedChecksum += rawdata.zero       ; // TODO: unknown
		calculatedChecksum += rawdata.patientID  ; // dir + edb
		calculatedChecksum += rawdata.studyID    ; // .edb
		calculatedChecksum += rawdata.seriesID   ; // .sdb
		calculatedChecksum += rawdata.imageID    ;
		calculatedChecksum += rawdata.subID      ;

		// calculatedChecksum += rawdata.unknown    ;
		calculatedChecksum += rawdata.type;

		calculatedChecksum -= 0x789ABCDF;
	}

	bool DictEntryRawData::validIndexEntry() const
	{
		switch(type)
		{
			case EntryType::Data:
				return rawdata.dataAddress == foundAddr && (std::memcmp(dataRawHeader.mdbdataStr, "MDbData", 8) == 0);
			case EntryType::Dir:
				return rawdata.indexAddress == foundAddr;
		}
		assert(false);

		return false; // for release modus and prevent compiler warniung
	}

	bool DictEntryRawData::compare(const E2E::DictEntryRawData& other) const
	{
		return other.rawdata.indexAddress == rawdata.indexAddress
		    && other.rawdata.dataAddress  == rawdata.dataAddress
		    && other.rawdata.dataLengt    == rawdata.dataLengt
		    && other.rawdata.zero         == rawdata.zero
		    && other.rawdata.patientID    == rawdata.patientID
		    && other.rawdata.studyID      == rawdata.studyID
		    && other.rawdata.seriesID     == rawdata.seriesID
		    && other.rawdata.imageID      == rawdata.imageID
		    && other.rawdata.subID        == rawdata.subID

		//    && other.rawdata.unknown      == rawdata.unknown;
		    && other.rawdata.type         == rawdata.type;
		//    && other.rawdata.checksum     == rawdata.checksum*/
	}



	void DictEntryRawData::print(std::ostream& stream) const
	{
		stream << "indexAddress: " << rawdata.indexAddress << '\n';
		stream << "dataAddress : " << rawdata.dataAddress  << '\n';
		stream << "dataLengt   : " << rawdata.dataLengt    << '\n';
		stream << "zero        : " << rawdata.zero         << '\n';
		stream << "patientID   : " << rawdata.patientID    << '\n';
		stream << "studyID     : " << rawdata.studyID      << '\n';
		stream << "seriesID    : " << rawdata.seriesID     << '\n';
		stream << "imageID     : " << rawdata.imageID      << '\n';
		stream << "subID       : " << rawdata.subID        << '\n';
		stream << "unknown     : " << rawdata.unknown      << '\n';
		stream << "type        : " << rawdata.type         << '\n';
		stream << "checksum    : " << rawdata.checksum     << '\n';
		stream << "calculatedChecksum  : " << calculatedChecksum   << '\n';
		stream << "foundAddr           : " << foundAddr            << '\n';
		stream << "isValid             : " << isValid()            << '\n';
	}

}
