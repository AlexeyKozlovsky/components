
#ifndef libmodbus_EXPORT_H
#define libmodbus_EXPORT_H

#ifdef libmodbus_BUILT_AS_STATIC
#  define libmodbus_EXPORT
#  define LIBMODBUS_NO_EXPORT
#else
#  ifndef libmodbus_EXPORT
#    ifdef libmodbus_EXPORTS
        /* We are building this library */
#      define libmodbus_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define libmodbus_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef LIBMODBUS_NO_EXPORT
#    define LIBMODBUS_NO_EXPORT 
#  endif
#endif

#ifndef LIBMODBUS_DEPRECATED
#  define LIBMODBUS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIBMODBUS_DEPRECATED_EXPORT
#  define LIBMODBUS_DEPRECATED_EXPORT libmodbus_EXPORT LIBMODBUS_DEPRECATED
#endif

#ifndef LIBMODBUS_DEPRECATED_NO_EXPORT
#  define LIBMODBUS_DEPRECATED_NO_EXPORT LIBMODBUS_NO_EXPORT LIBMODBUS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBMODBUS_NO_DEPRECATED
#    define LIBMODBUS_NO_DEPRECATED
#  endif
#endif

#endif /* libmodbus_EXPORT_H */
