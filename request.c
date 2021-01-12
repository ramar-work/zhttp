/* ------------------------------------------- * 
 * request.c
 * ---------
 * Tests for C-based HTTP parser & request builder
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
 * 12-02-20 - Fixed an off-by-one bug in memblk* functions.
 * 12-03-20 - So many tests added
 * 
 * ------------------------------------------- */
#include <stdio.h>
#include "zhttp.h"


#define TESTCASE(a) \
	{ #a, a, sizeof( a ) }


#include "tests/get.c"
#include "tests/unsupported.c"
#include "tests/post.c"
#if 0
#include "tests/connect.c"
#include "tests/head.c"
#include "tests/options.c"
#include "tests/patch.c"
#include "tests/put.c"
#include "tests/trace.c"
#endif


//...
typedef struct TestCase {
	const char *name;
	const unsigned char *content;
	int len;
} TestCase;


TestCase cases[] = {
#if 1
	TESTCASE(GET_a),
	TESTCASE(GET_b),
	TESTCASE(GET_c),
	TESTCASE(GET_d),
	TESTCASE(GET_e),
#endif
	//TESTCASE(GET_f),
#if 1
	TESTCASE(GET_g),
	TESTCASE(GET_h),
	TESTCASE(GET_i),
	TESTCASE(UNSUP_a),
	TESTCASE(UNSUP_b),
	TESTCASE(POST_a),
	TESTCASE(POST_b),
	TESTCASE(POST_c),
#endif
	{ NULL }
};


int main ( int argc, char *argv[] ) {
	//Just loop and serialize...
	TestCase *cc = cases;
	while ( cc->content ) {
		char err[ 2048 ] = {0};
		struct HTTPBody tmp = {0};
		fprintf( stderr, "\nREQUEST %s\n=========\n", cc->name );
		//write( 2, cc->content, cc->len );

		//This is how this would run normally
		tmp.mlen = cc->len; 
		tmp.msg = malloc( cc->len );
		memcpy( tmp.msg, cc->content, cc->len ); 

		//Finally, parse the request
		http_parse_request( &tmp, err, sizeof( err ) );
		if ( tmp.error == ZHTTP_NONE ) 
			print_httpbody( &tmp );
		else {
			fprintf( stderr, "%s\n", err );	
		}
		http_free_body( &tmp );
		cc++;
	}	
	return 0;
}
