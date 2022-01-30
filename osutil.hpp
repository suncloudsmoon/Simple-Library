/*
 * Copyright (c) 2022, suncloudsmoon and the Simple-Library contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SL_OSUTIL_HPP
#define SL_OSUTIL_HPP

#include <string>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
#include "winutil.hpp"
#endif

namespace sl {
	namespace osutil {
		/*
		* Types of message to display in a message popup.
		*/
		enum class message_type {
			info, warning, error
		};
		/*
		* Shows a message popup on a GUI screen.
		* 
		* title - the title of the message popup.
		* description - the description of the message popup.
		* type - type of message popup, such as message_type::info, message_type::warning,
		*		and message_type::error.
		*/
		inline void show_message_popup(const std::string& title, const std::string& description,
			message_type type = message_type::info) {
#ifdef _WIN32
			std::wstring wide_title_str{ title.begin(), title.end() };
			std::wstring wide_description_str{ description.begin(), description.end() };
			UINT icon_type{ 0 };
			switch (type) {
			case message_type::info:
				icon_type = MB_ICONINFORMATION;
				break;
			case message_type::warning:
				icon_type = MB_ICONWARNING;
				break;
			case message_type::error:
				icon_type = MB_ICONERROR;
				break;
			default:
				icon_type = MB_ICONINFORMATION;
				break;
			}
			MessageBox(NULL, wide_description_str.c_str(), wide_title_str.c_str(),
				icon_type | MB_OK);
#else
#error "Showing message popups is not supported on other platforms yet!"
#endif
		}

		/*
		* Gets the current executable path of the application that's running.
		*/
		inline std::string get_executable_path() {
			std::string full_executable_path;
#ifdef _WIN32
			constexpr unsigned char_arr_size{ 1000 };
			wchar_t* char_arr = new wchar_t[char_arr_size]();
			GetModuleFileName(nullptr, char_arr, char_arr_size); // includes the null terminator!
			std::wstring_view wide_str{ char_arr };
			full_executable_path.assign(wide_str.begin(), wide_str.end());
			delete[] char_arr;
#else
#error "Getting executable path is not supported for other platforms yet!"
#endif
			return full_executable_path;
		}
	}
}

#endif /* SL_OSUTIL_HPP */