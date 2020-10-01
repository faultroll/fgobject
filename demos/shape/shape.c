#include "shape.h"
#include <stdio.h>

static void shape_base_init(ShapeClass *self);
static void shape_base_finalize(ShapeClass *self);
static void shape_class_init(ShapeClass *self);

GType shape_get_type()
{
    static GType type = 0;

    if (type == 0) {
        const GTypeInfo info = {
            sizeof(ShapeClass),
            (GBaseInitFunc)shape_base_init,
            (GBaseFinalizeFunc)shape_base_finalize,
            (GClassInitFunc)shape_class_init,
            NULL,
            NULL,
            sizeof(Shape),
            0,
            NULL,
            // NULL,
        };
        const GTypeFundamentalInfo fundamental_info = {
            G_TYPE_FLAG_CLASSED
            | G_TYPE_FLAG_INSTANTIATABLE
            | G_TYPE_FLAG_DERIVABLE
            | G_TYPE_FLAG_DEEP_DERIVABLE
        };
        type = g_type_register_fundamental(g_type_fundamental_next(),
                                           "Shape", &info, &fundamental_info, 0);
    }

    return type;
}

static void shape_base_init(ShapeClass *self)
{
    printf("Shape(0x%08x)::base::initialize\n", (gpointer)self);
}

static void shape_base_finalize(ShapeClass *self)
{
    printf("Shape(0x%08x)::base::finalize\n", (gpointer)self);
}

static void shape_class_init(ShapeClass *klass)
{
    printf("Shape(0x%08x)::class::initialize\n", (gpointer)klass);

    klass->calculateArea = NULL;
}

guint shape_calculate_area(Shape *shape)
{
    if (!IS_SHAPE(shape))
        return 0;

    if (SHAPE_GET_CLASS(shape)->calculateArea == NULL) {
        printf("Shape::calculateArea is not implemented\n");

        return 0;
    }

    return SHAPE_GET_CLASS(shape)->calculateArea(shape);
}
