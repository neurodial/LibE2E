#pragma once

#include <fstream>

namespace StreamHelper
{
	template<typename T>
	inline void readFStream(std::istream& stream, T* dest, std::size_t num = 1)
	{
		stream.read(reinterpret_cast<char*>(dest), sizeof(T)*num);
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
