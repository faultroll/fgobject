
#include <stdio.h>

#define Nothing NULL

typedef struct {
    void *thing;
} Maybe;

Maybe foo(void *thing)
{
    return (Maybe) {
        .thing = thing,
    };
}

Maybe aha(void *(*f)(void *), Maybe a)
{
    return foo(f(a.thing));
    // return bar(foo(f(a.thing)), foo);
}

Maybe bar(Maybe a, Maybe(*contuation)(void *thing))
{
    return a.thing ? contuation(a.thing) : foo(Nothing);
}

Maybe test_a(void *thing)
{
    (*(int *)thing) *= 10;
    printf("Invoking (%s), thing is (%d)\n", __func__, (*(int *)thing));

    return foo(thing);
}

Maybe test_b(void *thing)
{
    (*(int *)thing) *= 100;
    printf("Invoking (%s), thing is (%d)\n", __func__, (*(int *)thing));

    return foo(thing);
}

Maybe test_c(void *thing)
{
    (*(int *)thing) += 1000;
    printf("Invoking (%s), thing is (%d)\n", __func__, (*(int *)thing));

    return foo(thing);
}

Maybe test_fail(void *thing)
{
    thing = Nothing;
    printf("Invoking (%s), thing is (%p)\n", __func__, thing);

    return foo(thing);
}

int main(void)
{
    /* test done */
    int a = 2;
#if 1
    Maybe x = bar(bar(bar(foo(&a), test_a), test_b), test_c);
#else
    Maybe x = foo(&a);
    if (x.thing) {
        x = test_a(x.thing);
        if (x.thing) {
            x = test_b(x.thing);
            if (x.thing) {
                x = test_c(x.thing);
            }
        }
    }
#endif
    printf("thing is (%d)\n", *(int *)(x.thing));

    /* test stops */
    x = bar(bar(bar(foo(&a), test_a), test_fail), test_c);
    printf("thing is (%p)\n", x.thing);

    return 0;
}
