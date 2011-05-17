

#ifndef ARDUINOROVERLIB_H
#define ARDUINOROVERLIB_H

#ifdef __cplusplus
extern "C"{
#endif

#include <stdlib.h>
 
// provide a dummy callback for the linking stage
void __cxa_pure_virtual(void); 

__extension__ typedef int __guard __attribute__((mode (__DI__))); 

int __cxa_guard_acquire(__guard *); 
void __cxa_guard_release (__guard *); 
void __cxa_guard_abort (__guard *);

#ifdef __cplusplus
}
#endif

#endif
