#include "circle.h"
#include <stdio.h>

struct _CirclePrivate {
    guint radius;
};
#define CIRCLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), \
                                 CIRCLE_TYPE, CirclePrivate))

static void circle_base_init(CircleClass *klass);
static void circle_base_finalize(CircleClass *klass);
static void circle_class_init(CircleClass *klass);
static void circle_init(Circle *circle);
static guint circle_calculate_area(Circle *self);

GType circle_get_type()
{
    static GType type = 0;

    if (type == 0) {
        static const GTypeInfo info = {
            sizeof(CircleClass),
            (GBaseInitFunc)circle_base_init,
            (GBaseFinalizeFunc)circle_base_finalize,
            (GClassInitFunc)circle_class_init,
            NULL,
            NULL,
            sizeof(Circle),
            0,
            (GInstanceInitFunc)circle_init,
            // NULL,
        };

        type = g_type_register_static(SHAPE_TYPE, "Circle", &info, 0);
    }

    return type;
}

static void circle_base_init(CircleClass *klass)
{
    printf("Circle(0x%08x)::base::initialize\n", (gpointer)klass);
}

static void circle_base_finalize(CircleClass *klass)
{
    printf("Circle(0x%08x)::base::finalize\n", (gpointer)klass);
}

static void circle_class_init(CircleClass *klass)
{
    printf("Circle(0x%08x)::class::initialize\n", (gpointer)klass);

    SHAPE_CLASS(klass)->calculateArea = (void *)circle_calculate_area;

    g_type_class_add_private(klass, sizeof(CirclePrivate));
}

static void circle_init(Circle *self)
{
    CirclePrivate *priv;

    printf("Circle(0x%08x)::instance::initialize\n", (gpointer)self);

    self->priv = priv = CIRCLE_GET_PRIVATE(self);

    priv->radius = 0;
}

Circle *circle_new(guint radius)
{
    Circle *circle;

    circle = (Circle *)g_type_create_instance(CIRCLE_TYPE);
    if (circle != NULL) {
        circle->priv->radius = radius;
        printf("Circle(0x%08x, r=%u) is created.\n",
               (gpointer)circle, circle->priv->radius);
    }

    return circle;
}

void circle_free(Circle *circle)
{
    if (circle != NULL && IS_CIRCLE(circle))
        g_type_free_instance((GTypeInstance *)circle);
}

static guint circle_calculate_area(Circle *self)
{
    printf("Circle(0x%08x)::calculateArea\n", (gpointer)self);

    return self->priv->radius * self->priv->radius * 3;
}

void circle_set_radius(Circle *circle, guint radius)
{
    if (circle != NULL && IS_CIRCLE(circle))
        circle->priv->radius = radius;
}

guint circle_get_radius(Circle *circle)
{
    if (circle != NULL && IS_CIRCLE(circle))
        return circle->priv->radius;
    else
        return 0;
}
