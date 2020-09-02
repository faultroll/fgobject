// derived.c
#include "derived.h"
#include <stdio.h>
 
void derived_instance_set_i(Derived *instance, gint i) {
    instance->derived_instance_i = i;
    printf("Invoking derived_instance_set_i(): derived_instance_i=%d\n", instance->derived_instance_i);
}
 
void derived_instance_dump(Base *instance) {
    Derived *derived = G_TYPE_CHECK_INSTANCE_CAST(instance, derived_get_type(), Derived);
    printf("Invoking derived_instance_dump(): base_instance_i=%d, derived_instance_i=%d\n", instance->base_instance_i, derived->derived_instance_i);
}
 
static void derived_class_init(DerivedClass *klass, gpointer data) {
    printf("Calling derived_class_init()\n");
    base_class_set_i(300);
    /* override */
    BaseClass *base_klass = G_TYPE_CHECK_CLASS_CAST(klass, base_get_type(), BaseClass);
    base_klass->base_instance_dump = derived_instance_dump;
}
 
static void derived_instance_init(Derived *instance, gpointer data) {
    instance->derived_instance_i = 400;
    printf("Calling derived_instance_init(): derived_instance_i=%d\n", instance->derived_instance_i);
}
 
GType derived_get_type() {
    static GType derived_type = 0;
    if(derived_type == 0) {
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
            base_get_type(), "DerivedStaticClass", &derived_type_info, 0);
    }
    return derived_type;
}