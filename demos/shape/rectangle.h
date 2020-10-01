#ifndef __GOBJECT_TEST_RECTANGLE_CLASS_INCLUDED__
#define __GOBJECT_TEST_RECTANGLE_CLASS_INCLUDED__

#include "gtype.h"

#include "shape.h"

G_BEGIN_DECLS

#define RECTANGLE_TYPE              (rectangle_get_type())
#define RECTANGLE(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), RECTANGLE_TYPE, Rectangle))
#define IS_RECTANGLE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), RECTANGLE_TYPE))
#define RECTANGLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), RECTANGLE_TYPE, RectangleClass))
#define IS_RECTANGLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass), RECTANGLE_TYPE))
#define RECTANGLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), RECTANGLE_TYPE, RectangleClass))

typedef struct _Rectangle        Rectangle;
typedef struct _RectangleClass   RectangleClass;
typedef struct _RectanglePrivate RectanglePrivate;

struct _Rectangle {
    Shape parent;

    RectanglePrivate *priv;
};

struct _RectangleClass {
    ShapeClass parent;
};

GType       rectangle_get_type();

Rectangle  *rectangle_new(guint width, guint height);
void        rectangle_free(Rectangle *rect);

void        rectangle_set_width(Rectangle *rect, guint width);
void        rectangle_set_height(Rectangle *rect, guint height);
guint       rectangle_get_width(Rectangle *rect);
guint       rectangle_get_height(Rectangle *rect);

G_END_DECLS

#endif /* __GOBJECT_TEST_RECTANGLE_CLASS_INCLUDED__ */