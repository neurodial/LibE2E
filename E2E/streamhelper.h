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
