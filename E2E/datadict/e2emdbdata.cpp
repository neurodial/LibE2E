#include "e2emdbdata.h"
#include "e2emdbdir.h"

#include <cstring>
#include <iostream>
#include <iomanip>

#include "../structure/root.h"

//#define DEBUG_OUT(A) std::cout << A;
 #define DEBUG_OUT(A) ;

#include "../streamhelper.h"
#include "../dataelements/baseelement.h"
#include "../dataelements/image.h"
#include "../dataelements/segmentationdata.h"
#include "../dataelements/stringlistelement.h"
#include "../dataelements/patientdataelement.h"
#include "../dataelements/textelement.h"
#include "../dataelements/bscansmetadataelement.h"
#include <E2E/dataelements/bscanmetadataelement.h>
#include <E2E/dataelements/imageregistration.h>
#include <E2E/dataelements/patimage_2335.h>
#include <E2E/dataelements/studydata.h>
#include <E2E/dataelements/slodataelement.h>

#include "../e2edata.h"


E2E::MDbData::DataClass E2E::MDbData::getDataClass() const
{
	const DictEntryRawData::Raw& data = dictRawData->getRaw();
	if(data.imageID != -1)
		return DataClass::Image;
	if(data.seriesID != -1)
		return DataClass::Series;
	if(data.studyID != -1)
		return DataClass::Study;
	if(data.patientID != -1)
		return DataClass::Patient;
	return DataClass::General;

}


namespace E2E
{
	MDbData::MDbData(const E2E::Options& options, std::ifstream& stream, E2E::DataRoot& e2edata, const E2E::DictEntryRawData& mdbDirEntry)
	: mdbDirEntry(mdbDirEntry)
	, e2edata(e2edata)
	, options(options)
	{
		if(mdbDirEntry.getRaw().dataLengt <= 4) // TODO: prüfe dateigröße gegen speicheradresse
			return;

		std::string a;
		stream.seekg(mdbDirEntry.getRaw().dataAddress);


		dictRawData = new DictEntryRawData(stream, stream.tellg(), DictEntryRawData::EntryType::Data); // TODO: move tellg to DictEntryRawData class? complexity?
		// const DictEntryRawData::Raw& data = dictRawData->getRaw();

		// DEBUG_OUT(mdbDirEntry.validChecksum() << '\t' << mdbDirEntry.validIndexEntry() << '\t');
		// DEBUG_OUT(dictRawData->validChecksum() << '\t' << dictRawData->validIndexEntry() << '\t');
		DEBUG_OUT(isValid(mdbDirEntry) << "\t" << std::hex << mdbDirEntry.getRaw().indexAddress << "\t" << mdbDirEntry.getRaw().dataAddress << "\t" << mdbDirEntry.getRaw().dataLengt << "\t" << " (" << std::dec << mdbDirEntry.getRaw().dataLengt << ")")
		DEBUG_OUT( '\t' << mdbDirEntry.getRaw().zero << '\t' << mdbDirEntry.getRaw().patientID << '\t' << mdbDirEntry.getRaw().studyID << '\t' << mdbDirEntry.getRaw().seriesID << '\t' << mdbDirEntry.getRaw().imageID << '\t' << mdbDirEntry.getRaw().subID << '\t')
		// DEBUG_OUT(mdbDirEntry.getRaw().unknown << '\t' << mdbDirEntry.getRaw().type << '\t')
			


		DEBUG_OUT('(' << mdbDirEntry.getRaw().unknown << " - " << data.unknown << ")\t")
		DEBUG_OUT(std::hex << mdbDirEntry.getRaw().type << '\t')
		DEBUG_OUT('(' << (data.checksum - 0x8765431C - mdbDirEntry.getRaw().indexAddress) << ")\t")


		// DEBUG_OUT("[ " /* << mdbDirEntry.calculatedChecksum << '\t' */ << std::dec << (mdbDirEntry.getCalculatedChecksum() - mdbDirEntry.data.checksum - 0x789ABCDF) << " ]\t");


		DEBUG_OUT( static_cast<int>(getDataClass()) << ' ')


		if(isValid(mdbDirEntry))
		{
			bool rawData = true;
			switch(mdbDirEntry.getRaw().type)
			{
				case 0x40000000:
				{
					DEBUG_OUT("Bild");
					try
					{
						Image* image = new Image(stream, *this);
						rawData = false;
						if(getSubId() == 0 && getDataClass() == DataClass::Image)
								getSeries().takeSloImage(image);
						else
						{
							switch(getDataClass())
							{
								case DataClass::Series:
									getSeries().takeSloImage(image);
									break;
								case DataClass::Image:
									getBScan().takeImage(image);
									break;
								default:
									delete image;
									rawData = true;
									std::cerr << "image: unexpected data class";
							}
						}
					}
					catch(const char* c)
					{
						rawData = true;
						std::cerr << c;
					}
					catch(...)
					{
						rawData = true;
								std::cerr << "image: unexpected exception";
					}

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
							case DataClass::Series:
								getSeries().takePixmap(image);
								break;
							case DataClass::Image:
								getBScan().takePixmap(image);
								break;
							default:
								delete image;
								rawData = true;
								std::cerr << "jfif image: unexpected data class";
						}
					}
					break;
				}
				case 0x09: // Patientendaten : Name, ID
					{
						DEBUG_OUT("Patientendaten : Name, ID");
						PatientDataElement* patientData;
						try
						{
							patientData = new PatientDataElement(stream, *this);
							getPatient().takePatientData(patientData);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "patientData can't set\n";
							delete patientData;
						}
					}
					break;
				case 0x0a:
					DEBUG_OUT("apture Mod le 1");
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x0d:
					DEBUG_OUT("Spectralis OCT");
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x3a:
					DEBUG_OUT("StudyData");
					{
						StudyData* studyData;
						try
						{
							studyData = new StudyData(stream, *this);
							getStudy().takeStudyData(studyData);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "studyData can't set\n";
							delete studyData;
						}
					}
					break;

				case 0x34:
					DEBUG_OUT("PatientUID");

					if(getDataClass() == DataClass::Patient)
					{
						TextElement* uid;
						try
						{
							uid = new TextElement(stream, *this);
							getPatient().takePatientUID(uid);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "PatientUID can't set\n";
							delete uid;
						}
					}
					else
						std::cerr << "PatientUID outsite from patient root\n";
					break;
				case 0x35:
					// std::cout << "StudyUID?";
					DEBUG_OUT("StudyUID");

					if(getDataClass() == DataClass::Study)
					{
						TextElement* uid;
						try
						{
							uid = new TextElement(stream, *this);
							getStudy().takeStudyUID(uid);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "StudyUID can't set\n";
							delete uid;
						}
					}
					else
						std::cerr << "StudyUID outsite from patient root\n";
					break;
				case 0x36:
					// std::cout << "UUID?";
					DEBUG_OUT("UUID");
					if(getDataClass() == DataClass::Series)
					{
						TextElement* uid;
						try
						{
							uid = new TextElement(stream, *this);
							getSeries().takeSeriesUID(uid);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "SeriesUID can't set\n";
							delete uid;
						}
					}
					else
						std::cerr << "SeriesUID outsite from patient root\n";
					break;
				case 0xe8:
					// std::cout << "UUID?";
					DEBUG_OUT("UUID");
					break;
				case 0xe9:
					DEBUG_OUT("Unbekannte ID");
					break;
				case 0x2328:
					// std::cout << "Gerätename?";
					DEBUG_OUT("PTC?");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x2329:
					// std::cout << "Gerätename?";
					DEBUG_OUT("Gerätename");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x232d:
					// std::cout << "Retina?";
					DEBUG_OUT("Retina");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x232e:
					// std::cout << "OCT ART Volume?";
					DEBUG_OUT("OCT ART Volume");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x232f:
					// std::cout << "Infra-Red     IR?";
					DEBUG_OUT("Infra-Red     IR?");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x2330:
					// std::cout << "OCT?";
					DEBUG_OUT("OCT");
					addUnknowStringList2Structure(stream);
					rawData = false;
					break;
				case 0x2335:
					if(getDataClass() == DataClass::Patient)
					{
						PatImage_2335* image = new PatImage_2335(stream, *this);
						try
						{
							getPatient().takePatImage_2335(image);
							rawData = false;
						}
						catch(...)
						{
							delete image;
							std::cerr << "PatImage_2335 cant set\n";
						}
					}
					DEBUG_OUT("PatImage");
					break;
				case 0x2714:
					if(getDataClass() == DataClass::Image)
					{
						BScanMetaDataElement* metaData = new BScanMetaDataElement(stream, *this);
						getBScan().takeBScanMetaDataElement(metaData);
						rawData = false;
					}
					// std::cout << "OCT?";
					DEBUG_OUT("BScanMetaData");
					break;
				case 0x2726: // Image registration (Stern-Scan)
				case 0x271c: // Image registration
					DEBUG_OUT("Bildregistrierung");
					if(getDataClass() == DataClass::Image)
					{
						ImageRegistration* registration;
						try
						{
							registration = new ImageRegistration(stream, *this);
							getBScan().takeImageRegistrationData(registration);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "BScansMetaDataElement can't set\n";
							delete registration;
						}
					}
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x271d: // Bildmetadaten
					DEBUG_OUT("Bildmetadaten");
					if(getDataClass() == DataClass::Series)
					{
						BScansMetaDataElement* metaData;
						try
						{
							metaData = new BScansMetaDataElement(stream, *this);
							getSeries().takeBScansMetaData(metaData);
							rawData = false;
						}
						catch(...)
						{
							std::cerr << "BScansMetaDataElement can't set\n";
							delete metaData;
						}
					}
					// e2edata->imageMetaData.readData(stream);
					break;
				case 0x2723: // Segentierungsdaten
					DEBUG_OUT("Segentierungsdaten");
					if(getDataClass() == DataClass::Image)
					{
						SegmentationData* segData = new SegmentationData(stream, *this);
						rawData = false;
						getBScan().takeSegmentationData(segData);
					}
					else
						std::cerr << "SegmentationData outsite from a image\n";
					break;
				case 0x2729: // SloDataElement
					DEBUG_OUT("SloDataElement");
					if(getDataClass() == DataClass::Series)
					{
						SloDataElement* sloData;
						try
						{
							sloData = new SloDataElement(stream, *this);
							rawData = false;
							getSeries().takeSloDataElement(sloData);
						}
						catch(...)
						{
							std::cerr << "SloDataElement can't set\n";
							delete sloData;
						}
					}
					else
						std::cerr << "SloDataElement outsite from a Series\n";
					break;
			}

			if(rawData && options.readRawData)
				addUnknow2Structure(stream);

		}
		DEBUG_OUT(std::endl)
	}

	MDbData::~MDbData()
	{
		delete dictRawData;
	}


	inline bool MDbData::isValid(const DictEntryRawData& mdbDirEntry)
	{
		return dictRawData->isValid() && mdbDirEntry.compare(*dictRawData);
	}



	void MDbData::addUnknow2Structure(std::ifstream& stream)
	{
		BaseElement* baseElement = new BaseElement(stream, *this);


		switch(getDataClass())
		{
			case DataClass::General:
				e2edata.takeRawElement(baseElement);
				break;
			case DataClass::Patient:
				getPatient().takeRawElement(baseElement);
				break;
			case DataClass::Study:
				getStudy().takeRawElement(baseElement);
				break;
			case DataClass::Series:
				getSeries().takeRawElement(baseElement);
				break;
			case DataClass::Image:
				getBScan().takeRawElement(baseElement);
				break;
		}
	}

	bool MDbData::addUnknowStringList2Structure(std::ifstream& stream)
	{
		StringListElement* baseElement = nullptr;
		try
		{
			baseElement = new StringListElement(stream, *this);
		}
		catch(...)
		{
			MDbData::addUnknow2Structure(stream);
			return false;
		}


		switch(getDataClass())
		{
			case DataClass::General:
				e2edata.takeStringListElement(baseElement);
				break;
			case DataClass::Patient:
				getPatient().takeStringListElement(baseElement);
				break;
			case DataClass::Study:
				getStudy().takeStringListElement(baseElement);
				break;
			case DataClass::Series:
				getSeries().takeStringListElement(baseElement);
				break;
			case DataClass::Image:
				getBScan().takeStringListElement(baseElement);
				break;
		}
		return true;
	}


	int MDbData::getSubId() const
	{
		return dictRawData->getRaw().subID;
	}

	int MDbData::getImageId() const
	{
		return dictRawData->getRaw().imageID;
	}

	int MDbData::getSeriesId() const
	{
		return dictRawData->getRaw().seriesID;
	}

	int MDbData::getStudyId() const
	{
		return dictRawData->getRaw().studyID;
	}

	int MDbData::getPatientId() const
	{
		return dictRawData->getRaw().patientID;
	}

	std::size_t MDbData::getDataAdress() const
	{

		return dictRawData->getRaw().dataAddress;
	}

	std::size_t MDbData::getDataLength() const
	{
		return dictRawData->getRaw().dataLengt;
	}


	inline BScan& MDbData::getBScan()
	{
		return e2edata.getPatient(getPatientId()).getStudy(getStudyId()).getSeries(getSeriesId()).getBScan(getImageId());
	}

	inline Series& MDbData::getSeries()
	{
		return e2edata.getPatient(getPatientId()).getStudy(getStudyId()).getSeries(getSeriesId());
	}

	inline Study& MDbData::getStudy()
	{
		return e2edata.getPatient(getPatientId()).getStudy(getStudyId());
	}

	inline Patient& MDbData::getPatient()
	{
		return e2edata.getPatient(getPatientId());
	}


	int MDbData::getTypeValue() const
	{
		return dictRawData->getRaw().type;
	}


	bool MDbData::evaluate(std::ifstream& stream, DataRoot& e2edata, const DictEntryRawData& mdbDirEntry, const Options& options)
	{
		try
		{
			MDbData data(options, stream, e2edata, mdbDirEntry);
		}
		catch(...)
		{
			return false;
		}
		return true;
	}


	
}

