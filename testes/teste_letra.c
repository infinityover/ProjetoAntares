// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
 
// Para utilizarmos a função fprintf
#include <stdio.h>
 
// Atributos da tela
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;
 
int main(void)
{
    // A nossa janela
    ALLEGRO_DISPLAY *janela = NULL;
 
    // O nosso arquivo de fonte
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
    fonte = al_load_font("./fontes/OpenSans.ttf", 48, 0);
    if (!fonte)
    {
        al_destroy_display(janela);
        fprintf(stderr, "Falha ao carregar fonte.\n");
        return -1;
    }
 
    // Preenchemos a tela com a cor branca
    al_clear_to_color(al_map_rgb(255, 255, 255));
 
    // Texto alinhado à esquerda
    al_draw_text(fonte, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, "Esquerda");
 
    // Texto alinhado à direita
    al_draw_text(fonte, al_map_rgb(0, 255, 0), LARGURA_TELA - 10, 50, ALLEGRO_ALIGN_RIGHT, "Direita");
 
    // Texto centralizado
    al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 90, ALLEGRO_ALIGN_CENTRE, "Centro");
 
    // Exemplo de impressão de valores variáveis
    int i = 2;
    char *texto = "Uma string qualquer";
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 250, ALLEGRO_ALIGN_CENTRE, "Teste %d - %s", i, texto);
 
    // Atualizamos a tela
    al_flip_display();
 
    // Desalocação da fonte e da janela
    al_destroy_font(fonte);
    al_destroy_display(janela);
 
    return 0;
}