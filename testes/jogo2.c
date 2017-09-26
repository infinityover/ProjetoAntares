// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h> 
#include <stdio.h>
 
// Atributos da tela
const int LARGURA_TELA = 960;
const int ALTURA_TELA = 720;
 
int main(void)
{
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0;
    // Flag que condicionará nosso looping
    int sair = 0;
    
    // Inicializa a Allegro
    al_init();

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }
    
    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }
 
    // Configura o título da janela
    al_set_window_title(janela, "Aprendendo - Pré-História");
 
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Alocamos o botão para fechar a aplicação
    botao_sair = al_load_bitmap("BT_Sair.png");
 
    // Desenha a imagem na tela
    al_draw_bitmap(botao_sair, 0, 0, 0);
 

    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar botão de saída.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
 
    while (!sair)
    {
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            // Ou se o evento foi um clique do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10)
                {
                    sair = 1;
                }
            }
        }
 
        // Atualiza a tela
        al_flip_display();
    }
 
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_sair);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}