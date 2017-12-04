bool inicializar()
{
  // Inicializa o Allegro
  if (!al_init()){
    fprintf(stderr, "Erro ao inicializar a Allegro.\n");
    return false;
  }

  // Metodo do addon de inicializacao de imagem
  al_init_image_addon();
  janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
  if (!janela){
    fprintf(stderr, "Erro ao criar janela.\n");
    return false;
  }

  // Configura o título da janela
  al_set_window_title(janela, "Aprendendo Pre-Historia");

  // Torna apto o uso de mouse na aplicação
  if (!al_install_mouse()){
    fprintf(stderr, "Erro ao inicializar o mouse.\n");
    al_destroy_display(janela);
    return false;
  }

  // Atribui o cursor padrão do sistema na aplicação
  if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
    fprintf(stderr, "Erro ao atribuir ponteiro do mouse.\n");
    al_destroy_display(janela);
    return false;
  }

  // Torna apto o uso do teclado na aplicação
  if (!al_install_keyboard()){
    fprintf(stderr, "Erro ao inicializar o teclado.\n");
    return false;
  }

  if (!al_install_audio())
  {
    fprintf(stderr, "Erro ao inicializar áudio.\n");
    return false;
  }

  if (!al_init_acodec_addon())
  {
    fprintf(stderr, "Erro ao inicializar codecs de áudio.\n");
    return false;
  }

  if (!al_reserve_samples(1))
  {
    fprintf(stderr, "Erro ao alocar canais de áudio.\n");
    return false;
  }

  sample[0] = al_load_sample("sounds/tela-mapa.ogg");
  sample[1] = al_load_sample("sounds/fase2-caca.ogg");
  sample[2] = al_load_sample("sounds/som-de-vitoria.ogg");

  if (!sample[0] || !sample[1] || !sample[2])
  {
    fprintf(stderr, "Erro ao carregar samples.\n");
    al_destroy_display(janela);
    al_destroy_sample(sample[0]);
    al_destroy_sample(sample[1]);
    al_destroy_sample(sample[2]);
    return false;
  }

  // Cria a fila de eventos na aplicação
  fila_eventos = al_create_event_queue();
  if (!fila_eventos){
    fprintf(stderr, "Erro ao inicializar a fila de eventos.\n");
    al_destroy_display(janela);
    return false;
  }

  // Cria o timer na aplicação
  timer = al_create_timer(0.01);
  if (!timer){
    fprintf(stderr, "Erro ao criar timer.\n");
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    return false;
  }

  // Dizemos que vamos tratar os eventos vindos do mouse
  al_register_event_source(fila_eventos, al_get_mouse_event_source());
  al_register_event_source(fila_eventos, al_get_keyboard_event_source());
  al_register_event_source(fila_eventos, al_get_display_event_source(janela));
  al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
  al_set_window_position(janela, 300, 100);
  return true;
}

bool carregar_imagens()
{
  lanca.imagem[0] = al_load_bitmap("img/Lanca-Cond1.png");
  lanca.imagem[1] = al_load_bitmap("img/Lanca-Cond2.png");
  lanca.imagem_ativa = lanca.imagem[0];
  if(!lanca.imagem_ativa){
    printf("Erro ao carregar imagem da lança\n" );
  }

  // Alocando os backgrounds
  backgrounds_T.imagem[0] = al_load_bitmap("img/Entradas-Transparencia.bmp");
  backgrounds_T.imagem[1] = al_load_bitmap("img/Mapa-Transparencia.bmp");
  backgrounds_T.imagem[2] = al_load_bitmap("img/Fase-Transparencia.bmp");
  backgrounds_T.ativo[0] = backgrounds_T.imagem[0];
  backgrounds_T.ativo[1] = backgrounds_T.imagem[1];

  backgrounds.imagem[0] = al_load_bitmap("img/Tela_Inicial.png");
  backgrounds.imagem[1]  = al_load_bitmap("img/Mapa.bmp");
  backgrounds.imagem[2]  = al_load_bitmap("img/Fase.bmp");
  backgrounds.imagem[3]  = al_load_bitmap("img/you-win.bmp");
  backgrounds.imagem[4]  = al_load_bitmap("img/game-over.bmp");
  backgrounds.ativo[0] = backgrounds.imagem[0];
  //javali.pos_x = 90;
  //javali.pos_y = 90;

  javali.pos_x = 200;
  javali.pos_y = 400;

  javali.imagem_esquerda[0] = al_load_bitmap("img/javali/4.png");
  javali.imagem_esquerda[1] = al_load_bitmap("img/javali/4.png");
  javali.imagem_esquerda[2] = al_load_bitmap("img/javali/5.png");
  javali.imagem_esquerda[3] = al_load_bitmap("img/javali/5.png");
  if (!javali.imagem_esquerda[0] || !javali.imagem_esquerda[1] || !javali.imagem_esquerda[2] || !javali.imagem_esquerda[3])
  {
    printf("Erro ao carregar imagens javali esquerda\n");
    return false;
  }

  javali.imagem_direita[0] = al_load_bitmap("img/javali/1.png");
  javali.imagem_direita[1] = al_load_bitmap("img/javali/1.png");
  javali.imagem_direita[2] = al_load_bitmap("img/javali/2.png");
  javali.imagem_direita[3] = al_load_bitmap("img/javali/2.png");
  if (!javali.imagem_direita[0] || !javali.imagem_direita[1] || !javali.imagem_direita[2] || !javali.imagem_direita[3])
  {
    printf("Erro ao carregar imagens javali direita");
    return false;
  }

  javali.imagem_morto[0] = al_load_bitmap("img/javali/morto1.png");
  javali.imagem_morto[1] = al_load_bitmap("img/javali/morto1.png");
  javali.imagem_morto[2] = al_load_bitmap("img/javali/morto2.png");
  javali.imagem_morto[3] = al_load_bitmap("img/javali/morto2.png");
  if (!javali.imagem_morto[0] || !javali.imagem_morto[1] || !javali.imagem_morto[2] || !javali.imagem_morto[3])
  {
    printf("Erro ao carregar imagens javali morto");
    return false;
  }

  javali.imagem_ativa = javali.imagem_direita[0];

  // Alocamos o botão para novo jogo
  botao_novo.desativado = al_load_bitmap("img/BT_Novo_Desativado.png");
  botao_novo.ativado = al_load_bitmap("img/BT_Novo_Ativado.png");

  // Alocamos o botão para fechar a aplicação
  botao_sair.desativado = al_load_bitmap("img/BT_Sair_Desativado.png");
  botao_sair.ativado = al_load_bitmap("img/BT_Sair_Ativado.png");

  // Alocamos os sprites do personagem
  personagem.imagem_baixo[0] = al_load_bitmap("img/caveman/caveman02.png");
  personagem.imagem_baixo[1] = al_load_bitmap("img/caveman/caveman03.png");
  personagem.imagem_baixo[2] = al_load_bitmap("img/caveman/caveman02.png");
  personagem.imagem_baixo[3] = al_load_bitmap("img/caveman/caveman01.png");
  if (!personagem.imagem_baixo[0] || !personagem.imagem_baixo[1] || !personagem.imagem_baixo[2] || !personagem.imagem_baixo[3])
  {
    printf("Erro ao carregar imagens personagem baixo");
    return false;
  }

  personagem.imagem_esquerda[0] = al_load_bitmap("img/caveman/caveman05.png");
  personagem.imagem_esquerda[1] = al_load_bitmap("img/caveman/caveman04.png");
  personagem.imagem_esquerda[2] = al_load_bitmap("img/caveman/caveman06.png");
  personagem.imagem_esquerda[3] = al_load_bitmap("img/caveman/caveman05.png");
  if (!personagem.imagem_esquerda[0] || !personagem.imagem_esquerda[1] || !personagem.imagem_esquerda[2] || !personagem.imagem_esquerda[3])
  {
    printf("Erro ao carregar imagem personagem esquerda");
    return false;
  }

  personagem.imagem_direita[0] = al_load_bitmap("img/caveman/caveman08.png");
  personagem.imagem_direita[1] = al_load_bitmap("img/caveman/caveman09.png");
  personagem.imagem_direita[2] = al_load_bitmap("img/caveman/caveman07.png");
  personagem.imagem_direita[3] = al_load_bitmap("img/caveman/caveman08.png");
  if (!personagem.imagem_direita[0] || !personagem.imagem_direita[1] || !personagem.imagem_direita[2] || !personagem.imagem_direita[3])
  {
    printf("Erro ao carregar imagem personagem direita");
    return false;
  }

  personagem.imagem_cima[0] = al_load_bitmap("img/caveman/caveman11.png");
  personagem.imagem_cima[1] = al_load_bitmap("img/caveman/caveman12.png");
  personagem.imagem_cima[2] = al_load_bitmap("img/caveman/caveman10.png");
  personagem.imagem_cima[3] = al_load_bitmap("img/caveman/caveman11.png");
  if (!personagem.imagem_cima[0] || !personagem.imagem_cima[1] || !personagem.imagem_cima[2] || !personagem.imagem_cima[3])
  {
    printf("Erro ao carregar imagem personagem cima");
    return false;
  }

  personagem.imagem_ativa = personagem.imagem_baixo[3];

  if (!botao_novo.desativado || !botao_novo.ativado)
  {
    fprintf(stderr, "Erro ao criar botão novo jogo.\n");
    al_destroy_display(janela);
    return false;
  }
  if (!botao_sair.desativado || !botao_sair.ativado)
  {
    fprintf(stderr, "Erro ao criar botão de saída.\n");
    al_destroy_display(janela);
    return false;
  }

  return true;
}

void finalizar()
{
  // Desaloca os recursos utilizados na aplicação
  al_destroy_bitmap(botao_novo.ativado);
  al_destroy_bitmap(botao_novo.desativado);
  al_destroy_bitmap(botao_sair.ativado);
  al_destroy_bitmap(botao_sair.desativado);

  al_destroy_bitmap(backgrounds.imagem[0]);
  al_destroy_bitmap(backgrounds.imagem[1]);
  al_destroy_bitmap(backgrounds.imagem[2]);
  al_destroy_bitmap(backgrounds.imagem[3]);
  al_destroy_bitmap(backgrounds.imagem[4]);

  al_destroy_bitmap(backgrounds_T.imagem[0]);
  al_destroy_bitmap(backgrounds_T.imagem[1]);
  al_destroy_bitmap(backgrounds_T.imagem[2]);

  al_destroy_bitmap(personagem.imagem_direita[0]);
  al_destroy_bitmap(personagem.imagem_direita[1]);
  al_destroy_bitmap(personagem.imagem_direita[2]);
  al_destroy_bitmap(personagem.imagem_direita[3]);
  al_destroy_bitmap(personagem.imagem_esquerda[0]);
  al_destroy_bitmap(personagem.imagem_esquerda[1]);
  al_destroy_bitmap(personagem.imagem_esquerda[2]);
  al_destroy_bitmap(personagem.imagem_esquerda[3]);
  al_destroy_bitmap(personagem.imagem_baixo[0]);
  al_destroy_bitmap(personagem.imagem_baixo[1]);
  al_destroy_bitmap(personagem.imagem_baixo[2]);
  al_destroy_bitmap(personagem.imagem_baixo[3]);
  al_destroy_bitmap(personagem.imagem_cima[0]);
  al_destroy_bitmap(personagem.imagem_cima[1]);
  al_destroy_bitmap(personagem.imagem_cima[2]);
  al_destroy_bitmap(personagem.imagem_cima[3]);

  al_destroy_bitmap(javali.imagem_morto[0]);
  al_destroy_bitmap(javali.imagem_morto[1]);
  al_destroy_bitmap(javali.imagem_morto[2]);
  al_destroy_bitmap(javali.imagem_morto[3]);
  al_destroy_bitmap(javali.imagem_direita[0]);
  al_destroy_bitmap(javali.imagem_direita[1]);
  al_destroy_bitmap(javali.imagem_direita[2]);
  al_destroy_bitmap(javali.imagem_direita[3]);
  al_destroy_bitmap(javali.imagem_esquerda[0]);
  al_destroy_bitmap(javali.imagem_esquerda[1]);
  al_destroy_bitmap(javali.imagem_esquerda[2]);
  al_destroy_bitmap(javali.imagem_esquerda[3]);

  al_destroy_bitmap(lanca.imagem[0]);
  al_destroy_bitmap(lanca.imagem[1]);

  al_destroy_timer(timer);
  al_destroy_sample(sample[0]);
  al_destroy_sample(sample[1]);
  al_destroy_sample(sample[2]);
  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);
}

struct objeto verifica_movimentacao(struct objeto personagem)
{
  if (personagem.frame_ativo == 3){
    personagem.frame_ativo = 0;
  } else{
    personagem.frame_ativo++;
  }
  switch (personagem.orientacao) {
    case 'D':
      cor = al_get_pixel(backgrounds_T.ativo[1], personagem.pos_x + 1, personagem.pos_y);
      al_unmap_rgb(cor, &r, &g, &b);

      if (r < 100 || g < 100 || b < 100){
        personagem.pos_x = personagem.pos_x + 1;
        personagem.imagem_ativa = personagem.imagem_direita[personagem.frame_ativo];
      } else {
        personagem.pos_x = personagem.pos_x - 1;
        personagem.imagem_ativa = personagem.imagem_direita[personagem.frame_ativo];
      }
      break;
    case 'E':
      cor = al_get_pixel(backgrounds_T.ativo[1], personagem.pos_x - 1, personagem.pos_y);
      al_unmap_rgb(cor, &r, &g, &b);

      if (r < 100 || g < 100 || b < 100){
        personagem.pos_x = personagem.pos_x - 1;
        personagem.imagem_ativa = personagem.imagem_esquerda[personagem.frame_ativo];
      } else {
        personagem.pos_x = personagem.pos_x + 1;
        personagem.imagem_ativa = personagem.imagem_esquerda[personagem.frame_ativo];
      }
      break;
    case 'C':
      cor = al_get_pixel(backgrounds_T.ativo[1], personagem.pos_x, personagem.pos_y - 1);
      al_unmap_rgb(cor, &r, &g, &b);

      if (r < 100 || g < 100 || b < 100){
        personagem.pos_y = personagem.pos_y - 1;
        personagem.imagem_ativa = personagem.imagem_cima[personagem.frame_ativo];
      } else {
        personagem.pos_y = personagem.pos_y + 1;
        personagem.imagem_ativa = personagem.imagem_cima[personagem.frame_ativo];
      }
      break;
    case 'B':
      cor = al_get_pixel(backgrounds_T.ativo[1], personagem.pos_x, personagem.pos_y + 1);
      al_unmap_rgb(cor, &r, &g, &b);

      if (r < 100 || g < 100 || b < 100){
        personagem.pos_y = personagem.pos_y + 1;
        personagem.imagem_ativa = personagem.imagem_baixo[personagem.frame_ativo];
      } else {
        personagem.pos_y = personagem.pos_y - 1;
        personagem.imagem_ativa = personagem.imagem_baixo[personagem.frame_ativo];
      }
      break;
  }
  return personagem;
}

int verifica_fim(){
  cor = al_get_pixel(backgrounds_T.ativo[0], personagem.pos_x-5, personagem.pos_y-5);
  al_unmap_rgb(cor, &r, &g, &b);
  if (r < 10 && g < 10 && b < 10){
    return 0;
  }
  return 1;
}

void cria_lanca(objeto_voador *lanca, ALLEGRO_EVENT *evento){

  float A, B, C;
  lanca->pos_x = personagem.pos_x;
  lanca->pos_y = personagem.pos_y;
  lanca->ativo = 1;
  float todo = abs(evento->mouse.x - personagem.pos_x) + abs(evento->mouse.y - personagem.pos_y);
  lanca->pos_incy = (evento->mouse.y - personagem.pos_y) / todo;
  lanca->pos_incx = (evento->mouse.x - personagem.pos_x) / todo;

  if (evento->mouse.y < personagem.pos_y){
    A = personagem.pos_x - LARGURA_TELA;
    B = sqrt((pow(evento->mouse.x - personagem.pos_x,2))+(pow(evento->mouse.y - personagem.pos_y,2)));
    C = sqrt((pow((A - (evento->mouse.x - personagem.pos_x)),2))+(pow(evento->mouse.y - personagem.pos_y,2)));
    lanca->imagem_ativa = lanca->imagem[0];
  } else {
    A = personagem.pos_x - LARGURA_TELA;
    B = sqrt((pow(personagem.pos_x - evento->mouse.x,2))+(pow(personagem.pos_y - evento->mouse.y,2)));
    C = sqrt((pow((A - (personagem.pos_x - evento->mouse.x)),2))+(pow(personagem.pos_y - evento->mouse.y,2)));
    lanca->imagem_ativa = lanca->imagem[1];
  }
  lanca->angulo = acos(-(pow(C,2)-(pow(A,2) + pow(B,2)))/(-2*A*B));

  return;
}

void move_lanca(objeto_voador *lanca, int *morto){
  if (lanca->pos_y >= ALTURA_TELA || lanca->pos_x >= LARGURA_TELA || lanca->pos_y < 0 || lanca->pos_x < 0){
    lanca->ativo = 0;
    return;
  }

  lanca->pos_x += (lanca->pos_incx)*10;
  lanca->pos_y += (lanca->pos_incy)*10;

  verifica_colisao_lanca(lanca, morto);
}

void verifica_colisao_lanca(objeto_voador *lanca, int *morto){
  int pos_xfim = (javali.pos_x) + al_get_bitmap_width(javali.imagem_ativa);
  int pos_yfim = (javali.pos_y) + al_get_bitmap_height(javali.imagem_ativa);

  if (lanca->pos_x >= javali.pos_x && lanca->pos_x <= pos_xfim){
    if(lanca->pos_y >= javali.pos_y && lanca->pos_y <= pos_yfim ){
      lanca->ativo = 0;
      *morto = 1;
      clock1 = 0;
      javali.frame_ativo = 0;
    }
  }
  return;
}

void verifica_colisao_javali(int *morto){
  int pos_xfim = (javali.pos_x) + al_get_bitmap_width(javali.imagem_ativa);
  int pos_yfim = (javali.pos_y) + al_get_bitmap_height(javali.imagem_ativa);

  if (personagem.pos_x >= javali.pos_x && personagem.pos_x <= pos_xfim){
    if(personagem.pos_y >= javali.pos_y && personagem.pos_y <= pos_yfim){
      *morto = 1;
      al_stop_sample(&ret_id);
    }
  }
  return;
}

int tela_inicial(int loop)
{
  int no_novo = 0, no_ajuda = 0, no_sair = 0, novo_jogo = 0;

  backgrounds.ativo[0] = backgrounds.imagem[0];
  al_start_timer(timer);

  while (!loop){
    // Verificamos se há eventos na fila
    while (!al_is_event_queue_empty(fila_eventos))
    {
      al_wait_for_event(fila_eventos, &evento);

      // Se o evento foi fechar o jogo
      if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      {
        return -1;
      }

      // Tratamento após clicar no botão novo jogo
      if(novo_jogo == 1)
      {
        novo_jogo = 0;
        return 0;
      }

      // Se o evento foi movimentar o mouse
      if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
      {
        if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_novo.ativado) - 35 && evento.mouse.x <= LARGURA_TELA - 35 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_novo.ativado) - 220 && evento.mouse.y <= ALTURA_TELA - 220){
          no_novo = 1;
          no_sair = 0;

        } else if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair.ativado) - 35 && evento.mouse.x <= LARGURA_TELA - 35 && evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair.ativado) - 100 && evento.mouse.y <= ALTURA_TELA - 100)
        {
          no_novo = 0;
          no_sair = 1;
        }
      }
      // Se o evento foi um clique do mouse
      else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
      {
        //click no botão sair
        if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair.ativado) - 35 &&
            evento.mouse.x <= LARGURA_TELA - 35 &&
            evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair.ativado) - 100 &&
            evento.mouse.y <= ALTURA_TELA - 100)
        {
            return -1;
            loop = 1;
        }

        //Click no botão novo
        if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_novo_exibir) - 35 &&
            evento.mouse.x <= LARGURA_TELA - 35 &&
            evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_novo_exibir) - 220 &&
            evento.mouse.y <= ALTURA_TELA - 220)
        {
            novo_jogo = 1;
            al_play_sample(sample[0], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ret_id);
        }
      }
    }

    // Desenha o background na tela
    al_draw_bitmap(backgrounds.ativo[0], 0, 0, 0);

    // aloca os botões ativos
    if (no_novo == 1 )
    {
      botao_novo_exibir = botao_novo.ativado;
    } else
    {
      botao_novo_exibir = botao_novo.desativado;
    }

    if (no_sair == 1 )
    {
      botao_sair_exibir = botao_sair.ativado;
    } else
    {
      botao_sair_exibir = botao_sair.desativado;
    }

    //Desenha BT_Novo_Jogo
    al_draw_bitmap(botao_novo_exibir, LARGURA_TELA - al_get_bitmap_width(botao_novo_exibir) - 35,
    ALTURA_TELA - al_get_bitmap_height(botao_novo_exibir) -220, 0);

    //Desenha BT_Sair
    al_draw_bitmap(botao_sair_exibir, LARGURA_TELA - al_get_bitmap_width(botao_sair_exibir) - 35,
    ALTURA_TELA - al_get_bitmap_height(botao_sair_exibir) - 100, 0);

    // Atualiza a tela
    al_flip_display();
  }
  return 0;
}

int fase_1()
{
  //int frame_ativo = 0;
  bool entrou = false;

	personagem.pos_x = 106, personagem.pos_y = 497;
  personagem.orientacao = 'B';
  int loop = 0;

  // aloca o background da 1ª fase
  backgrounds.ativo[0] = backgrounds.imagem[1];
  backgrounds_T.ativo[1] = backgrounds_T.imagem[1];

  al_start_timer(timer);
  while (!loop){
    // Verificamos se há eventos na fila
    while (!al_is_event_queue_empty(fila_eventos)){
      al_wait_for_event(fila_eventos, &evento);
      // Se o evento foi fechar o jogo
      if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return -1;
      }
      if(evento.type == ALLEGRO_EVENT_KEY_UP)
      {
        entrou = true;
      }
      if (entrou == true && personagem.frame_ativo == 0 && evento.type != ALLEGRO_EVENT_KEY_DOWN)
      {
        tecla_pressionada = 0;
        entrou = false;
      }
      if(evento.type == ALLEGRO_EVENT_TIMER && tecla_pressionada == 1)
      {
        personagem = verifica_movimentacao(personagem);
      }
      if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(evento.keyboard.keycode){
          case ALLEGRO_KEY_UP:
            tecla_pressionada = 1;
            personagem.orientacao = 'C';
            break;
          case ALLEGRO_KEY_DOWN:
            tecla_pressionada = 1;
            personagem.orientacao = 'B';
            break;
          case ALLEGRO_KEY_LEFT:
            tecla_pressionada = 1;
            personagem.orientacao = 'E';
            break;
          case ALLEGRO_KEY_RIGHT:
            tecla_pressionada = 1;
            personagem.orientacao = 'D';
            break;
        }
      }
      if(evento.type == ALLEGRO_EVENT_TIMER){
        if(!verifica_fim()){
          al_stop_sample(&ret_id);

          al_play_sample(sample[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ret_id);
          loop = 1;
        }
      }
    }

    //Desenha background
    al_draw_bitmap(backgrounds.ativo[0], 0,0,0);
    //Desenha Personagem quando pressionado o botão novo jogo
    al_draw_bitmap(personagem.imagem_ativa, personagem.pos_x, personagem.pos_y, 0);
    // Atualiza a tela
    al_flip_display();
  }
  loop = 0;
  return 0;
}

int fase_2(){
  bool entrou = false;

	personagem.pos_x = 106, personagem.pos_y = 497;
  personagem.orientacao = 'B';

  int loop = 0;
  int lanca_ativa = 0;
  int pos_dir = 1;
  int pos_esq = 0;
  int morto = 0;
  int morto_p = 0;
  int foi = 0;

  backgrounds.ativo[0] = backgrounds.imagem[2];
  backgrounds_T.ativo[1] = backgrounds_T.imagem[2];

  al_start_timer(timer);
  while (!loop){
    // Verificamos se há eventos na fila
    while (!al_is_event_queue_empty(fila_eventos)){
      al_wait_for_event(fila_eventos, &evento);
      // Se o evento foi fechar o jogo
      if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return -1;
        loop = 1;
      }
      if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && !(lanca.ativo)){
        cria_lanca(&lanca, &evento);
        lanca_ativa = 1;
      }else{
        move_lanca(&lanca, &morto);
      }
      if(evento.type == ALLEGRO_EVENT_TIMER){
        clock1++;
      }
      if(evento.type == ALLEGRO_EVENT_TIMER && morto_p != 1){
        verifica_colisao_javali(&morto_p);
      }
      if(evento.type == ALLEGRO_EVENT_TIMER && !lanca_ativa){
        move_lanca(&lanca, &morto);
      }
      if(evento.type == ALLEGRO_EVENT_KEY_UP)
      {
        entrou = true;
      }
      if (entrou == true && personagem.frame_ativo == 0 && evento.type != ALLEGRO_EVENT_KEY_DOWN)
      {
        tecla_pressionada = 0;
        entrou = false;
      }
      if(evento.type == ALLEGRO_EVENT_TIMER && tecla_pressionada == 1)
      {
        personagem = verifica_movimentacao(personagem);
      }
      if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(evento.keyboard.keycode){
            case ALLEGRO_KEY_UP:
              tecla_pressionada = 1;
              personagem.orientacao = 'C';
              break;
            case ALLEGRO_KEY_DOWN:
              tecla_pressionada = 1;
              personagem.orientacao = 'B';
              break;
            case ALLEGRO_KEY_LEFT:
              tecla_pressionada = 1;
              personagem.orientacao = 'E';
              break;
            case ALLEGRO_KEY_RIGHT:
              tecla_pressionada = 1;
              personagem.orientacao = 'D';
              break;
        }
      }
    }
    al_draw_bitmap(backgrounds.ativo[0], 0,0,0);
    al_draw_bitmap(personagem.imagem_ativa, personagem.pos_x, personagem.pos_y, 0);

    if (morto != 1 || (morto == 1 && javali.frame_ativo < 3))
    {
      if (javali.frame_ativo == 3){
        javali.frame_ativo = 0;
      } else{
        javali.frame_ativo++;
      }
    }

    if(morto != 1 && morto_p != 1){
      if (javali.pos_x <= 800 && pos_dir == 1){
        javali.imagem_ativa = javali.imagem_direita[javali.frame_ativo];

        if (javali.pos_x >= 790){
          javali.imagem_ativa = javali.imagem_esquerda[javali.frame_ativo];
          pos_dir = 0;
          pos_esq = 1;
        }
        javali.pos_x += 10;
      }else if (javali.pos_x >= 90 && pos_esq == 1){
        javali.imagem_ativa = javali.imagem_esquerda[javali.frame_ativo];

        if (javali.pos_x == 90){
          javali.imagem_ativa = javali.imagem_direita[javali.frame_ativo];
          pos_dir = 1;
          pos_esq = 0;
        }
        javali.pos_x -= 10;
      }
    } else if (morto == 1) {
      javali.imagem_ativa = javali.imagem_morto[javali.frame_ativo];
      al_draw_bitmap(javali.imagem_ativa, javali.pos_x, javali.pos_y, 0);
      if (morto_p == 1 && foi != 1){
        al_stop_sample(&ret_id);

        al_play_sample(sample[2], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, ret_id);
        clock1 = 0;
        foi = 1;
      }
      if (clock1%500 == 0 && morto_p == 1){
        you_win();
        return -1;
      }
    } else if (morto_p == 1) {
      game_over();
      return -1;
    }

    al_draw_bitmap(javali.imagem_ativa, javali.pos_x, javali.pos_y, 0);

    if (lanca.ativo == 1){
      al_draw_rotated_bitmap(lanca.imagem_ativa, 0, 0, lanca.pos_x, lanca.pos_y, lanca.angulo, 0);
    }
    // Atualiza a tela
    al_flip_display();
  }
  return;
}

void you_win (){
  clock1 = 0;
  int loop = 0;
  // aloca o background da tela inicial
  backgrounds.ativo[0] = backgrounds.imagem[3];
  al_start_timer(timer);
  while (!loop){
    // Verificamos se há eventos na fila
    while (!al_is_event_queue_empty(fila_eventos)){
      al_wait_for_event(fila_eventos, &evento);
      // Se o evento foi fechar o jogo
      if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return;
      }
      if(evento.type == ALLEGRO_EVENT_TIMER){
        clock1++;
      }
    }

    if (clock1%500 == 0){
      clock1 = 0;
      return;
    }

    al_draw_bitmap(backgrounds.ativo[0], 0,0,0);
    al_flip_display();
  }
}

void game_over (){
  clock1 = 0;
  int loop = 0;
  // aloca o background da tela inicial
  backgrounds.ativo[0] = backgrounds.imagem[4];
  al_start_timer(timer);
  while (!loop){
    // Verificamos se há eventos na fila
    while (!al_is_event_queue_empty(fila_eventos)){
      al_wait_for_event(fila_eventos, &evento);
      // Se o evento foi fechar o jogo
      if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return;
      }
      if(evento.type == ALLEGRO_EVENT_TIMER){
        clock1++;
      }
    }

    if (clock1%500 == 0){
      return;
    }

    al_draw_bitmap(backgrounds.ativo[0], 0,0,0);
    al_flip_display();
  }
}
