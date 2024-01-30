
#ifndef MODBUSWRAPPERS_EXPORT_H
#define MODBUSWRAPPERS_EXPORT_H

#ifdef MODBUSWRAPPERS_STATIC_DEFINE
#  define MODBUSWRAPPERS_EXPORT
#  define MODBUSWRAPPERS_NO_EXPORT
#else
#  ifndef MODBUSWRAPPERS_EXPORT
#    ifdef modbuswrappers_EXPORTS
        /* We are building this library */
#      define MODBUSWRAPPERS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MODBUSWRAPPERS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef MODBUSWRAPPERS_NO_EXPORT
#    define MODBUSWRAPPERS_NO_EXPORT 
#  endif
#endif

#ifndef MODBUSWRAPPERS_DEPRECATED
#  define MODBUSWRAPPERS_DEPRECATED __declspec(deprecated)
#endif

#ifndef MODBUSWRAPPERS_DEPRECATED_EXPORT
#  define MODBUSWRAPPERS_DEPRECATED_EXPORT MODBUSWRAPPERS_EXPORT MODBUSWRAPPERS_DEPRECATED
#endif

#ifndef MODBUSWRAPPERS_DEPRECATED_NO_EXPORT
#  define MODBUSWRAPPERS_DEPRECATED_NO_EXPORT MODBUSWRAPPERS_NO_EXPORT MODBUSWRAPPERS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MODBUSWRAPPERS_NO_DEPRECATED
#    define MODBUSWRAPPERS_NO_DEPRECATED
#  endif
#endif

#endif /* MODBUSWRAPPERS_EXPORT_H */
