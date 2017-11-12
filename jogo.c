#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "variaveis.c"
#include "funcoes.c"

//=====================================================================================================
//    CÓDIGO PRINCIPAL DO JOGO
//=====================================================================================================

int main(void){
    int retorno_tela_inicial = 0, retorno_fase1 = 0, loop = 0;

    if (!inicializar())
        return -1;

    if (!carregar_imagens())
        return -1;

    retorno_tela_inicial = tela_inicial(loop);

    if (retorno_tela_inicial == -1)
    {
    	finalizar();
    	return -1;
    }

	retorno_fase1 = fase_1(retorno_tela_inicial, loop);

    if (retorno_fase1 == -1)
    {
    	finalizar();
    	return -1;
    }
    //fase_2()

    finalizar();
    return 0;
}
