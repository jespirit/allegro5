/*
 * SCANEXP - serves as a support to scan the header files.
 *
 *  By Michael Rickmann.
 */
#define SCAN_DEPEND


#define AL_VAR(type, name)                   allexpvar name##_sym
#define AL_FUNCPTR(type, name, args)         allexpfpt name##_sym
#define AL_ARRAY(type, name)                 allexparr name##_sym
#define AL_FUNC(type, name, args)            allexpfun name##_sym
#define AL_INLINE(type, name, args, code)    allexpinl name##_sym


#define ALLEGRO_LITTLE_ENDIAN
#define ALLEGRO_COLOR8
#define ALLEGRO_COLOR16
#define ALLEGRO_COLOR24
#define ALLEGRO_COLOR32
#define ALLEGRO_NO_COLORCOPY
#define ALLEGRO_WINDOWS
/* Make OpenGL mandatory. A library without OpenGL lacks many
 * exports specific to OpenGL, which makes it ABI incompatible. */
#define ALLEGRO_CFG_OPENGL


#if defined ALLEGRO_API

   #include "allegro5/allegro5.h"

#elif defined ALLEGRO_WINAPI

   #define ALLEGRO_H
   #include "allegro5/winalleg.h"
   #include "allegro5/platform/alwin.h"

#elif defined ALLEGRO_INTERNALS

   #define ALLEGRO_H
   #include "allegro5/internal/aintern.h"

#endif

