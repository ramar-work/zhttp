/* ------------------------------------------- * 
 * unsupported.c
 * ---------
 * Test for acceptance of unsupported methods C-based HTTP parser, request 
 * and response builder 
 *
 * Usage
 * -----
 * Soon to come...
 *
 * LICENSE
 * -------
 * Copyright 2020 Tubular Modular Inc. dba Collins Design
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 * ------------------------------------------- */
const unsigned char UNSUP_a[] = 
"NOTHING /path/of/prot?abcdef=wopdawg&hella_awesome=1&aa=bb HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char UNSUP_b[] = 
"delete /path/of/prot?abcdef=wopdawg&hella_awesome=1 HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char UNSUP_c[] = 
"DEL /path/of/prot?abcdef=wopdawg&hella_awesome=1 HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

