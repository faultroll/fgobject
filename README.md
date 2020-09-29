
excuse my poor chinglish

---

## perpose

This is a learning-oop-in-c project, reinventing oop system in c based on gtype(you don't need gobject, so we make it fallen, fallen from the sky we cannot touch).

- learn oop & gobject (paste some useful links)
- minimize gtype for embedded linux (daydreaming: run on mcu like stm32/8051) 
- learning cmake & gtestutil & github-ci

## oop in gobject
- encapsulation	
- inheritance
- polymorphism

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
(generic/GValue & [signals/closure](http://pingf.is-programmer.com/posts/21355.html) & ffi/marshal/paramspecs in GObject are unneeded for basic oop)

## implement

based on glib-2.64.4 (in config.h, seems no relative changes in 2.64.5). removes the some features above in gtype(not neceesary, and IMO user should manage memory by themself)
use following sentence to build the library and run demo
``` cmake
cmake -B build -DCMAKE_INSTALL_PREFIX="dist" && make -j -C build -f Makefile install
cd demos && cmake -B build && make -j -C build -f Makefile
LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:`pwd`/../dist/lib" ./build/demos
```
the implement is as follow
```asciiflow
+-------+   +-------+
| gtype <-+-+ gcons |
+-------+ | +---^---+
          |     |
          | +---+---+
          +-+ gstor |
          | +---^---+
          |     |
          | +---+---+
          +-+ gsync |       bare metal
          | +---^---+       +-------+
          |     |           | libc  |
          | +---+---+       +-------+
          +-+ gutil <-------+
            +-------+       +-------+
                            | posix |
                            +-------+
                               os

```
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

    ghash -- grefcount -- gatomic

- gstor

  storage&datastructure

  - gquark&ghash&gslist

    gquark -- ghash -- gslice

  - gslice

  - gslist&gatomicarray

    gatomicarray -- gslice

- gcons

  constructor

  - gonce(spilt from gthread, for it relay on gslist)

    gonce(gthread) -- gslist -- gslice -- gprivate(gthread) -- gmem

  - constructor.h

- gtype

  you don't need gobject, gtype is enough

  successfully compiled on x86_64-linux-gnu, target size 115kB

  - static
    
    gtype
  
  - dynamic
    
    gtypeplugin&gtypemodule

    TODO gtypemodule use auto_ptr, which need dlist(glist.c), reinvent some

- tests

  TODO gtestutils

  [gtestutils](https://segmentfault.com/a/1190000003996312), [monad in c](https://segmentfault.com/a/1190000012435966)

- demos
  
  from learning gobject [1](http://www.wl-chuang.com/blog/categories/gobject), [2](http://garfileo.is-programmer.com/2011/7/14/gobject-notes.27977.html), ...

## TODOs

  next vesion
  - delete unneeded code & rename files
    - print funcs & debug funcs in gmessages&gutils&gstrfuncs
  - gtestutils & github-ci
  - config.h & glibconfig.h
  - reinvent gtypemodule
  - reinvent gobject using fgobject(gtype)
  - be up-to-date with glib mainline(at least glib-2.64.x)
