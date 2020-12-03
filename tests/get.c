/* ------------------------------------------- * 
 * get.c
 * ---------
 * GET request tests for C-based HTTP parser, request and response builder 
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
 * CHANGELOG 
 * ---------
 * 12-01-20 - Fixed a seek bug in memstr, adding tests
 *          - Added memblk functions. 
 * 12-02-20 - Fixed an off-by-one bug in memblk* functions.
 * 
 * ------------------------------------------- */
const unsigned char GET_a[] = "G";

const unsigned char GET_b[] = "GET\r\n";

const unsigned char GET_c[] = "GET /\0 HTTP/1.0";

const unsigned char GET_d[] = "GET / HTTP/1.7";

const unsigned char GET_e[] = 
"GET / HTTP/1.1\r\r\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char GET_f[] = //Weird issue with allocation...
"GET /path/not/life/1/2/3/4/5/6/7 HTTP/1.1"
"Host: domo.hypno:2333"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char GET_g[] = 
"GET /path/not/life/1/2/3/4/5/6/7 HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char GET_h[] = 
"GET /path/of/prot?abcdef=wopdawg&hella_awesome=1&aa=bb HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive"
"\r\n\r\n";

const unsigned char GET_i[] =
"GET / HTTP/1.1\r\n"
"Host: domo.hypno:2333\r\n"
"Connection: keep-alive\r\n"
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36 OPR/72.0.3815.400\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Accept-Language: en-US,en;q=0.9"
"\r\n\r\n";
