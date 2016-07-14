#include "patientdataelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

namespace E2E
{
	PatientDataElement::PatientDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		std::size_t startpos = stream.tellg();

		if(131 != data.getDataLength())
			throw "Wrong Element";

		StreamHelper::readString(stream, forename, 30);
		stream.seekg(startpos+31);
		StreamHelper::readString(stream, surname, 50);
		stream.seekg(startpos+82);
		StreamHelper::readString(stream, title, 10);
		
		char sexChar;
		stream.seekg(startpos+101);
		StreamHelper::readFStream(stream, &sexChar);
		// stream.seekg(startpos+102);
		StreamHelper::readString(stream, id, 20);
		
		
		switch(sexChar)
		{
			case 'F':
				sex = Sex::Female;
				break;
			case 'M':
				sex = Sex::Male;
				break;
			default:
				// TODO:
				break;
		}
	}

	E2E::PatientDataElement::~PatientDataElement()
	{

	}



}