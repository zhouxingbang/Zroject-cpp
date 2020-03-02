#pragma once

#ifndef BUILD_STATIC
# if defined(ZKERNEL_LIB)
#  define ZKERNEL_EXPORT __declspec(dllexport)
# else
#  define ZKERNEL_EXPORT __declspec(dllimport)
# endif
#else
# define ZKERNEL_EXPORT
#endif
