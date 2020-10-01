#ifndef __GOBJECT_TEST_DRAWABLE_IFACE_INCLUDED__
#define __GOBJECT_TEST_DRAWABLE_IFACE_INCLUDED__

#include "gtype.h"

G_BEGIN_DECLS

#define DRAWABLE_IFACE                  (drawable_get_type())
#define DRAWABLE(obj)                   (G_TYPE_CHECK_INSTANCE_CAST((obj), DRAWABLE_IFACE, Drawable))
#define IS_DRAWABLE(obj)                (G_TYPE_CHECK_INSTANCE_TYPE((obj), DRAWABLE_IFACE))
#define DRAWABLE_GET_INTERFACE(inst)    (G_TYPE_INSTANCE_GET_INTERFACE((inst), DRAWABLE_IFACE, DrawableInterface))

typedef struct _Drawable            Drawable;
typedef struct _DrawableInterface   DrawableInterface;
// typedef struct _DrawablePrivate DrawablePrivate;

struct _Drawable {
    GTypeInstance parent;
};

struct _DrawableInterface {
    GTypeInterface parent;

    void (*draw)(Drawable *self);
};

GType   drawable_get_type();

void    draw_object(Drawable *drawable);

G_END_DECLS

#endif /* __GOBJECT_TEST_DRAWABLE_IFACE_INCLUDED__ */