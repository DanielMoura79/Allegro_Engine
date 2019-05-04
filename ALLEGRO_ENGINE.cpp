#include <allegro.h>

//DECLARACOES INICIAIS-------------------------------------------------------------------------------------------------------------------------------
int sair=0; void sair_allegro() {sair=1;}; 
int timer=0; void tempo() {timer++;};
int Ctrl_FPS=60; float delay=0;
int Horas=0; int Minutos=0; int Segundos=0;

int P1_x=100; 
int P1_y=50;
void check_keys();
int key_UP_pressed=0; int key_UP_hold=0; int key_UP_released=0; int key_UP_status=0;
int key_DOWN_pressed=0; int key_DOWN_hold=0; int key_DOWN_released=0; int key_DOWN_status=0;
int key_LEFT_pressed=0; int key_LEFT_hold=0; int key_LEFT_released=0; int key_LEFT_status=0;
int key_RIGHT_pressed=0; int key_RIGHT_hold=0; int key_RIGHT_released=0; int key_RIGHT_status=0;
int key_BT1_pressed=0; int key_BT1_hold=0; int key_BT1_released=0; int key_BT1_status=0;
int key_BT2_pressed=0; int key_BT2_hold=0; int key_BT2_released=0; int key_BT2_status=0;
int key_BT3_pressed=0; int key_BT3_hold=0; int key_BT3_released=0; int key_BT3_status=0;
int key_BT4_pressed=0; int key_BT4_hold=0; int key_BT4_released=0; int key_BT4_status=0;
int key_BT5_pressed=0; int key_BT5_hold=0; int key_BT5_released=0; int key_BT5_status=0;
int key_BT6_pressed=0; int key_BT6_hold=0; int key_BT6_released=0; int key_BT6_status=0;
int key_SELECT_pressed=0; int key_SELECT_hold=0; int key_SELECT_released=0; int key_SELECT_status=0;
int key_START_pressed=0; int key_START_hold=0; int key_START_released=0; int key_START_status=0;

//INICIALIZACAO ALLEGRO------------------------------------------------------------------------------------------------------------------------------
int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse(); 
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  int ModoFullscreen=0;
  install_int_ex(tempo, BPS_TO_TIMER(60)); //60fps
  set_window_title("ALLEGRO ENGINE");
  set_close_button_callback( sair_allegro );
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  BITMAP *buffer  = create_bitmap(320,240);
  BITMAP *bufferx = create_bitmap(640,480);  
  BITMAP *ninja = load_bitmap("ninja.pcx", NULL);
  
  //SAMPLE *efeito      = load_sample("efeito.wav");
  // play_sample(efeito, 255, 128, 1000, 0);
	//MIDI *bgmusic       = load_midi("bgmusic.mid");
  //play_midi(bgmusic, 1);
  
	//LOOP DE JOGO-------------------------------------------------------------------------------------------------------------------------------------
  while (sair==0)
  {
  check_keys();
	delay=timer; Segundos=((timer/60)-Minutos*60)-Horas*3600;
	if (Segundos>=60) { Minutos++; Segundos=0; if(Minutos>=60){ Horas++; Minutos=0; };};
	
	/*TECLAS DE SISTEMA*/
	if (key[KEY_ESC]) {sair=1;}; 
	if (key[KEY_ALT] and key[KEY_F4]) {sair=1;};
	if (ModoFullscreen==0 and key[KEY_ALT] and key[KEY_ENTER]) {ModoFullscreen=1; set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);};
	if (ModoFullscreen==1 and key[KEY_ALT] and key[KEY_ENTER]) {ModoFullscreen=0; set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);};
	if ( key[KEY_F9 ] ) { Ctrl_FPS= 1; install_int_ex(tempo, BPS_TO_TIMER(1)); };
	if ( key[KEY_F10] ) { Ctrl_FPS+=-1; if (Ctrl_FPS<1 ) { Ctrl_FPS= 1; }; install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); };
	if ( key[KEY_F11] ) { Ctrl_FPS+=+1; if (Ctrl_FPS>60) { Ctrl_FPS=60; }; install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); };
	if ( key[KEY_F12] ) { Ctrl_FPS=60; install_int_ex(tempo, BPS_TO_TIMER(60)); };	
	
	/* SEU CODIGO AQUI!!! */
	if (key_RIGHT_status >0) { P1_x+=2; }; //esse codigo movimenta o player para a direita
	if (key_LEFT_status  >0) { P1_x-=2; }; //esse codigo movimenta o player para a esquerda
	if (key_UP_status    >0) { P1_y-=2; }; //esse codigo movimenta o player para cima
	if (key_DOWN_status  >0) { P1_y+=2; }; //esse codigo movimenta o player para baixo
	
	//FUNCOES DE DESENHO-------------------------------------------------------------------------------------------------------------------------------
	clear_to_color(buffer,makecol(100,149,237)); //fundo azul
	draw_sprite(buffer, ninja, P1_x, P1_y); //sprite do personagem
	stretch_blit(buffer, bufferx, 0, 0, 320, 240, 0, 0, 640, 480); //Render 2X!!!
	textprintf_right_ex(bufferx, font, 630, 5, makecol(255,255,000), -1, "ALLEGRO ENGINE BY DANIEL MOURA. - FPS[%d] [%d]", Ctrl_FPS, timer);
	circle(bufferx, P1_x*2,  P1_y*2, 1, makecol(255,255,000) );
	textprintf_centre_ex(bufferx, font, P1_x*2, (P1_y*2)-10, makecol(255,255,255), -1, "[%i,%i]", P1_x, P1_y);
	textprintf_ex(bufferx, font, 5,  20, makecol(255,255,255), -1, "[BT STATUS]");
	textprintf_ex(bufferx, font, 5,  30, makecol(255,255,255), -1, "BT UP.....[%i]", key_UP_status);
	textprintf_ex(bufferx, font, 5,  40, makecol(255,255,255), -1, "BT DOWN...[%i]", key_DOWN_status);
	textprintf_ex(bufferx, font, 5,  50, makecol(255,255,255), -1, "BT LEFT...[%i]", key_LEFT_status);
	textprintf_ex(bufferx, font, 5,  60, makecol(255,255,255), -1, "BT RIGHT..[%i]", key_RIGHT_status);
	textprintf_ex(bufferx, font, 5,  70, makecol(255,255,000), -1, "BT BT1....[%i]", key_BT1_status);
	textprintf_ex(bufferx, font, 5,  80, makecol(255,255,000), -1, "BT BT2....[%i]", key_BT2_status);
	textprintf_ex(bufferx, font, 5,  90, makecol(255,255,000), -1, "BT BT3....[%i]", key_BT3_status);
	textprintf_ex(bufferx, font, 5, 100, makecol(255,255,000), -1, "BT BT4....[%i]", key_BT4_status);
	textprintf_ex(bufferx, font, 5, 110, makecol(255,255,000), -1, "BT BT5....[%i]", key_BT5_status);
	textprintf_ex(bufferx, font, 5, 120, makecol(255,255,000), -1, "BT BT6....[%i]", key_BT6_status);
	textprintf_ex(bufferx, font, 5, 130, makecol(255,255,000), -1, "BT SELECT.[%i]", key_SELECT_status);
	textprintf_ex(bufferx, font, 5, 140, makecol(255,255,000), -1, "BT START..[%i]", key_START_status);
	//exibe relogio
	if (Horas>=10 and Minutos>=10 and Segundos>=10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[%d:%d:%d]"   , Horas, Minutos, Segundos); };
	if (Horas>=10 and Minutos>=10 and Segundos <10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[%d:%d:0%d]"  , Horas, Minutos, Segundos); };
	if (Horas>=10 and Minutos <10 and Segundos>=10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[%d:0%d:%d]"  , Horas, Minutos, Segundos); };
	if (Horas>=10 and Minutos <10 and Segundos <10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[%d:0%d:0%d]" , Horas, Minutos, Segundos); };
	if (Horas <10 and Minutos>=10 and Segundos>=10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[0%d:%d:%d]"  , Horas, Minutos, Segundos); };
	if (Horas <10 and Minutos>=10 and Segundos <10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[0%d:%d:0%d]" , Horas, Minutos, Segundos); };
	if (Horas <10 and Minutos <10 and Segundos>=10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[0%d:0%d:%d]" , Horas, Minutos, Segundos); };
	if (Horas <10 and Minutos <10 and Segundos <10) { textprintf_ex(bufferx, font, 5, 5, makecol(255,255,255), -1, "[0%d:0%d:0%d]", Horas, Minutos, Segundos); };
	draw_sprite(screen, bufferx, 0, 0);
	//show_mouse(screen);
	
	//FINALIZACOES-------------------------------------------------------------------------------------------------------------------------------------
	while(timer==delay){};	
	clear(buffer);
	clear(bufferx);
  }; 
  
	destroy_bitmap(buffer); 
	destroy_bitmap(bufferx);
	//destroy_sample(efeito); 
	//destroy_midi(bgmusic);
  return 0;
};

END_OF_MAIN();
//-FIM DO PROGRAMA-----------------------------------------------------------------------------------------------------------------------------------

//-CHECAR TECLAS-//
/*
  key_x_status==0 -> botao nao pressionado
  key_x_status==1 -> apertou o botao
  key_x_status==2 -> botao mantido apertado
  key_x_status==3 -> soltou o botao
  Onde "x" representa: UP, DOWN, LEFT, RIGHT, BT1, BT2, BT3, BT4, BT5, BT6, SELECT, START
  Configurado para: Setas direcionais, A, S, D, Z, X, C, ESPACO e ENTER
*/

void check_keys() 
{
  if (key[KEY_UP]) {
  if (key_UP_pressed==1 and key_UP_hold==0) { key_UP_hold=1; key_UP_pressed=0; };
	if (key_UP_pressed==0 and key_UP_hold==0) { key_UP_pressed=1; };};
	if (!key[KEY_UP]) {
	if (key_UP_released==1) { key_UP_released=0; key_UP_pressed=0; key_UP_hold=0; };
	if (key_UP_pressed>0 or key_UP_hold>0) { key_UP_released=1; };};
	if ( key_UP_pressed==0 and key_UP_hold==0 and key_UP_released==0 ) { key_UP_status=0; };
	if ( key_UP_pressed==1  ) { key_UP_status=1; };
	if ( key_UP_hold==1     ) { key_UP_status=2; };
	if ( key_UP_released==1 ) { key_UP_status=3; };
  if (key[KEY_DOWN]) {
	if (key_DOWN_pressed==1 and key_DOWN_hold==0) { key_DOWN_hold=1; key_DOWN_pressed=0; };
	if (key_DOWN_pressed==0 and key_DOWN_hold==0) { key_DOWN_pressed=1; };};
	if (!key[KEY_DOWN]) {
	if (key_DOWN_released==1) { key_DOWN_released=0; key_DOWN_pressed=0; key_DOWN_hold=0; };
	if (key_DOWN_pressed>0 or key_DOWN_hold>0) { key_DOWN_released=1; };};
	if ( key_DOWN_pressed==0 and key_DOWN_hold==0 and key_DOWN_released==0 ) { key_DOWN_status=0; };
	if ( key_DOWN_pressed==1  ) { key_DOWN_status=1; };
	if ( key_DOWN_hold==1     ) { key_DOWN_status=2; };
	if ( key_DOWN_released==1 ) { key_DOWN_status=3; };
  if (key[KEY_LEFT]) {
	if (key_LEFT_pressed==1 and key_LEFT_hold==0) { key_LEFT_hold=1; key_LEFT_pressed=0; };
	if (key_LEFT_pressed==0 and key_LEFT_hold==0) { key_LEFT_pressed=1; };};
	if (!key[KEY_LEFT]) {
	if (key_LEFT_released==1) { key_LEFT_released=0; key_LEFT_pressed=0; key_LEFT_hold=0; };
	if (key_LEFT_pressed>0 or key_LEFT_hold>0) { key_LEFT_released=1; };};
	if ( key_LEFT_pressed==0 and key_LEFT_hold==0 and key_LEFT_released==0 ) { key_LEFT_status=0; };
	if ( key_LEFT_pressed==1  ) { key_LEFT_status=1; };
	if ( key_LEFT_hold==1     ) { key_LEFT_status=2; };
	if ( key_LEFT_released==1 ) { key_LEFT_status=3; };
  if (key[KEY_RIGHT]) {
	if (key_RIGHT_pressed==1 and key_RIGHT_hold==0) { key_RIGHT_hold=1; key_RIGHT_pressed=0; };
	if (key_RIGHT_pressed==0 and key_RIGHT_hold==0) { key_RIGHT_pressed=1; };};
	if (!key[KEY_RIGHT]) {
	if (key_RIGHT_released==1) { key_RIGHT_released=0; key_RIGHT_pressed=0; key_RIGHT_hold=0; };
	if (key_RIGHT_pressed>0 or key_RIGHT_hold>0) { key_RIGHT_released=1; };};
	if ( key_RIGHT_pressed==0 and key_RIGHT_hold==0 and key_RIGHT_released==0 ) { key_RIGHT_status=0; };
	if ( key_RIGHT_pressed==1  ) { key_RIGHT_status=1; };
	if ( key_RIGHT_hold==1     ) { key_RIGHT_status=2; };
	if ( key_RIGHT_released==1 ) { key_RIGHT_status=3; };
  if (key[KEY_A]) {
	if (key_BT1_pressed==1 and key_BT1_hold==0) { key_BT1_hold=1; key_BT1_pressed=0; };
	if (key_BT1_pressed==0 and key_BT1_hold==0) { key_BT1_pressed=1; };};
	if (!key[KEY_A]) {
	if (key_BT1_released==1) { key_BT1_released=0; key_BT1_pressed=0; key_BT1_hold=0; };
	if (key_BT1_pressed>0 or key_BT1_hold>0) { key_BT1_released=1; };};
	if ( key_BT1_pressed==0 and key_BT1_hold==0 and key_BT1_released==0 ) { key_BT1_status=0; };
	if ( key_BT1_pressed==1  ) { key_BT1_status=1; };
	if ( key_BT1_hold==1     ) { key_BT1_status=2; };
	if ( key_BT1_released==1 ) { key_BT1_status=3; };
  if (key[KEY_S]) {
	if (key_BT2_pressed==1 and key_BT2_hold==0) { key_BT2_hold=1; key_BT2_pressed=0; };
	if (key_BT2_pressed==0 and key_BT2_hold==0) { key_BT2_pressed=1; };};
	if (!key[KEY_S]) {
	if (key_BT2_released==1) { key_BT2_released=0; key_BT2_pressed=0; key_BT2_hold=0; };
	if (key_BT2_pressed>0 or key_BT2_hold>0) { key_BT2_released=1; };};
	if ( key_BT2_pressed==0 and key_BT2_hold==0 and key_BT2_released==0 ) { key_BT2_status=0; };
	if ( key_BT2_pressed==1  ) { key_BT2_status=1; };
	if ( key_BT2_hold==1     ) { key_BT2_status=2; };
	if ( key_BT2_released==1 ) { key_BT2_status=3; };
  if (key[KEY_D]) {
	if (key_BT3_pressed==1 and key_BT3_hold==0) { key_BT3_hold=1; key_BT3_pressed=0; };
	if (key_BT3_pressed==0 and key_BT3_hold==0) { key_BT3_pressed=1; };};
	if (!key[KEY_D]) {
	if (key_BT3_released==1) { key_BT3_released=0; key_BT3_pressed=0; key_BT3_hold=0; };
	if (key_BT3_pressed>0 or key_BT3_hold>0) { key_BT3_released=1; };};
	if ( key_BT3_pressed==0 and key_BT3_hold==0 and key_BT3_released==0 ) { key_BT3_status=0; };
	if ( key_BT3_pressed==1  ) { key_BT3_status=1; };
	if ( key_BT3_hold==1     ) { key_BT3_status=2; };
	if ( key_BT3_released==1 ) { key_BT3_status=3; };
  if (key[KEY_Z]) {
	if (key_BT4_pressed==1 and key_BT4_hold==0) { key_BT4_hold=1; key_BT4_pressed=0; };
	if (key_BT4_pressed==0 and key_BT4_hold==0) { key_BT4_pressed=1; };};
	if (!key[KEY_Z]) {
	if (key_BT4_released==1) { key_BT4_released=0; key_BT4_pressed=0; key_BT4_hold=0; };
	if (key_BT4_pressed>0 or key_BT4_hold>0) { key_BT4_released=1; };};
	if ( key_BT4_pressed==0 and key_BT4_hold==0 and key_BT4_released==0 ) { key_BT4_status=0; };
	if ( key_BT4_pressed==1  ) { key_BT4_status=1; };
	if ( key_BT4_hold==1     ) { key_BT4_status=2; };
	if ( key_BT4_released==1 ) { key_BT4_status=3; };
  if (key[KEY_X]) {
	if (key_BT5_pressed==1 and key_BT5_hold==0) { key_BT5_hold=1; key_BT5_pressed=0; };
	if (key_BT5_pressed==0 and key_BT5_hold==0) { key_BT5_pressed=1; };};
	if (!key[KEY_X]) {
	if (key_BT5_released==1) { key_BT5_released=0; key_BT5_pressed=0; key_BT5_hold=0; };
	if (key_BT5_pressed>0 or key_BT5_hold>0) { key_BT5_released=1; };};
	if ( key_BT5_pressed==0 and key_BT5_hold==0 and key_BT5_released==0 ) { key_BT5_status=0; };
	if ( key_BT5_pressed==1  ) { key_BT5_status=1; };
	if ( key_BT5_hold==1     ) { key_BT5_status=2; };
	if ( key_BT5_released==1 ) { key_BT5_status=3; };	
  if (key[KEY_C]) {
	if (key_BT6_pressed==1 and key_BT6_hold==0) { key_BT6_hold=1; key_BT6_pressed=0; };
	if (key_BT6_pressed==0 and key_BT6_hold==0) { key_BT6_pressed=1; };};
	if (!key[KEY_C]) {
	if (key_BT6_released==1) { key_BT6_released=0; key_BT6_pressed=0; key_BT6_hold=0; };
	if (key_BT6_pressed>0 or key_BT6_hold>0) { key_BT6_released=1; };};
	if ( key_BT6_pressed==0 and key_BT6_hold==0 and key_BT6_released==0 ) { key_BT6_status=0; };
	if ( key_BT6_pressed==1  ) { key_BT6_status=1; };
	if ( key_BT6_hold==1     ) { key_BT6_status=2; };
	if ( key_BT6_released==1 ) { key_BT6_status=3; };
  if (key[KEY_SPACE]) {
	if (key_SELECT_pressed==1 and key_SELECT_hold==0) { key_SELECT_hold=1; key_SELECT_pressed=0; };
	if (key_SELECT_pressed==0 and key_SELECT_hold==0) { key_SELECT_pressed=1; };};
	if (!key[KEY_SPACE]) {
	if (key_SELECT_released==1) { key_SELECT_released=0; key_SELECT_pressed=0; key_SELECT_hold=0; };
	if (key_SELECT_pressed>0 or key_SELECT_hold>0) { key_SELECT_released=1; };};
	if ( key_SELECT_pressed==0 and key_SELECT_hold==0 and key_SELECT_released==0 ) { key_SELECT_status=0; };
	if ( key_SELECT_pressed==1  ) { key_SELECT_status=1; };
	if ( key_SELECT_hold==1     ) { key_SELECT_status=2; };
	if ( key_SELECT_released==1 ) { key_SELECT_status=3; };
  if (key[KEY_ENTER]) {
	if (key_START_pressed==1 and key_START_hold==0) { key_START_hold=1; key_START_pressed=0; };
	if (key_START_pressed==0 and key_START_hold==0) { key_START_pressed=1; };};
	if (!key[KEY_ENTER]) {
	if (key_START_released==1) { key_START_released=0; key_START_pressed=0; key_START_hold=0; };
	if (key_START_pressed>0 or key_START_hold>0) { key_START_released=1; };};
	if ( key_START_pressed==0 and key_START_hold==0 and key_START_released==0 ) { key_START_status=0; };
	if ( key_START_pressed==1  ) { key_START_status=1; };
	if ( key_START_hold==1     ) { key_START_status=2; };
	if ( key_START_released==1 ) { key_START_status=3; };
};

