#include "baseelement.h"

#include "../datadict/e2emdbdata.h"

namespace E2E
{

	E2E::BaseElement::BaseElement(std::istream& stream, E2E::MDbData& data)
	{
		std::size_t pos    = stream.tellg();
		std::size_t readLengt  = data.getDataLength(); // TODO
		std::size_t readAdress = data.getDataAdress() + 60;

		rawData = new char[readLengt];

		stream.seekg(readAdress);
		stream.read(rawData, readLengt);
		rawDataLength = readLengt; // data.getDataLength(); //

		stream.seekg(pos);
	}

	BaseElement::~BaseElement()
	{
		delete rawData;
	}



}