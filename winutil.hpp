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

#ifndef SL_WINUTIL_HPP
#define SL_WINUTIL_HPP

#include <filesystem>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace sl {
	namespace osutil {
		/*
		* Windows utils for creating .url shorcuts.
		*/
		namespace win {
			constexpr const char* user_profile_path_env{ "userprofile" };
			constexpr const char* app_data_path_env{ "appdata" };
			constexpr const char* username_env{ "username" };

			constexpr const char* start_menu_path{ R"(\Microsoft\Windows\Start Menu\Programs)" };
			constexpr const char* desktop_path{ R"(\Desktop)" };

			constexpr const char* url_description_hash{ "[{5CBF2787-48CF-4208-B90E-EE5E5D420294}]" };
			constexpr const char* url_notes_field_hash{ "[{B9B4B3FC-2B51-4A42-B5D8-324146AFCF25}]" };
			constexpr const char* url_star_rating_hash{ "[{64440492-4C8B-11D1-8B70-080036B11A03}]" };

			constexpr unsigned default_icon_index{ 0 };

			namespace fs = std::filesystem;

			/*
			* Creates .url shortcuts for windows
			*
			* dest - path to where the shortcut is created (with .url extension at the end).
			* url - where the shortcut points to (can be a website, file path, etc.).
			* icon_path - path to the icon file (like a .ico file stored in a directory).
			* description - description of the shortcut.
			* notes - notes of the shortcut.
			* rating - rating of the shortcut in the range from 1 to 5 stars.
			*/
			inline bool create_shortcut(const fs::path& dest, std::string url, std::string icon_path,
				const std::string& description, const std::string& notes, unsigned rating) {
#ifndef _WIN32
#error "sl::osutil::win::create_shortcut() is a windows utility!"
#endif
				std::ofstream out{ dest };
				if (out.is_open()) {
					out << "[InternetShortcut]\n";
					out << "URL=" << url << '\n';
					out << "IconFile=" << icon_path << '\n';
					out << "IconIndex=" << default_icon_index << '\n';

					out << url_description_hash << '\n';
					out << "Prop21=31," << '\"' << description << '\"' << '\n';

					out << url_notes_field_hash << '\n';
					out << "Prop5=31," << '\"' << notes << '\"' << '\n';

					out << url_star_rating_hash << '\n';
					out << "Prop9=19,";

					switch (rating) {
					case 1:
						out << "1";
						break;
					case 2:
						out << "25";
						break;
					case 3:
						out << "50";
						break;
					case 4:
						out << "75";
						break;
					case 5:
						out << "99";
						break;
					default:
						out << "1";
						break;
					}
					out << '\n';
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
}

#endif /* SL_WINUTIL_HPP */