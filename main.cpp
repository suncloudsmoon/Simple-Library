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

#include <iostream>
#include <stdexcept>
#include "osutil.hpp"
#include "cwrapper.hpp"

void test_c_wrapper();
void test_os_util();

int main() {
	test_c_wrapper();
	/*test_os_util();*/
}

void test_c_wrapper() {
	sl::FILE some;
	if (!some.open("hello.txt", "w"))
		throw std::runtime_error("Unable to open hello.txt!");
	some.printf("%s", "hello");
}

void test_os_util() {
	namespace os = sl::osutil;
	std::cout << os::get_executable_path();
}