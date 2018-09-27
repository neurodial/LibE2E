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


#pragma once

#include <string>

#include "structure/root.h"

namespace CppFW { class Callback; }

namespace E2E
{
	struct Options
	{
		bool readThumbnails  = false;
		bool readRawData     = false;
		bool readBScanImages = true ;
	};

	class E2EData
	{
		std::size_t filesLoaded;
		DataRoot dataRoot;

		E2EData(const E2EData&)            = delete;
		E2EData& operator=(const E2EData&) = delete;

	public:
		E2EData();
		
		bool readE2EFile(const std::string& filename, CppFW::Callback* callback = nullptr);

		const DataRoot& getDataRoot() const                            { return dataRoot; }

		Options options;


		std::size_t getFilesLoaded()                             const { return filesLoaded; }
	};


}
