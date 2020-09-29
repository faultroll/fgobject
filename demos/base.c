// base.c
#include "base.h"
#include <stdio.h>

/* Base private struct */
struct _BasePrivate {
    /* instance variable, hidden */
    gint base_instance_i;
};
#define BASE_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE((obj), \
                                 BASE_TYPE, BasePrivate))

/* static field of Base class */
gint base_class_i;

/* static method of Base class */
void base_class_set_i(gint i)
{
    base_class_i = i;
    printf("Invoking base_class_set_i(): base_class_i=%d\n", base_class_i);
}

Base *base_new(void)
{
    return (Base *)g_type_create_instance(BASE_TYPE);
}

void base_free(Base *instance)
{
    if (instance != NULL && IS_BASE(instance))
        g_type_free_instance((GTypeInstance *)instance);
}

void base_instance_set_i(Base *instance, gint i)
{
    instance->priv->base_instance_i = i;
    printf("Invoking base_instance_set_i(): base_instance_i=%d\n",
           instance->priv->base_instance_i);
}

gint base_instance_get_i(Base *instance)
{
    printf("Invoking base_instance_get_i(): base_instance_i=%d\n",
           instance->priv->base_instance_i);
    return instance->priv->base_instance_i;
}

void base_instance_dump(Base *instance)
{
    printf("Invoking base_instance_dump(): base_instance_i=%d\n",
           base_instance_get_i(instance));
}

static void base_class_init(BaseClass *klass, gpointer data)
{
    base_class_i = 100;
    printf("Calling base_class_init(): base_class_i=%d\n", base_class_i);
    klass->base_instance_dump = base_instance_dump;

    g_type_class_add_private(klass, sizeof(BasePrivate));
}

static void base_instance_init(Base *instance, gpointer data)
{
    instance->priv = BASE_GET_PRIVATE(instance);

    instance->priv->base_instance_i = 200;
    printf("Calling base_instance_init(): base_instance_i=%d\n",
           instance->priv->base_instance_i);
}

GType base_get_type()
{
    static GType base_type = 0;
    if (base_type == 0) {
        static const GTypeInfo base_type_info = {
            sizeof(BaseClass),  /* class_size */
            NULL,               /* base_init */
            NULL,               /* base_finalize */
            (GClassInitFunc)base_class_init, /* class_init */
            NULL,               /* class_finalize */
            NULL,               /* class_data */
            sizeof(Base),       /* instance_size */
            0,                  /* n_preallocs */
            (GInstanceInitFunc)base_instance_init, /* instance_init */
            // NULL                /* value_table */
        };
        GTypeFundamentalInfo foo_type_fundamental_info = {
            G_TYPE_FLAG_CLASSED           /* Indicates a classed type */
            | G_TYPE_FLAG_INSTANTIATABLE  /* Indicates an instantiable type */
            | G_TYPE_FLAG_DERIVABLE       /* Indicates a flat derivable type */
            | G_TYPE_FLAG_DEEP_DERIVABLE  /* Indicates a deep derivable type */
        };
        base_type = g_type_register_fundamental(g_type_fundamental_next(),
                                                "BaseFundamentalType", &base_type_info, &foo_type_fundamental_info, 0);
    }
    return base_type;
}
