
#include <boost/predef.h>
// https://stackoverflow.com/questions/2989810/which-cross-platform-preprocessor-defines-win32-or-win32-or-win32

#if BOOST_COMP_GNUC 
	#define PACKSTRUCT( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#elif BOOST_COMP_MSVC
	#define PACKSTRUCT( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
	#error "unhandled compiler for packing struct"
#endif


