// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: FileIO.hpp
// 
// Current Data:
// 2021-07-05 11:08 PM
// 
// Creation Date:
// 2021-07-05 1:36 AM

#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <string>
#include <sstream>
#include <boost/locale/encoding.hpp>
#include <boost/endian.hpp>
#include <boost/endian/buffers.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "FileEncodings.hpp"
#include "FileIOException.hpp"

namespace Mpp
{
	using namespace boost;
	using namespace locale;

	/**
	 * \brief Reads the contents of a file.
	 * \param filePath The path to the file to read.
	 * \return A string containing contents of the file.
	 */
	static std::string ReadBinary(const std::string& filePath)
	{
		const filesystem::path p(filePath);

		if (!exists(p))
		{
			throw FileIOException("Unable to open file.", filePath);
		}

		filesystem::ifstream file(p, std::ios::binary);
		std::stringstream fileStream;

		fileStream << file.rdbuf();
		file.close();

		return fileStream.str();
	}

	template <typename T>
	static T ReadBytes(const std::string& fileContents, const size_t& offset)
	{
		if (offset + sizeof(T) >= fileContents.length())
		{
			throw std::exception("Index out of range.");
		}

		T val;
		memcpy(&val, &fileContents[offset], sizeof(T));
		return val;
	}

	template <typename T>
	static std::vector<T> ReadBytes(const std::string& fileContents, const size_t& offset, const size_t& length)
	{
		if (offset + sizeof(T) >= fileContents.length())
		{
			throw std::exception("Index out of range.");
		}

		auto output = std::vector<T>(fileContents.begin() + offset, fileContents.begin() + offset + length);

		return output;
	}

	static std::string ReadBytesString(const std::string& fileContents, const size_t& offset, const size_t& length,
	                                   const Encoding& encoding)
	{
		if (offset + length >= fileContents.length())
		{
			throw std::exception("Index out of range.");
		}

		std::string output;
		const auto dest = new char[length];
		std::copy_n(fileContents.begin() + offset, length, dest);

		switch (encoding)
		{
		case Encoding::Ascii:
			output = std::string(dest);
			break;

		case Encoding::Utf8:
			output = conv::from_utf<char>(dest, "UTF-8");
			break;
		}

		delete[] dest;

		return output;
	}
}

#endif
