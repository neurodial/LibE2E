#include "patientnameelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	PatientNameElement::PatientNameElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		if(131 != data.getDataLength())
			throw "Wrong Element";

		StreamHelper::readString(stream, forename, 30);
		stream.seekg(startpos+31);
		StreamHelper::readString(stream, surname, 90);
		stream.seekg(startpos+102);
		StreamHelper::readString(stream, id, 29);
	}

	E2E::PatientNameElement::~PatientNameElement()
	{

	}



}