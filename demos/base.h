// base.h
#ifndef BASE_H_
#define BASE_H_
 
#include "gtype.h"
 
/* Base object struct */
typedef struct _Base {
    GTypeInstance parent;
    /* instance variable, should be hidden */
    gint base_instance_i;
} Base;
 
/* Base class struct */
typedef struct _BaseClass {
    GTypeClass parent;
    /* instance method, used as a virtual method */
    void (*base_instance_dump)(struct _Base *instance);
} BaseClass;
 
/* static method of Base class */
void base_class_set_i(gint i);
 
/* non-virtual public method for Base object */
void base_instance_set_i(Base *instance, gint i);
 
/* virtual public method for Base object, both version are supported */
void base_instance_dump(Base *instance);
 
/* type method */
GType base_get_type();
 
 
#endif /* BASE_H_ */