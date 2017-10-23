//=====================================================================================================
//    Structs
//=====================================================================================================

//estrutura dos botões da tela inicial
struct botao{
    ALLEGRO_BITMAP *ativado;
    ALLEGRO_BITMAP *desativado;
} botao;

//estrutura das telas do jogo
struct telas{
    ALLEGRO_BITMAP *tela1;
    ALLEGRO_BITMAP *tela2;
} telas;

//estrutura de objetos das telas
struct objeto{
    int pontos;
    int pos_x;
    int pos_y;
    int frame_ativo;
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
ALLEGRO_EVENT evento;
ALLEGRO_COLOR cor;

int tecla_pressionada = 0;
unsigned char r, g, b;

struct botao botao_novo, botao_ajuda, botao_sair;
struct telas background, background_tela1;
struct objeto personagem;

const int LARGURA_TELA = 737; //920
const int ALTURA_TELA = 553; // 612
