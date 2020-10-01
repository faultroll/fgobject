#include "rectangle.h"
#include <stdio.h>

struct _RectanglePrivate {
    guint width;
    guint height;
};
#define RECTANGLE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), \
                                    RECTANGLE_TYPE, RectanglePrivate))

static void rectangle_base_init(RectangleClass *klass);
static void rectangle_base_finalize(RectangleClass *klass);
static void rectangle_class_init(RectangleClass *klass);
static void rectangle_init(Rectangle *rect);
static guint rectangle_calculate_area(Rectangle *self);
#if defined(DEMO_IFACE)
    #include "drawable.h"
    static void drawable_init(DrawableInterface *iface);
    static void rectangle_draw(Rectangle *self);
#endif

GType rectangle_get_type()
{
    static GType type = 0;

    if (type == 0) {
        static const GTypeInfo info = {
            sizeof(RectangleClass),
            (GBaseInitFunc)rectangle_base_init,
            (GBaseFinalizeFunc)rectangle_base_finalize,
            (GClassInitFunc)rectangle_class_init,
            NULL,
            NULL,
            sizeof(Rectangle),
            0,
            (GInstanceInitFunc)rectangle_init,
            // NULL,
        };

        type = g_type_register_static(SHAPE_TYPE, "Rectangle", &info, 0);

#if defined(DEMO_IFACE)
        static const GInterfaceInfo interface_info = {
            (GInterfaceInitFunc)drawable_init,
        };
        g_type_add_interface_static(type, DRAWABLE_IFACE, &interface_info);
#endif
    }

    return type;
}

static void rectangle_base_init(RectangleClass *klass)
{
    printf("Rectangle(0x%08x)::base::initialize\n", (gpointer)klass);
}

static void rectangle_base_finalize(RectangleClass *klass)
{
    printf("Rectangle(0x%08x)::base::finalize\n", (gpointer)klass);
}

static void rectangle_class_init(RectangleClass *klass)
{
    printf("Rectangle(0x%08x)::class::initialize\n", (gpointer)klass);

    SHAPE_CLASS(klass)->calculateArea = (void *)rectangle_calculate_area;

    g_type_class_add_private(klass, sizeof(RectanglePrivate));
}

static void rectangle_init(Rectangle *self)
{
    RectanglePrivate *priv;

    printf("Rectangle(0x%08x)::instance::initialize\n", (gpointer)self);

    self->priv = priv = RECTANGLE_GET_PRIVATE(self);

    priv->width = priv->height = 0;
}

Rectangle *rectangle_new(guint width, guint height)
{
    Rectangle *rect;

    rect = (Rectangle *)g_type_create_instance(RECTANGLE_TYPE);
    if (rect != NULL) {
        rect->priv->width = width;
        rect->priv->height = height;
        printf("Rectangle(0x%08x, w=%u, h=%u) is created.\n",
               (gpointer)rect, rect->priv->width, rect->priv->height);
    }

    return rect;
}

void rectangle_free(Rectangle *rect)
{
    if (rect != NULL && IS_RECTANGLE(rect))
        g_type_free_instance((GTypeInstance *)rect);
}

static guint rectangle_calculate_area(Rectangle *self)
{
    printf("Rectangle(0x%08x)::calculateArea\n", (gpointer)self);

    return self->priv->width * self->priv->height;
}

void rectangle_set_width(Rectangle *rect, guint width)
{
    if (rect != NULL && IS_RECTANGLE(rect))
        rect->priv->width = width;
}

void rectangle_set_height(Rectangle *rect, guint height)
{
    if (rect != NULL && IS_RECTANGLE(rect))
        rect->priv->height = height;
}

guint rectangle_get_width(Rectangle *rect)
{
    if (rect != NULL && IS_RECTANGLE(rect))
        return rect->priv->width;
    else
        return 0;
}

guint rectangle_get_height(Rectangle *rect)
{
    if (rect != NULL && IS_RECTANGLE(rect))
        return rect->priv->height;
    else
        return 0;
}

#if defined(DEMO_IFACE)
static void drawable_init(DrawableInterface *iface)
{
    printf("Rectangle(0x%08x)::Drawable::initialize\n", (gpointer)iface);

    iface->draw = (void *)rectangle_draw;
}

static void rectangle_draw(Rectangle *self)
{
    printf("Rectangle(0x%08x)::Drawable::draw\n", (gpointer)self);

    printf("\t+------+\n"
           "\t|      |\n"
           "\t+------+\n");
}
#endif
