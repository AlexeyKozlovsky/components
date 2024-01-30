
#ifndef WIDGETS_EXPORT_H
#define WIDGETS_EXPORT_H

#ifdef WIDGETS_STATIC_DEFINE
#  define WIDGETS_EXPORT
#  define WIDGETS_NO_EXPORT
#else
#  ifndef WIDGETS_EXPORT
#    ifdef widgets_EXPORTS
        /* We are building this library */
#      define WIDGETS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define WIDGETS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef WIDGETS_NO_EXPORT
#    define WIDGETS_NO_EXPORT 
#  endif
#endif

#ifndef WIDGETS_DEPRECATED
#  define WIDGETS_DEPRECATED __declspec(deprecated)
#endif

#ifndef WIDGETS_DEPRECATED_EXPORT
#  define WIDGETS_DEPRECATED_EXPORT WIDGETS_EXPORT WIDGETS_DEPRECATED
#endif

#ifndef WIDGETS_DEPRECATED_NO_EXPORT
#  define WIDGETS_DEPRECATED_NO_EXPORT WIDGETS_NO_EXPORT WIDGETS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef WIDGETS_NO_DEPRECATED
#    define WIDGETS_NO_DEPRECATED
#  endif
#endif

#endif /* WIDGETS_EXPORT_H */
