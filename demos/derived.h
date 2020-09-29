// derived.h
#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"
#include "gtype.h"

G_BEGIN_DECLS

#define DERIVED_TYPE               (derived_get_type())
#define DERIVED(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), DERIVED_TYPE, Derived))
#define IS_DERIVED(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), DERIVED_TYPE))
#define DERIVED_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass), DERIVED_TYPE, DerivedClass))
#define IS_DERIVED_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass), DERIVED_TYPE))
#define DERIVED_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj), DERIVED_TYPE, DerivedClass))

typedef struct _Derived            Derived;
typedef struct _DerivedClass       DerivedClass;
typedef struct _DerivedPrivate     DerivedPrivate;

/* Derived object struct */
struct _Derived {
    /* The GTypeClass structure is still the first member of the class structure */
    Base parent;
    /* private variable */
    DerivedPrivate *priv;
};

/* Derived class struct */
struct _DerivedClass {
    /* The TypeInstance structure is still the first member of the instance structure */
    BaseClass parent;
};

/* type method */
GType derived_get_type();

/* non-virtual public method for Derived object */
Derived *derived_new(void);
void derived_free(Derived *instance);
void derived_instance_set_i(Derived *instance, gint i);
gint derived_instance_get_i(Derived *instance);

/* (Overwrite) virtual public method for Derived object, both version are supported */
void derived_instance_dump(Base *instance);

G_END_DECLS

#endif /* DERIVED_H_ */