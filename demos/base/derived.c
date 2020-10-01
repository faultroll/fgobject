// derived.c
#include "derived.h"
#include <stdio.h>

/* Derived private struct */
struct _DerivedPrivate {
    /* instance variable, hidden */
    gint derived_instance_i;
};
#define DERIVED_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE((obj), \
                                    DERIVED_TYPE, DerivedPrivate))

Derived *derived_new(void)
{
    return (Derived *)g_type_create_instance(DERIVED_TYPE);
}

void derived_free(Derived *instance)
{
    if (instance != NULL && IS_DERIVED(instance))
        g_type_free_instance((GTypeInstance *)instance);
}

void derived_instance_set_i(Derived *instance, gint i)
{
    instance->priv->derived_instance_i = i;
    printf("Invoking derived_instance_set_i(): derived_instance_i=%d\n",
           instance->priv->derived_instance_i);
}

gint derived_instance_get_i(Derived *instance)
{
    printf("Invoking derived_instance_get_i(): derived_instance_i=%d\n",
           instance->priv->derived_instance_i);
    return instance->priv->derived_instance_i;
}

void derived_instance_dump(Base *instance)
{
    printf("Invoking derived_instance_dump(): base_instance_i=%d, derived_instance_i=%d\n",
           base_instance_get_i(instance), derived_instance_get_i(DERIVED(instance)));
}

static void derived_class_init(DerivedClass *klass, gpointer data)
{
    printf("Calling derived_class_init()\n");
    base_class_set_i(300);
    /* override */
    BaseClass *base_klass = BASE_CLASS(klass);
    base_klass->base_instance_dump = derived_instance_dump;

    g_type_class_add_private(klass, sizeof(DerivedPrivate));
}

static void derived_instance_init(Derived *instance, gpointer data)
{
    instance->priv = DERIVED_GET_PRIVATE(instance);

    instance->priv->derived_instance_i = 400;
    printf("Calling derived_instance_init(): derived_instance_i=%d\n",
           instance->priv->derived_instance_i);
}

GType derived_get_type()
{
    static GType derived_type = 0;
    if (derived_type == 0) {
        static const GTypeInfo derived_type_info = {
            sizeof(DerivedClass), /* class_size */
            NULL,               /* base_init */
            NULL,               /* base_finalize */
            (GClassInitFunc)derived_class_init, /* class_init */
            NULL,               /* class_finalize */
            NULL,               /* class_data */
            sizeof(Derived),    /* instance_size */
            0,                  /* n_preallocs */
            (GInstanceInitFunc)derived_instance_init, /* instance_init */
            // NULL                /* value_table */
        };
        derived_type = g_type_register_static(
                           BASE_TYPE, "DerivedStaticClass", &derived_type_info, 0);
    }
    return derived_type;
}
