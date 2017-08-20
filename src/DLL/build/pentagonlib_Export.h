
#ifndef pentagonlib_EXPORT_H
#define pentagonlib_EXPORT_H

#ifdef pentagonlib_BUILT_AS_STATIC
#  define pentagonlib_EXPORT
#  define PENTAGONLIB_NO_EXPORT
#else
#  ifndef pentagonlib_EXPORT
#    ifdef pentagonlib_EXPORTS
        /* We are building this library */
#      define pentagonlib_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define pentagonlib_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PENTAGONLIB_NO_EXPORT
#    define PENTAGONLIB_NO_EXPORT 
#  endif
#endif

#ifndef PENTAGONLIB_DEPRECATED
#  define PENTAGONLIB_DEPRECATED __declspec(deprecated)
#endif

#ifndef PENTAGONLIB_DEPRECATED_EXPORT
#  define PENTAGONLIB_DEPRECATED_EXPORT pentagonlib_EXPORT PENTAGONLIB_DEPRECATED
#endif

#ifndef PENTAGONLIB_DEPRECATED_NO_EXPORT
#  define PENTAGONLIB_DEPRECATED_NO_EXPORT PENTAGONLIB_NO_EXPORT PENTAGONLIB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PENTAGONLIB_NO_DEPRECATED
#    define PENTAGONLIB_NO_DEPRECATED
#  endif
#endif

#endif
