#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;


int main(void)
{

	ALLEGRO_DISPLAY *janela = NULL;
	
	ALLEGRO_BITMAP *imagem = NULL;

    ALLEGRO_FONT *fonte = NULL;

	    // Inicialização da biblioteca Allegro
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }
 
    // Inicialização do add-on para uso de fontes
    al_init_font_addon();
 
    // Inicialização do add-on para uso de fontes True Type
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return -1;
    }
 
    // Criação da nossa janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }
 
    // Carregando o arquivo de fonte
    fonte = al_load_font("pirulen.ttf", 48, 0);
    if (!fonte)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return -1;
    }

	imagem = al_load_bitmap("imagens_testes/m_1.jpg");
    
    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_draw_bitmap(imagem,0,0,0);

    al_draw_text(fonte, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Esquerda");

    al_flip_display();

   	al_rest(2.0);

	return 0;
	al_destroy_font(fonte);
	al_destroy_display(janela);
}