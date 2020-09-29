
#include "base.h"
#include "derived.h"

int main()
{
    /*
     * Official document:
     * Use of g_type_create_instance() is reserved for implementators of
     * fundamental types only. E.g. instances of the GObject hierarchy should
     * be created via g_object_new() and never directly through
     * g_type_create_instance() which doesn't handle things like singleton
     * objects or object construction.
     */
    Base *base = base_new();
    base_class_set_i(101);
    base_instance_set_i(base, 201);
    Derived *derived = derived_new();
    derived_instance_set_i(derived, 401);

    /* Test polymorphism */
    Base *instances[2] = { base, /* (Base *)derived */BASE(derived) };
    int i;
    for (i = 0; i < 2; i++) {
        Base *inst = instances[i];
        BaseClass *klass = BASE_GET_CLASS(inst);
        klass->base_instance_dump(inst);
    }

    derived_free(derived);
    base_free(base);

    return 0;
}
