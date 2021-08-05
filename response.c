/* ------------------------------------------- * 
 * response.c
 * ----------
 * Tests for C-based HTTP response builder
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
#include <stdlib.h>
#include <time.h>
#include "zhttp.h"


extern const char * words[];
extern const int wordslen;

#define TEST_SCASE(a,b,c) \
	{ (unsigned char *)c, b, a, strlen((char *)c) }

#define TEST_UCASE(a,b,c,d) \
	{ (unsigned char *)c, b, a, d }

#define SETVAL(a,b,l) \
	!( val = malloc( l + 1 )) || \
	!memset( val, 0, l + 1 ) || \
	!memcpy( val, b, l )

char * strdup( const char *v ) {
	int len = strlen( v );
	char *value = malloc( len + 1 );
	memset( value, 0, len + 1 );
	memcpy( value, v, len );
	return value;
}


int random() {
	return 0;
}
	

typedef struct TestCase {
	const unsigned char *content;
	const char *type;	
	int status;
	int len;
	int headers;
} TestCase;



//Try generating and freeing a message.
TestCase cases[] = {
	//Some text responses
	TEST_SCASE( 200, "text/plain", "hi there" ),
	TEST_SCASE( 302, "text/plain", "hi there" ),
	TEST_SCASE( 300, "text/plain", "hi there" ), //should be rejected, bc 300 is not a real code
	TEST_SCASE( 200, "text/html", "<html><h2>Hello</h2></html>" ),
	TEST_SCASE( 404, "text/html", "<html><h2>This is a 'Page Not Found' error</h2></html>" ),
	TEST_SCASE( 500, "text/html", "<html><h2>This is an 'Internal Server' error</h2></html>" ),
	{ NULL }
};


int main ( int argc, char *argv[] ) {

	TestCase *cc = cases;
	srand( time( NULL ) );
	int r = 0;

	while ( cc->content ) {
		unsigned char err[ 2048 ] = {0};
		zhttp_t tmp = {0}, *tt = &tmp;
		fprintf( stderr, "\nRESPONSE %d\n=========\n", r++ );

		//Typical setup (these should NEVER fail)
		http_set_status( tt, cc->status );
		http_set_ctype( tt, cc->type );

		//Do a random thing
		for ( int i = 0; i < rand() % 10; i++ )  {
			const char *word = words[ rand() % wordslen ];
			http_copy_header( tt, "X-Type-Header", word );
		}

		//Finally, copy the content
		http_copy_content( tt, cc->content, cc->len ); 

		//Realistically this should never fail
		if ( !http_finalize_response( tt, (char *)err, sizeof( err ) ) ) {
			return 0;
		}

		//Write the message
		write( 2, tmp.msg, tmp.mlen );
		write( 2, "\n", 1 );
		http_free_body( &tmp );
		cc++;
	}

	return 0;
}
