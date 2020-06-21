#ifndef __UTILS_H__
#define __UTILS_H__

#include <cassert>

#ifdef NDEBUG /* For Release Mode. */
#define ASSERT(value) if (!(value))\
			{\
				std::cout << "Error in line" << __LINE__ << std::endl; exit(0);\
			}
#else
#define ASSERT(value) assert(value)
#endif

#endif /*__UTILS_H__*/
