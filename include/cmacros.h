//In C++ projects these macros can cause problems with macros already defined in the C++ library,  so they are in a separate
// file which won't be installed

#ifndef min
#define min(a, b)   (((a) < (b))? (a): (b))
#endif

#ifndef max
#define max(a, b)   (((a) > (b))? (a): (b))
#endif
