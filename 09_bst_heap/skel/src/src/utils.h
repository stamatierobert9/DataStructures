/**
 * Useful structures/macros
 * 
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* stupid workaround for lambdachecker input from example */
void cleanup_example_string(char* str) {
	int len = strlen(str);

	if(str[len-2] == '\\') {
		str[len-2] = '\0';
	}
}

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

#endif
