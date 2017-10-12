#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

//=====================================================================================================
//    ESTRUTURA DE DADOS
//=====================================================================================================

//estrutura dos botões da tela inicial
struct botao{
    ALLEGRO_BITMAP *ativado;
    ALLEGRO_BITMAP *desativado;
} botao;

//estrutura dos botões ativos e desativamos
struct telas{
    ALLEGRO_BITMAP *tela1;
    ALLEGRO_BITMAP *tela2;
    ALLEGRO_BITMAP *tela3;
} telas;

//estrutura de objetos das telas
struct objeto{
    int pos_x;
    int pos_y;
    char orientacao;
    ALLEGRO_BITMAP *imagem_ativa;
    ALLEGRO_BITMAP *imagem_cima[4];
    ALLEGRO_BITMAP *imagem_baixo[4];
    ALLEGRO_BITMAP *imagem_esquerda[4];
    ALLEGRO_BITMAP *imagem_direita[4];
} objeto;

//=====================================================================================================
//    INICIALIZAÇÃO DAS VARIÁVEIS  GLOBAIS
//=====================================================================================================

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *botao_novo_exibir = NULL, *botao_ajuda_exibir = NULL, *botao_sair_exibir = NULL, *background_exibir = NULL, *background_exibir2 = NULL;
ALLEGRO_TIMER *timer = NULL;
int tecla_pressionada = 0;
const int LARGURA_TELA = 737;
const int ALTURA_TELA = 553;
struct botao botao_novo, botao_ajuda, botao_sair;
struct telas background;
struct objeto personagem;
unsigned char r, g, b;

volatile int milisegundos;


//=====================================================================================================
//    INICIALIZAÇÃO DAS FUNÇÕES UTILIZADAS NO CÓDIGO
//=====================================================================================================

bool inicializar();
bool carregar_imagens();
void finalizar();
void msec_counter() { milisegundos++; }

//=====================================================================================================
//    CÓDIGO PRINCIPAL DO JOGO
//=====================================================================================================

int main(void){
    int no_novo = 0, no_ajuda = 0, no_sair = 0, novo_jogo = 0, loop = 0, frame_ativo = 0, ultima_tecla = 0, Etipo = 0;
    ALLEGRO_COLOR cor;
    personagem.pos_x = 0;
    personagem.pos_y = 0;

    /*  
        no_novo     - Variavel de condicionamento do botão de novo jogo
        no_ajuda    - Variavel de condicionamento do botão de ajuda
        no_sair     - Variavel de condicionamento do botão de saida
    */
    
    if (!inicializar())
        return -1;
    
    if (!carregar_imagens())
        return -1;

    // aloca o background da tela inicial
    background_exibir = background.tela1;
    
    //=================================================================================================
    //    TELA INICIAL
    //=================================================================================================

    while (!loop){
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            no_novo = 0;
            no_ajuda = 0;
            no_sair = 0;
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            
            // Se o evento foi fechar o jogo
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                loop = 1;
                continue;
            }
            
            // Tratamento após clicar no botão novo jogo
            if(novo_jogo == 1)
            {
                loop = 1;
                continue;
            }
            
            // Se o evento foi movimentar o mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_novo.ativado) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_novo.ativado) - 220 &&
                    evento.mouse.y <= ALTURA_TELA - 220)
                {
                    no_novo = 1;
                } else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_ajuda.ativado) - 80 &&
                    evento.mouse.x <= LARGURA_TELA - 80 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_ajuda.ativado) - 140 &&
                    evento.mouse.y <= ALTURA_TELA - 140)
                {
                    no_ajuda = 1;
                } else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair.ativado) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair.ativado) - 60 &&
                    evento.mouse.y <= ALTURA_TELA - 60)
                {
                    no_sair = 1;
                }
            }
            // Se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                //click no botão sair
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair.ativado) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair.ativado) - 60 &&
                    evento.mouse.y <= ALTURA_TELA - 60)
                {
                    loop = 1;
                }
                
                //Click no botão novo
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_novo_exibir) - 35 &&
                    evento.mouse.x <= LARGURA_TELA - 35 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_novo_exibir) - 220 &&
                    evento.mouse.y <= ALTURA_TELA - 220)
                {
                    novo_jogo = 1;
                }
            } else
            {
                continue;
            }

        }
        
        // Desenha o background na tela
        al_draw_bitmap(background_exibir, 0, 0, 0);

        // aloca os botões ativos
        if (no_novo == 1 )
        {
            botao_novo_exibir = botao_novo.ativado;
        } else
        {
            botao_novo_exibir = botao_novo.desativado;
        }
        
        if (no_ajuda == 1 )
        {
            botao_ajuda_exibir = botao_ajuda.ativado;
        } else 
        {
            botao_ajuda_exibir = botao_ajuda.desativado;
        }
        
        if (no_sair == 1 )
        {
            botao_sair_exibir = botao_sair.ativado;
        } else 
        {
            botao_sair_exibir = botao_sair.desativado;
        }
        
        //Desenha BT_Novo_Jogo
        al_convert_mask_to_alpha(botao_novo_exibir,al_map_rgb(255,0,255));
        al_draw_bitmap(botao_novo_exibir, LARGURA_TELA - al_get_bitmap_width(botao_novo_exibir) - 35,
        ALTURA_TELA - al_get_bitmap_height(botao_novo_exibir) -220, 0);
        
        //Desenha BT_Ajuda
        al_convert_mask_to_alpha(botao_ajuda_exibir,al_map_rgb(255,0,255));
        al_draw_bitmap(botao_ajuda_exibir, LARGURA_TELA - al_get_bitmap_width(botao_ajuda_exibir) - 80,
        ALTURA_TELA - al_get_bitmap_height(botao_ajuda_exibir) - 140, 0);
        
        //Desenha BT_Sair
        al_convert_mask_to_alpha(botao_sair_exibir,al_map_rgb(255,0,255));
        al_draw_bitmap(botao_sair_exibir, LARGURA_TELA - al_get_bitmap_width(botao_sair_exibir) - 35,
        ALTURA_TELA - al_get_bitmap_height(botao_sair_exibir) - 60, 0);
        
        // Atualiza a tela
        al_flip_display();
    }
    
    //=================================================================================================
    //   1ª FASE
    //=================================================================================================
    
    if (novo_jogo == 1)
    {        
        loop = 0;
        
        // aloca o background da 1ª fase
        background_exibir = background.tela2;

        // aloca o background da 1ª fase
        background_exibir2 = background.tela3;

        al_start_timer(timer);

        int tempo_troca = 100;
        
        while (!loop)
        {          
            // Verificamos se há eventos na fila
            while (!al_is_event_queue_empty(fila_eventos))
            {
                ALLEGRO_EVENT evento;
                al_wait_for_event(fila_eventos, &evento);
                
                // Se o evento foi fechar o jogo
                if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    loop = 1;
                
                if(evento.type == ALLEGRO_EVENT_KEY_UP)
                    tecla_pressionada = 0;
                
                if(evento.type == ALLEGRO_EVENT_TIMER && tecla_pressionada == 1)
                {           
                    if (personagem.orientacao == 'D')
                    {
                        cor = al_get_pixel(background_exibir2, personagem.pos_x + 10, personagem.pos_y);
                        al_unmap_rgb(cor, &r, &g, &b);

                        if (r != 255 && g != 0 && b != 255)
                        {
                            personagem.pos_x = personagem.pos_x + 10;
                            personagem.imagem_ativa = personagem.imagem_direita[frame_ativo];
                        }
                    } else if(personagem.orientacao == 'E')
                    {
                        cor = al_get_pixel(background_exibir2, personagem.pos_x - 10, personagem.pos_y);
                        al_unmap_rgb(cor, &r, &g, &b);

                        if (r != 255 && g != 0 && b != 255)
                        {
                            personagem.pos_x = personagem.pos_x - 10;
                            personagem.imagem_ativa = personagem.imagem_esquerda[frame_ativo];
                        }
                    } else if (personagem.orientacao == 'C')
                    {
                        cor = al_get_pixel(background_exibir2, personagem.pos_x, personagem.pos_y - 10);
                        al_unmap_rgb(cor, &r, &g, &b);

                        if (r != 255 && g != 0 && b != 255)
                        {
                            personagem.pos_y = personagem.pos_y - 10;
                            personagem.imagem_ativa = personagem.imagem_cima[frame_ativo];
                        }
                    } else if (personagem.orientacao == 'B')
                    {
                        cor = al_get_pixel(background_exibir2, personagem.pos_x, personagem.pos_y + 10);
                        al_unmap_rgb(cor, &r, &g, &b);

                        if (r != 255 && g != 0 && b != 255)
                        {
                            personagem.pos_y = personagem.pos_y + 10;
                            personagem.imagem_ativa = personagem.imagem_baixo[frame_ativo];
                        }
                    }
                    
                    if (frame_ativo == 3)
                        frame_ativo = 0;
             
                }
                
                if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    tecla_pressionada = 1;
                    switch(evento.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_UP:
                            //personagem.pos_y = personagem.pos_y - 10;
                            //personagem.imagem_ativa = personagem.imagem_cima[frame_ativo];
                            personagem.orientacao = 'C';
                            break;
                        case ALLEGRO_KEY_DOWN:
                            //personagem.pos_y = personagem.pos_y + 10;
                            //personagem.imagem_ativa = personagem.imagem_baixo[frame_ativo];
                            personagem.orientacao = 'B';
                            break;
                        case ALLEGRO_KEY_LEFT:
                            //personagem.pos_x = personagem.pos_x -10;
                            //personagem.imagem_ativa = personagem.imagem_esquerda[frame_ativo];
                            personagem.orientacao = 'E';
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            //personagem.pos_x = personagem.pos_x + 10;
                            //personagem.imagem_ativa = personagem.imagem_direita[frame_ativo];
                            personagem.orientacao = 'D';
                            break;
                    }
                    if (frame_ativo == 3)
                    {
                        frame_ativo = 0;
                    } else{
                        frame_ativo++;
                    }
                }
                

                // Se o evento foi movimentar o mouse
                if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
                {
                    
                }
                // Se o evento foi um clique do mouse
                else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                    
                }
            }

            //Desenha background
            al_convert_mask_to_alpha(background_exibir,al_map_rgb(0,0,0));
            al_draw_bitmap(background_exibir, 0,0,0);            

            //Desenha Personagem quando pressionado o botão novo jogo
            al_draw_bitmap(personagem.imagem_ativa, personagem.pos_x, personagem.pos_y, 0);
            
            // Atualiza a tela
            al_flip_display();
        }
    }
    
    finalizar();
    return 0;
}

//===================================================================================================
//    FUNÇÕES
//===================================================================================================

bool inicializar()
{
    // Inicializa o Allegro
    al_init();
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }
    
    // Metodo do addon de inicializacao de imagem
    al_init_image_addon();
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    // Configura o título da janela
    al_set_window_title(janela, "Aprendendo Pré-História");
    
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return false;
    }

    // Atribui o cursor padrão do sistema na aplicação
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return false;
    }
    
    // Torna apto o uso do teclado na aplicação
    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }
    
    // Cria a fila de eventos na aplicação
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar a fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
    
    // Cria o timer na aplicação
    timer = al_create_timer(0.1);
    if (!timer)
    {
        fprintf(stderr, "Falha ao criar timer.\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        return false;
    }
    
    // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    
    return true;
}

bool carregar_imagens()
{
    // Alocando os backgrounds
    background.tela1 = al_load_bitmap("img/Tela_Inicial.bmp");
    background.tela2 = al_load_bitmap("img/Tela_Fase1.bmp");
    background.tela3 = al_load_bitmap("img/Trasparencia_Fase1.bmp");

    // Alocamos o botão para ajuda
    botao_ajuda.desativado = al_load_bitmap("img/BT_Ajuda_Desativado.bmp");
    botao_ajuda.ativado = al_load_bitmap("img/BT_Ajuda_Ativado.bmp");
    
    // Alocamos o botão para novo jogo
    botao_novo.desativado = al_load_bitmap("img/BT_Novo_Desativado.bmp");
    botao_novo.ativado = al_load_bitmap("img/BT_Novo_Ativado.bmp");
    
    // Alocamos o botão para fechar a aplicação
    botao_sair.desativado = al_load_bitmap("img/BT_Sair_Desativado.bmp");
    botao_sair.ativado = al_load_bitmap("img/BT_Sair_Ativado.bmp");

    // Alocamos os sprites do personagem
    personagem.imagem_baixo[0] = al_load_bitmap("testes/Sprite teste/personagem_01.png");
    personagem.imagem_baixo[1] = al_load_bitmap("testes/Sprite teste/personagem_02.png");
    personagem.imagem_baixo[2] = al_load_bitmap("testes/Sprite teste/personagem_03.png");
    personagem.imagem_baixo[3] = al_load_bitmap("testes/Sprite teste/personagem_04.png");
    if (!personagem.imagem_baixo[0] || !personagem.imagem_baixo[1] || !personagem.imagem_baixo[2] || !personagem.imagem_baixo[3])
    {
        printf("erro ao carregar imagem");
        return false;
    }
    
    personagem.imagem_esquerda[0] = al_load_bitmap("testes/Sprite teste/personagem_05.png");
    personagem.imagem_esquerda[1] = al_load_bitmap("testes/Sprite teste/personagem_06.png");
    personagem.imagem_esquerda[2] = al_load_bitmap("testes/Sprite teste/personagem_07.png");
    personagem.imagem_esquerda[3] = al_load_bitmap("testes/Sprite teste/personagem_08.png");
    if (!personagem.imagem_esquerda[0] || !personagem.imagem_esquerda[1] || !personagem.imagem_esquerda[2] || !personagem.imagem_esquerda[3])
    {
        printf("erro ao carregar imagem");
        return false;
    }

    personagem.imagem_direita[0] = al_load_bitmap("testes/Sprite teste/personagem_09.png");
    personagem.imagem_direita[1] = al_load_bitmap("testes/Sprite teste/personagem_10.png");
    personagem.imagem_direita[2] = al_load_bitmap("testes/Sprite teste/personagem_11.png");
    personagem.imagem_direita[3] = al_load_bitmap("testes/Sprite teste/personagem_12.png");
    if (!personagem.imagem_direita[0] || !personagem.imagem_direita[1] || !personagem.imagem_direita[2] || !personagem.imagem_direita[3])
    {
        printf("erro ao carregar imagem");
        return false;
    }

    personagem.imagem_cima[0] = al_load_bitmap("testes/Sprite teste/personagem_13.png");
    personagem.imagem_cima[1] = al_load_bitmap("testes/Sprite teste/personagem_14.png");
    personagem.imagem_cima[2] = al_load_bitmap("testes/Sprite teste/personagem_15.png");
    personagem.imagem_cima[3] = al_load_bitmap("testes/Sprite teste/personagem_16.png");
    if (!personagem.imagem_cima[0] || !personagem.imagem_cima[1] || !personagem.imagem_cima[2] || !personagem.imagem_cima[3])
    {
        printf("erro ao carregar imagem");
        return false;
    }
    
    personagem.imagem_ativa = personagem.imagem_cima[3];
    
    if (!botao_novo.desativado || !botao_novo.ativado)
    {
        fprintf(stderr, "Falha ao criar botão novo jogo.\n");
        al_destroy_display(janela);
        return false;
    }
    if (!botao_ajuda.desativado || !botao_ajuda.ativado)
    {
        fprintf(stderr, "Falha ao criar botão de ajuda.\n");
        al_destroy_display(janela);
        return false;
    }
    if (!botao_sair.desativado || !botao_sair.ativado)
    {
        fprintf(stderr, "Falha ao criar botão de saída.\n");
        al_destroy_display(janela);
        return false;
    }
    
    return true;
}

//int getpixel(ALLEGRO_BITMAP *bmp, int x, int y);

void finalizar()
{
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_novo.ativado);
    al_destroy_bitmap(botao_ajuda.ativado);
    al_destroy_bitmap(botao_sair.ativado);
    al_destroy_bitmap(botao_novo.desativado);
    al_destroy_bitmap(botao_ajuda.desativado);
    al_destroy_bitmap(botao_sair.desativado);
    //al_destroy_bitmap(background.tela1);
    //al_destroy_bitmap(background.tela2);
    //al_destroy_bitmap(personagem.imagem_cima);
    //al_destroy_bitmap(personagem.imagem_baixo);
    //al_destroy_bitmap(personagem.imagem_direita);
    //al_destroy_bitmap(personagem.imagem_esquerda);
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    
    /*Não remover, ponteiro destas variaveis já foram destruidos na desacolação acima
    al_destroy_bitmap(botao_novo_exibir);
    al_destroy_bitmap(botao_ajuda_exibir);
    al_destroy_bitmap(botao_sair_exibir);
    *********************************************************************************/
}