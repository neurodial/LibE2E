#include "bscansmetadataelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"


#include <iostream>

namespace
{

	struct Header
	{
		uint32_t undef[3];
		uint32_t numImages;
	} __attribute__((packed));;

	struct RawData
	{
		uint32_t undef[12];
		float x1;
		float y1;
		float x2;
		float y2;
		uint32_t undef2[5];
	} __attribute__((packed));

	void copyBScansData(E2E::BScansMetaDataElement::BScansData& data, const RawData& rawData)
	{
		data.x1 = rawData.x1;
		data.y1 = rawData.y1;
		data.x2 = rawData.x2;
		data.y2 = rawData.y2;
	}

	std::ostream& operator<<(std::ostream& stream, const RawData& data)
	{
		for(int i=0; i<sizeof(data.undef)/sizeof(data.undef[0]); ++i)
			stream << data.undef[i] << '\t';

		stream << data.x1 << '\t';
		stream << data.y1 << '\t';
		stream << data.x2 << '\t';
		stream << data.y2 << '\t';

		for(int i=0; i<sizeof(data.undef2)/sizeof(data.undef2[0]); ++i)
			stream << data.undef2[i] << '\t';

		return stream;
	}
}


namespace E2E
{

	BScansMetaDataElement::BScansMetaDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		Header header;
		StreamHelper::readFStream(stream, &header);

		// TODO size check

		for(int i=0; i<header.numImages; ++i)
		{
			BScansData dataField;
			RawData rawDataField;
			StreamHelper::readFStream(stream, &(rawDataField));

			std::cout << rawDataField << std::endl;

			copyBScansData(dataField, rawDataField);
			dataVec.push_back(dataField);
		}

	}

	BScansMetaDataElement::~BScansMetaDataElement()
	{

	}


}


/*

	class ImageMetaData
	{
	public:


		const Data& getData(std::size_t pos) const { return dataVec.at(pos); }
		std::size_t getNumData()             const { return dataVec.size();  }

		void readData(std::istream& stream)
		{
			readFStream(stream, &header);

			std::cout << " - numImages: " << header.numImages;

			for(int i=0; i<header.numImages; ++i)
			{
				Data dataField;
				readFStream(stream, &(dataField.raw));
				dataVec.push_back(dataField);

				std::cout << '\n' << dataField.raw.sloPos[0] << '\t' << dataField.raw.sloPos[1] << '\t' << dataField.raw.sloPos[2] << '\t' << dataField.raw.sloPos[3];
			}
		}

	private:
		Header header;
		std::vector<Data> dataVec;
	};

	*/

