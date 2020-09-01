
## perpose

This is a learning-oop-in-c project, reinventing oop system in c based on gtype(you don't need gobject, so we make it fallen, fallen from the sky we cannot touch).

- learn oop & gobject (paste some useful links)
- minimize gtype for embedded linux (daydreaming: run on mcu like stm32/8051) 
- learning cmake & gtestutil & github-ci

---

## TODO oop
- encaps
- inherit
- polymorph

gobject seems be inspired by java oop, not c++ oop. It treats class and interface differently. 

``` c
/* --- structures --- */
struct _TypeNode
{
  guint volatile ref_count;
#ifdef G_ENABLE_DEBUG
  guint volatile instance_count;
#endif
  GTypePlugin *plugin;
  guint        n_children; /* writable with lock */
  guint        n_supers : 8;
  guint        n_prerequisites : 9;
  guint        is_classed : 1;
  guint        is_instantiatable : 1;
  guint        mutatable_check_cache : 1;	/* combines some common path checks */
  GType       *children; /* writable with lock */
  TypeData * volatile data;
  GQuark       qname;
  GData       *global_gdata;
  union {
    GAtomicArray iface_entries;		/* for !iface types */
    GAtomicArray offsets;
  } _prot;
  GType       *prerequisites;
  GType        supers[1]; /* flexible array */
};
```
- qname -- name
- ref_count & is_classed & is_instantiatable & data -- for class & instantiate
- plugin -- dynamic type
- n_children/children & n_supers/supers -- for class inherit(one child one parent, one parent many children)
- global_gdata -- abstract type
- mutatable_check_cache & data(value_table) -- maybe for generic(value_table/GValue related), useless in oop
- _prot -- for interface(one class many interface)
- n_prerequisites & prerequisites -- for interface inherit(because interface struct don't have children or super like class)

[TypeNode](https://brionas.github.io/2014/06/14/GType-2/) storage is like below:

```asciiflow
                   static_fundamental_type_nodes

+---------+     +------------------------------------------------------------------+
|         |     |  +------------------------------------------------------------+  |
| iface   |     |  | class        | iface        | class         | ...          |  |
| array   +----------+_prot       |              |               |              |  |
|         |     |  |              |              |               |              |  |
+---------+     |  |              |              |               |              |  |
   many-to-many |  | +children    | +children    |               |              |  |
                |  +------------------------------------------------------------+  |
                +------------------------------------------------------------------+
                     |              |
          one-to-many+----------+   +------+--------------------+
                     |          |          |                    |
                +----+----+  +--+------+   +--------------+     +--------------+
                |         |  |         |   |              |     |              |
                |         |  |         |   |              |     |              |
                ++children|  ++children|   ++prerequisites|     ++prerequisites|
                +---------+  +---------+   +--------------+     +--------------+
                 |            |             |                    |
                 +            +             +                    +
```

The GType have three essential part of oop(TODO polymorph, as callback function, maybe contains in interface), so we can just use GType to reinvent the [oop system in c](https://www.gonwan.com/2011/03/13/oo-impelementation-in-c/).
(generic/GValue & signals/closure & ffi/marshal/paramspecs in GObject are unneeded for basic oop)

## implement

- gutil

  utility

  - gmacros&gversionmacros

    .../deprecated/...
  
  - gmessages

    return_if_xxx/g_warning/...

    gabort/gassert/...
  
  - config&glibconfig

    platformdiff(you have build the origin glib with meson to get config.h&glibconfig.h)

  - gutils&gmem&gstrfunc

    g_bit_storage/...

  - trace

    stub, remove TRACE(...)

- gsync

  synchronize

  - gthread(named glock seems better)

    once_init/lock/...(no thread func needed)

    DONE spilt to gcons. (gonce<--gslist<--gslice<--gprivate, and gonce&gpirvate are in the same file gthread.c. temporarily spilt gonce to stor) TODO elegant way needed.
  
  - gatomic

  - grefcount

- gstor

  storage&datastructure

  - gquark&ghash&gslist

  - gslice

  - gslist&gatomicarray

- gcons

  constructor

  - gonce(spilt from gthread, for it relay on gslist)

  - constructor.h

- gtype

  you don't need gobject, gtype is enough

  - static
    
    gtype
  
  - dynamic
    
    gtypeplugin&gtypemodule

    TODO gtypemodule use auto_ptr, which need dlist(glist.c), reinvent some

- tests
  
  demos from learning gobject [1](http://www.wl-chuang.com/blog/categories/gobject), [2](http://garfileo.is-programmer.com/2011/7/14/gobject-notes.27977.html), ...

