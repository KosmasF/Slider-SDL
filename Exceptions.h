#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdio.h>
#include <stdlib.h>

extern void *__cxa_allocate_exception(size_t thrown_size);
extern void __cxa_throw (void *thrown_exception, void* *tinfo, void (*dest) (void *) );
extern void * _ZTIl; // typeinfo of long

#endif