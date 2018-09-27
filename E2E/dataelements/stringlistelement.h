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

#include <istream>
#include <vector>
#include <string>


#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class StringListElement : public BaseElement
	{
	public:
		typedef std::vector<std::u16string> StringList;
		StringListElement(std::istream& stream, MDbData& data);
		virtual ~StringListElement();

		const std::u16string& getString(std::size_t pos) const   { return stringList.at(pos); }

		StringList::const_iterator begin() const                 { return stringList.begin(); }
		StringList::const_iterator end()   const                 { return stringList.end()  ; }

		std::size_t                size()  const                 { return stringList.size() ; }
		
	private:
		StringList stringList;
	};
}


