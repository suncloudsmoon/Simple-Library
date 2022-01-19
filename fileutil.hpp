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

#ifndef SL_FILEUTIL_HPP
#define SL_FILEUTIL_HPP

#include <filesystem>
#include <functional>
#include <fstream>
#include <string>
#include <iterator>

namespace sl {
	namespace fileutil {
		namespace fs = std::filesystem;
		using extension = std::string;

		/*
		* Writes content to file.
		* 
		* path - path to write the content to.
		* src - a string or object (overloading <<) to write to file.
		*/
		template<typename FilePath, typename Content>
		bool write_to_file(const FilePath& path, const Content& src) {
			std::ofstream out(path);
			if (out.is_open()) {
				out << src;
				return true;
			}
			return false;
		}

		/*
		* Renames file extensions
		* 
		* path - files inside the directory and its sub-directories will be renamed.
		* from - contains the previous extension to search for, like ".txt".
		* to - has the extension to replace the from extension, like ".data".
		*/
		void rename_file_extensions(const fs::path& path, const extension& from, 
									const extension& to, bool is_sub_dirs) {
			if (is_sub_dirs) {
				for (const auto& dir :
					fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
					auto old_path = dir.path();
					if (old_path.extension().string() == from) {
						auto copy_old_path = old_path;
						fs::rename(old_path, copy_old_path.replace_extension(to));
					}
				}
			}
			else {
				for (const auto& dir :
					fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
					auto old_path = dir.path();
					if (old_path.extension().string() == from) {
						auto copy_old_path = old_path;
						fs::rename(old_path, copy_old_path.replace_extension(to));
					}
				}
			}
			
		}

		/*
		* Changes a file's content given the lambda's return value.
		* 
		* path - the directory to search for files.
		* is_sub_dirs - whether the function to look for files inside sub-directories.
		* func - a lambda function that takes in the path of the file and the reference to its contents
		*		and returns true to change the file's contents and false otherwise.
		*/
		void change_file_when(const fs::path& path, bool is_sub_dirs, 
							std::function <bool(const fs::path&, std::string&)> func) {
			if (is_sub_dirs) {
				for (const auto& s : fs::recursive_directory_iterator{ path, fs::directory_options::skip_permission_denied }) {
					if (s.is_regular_file()) {
						std::ifstream in{ s.path() };
						std::string contents{ std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
						if (func(s.path(), contents))
							write_to_file(s.path(), contents);
					}
				}
			}
			else {
				for (const auto& s : fs::directory_iterator{ path, fs::directory_options::skip_permission_denied }) {
					if (s.is_regular_file()) {
						std::ifstream in{ s.path() };
						std::string contents{ std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
						if (func(s.path(), contents))
							write_to_file(s.path(), contents);
					}
				}
			}
		}
		
	}
}

#endif /* SL_FILEUTIL_HPP */