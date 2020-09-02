
#include "base.h"
#include "derived.h"

int main() {
    /*
     * Official document:
     * Use of g_type_create_instance() is reserved for implementators of
     * fundamental types only. E.g. instances of the GObject hierarchy should
     * be created via g_object_new() and never directly through
     * g_type_create_instance() which doesn't handle things like singleton
     * objects or object construction.
     */
    Base *base = (Base *)g_type_create_instance(base_get_type());
    base_class_set_i(101);
    base_instance_set_i(base, 201);
    Derived *derived = (Derived *)g_type_create_instance(derived_get_type());
    derived_instance_set_i(derived, 401);
 
    /* Test polymorphism */
    Base *instances[2] = { base, (Base *)derived };
    int i;
    for (i = 0; i < 2; i++) {
        Base *inst = instances[i];
        BaseClass *klass = G_TYPE_INSTANCE_GET_CLASS(inst, base_get_type(), BaseClass);
        klass->base_instance_dump(inst);
    }
 
    return 0;
}