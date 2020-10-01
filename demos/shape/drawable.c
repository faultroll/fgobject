#include "drawable.h"
#include <stdio.h>

static void drawable_base_init(DrawableInterface *self);
static void drawable_base_finalize(DrawableInterface *self);
static void drawable_class_init(DrawableInterface *self);

GType drawable_get_type()
{
    static GType type = 0;

    if (type == 0) {
        static const GTypeInfo info = {
            sizeof(DrawableInterface),
            (GBaseInitFunc)drawable_base_init,
            (GBaseFinalizeFunc)drawable_base_finalize,
            (GClassInitFunc)drawable_class_init,
            NULL,
            NULL,
        };

        type = g_type_register_static(G_TYPE_INTERFACE, "Drawable",
                                      &info, 0);
    }

    return type;
}

static void drawable_base_init(DrawableInterface *self)
{
    printf("Drawable(0x%08x)::base::initialize\n", (gpointer)self);
}

static void drawable_base_finalize(DrawableInterface *self)
{
    printf("Drawable(0x%08x)::base::finalize\n", (gpointer)self);
}

static void drawable_class_init(DrawableInterface *self)
{
    printf("Drawable(0x%08x)::class::initialize\n", (gpointer)self);
}

void draw_object(Drawable *drawable)
{
    if (!IS_DRAWABLE(drawable)) {
        printf("%s(0x%08x) is not drawable.\n",
               g_type_name(G_TYPE_FROM_INSTANCE(drawable)), (gpointer)drawable);
    } else {
        DRAWABLE_GET_INTERFACE(drawable)->draw(drawable);
    }
}
