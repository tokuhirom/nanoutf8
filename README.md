nanoutf8
========

Tiny UTF-8 library for C/C++.

This library provides some basic functions for operating UTF-8 string.

## Functions

### `static size_t nanoutf8_byte_count_from_first_char(char c)`

Detect the next char's size.

### `static size_t nanoutf8_encode(uint64_t ch, char *buf)`

Encode ch to buf.

This function returns the bytes.

### `static uint32_t nanoutf8_peek_char(const char* const src, size_t srclen, size_t *lenp, bool *ok)`

Peek one UTF-8 character from src. srclen is the length of src.

This function writes length of first character to lenp.

If an error was detected, this function makes `*ok` to false.

## LICENSE

The MIT License (MIT)

Copyright © 2013 Tokuhiro Matsuno, http://64p.org/ <tokuhirom@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Fork this project to create your own MIT license that you can always link to.
