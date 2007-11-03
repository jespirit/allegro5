#include "allegro.h"

int main(void)
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *bitmap;
    al_init();
    display = al_create_display(320, 200);
    bitmap = al_load_bitmap("mysha.pcx");
    al_draw_bitmap(bitmap, 0, 0, 0);
    al_flip_display();
    al_rest(1000);
    return 0;
}
END_OF_MAIN()
