/* ------------------------------------------- * 
 * zwalker.c
 * ---------
 * A less error prone way of iterating through strings and unsigned character
 * data.
 *
 * Usage
 * -----
 *
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
 * 
 * ------------------------------------------- */
#include "zwalker.h"

//Return count of occurences of a character in some block.
int memchrocc (const void *a, const char b, int size) {
	int occ = 0;
	while ( --size ) {
		*( (const unsigned char *)a++ ) == b ? occ++ : 0; 
	}
	return occ;
}


//Where exactly is a character in memory
int memchrat (const void *a, const char b, int size) {
	int pos = 0, osize = size - 1;
	while ( --size ) {
		if ( *( (unsigned char *)a++ ) == b ) {
			return pos;
		}
		pos++;
	}
	return ( pos == osize ) ? -1 : pos;
}


//Find a specific string in memory
void * memblk (const void *a, const void *b, int size_a, int size_b) {
	while ( --size_a > size_b ) {
		if ( *(unsigned char *)a == *(unsigned char *)b && !memcmp(a, b, size_b) ) {
			return (void *)a;
		}
		a++; 
	}
	return NULL;	
}


//Where exactly is a substr in memory
int memblkat (const void *a, const void *b, int size_a, int size_b) {
	int pos = 0;
	while ( --size_a > size_b ) {
		if ( *(unsigned char *)a == *(unsigned char *)b && !memcmp(a, b, size_b) ) {
			return pos;
		}
		a++, pos++;
	}
	return -1;	
}


//Return count of occurences of a string in some block.
int memblkocc (const void *a, const void *b, int size_a, int size_b ) {
	int occ = 0;
	while ( size_a > size_b ) {
		if ( *(unsigned char *)a == *(unsigned char *)b && !memcmp(a, b, size_b) ) {
			occ++, a += size_b, size_a -= size_b;
			continue;	
		}
		a++, size_a--; 
	}
	return occ;
}


//Walk through unsigned character data 
int memwalk ( 
		zWalker *w
	, const unsigned char * data
	, const unsigned char * tokens
	, const int datalen
	, const int toklen )
{
	//Setup the structure
	w->ptr = (unsigned char *)( !w->ptr ? data : w->ptr );
	w->pos = w->next;

	//Find the tokens specified, and bring back that position
	while ( w->next++ < datalen && !memchr( tokens, *(w->ptr++), toklen ) ) ;

	//Die if no tokens were found
	if ( w->next == datalen ) {
		//fprintf(stderr, "No tokens found, stopping.\n" );
		return 0;
	}	

	//TODO: If you want to include the token, specify it...
	w->size = w->next - w->pos;
	w->chr = *( w->ptr - 1 );
	w->rptr = w->ptr - 1;
#if 0
	fprintf(stderr, "I found a token: '%c'\n", w->chr );
	fprintf(stderr, "position (current position in the string): %d\n", w->pos );
	fprintf(stderr, "next (position after the token): %d\n", w->next );
	fprintf(stderr, "size of workable block: %d\n", w->size );
#endif
	return 1; 
}

#include <unistd.h>
#include <stdio.h>

//"Jump" through unsigned character data (by looking for blocks larger than one character)
int memjump (
		zWalker *w
	, const unsigned char * data
	, const unsigned char ** tokens
	, const int datalen
	, const int * toklen )
{
	//Setup the structure
	w->ptr = (unsigned char *)( !w->ptr ? data : w->ptr );
	w->pos = w->next;
	w->rsize = 0;

	//Find the tokens specified, and bring back that position
	int match = 0;
	while ( ( w->next < datalen ) && !match ) {
		const unsigned char **t = tokens;
		const int *l = toklen;
		while ( *t ) {
			//Skip the token if it's too big
			if ( *l > ( datalen - w->next ) ) {
				t++, l++;
				continue;
			}

			//Move up and report our match if we found one
			if ( memchr( *t, *w->ptr, *l ) && memcmp( *t, w->ptr, *l ) == 0 ) {
				w->next += *l, w->ptr += *l, match = 1, w->rsize = *l;
				break;	
			}
			t++, l++;
		}

		if ( match ) {
			break;
		}

		w->ptr++, w->next++;
	}

	//Die if no tokens were found
	if ( w->next == datalen ) {
		return 0;
	}	

	//TODO: If you want to include the token, specify it...
	w->size = w->next - w->pos;
	w->chr = *( w->ptr - 1 );
	w->rptr = w->ptr - w->rsize;
	
	return 1;
}


//Initialize a zWalker structure
void zwalker_init( zWalker *w ) {
	memset( w, 0, sizeof( zWalker ) );
} 


//Return one less than the size of the block found
void zwalker_discard_tokens( zWalker *w ) {
	w->keep_token = ZWALKER_DISCARD_TOKEN;	
}


//...


#if 0
//Finds the 1st occurence of one char, Keep running until no tokens are found in range...
int memtok (const void *a, const unsigned char *tokens, int sz, int tsz) {
	int n, p = -1;
	
	for ( int i = 0; i < tsz; i++ ) {
	#if 1
		p = ( ( p > ( n = memchrat(a, tokens[i], sz) ) && n > -1 ) || p == -1 ) ? n : p;
	#else
	{
		p = ((p > (n = memchrat(a, tokens[i], sz)) && n > -1) || p == -1) ? n : p;
		fprintf(stderr, "found char %d at %d\n", tokens[i], memchrat(a, tokens[i], sz));
		nmprintf("p is", p);
	}
	#endif
	}
	
	return p;
}


//Finds the first occurrence of a complete token (usually a string). 
//keep running until no more tokens are found.
int memmatch (const void *a, const char *tokens, int sz, char delim) {
	int p=-1, n, occ = -1;

	/*Check that the user has supplied a delimiter. (or fail in the future)*/
	if (!(occ = memchrocc(tokens, delim, strlen(tokens))))
		return -1 /*I found nothing, sorry*/;

	/*Initialize a temporary buffer for each copy*/
	int t = 0; 
	char buf[strlen(tokens) - occ];
	memset(&buf, 0, strlen(tokens) - occ);

	/*Loop through each string in the token list*/
	while (t < strlen(tokens) && (n = memtok(&tokens[t], (unsigned char *)"|\0", sz, 2)) > -1) {
		/*Copy to an empty buffer*/
		memcpy(buf, &tokens[t], n);
		buf[n] = '\0';
		t += n + 1;

		/*This should find the FIRST occurrence of what we're looking for within block*/
		p = ((p > (n = memstrat(a, buf, sz)) && n > -1) || p == -1) ? n : p;
		/*fprintf(stderr, "found str %s at %d\n", buf, memstrat(a, buf, sz)); nmprintf("p is", p);*/
		memset(&buf, 0, strlen(tokens) - occ);
	}
	return p;
}
#endif

