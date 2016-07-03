#include "baseelement.h"

#include "../datadict/e2emdbdata.h"

namespace E2E
{

	E2E::BaseElement::BaseElement(std::istream& stream, E2E::MDbData& data)
	{
		std::size_t pos    = stream.tellg();
		std::size_t readLengt  = data.getDataLength() + 65; // TODO
		std::size_t readAdress = data.getDataAdress();

		rawData = new char[readLengt];

		stream.seekg(readAdress);
		stream.read(rawData, readLengt);
		rawDataLength = data.getDataLength(); // readLengt;

		stream.seekg(pos);
	}

	BaseElement::~BaseElement()
	{
		delete rawData;
	}



}