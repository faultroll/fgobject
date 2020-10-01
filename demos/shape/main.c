
#include <stdio.h>
#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#if defined(DEMO_IFACE)
    #include "drawable.h"
#endif

int main(int argc, char **argv)
{
    Circle *circle;
    Rectangle *rect;

    circle = circle_new(6);
    printf("Area of Circle(0x%08x) is %u.\n",
           (gpointer)circle, shape_calculate_area(SHAPE(circle)));
#if defined(DEMO_IFACE)
    draw_object(DRAWABLE(circle));
#endif
    circle_free(circle);

    rect = rectangle_new(4, 5);
    printf("Area of Rectangle(0x%08x) is %u.\n",
           (gpointer)rect, shape_calculate_area(SHAPE(rect)));
#if defined(DEMO_IFACE)
    draw_object(DRAWABLE(rect));
#endif
    rectangle_free(rect);

    return 0;
}
