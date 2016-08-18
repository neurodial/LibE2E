#include "bscanmetadataelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include "../e2e_packhelper.h"


#include <iostream>

namespace
{
	PACKSTRUCT(
	struct MetaDataStruct
	{
		uint32_t unknown1;
		uint32_t imgSizeX;
		uint32_t imgSizeY;
		float    posX1;
		float    posY1;
		float    posX2;
		float    posY2;
	});

	void copyBScansData(const MetaDataStruct& mds, E2E::BScanMetaDataElement::BScanData& bsd)
	{
		bsd.x1 = mds.posX1;
		bsd.y1 = mds.posY1;
		bsd.x2 = mds.posX2;
		bsd.y2 = mds.posY2;
	}
}


namespace E2E
{

	BScanMetaDataElement::BScanMetaDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		// TODO size check

		MetaDataStruct header;
		StreamHelper::readFStream(stream, &header);

		copyBScansData(header, bscanData);

	}

	BScanMetaDataElement::~BScanMetaDataElement()
	{

	}


}