// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: M64.h
// 
// Current Data:
// 2021-07-06 8:22 AM
// 
// Creation Date:
// 2021-07-05 12:19 AM

#ifndef M64_H
#define  M64_H

#include <string>
#include <vector>

#include "Input.h"

namespace Mpp
{
	class M64
	{
		friend class M64Parser;
	public:
		using iterator = std::vector<Input>::iterator;
		using const_iterator = std::vector<Input>::const_iterator;

		static M64 CreateFromFile(const std::string& filePath);

		Input const& operator[](size_t index);
		const Input& operator[](size_t index) const;

		iterator begin() noexcept { return _inputs.begin(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return _inputs.cbegin(); }
		iterator end() noexcept { return _inputs.end(); }
		[[nodiscard]] const_iterator cend() const noexcept { return _inputs.cend(); }

	private:
		M64() = default;

		int32_t _signature;
		uint32_t _version;
		int32_t _movieUid;
		uint32_t _viCount;
		uint32_t _rerecordCount;
		uint8_t _viPerSecond;
		uint8_t _controllerCount;
		uint32_t _totalInputs;
		uint16_t _movieStartType;
		uint32_t _controllerFlags;
		std::string _RomName;
		uint32_t _Crc32;
		uint16_t _regionCode;
		std::string _videoPluginName;
		std::string _audioPluginName;
		std::string _inputPluginName;
		std::string _rspPluginName;
		std::string _authorName;
		std::string _authorMovieDescription;
		std::vector<Input> _inputs;
	};
}

#endif
