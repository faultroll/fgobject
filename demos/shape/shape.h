#ifndef __GOBJECT_TEST_SHAPE_CLASS_INCLUDED__
#define __GOBJECT_TEST_SHAPE_CLASS_INCLUDED__

#include "gtype.h"

G_BEGIN_DECLS

#define SHAPE_TYPE             (shape_get_type())
#define SHAPE(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), SHAPE_TYPE, Shape))
#define IS_SHAPE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), SHAPE_TYPE))
#define SHAPE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), SHAPE_TYPE, ShapeClass))
#define IS_SHAPE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), SHAPE_TYPE))
#define SHAPE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), SHAPE_TYPE, ShapeClass))

typedef struct _Shape        Shape;
typedef struct _ShapeClass   ShapeClass;
// typedef struct _ShapePrivate ShapePrivate;

struct _Shape {
    GTypeInstance parent;
};

struct _ShapeClass {
    GTypeClass parent;

    guint(*calculateArea)(Shape *shape);
};

GType   shape_get_type();

guint   shape_calculate_area(Shape *shape);

G_END_DECLS

#endif /* __GOBJECT_TEST_SHAPE_CLASS_INCLUDED__ */