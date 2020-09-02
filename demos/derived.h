// derived.h
#ifndef DERIVED_H_
#define DERIVED_H_
 
#include "base.h"
#include "gtype.h"
 
/* Derived object struct */
typedef struct _Derived {
    /* The GTypeClass structure is still the first member of the class structure */
    Base parent;
    /* should be hidden */
    gint derived_instance_i;
} Derived;
 
/* Derived class struct */
typedef struct _DerivedClass {
    /* The TypeInstance structure is still the first member of the instance structure */
    BaseClass parent;
} DerivedClass;
 
/* non-virtual public method for Derived object */
void derived_instance_set_i(Derived *instance, gint i);
 
/* (Overwrite) virtual public method for Derived object, both version are supported */
void derived_instance_dump(Base *instance);
 
/* type method */
GType derived_get_type();
 
 
#endif /* DERIVED_H_ */