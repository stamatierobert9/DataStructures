/**
 * Useful structures/macros
 *
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#endif /* __UTILS_H_ */
