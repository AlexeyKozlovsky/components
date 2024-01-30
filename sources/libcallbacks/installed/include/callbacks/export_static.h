
#ifndef CALLBACKS_EXPORT_H
#define CALLBACKS_EXPORT_H

#ifdef CALLBACKS_STATIC_DEFINE
#  define CALLBACKS_EXPORT
#  define CALLBACKS_NO_EXPORT
#else
#  ifndef CALLBACKS_EXPORT
#    ifdef callbacks_EXPORTS
        /* We are building this library */
#      define CALLBACKS_EXPORT 
#    else
        /* We are using this library */
#      define CALLBACKS_EXPORT 
#    endif
#  endif

#  ifndef CALLBACKS_NO_EXPORT
#    define CALLBACKS_NO_EXPORT 
#  endif
#endif

#ifndef CALLBACKS_DEPRECATED
#  define CALLBACKS_DEPRECATED 
#endif

#ifndef CALLBACKS_DEPRECATED_EXPORT
#  define CALLBACKS_DEPRECATED_EXPORT CALLBACKS_EXPORT CALLBACKS_DEPRECATED
#endif

#ifndef CALLBACKS_DEPRECATED_NO_EXPORT
#  define CALLBACKS_DEPRECATED_NO_EXPORT CALLBACKS_NO_EXPORT CALLBACKS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CALLBACKS_NO_DEPRECATED
#    define CALLBACKS_NO_DEPRECATED
#  endif
#endif

#endif /* CALLBACKS_EXPORT_H */
