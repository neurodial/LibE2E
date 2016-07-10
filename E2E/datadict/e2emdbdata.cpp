#include "e2emdbdata.h"
#include "e2emdbdir.h"

#include <cstring>
#include <iostream>
#include <iomanip>

#include "../structure/root.h"

#define DEBUG_OUT(A) std::cout << A;
// #define DEBUG_OUT(A)

#include "../streamhelper.h"
#include "../dataelements/baseelement.h"
#include "../dataelements/image.h"
#include "../dataelements/segmentationdata.h"

#include "../e2edata.h"

namespace
{

	struct MDbDataRawData
	{
		uint8_t  mdbdataStr[0x08]; // MDbData + \0
		uint32_t zero1;
		uint32_t undef;
		uint32_t indexAddress;
		uint32_t dataAddress;
		uint32_t dataLengt;

		// uint8_t  dataBlock[0x16];
		uint32_t  zero       ; // TODO: unknown
		int32_t   patient    ; // dir + edb
		int32_t   series     ; // .edb
		int32_t   scann      ; // .sdb
		int32_t   imageID    ;
		int16_t   imageSubID ;

		uint8_t  unknownDataBlock[10];

	} __attribute__((packed));

	MDbDataRawData* getMDbDataRawData(void* voidData) { return reinterpret_cast<MDbDataRawData*>(voidData); }

}


E2E::MDbData::DataClass E2E::MDbData::getDataClass() const
{
	MDbDataRawData& data = *(getMDbDataRawData(rawData));
	if(data.imageID != -1)
		return DataClass::Image;
	if(data.scann != -1)
		return DataClass::Scann;
	if(data.series != -1)
		return DataClass::Series;
	if(data.patient != -1)
		return DataClass::Patient;
	return DataClass::General;

}


static_assert(sizeof(MDbDataRawData) == E2E::MDbData::headerSize, "headerSize is incorrect");


namespace E2E
{
	MDbData::MDbData(const Options& options)
	: rawData(new MDbDataRawData)
	, options(options)
	{

	}

	MDbData::~MDbData()
	{
		delete getMDbDataRawData(rawData);
	}

	
	bool MDbData::isValid(const MDbDirEntry& mdbDirEntry)
	{
		MDbDataRawData& data = *(getMDbDataRawData(rawData));

		return memcmp(data.mdbdataStr, "MDbData", 8) == 0
		    && mdbDirEntry.data.indexAddress == data.indexAddress
		    && mdbDirEntry.data.dataAddress  == data.dataAddress
		    && mdbDirEntry.data.dataLengt    == data.dataLengt
		    && mdbDirEntry.data.zero         == data.zero
		    && mdbDirEntry.data.patient      == data.patient
		    && mdbDirEntry.data.imageScanID  == data.series
		    && mdbDirEntry.data.imageDirID   == data.scann
		    && mdbDirEntry.data.imageID      == data.imageID
		    && mdbDirEntry.data.imageSubID   == data.imageSubID ;
	}

	
	bool MDbData::evaluate(std::ifstream& stream, DataRoot& e2edata, const MDbDirEntry& mdbDirEntry)
	{

		stream.seekg(mdbDirEntry.data.dataAddress);

//		MDbData data;
		MDbDataRawData& data = *(reinterpret_cast<MDbDataRawData*>(rawData));

		StreamHelper::readFStream(stream, &(data));

		DEBUG_OUT(isValid(mdbDirEntry) << "\t" << std::hex << mdbDirEntry.data.indexAddress << "\t" << mdbDirEntry.data.dataAddress << "\t" << mdbDirEntry.data.dataLengt << "\t" << " (" << std::dec << mdbDirEntry.data.dataLengt << ")")
		DEBUG_OUT( '\t' << mdbDirEntry.data.zero << '\t' << mdbDirEntry.data.patient << '\t' << mdbDirEntry.data.imageScanID << '\t' << mdbDirEntry.data.imageDirID << '\t' << mdbDirEntry.data.imageID << '\t' << mdbDirEntry.data.imageSubID << '\t')
		for(std::size_t i=0; i<sizeof(MDbDirEntry::RawData::undef); ++i)
			DEBUG_OUT( std::hex << std::setw(2) << (static_cast<unsigned>(mdbDirEntry.data.undef[i]) & 0xFF) << ' ')


		DEBUG_OUT( static_cast<int>(getDataClass()) << ' ')
		//std::cout << "Lese " << std::hex << set.data.dataAddress;

		if(isValid(mdbDirEntry))
		{
			bool rawData = true;
			switch(mdbDirEntry.data.undef[2])
			{
				case 0x00:
				{
					DEBUG_OUT("Bild");
					Image* image = new Image(stream, *this);
					rawData = false;
					switch(getDataClass())
					{
						case DataClass::Scann:
							getCScan(e2edata).takeSloImage(image);
							break;
						case DataClass::Image:
							getBScan(e2edata).takeImage(image);
							break;
						default:
							delete image;
							rawData = true;
							std::cerr << "image: unexpected data class";
					}

					// readImage(stream, cscan, set);
					// e2edata.getPatient();
					break;
				}
				case 0x02: // Vorschaubild JFIF
				{
					DEBUG_OUT("Vorschaubild JFIF");
					if(options.readThumbnails)
					{
						Image* image = Image::fromJFIF(stream, *this);
						rawData = false;
						switch(getDataClass())
						{
							case DataClass::Scann:
								getCScan(e2edata).takePixmap(image);
								break;
							case DataClass::Image:
								getBScan(e2edata).takePixmap(image);
								break;
							default:
								delete image;
								rawData = true;
								std::cerr << "image: unexpected data class";
						}
					}
					break;
				}
				case 0x09: // Patientendaten : Name, ID
					DEBUG_OUT("Patientendaten : Name, ID");
					/*PatientData pdata;
					StreamHelper::readFStream(stream, &(pdata.data));

					pdata.printData();*/
					break;
				case 0x0a:
					DEBUG_OUT("apture Mod le 1");
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x0d:
					DEBUG_OUT("Spectralis OCT");
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x1d: // Bildmetadaten
					DEBUG_OUT("Bildmetadaten");
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x23: // Segentierungsdaten
					DEBUG_OUT("Segentierungsdaten");
					if(getDataClass() == DataClass::Image)
					{
						SegmentationData* segData = new SegmentationData(stream, *this);
						rawData = false;
						getBScan(e2edata).takeSegmentationData(segData);
					}
					else
						std::cerr << "SegmentationData outsite from a image\n";
					break;
				case 0x29:
					// std::cout << "Gerätename?";
					DEBUG_OUT("Gerätename");
					break;
				case 0x2d:
					// std::cout << "Retina?";
					DEBUG_OUT("Retina");
					break;
				case 0x2e:
					// std::cout << "OCT ART Volume?";
					DEBUG_OUT("OCT ART Volume");
					break;
				case 0x2f:
					// std::cout << "Infra-Red     IR?";
					DEBUG_OUT("Infra-Red     IR?");
					break;
				case 0x30:
					// std::cout << "OCT?";
					DEBUG_OUT("OCT");
					break;
				case 0x3a:
					// std::cout << "ua. Operatorname?";
					DEBUG_OUT("ua. Operatorname");
					break;
				case 0x35:
					// std::cout << "StudyUID?";
					DEBUG_OUT("StudyUID");
					break;
				case 0x36:
					// std::cout << "UUID?";
					DEBUG_OUT("UUID");
					break;
				case 0xe8:
					// std::cout << "UUID?";
					DEBUG_OUT("UUID");
					break;
				case 0xe9:
					DEBUG_OUT("Unbekannte ID");
					break;
			}

			if(rawData && options.readRawData)
				addUnknow2Structure(stream, e2edata);

		}
		DEBUG_OUT(std::endl)

		return true;
	}


	void MDbData::addUnknow2Structure(std::ifstream& stream, DataRoot& e2edata)
	{
		BaseElement* baseElement = new BaseElement(stream, *this);


		switch(getDataClass())
		{
			case DataClass::General:
				e2edata.takeRawElement(baseElement);
				break;
			case DataClass::Patient:
				e2edata.getPatient(getPatientId()).takeRawElement(baseElement);
				break;
			case DataClass::Series:
				e2edata.getPatient(getPatientId()).getSeries(getSeriesId()).takeRawElement(baseElement);
				break;
			case DataClass::Scann:
				e2edata.getPatient(getPatientId()).getSeries(getSeriesId()).getCScan(getScanId()).takeRawElement(baseElement);
				break;
			case DataClass::Image:
				e2edata.getPatient(getPatientId()).getSeries(getSeriesId()).getCScan(getScanId()).getBScan(getImageId()).takeRawElement(baseElement);
				break;
		}
	}


	int MDbData::getImageSubId() const
	{
		return getMDbDataRawData(rawData)->imageSubID;
	}

	int MDbData::getImageId() const
	{
		return getMDbDataRawData(rawData)->imageID;
	}

	int MDbData::getScanId() const
	{
		return getMDbDataRawData(rawData)->scann;
	}

	int MDbData::getSeriesId() const
	{
		return getMDbDataRawData(rawData)->series;
	}

	int MDbData::getPatientId() const
	{
		return getMDbDataRawData(rawData)->patient;
	}

	std::size_t MDbData::getDataAdress() const
	{

		return getMDbDataRawData(rawData)->dataAddress;
	}

	std::size_t MDbData::getDataLength() const
	{
		return getMDbDataRawData(rawData)->dataLengt;
	}


	BScan& MDbData::getBScan(DataRoot& e2edata)
	{
		return e2edata.getPatient(getPatientId()).getSeries(getSeriesId()).getCScan(getScanId()).getBScan(getImageId());
	}

	CScan& MDbData::getCScan(DataRoot& e2edata)
	{
		return e2edata.getPatient(getPatientId()).getSeries(getSeriesId()).getCScan(getScanId());
	}

	Series& MDbData::getSeries(DataRoot& e2edata)
	{
		return e2edata.getPatient(getPatientId()).getSeries(getSeriesId());
	}

	Patient& MDbData::getPatient(DataRoot& e2edata)
	{
		return e2edata.getPatient(getPatientId());
	}

	
}

