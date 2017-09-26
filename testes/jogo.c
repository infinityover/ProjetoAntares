// Os arquivos de cabeçalho
#include <allegro5/allegro.h>

// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
 
#include <stdio.h>
 
// Atributos da tela
const int LARGURA_TELA = 737;
const int ALTURA_TELA = 553;
 
int main(void)
{
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *botao_novo = 0, *botao_ajuda=0, *botao_sair = NULL,  *background = NULL;
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
    al_set_window_title(janela, "Aprendendo Pré-História");
 
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



    // Alocamos o background
    background = al_load_bitmap("Tela_Inicial.bmp");
    if (!background)
    {
        fprintf(stderr, "Falha ao criar background.\n");
        al_destroy_display(janela);
        return -1;
    }
    


    // Alocamos o botão para fechar a aplicação
    botao_novo = al_load_bitmap("BT_Novo1.bmp");
    if (!botao_novo)
    {
        fprintf(stderr, "Falha ao criar botão novo jogo.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o botão para fechar a aplicação
    botao_ajuda = al_load_bitmap("BT_Ajuda1.bmp");
    if (!botao_ajuda)
    {
        fprintf(stderr, "Falha ao criar botão de ajuda.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Alocamos o botão para fechar a aplicação
    botao_sair = al_load_bitmap("BT_Sair1.bmp");
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar botão de saída.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar a fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    
    int no_novo, no_ajuda, no_sair;

    while (!sair)
    {
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            no_novo = 0;
            no_ajuda = 0;
            no_sair = 0;
 
            // Se o evento foi de movimentação do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_novo) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_novo) - 220 &&
                    evento.mouse.y <= ALTURA_TELA - 220)
                {
                    no_novo = 1;
                } else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_ajuda) - 80 &&
                    evento.mouse.x <= LARGURA_TELA - 80 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_ajuda) - 140 &&
                    evento.mouse.y <= ALTURA_TELA - 140)
                {
                    no_ajuda = 1;
                } else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 60 &&
                    evento.mouse.y <= ALTURA_TELA - 60)
                {
                    no_sair = 1;
                }

            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 60 &&
                    evento.mouse.y <= ALTURA_TELA - 60)
                {
                    sair = 1;
                }
            }
        }

        // Desenha o background na tela
        al_draw_bitmap(background, 0, 0, 0);

        if (no_novo == 1 )
        {
            
            botao_novo = al_load_bitmap("BT_Novo.bmp");
        } else
        {
            botao_novo = al_load_bitmap("BT_Novo1.bmp");
        }

        if (no_ajuda == 1 )
        {
            botao_ajuda = al_load_bitmap("BT_Ajuda.bmp");
        } else
        {
            botao_ajuda = al_load_bitmap("BT_Ajuda1.bmp");
        }

        if (no_sair == 1 )
        {
            botao_sair = al_load_bitmap("BT_Sair2.bmp");
        } else
        {
            botao_sair = al_load_bitmap("BT_Sair1.bmp");
        }
        
        al_convert_mask_to_alpha(botao_novo,al_map_rgb(255,0,255));
        // Desenha a sair na tela
        al_draw_bitmap(botao_novo, LARGURA_TELA - al_get_bitmap_width(botao_novo) - 35,
        ALTURA_TELA - al_get_bitmap_height(botao_novo) -220, 0);

        al_convert_mask_to_alpha(botao_ajuda,al_map_rgb(255,0,255));
        // Desenha a sair na tela
        al_draw_bitmap(botao_ajuda, LARGURA_TELA - al_get_bitmap_width(botao_ajuda) - 80,
        ALTURA_TELA - al_get_bitmap_height(botao_ajuda) - 140, 0);

        al_convert_mask_to_alpha(botao_sair,al_map_rgb(255,0,255));
        // Desenha a sair na tela
        al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 35,
        ALTURA_TELA - al_get_bitmap_height(botao_sair) - 60, 0);

        // Atualiza a tela
        al_flip_display();

    }
 
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_novo);
    al_destroy_bitmap(botao_ajuda);
    al_destroy_bitmap(botao_sair);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
 
    return 0;
}