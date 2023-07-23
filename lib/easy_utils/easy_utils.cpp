//
// Created by rohandev on 7/23/23.
//

#include "easy_utils.h"
/*
 * Look at https://cwe.mitre.org/data/definitions/467.html
 * sizeof() on a pointer can produce side effect on malloc()!
 * sizeof(...)` on the pointer type can result in a dynamic allocation being dumped into the pointer.
 * This could not be caught because C's malloc() yields void*.
 * If malloc() had a typed returned, this would have been caught by the type system.
 */
#define safe_alloc(...) \
     (__VA_ARGS__*)malloc(sizeof(__VA_ARGS__))