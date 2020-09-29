// base.h
#ifndef BASE_H_
#define BASE_H_

#include "gtype.h"

G_BEGIN_DECLS

#define BASE_TYPE               (base_get_type())
#define BASE(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), BASE_TYPE, Base))
#define IS_BASE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), BASE_TYPE))
#define BASE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass), BASE_TYPE, BaseClass))
#define IS_BASE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass), BASE_TYPE))
#define BASE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj), BASE_TYPE, BaseClass))

typedef struct _Base            Base;
typedef struct _BaseClass       BaseClass;
typedef struct _BasePrivate     BasePrivate;

/* Base object struct */
struct _Base {
    GTypeInstance parent;
    /* private variable */
    BasePrivate *priv;
};

/* Base class struct */
struct _BaseClass {
    GTypeClass parent;
    /* instance method, used as a virtual method */
    void (*base_instance_dump)(Base *instance);
};

/* type method */
GType base_get_type();

/* static method of Base class */
void base_class_set_i(gint i);

/* non-virtual public method for Base object */
Base *base_new(void);
void base_free(Base *instance);
void base_instance_set_i(Base *instance, gint i);
gint base_instance_get_i(Base *instance);

/* virtual public method for Base object, both version are supported */
void base_instance_dump(Base *instance);

G_END_DECLS

#endif /* BASE_H_ */