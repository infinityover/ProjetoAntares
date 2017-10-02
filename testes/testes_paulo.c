#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


int main(void)
{
    ALLEGRO_DISPLAY *janela = NULL;

    ALLEGRO_BITMAP *imagem = NULL;

    al_init();

    al_init_image_addon();

    al_init_font_addon();
 

    imagem = al_load_bitmap("imagens_testes/m_1.jpg");

    janela = al_create_display(640,480);

    al_draw_bitmap(imagem,0,0,0);

    al_flip_display();

    return 0;

    //ALLEGRO_DISPLAY *janela = NULL;
    // 
    //if (!al_init())
    //{
    //    fprintf(stderr, "Falha ao inicializar a Allegro 5\n");
    //    return -1;
    //}
    //
    //janela = al_create_display(640, 480);
    //if (!janela)
    //{
    //    fprintf(stderr, "Falha ao criar a janela\n");
    //    return -1;
    //}
    //
    //al_clear_to_color(al_map_rgb(255, 255, 255));
    //
    //al_flip_display();
    //
    //al_rest(10.0);
    //
    //al_destroy_display(janela);
    //
    //return 0;
}