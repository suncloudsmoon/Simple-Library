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

#ifndef CWRAPPER_HPP
#define CWRAPPER_HPP

#include <cstdio>
#include <cstddef>
#include <cstdarg>

namespace sl {
	struct FILE {
		FILE() : ptr(nullptr) {}
		~FILE() { if (ptr) std::fclose(ptr); }
		operator std::FILE* () { return ptr; }
		int error() { return std::ferror(ptr); }
		int eof() { return std::feof(ptr); }
		bool open(const char* path, const char* mode) { return ptr = std::fopen(path, mode); }
		std::size_t read(void* data, std::size_t size, std::size_t count) {
			return std::fread(data, size, count, ptr);
		}
		std::size_t write(const void* data, std::size_t size, std::size_t count) {
			return std::fwrite(data, size, count, ptr);
		}
		int scanf(const char* format, ...) {
			va_list list;
			va_start(list, format);
			int res = std::vfscanf(ptr, format, list);
			va_end(list);
			return res;
		}
		int printf(const char* format, ...) {
			va_list list;
			va_start(list, format);
			int res = std::vfprintf(ptr, format, list);
			va_end(list);
			return res;
		}
		int flush() { return std::fflush(ptr); }
		int getc() { return std::fgetc(ptr); }
		int getpos(std::fpos_t* pos) { return std::fgetpos(ptr, pos); }
		char* gets(char* str, int max_count) { return std::fgets(str, max_count, ptr); }
		int putc(int ch) { return std::fputc(ch, ptr); }
		int puts(const char* str) { return std::fputs(str, ptr); }
		std::FILE* reopen(const char* file_name, const char* mode) { return std::freopen(file_name, mode, ptr); }
		int seek(long int offset, int origin) { return std::fseek(ptr, offset, origin); }
		int setpos(const std::fpos_t* pos) { return std::fsetpos(ptr, pos); }
		long int tell() { return std::ftell(ptr); }
	private:
		std::FILE* ptr;
	};
}

#endif /* CWRAPPER_HPP */