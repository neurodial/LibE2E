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

#include <fstream>

namespace StreamHelper
{
	template<typename T>
	inline void readFStream(std::istream& stream, T* dest, std::size_t num = 1)
	{
		stream.read(reinterpret_cast<char*>(dest), sizeof(T)*num);
	}

	template<typename T>
	std::size_t readString(std::istream& stream, std::basic_string<T>& string, std::size_t maxChars)
	{
		T ch;
		string.reserve(maxChars);
		std::size_t charRead;
		for(charRead = 0; charRead < maxChars; ++charRead)
		{
			StreamHelper::readFStream(stream, &ch);
			if(ch == 0)
				break;
			string.push_back(ch);
		}
		return charRead;
	}

	inline bool testString(std::istream& stream, const char* const str, std::size_t len)
	{
		char ch;
		const char* strTest = str;
		for(std::size_t i=0; i<len; ++i)
		{
			stream.read(&ch, 1);
			if(ch != *strTest)
			{
				// std::cerr << str << " not correct: " << static_cast<int>(ch) << " != " << static_cast<int>(*strTest) << " (" << *strTest << ")\n";
				return false;
			}
			++strTest;
		}
		// std::cout << str << " ok\n";
		return true;
	}
	
}
