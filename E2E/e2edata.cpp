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


#include "e2edata.h"

#include<iostream>
#include <fstream>
#include <iomanip>

#include "datadict/e2emdbdir.h"
#include "datadict/e2emdbdata.h"
#include "streamhelper.h"

#include <oct_cpp_framework/callback.h>


namespace E2E
{

	E2EData::E2EData()
	: filesLoaded(0)
	, dataRoot(this)
	{

	}




	bool E2EData::readE2EFile(const std::string& filename, CppFW::Callback* callback)
	{
		std::ifstream stream(filename, std::ios::binary | std::ios::in);
		if(!stream)
		{
			std::cerr << "Can't open file " << filename << '\n';
			return false;
		}

		if(!StreamHelper::testString(stream, "CMDb", 4))
		{
			std::cerr << "file is not of type E2E: " << filename << '\n';
			return false;
		}

		stream.seekg(0x20, std::ios_base::cur);

		if(!StreamHelper::testString(stream, "MDbMDir", 7))
		{
			std::cerr << "file is not of type E2E: " << filename << '\n';
			return false;
		}



		MDbDir dir;

		dir.readIndex(stream, 0x4c);

		CppFW::Callback callb;
		if(callback)
		{
			callback->callback(0.1);
			callb = callback->createSubTask(0.9, 0.1);
		}

		const std::vector<DictEntryRawData>& vec = dir.getIndexVec();

		CppFW::CallbackStepper dictCallbackStepper(&callb, vec.size());
		for(const DictEntryRawData& dirEntry : vec)
		{
			MDbData::evaluate(stream, dataRoot, dirEntry, options);
			++dictCallbackStepper;
		}

		++filesLoaded;

		return true;
	}

}
