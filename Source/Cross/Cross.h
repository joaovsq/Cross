

#ifndef CROSS_API_H
#define CROSS_API_H

#ifdef _MSC_VER

#pragma warning(disable: 4251)
#pragma warning(disable: 4275)

#ifdef CROSS_STATIC_DEFINE
#  define CROSS_API
#  define CROSS_NO_EXPORT
#else
#  ifndef CROSS_API
#    ifdef CROSS_EXPORTS
        /* We are building this library */
#      define CROSS_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define CROSS_API __declspec(dllimport)
#    endif
#  endif

#  ifndef CROSS_NO_EXPORT
#    define CROSS_NO_EXPORT 
#  endif
#endif

#ifndef CROSS_DEPRECATED
#  define CROSS_DEPRECATED __declspec(deprecated)
#endif

#ifndef CROSS_DEPRECATED_EXPORT
#  define CROSS_DEPRECATED_EXPORT CROSS_API CROSS_DEPRECATED
#endif

#ifndef CROSS_DEPRECATED_NO_EXPORT
#  define CROSS_DEPRECATED_NO_EXPORT CROSS_NO_EXPORT CROSS_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define CROSS_NO_DEPRECATED
#endif

#else

#ifdef CROSS_STATIC_DEFINE
#ifndef CROSS_API
#  define CROSS_API
#endif
#  define CROSS_NO_EXPORT
#else
#  ifndef CROSS_API
#    ifdef CROSS_EXPORTS
        /* We are building this library */
#      define CROSS_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CROSS_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CROSS_NO_EXPORT
#    define CROSS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CROSS_DEPRECATED
#  define CROSS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CROSS_DEPRECATED_EXPORT
#  define CROSS_DEPRECATED_EXPORT CROSS_API CROSS_DEPRECATED
#endif

#ifndef CROSS_DEPRECATED_NO_EXPORT
#  define CROSS_DEPRECATED_NO_EXPORT CROSS_NO_EXPORT CROSS_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define CROSS_NO_DEPRECATED
#endif

#endif

#endif

