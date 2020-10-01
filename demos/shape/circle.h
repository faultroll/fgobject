#ifndef __GOBJECT_TEST_CIRCLE_CLASS_INCLUDED__
#define __GOBJECT_TEST_CIRCLE_CLASS_INCLUDED__

#include "gtype.h"

#include "shape.h"

G_BEGIN_DECLS

#define CIRCLE_TYPE             (circle_get_type())
#define CIRCLE(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), CIRCLE_TYPE, Circle))
#define IS_CIRCLE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), CIRCLE_TYPE))
#define CIRCLE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), CIRCLE_TYPE, CircleClass))
#define IS_CIRCLE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), CIRCLE_TYPE))
#define CIRCLE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), CIRCLE_TYPE, CircleClass))

typedef struct _Circle        Circle;
typedef struct _CircleClass   CircleClass;
typedef struct _CirclePrivate CirclePrivate;

struct _Circle {
    Shape parent;

    CirclePrivate *priv;
};

struct _CircleClass {
    ShapeClass parent;
};

GType   circle_get_type();

Circle *circle_new(guint radius);
void    circle_free(Circle *circle);

void    circle_set_radius(Circle *circle, guint radius);
guint   circle_get_radius(Circle *circle);

G_END_DECLS

#endif /* __GOBJECT_TEST_CIRCLE_CLASS_INCLUDED__ */