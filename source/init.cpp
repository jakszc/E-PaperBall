#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include "al_defs.h"
#include <iostream>

bool init_allegro(al_defs* al)
{
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, "allegro init nie dziala", NULL, NULL, NULL);
		return 0;
	}
	al->display = al_create_display(640, 640);
	al_set_window_position(al->display, 200, 100);
	al_set_window_title(al->display, "Electronic Paper Ball");
	if (!al->display)
	{
		al_show_native_message_box(NULL, NULL, NULL, "display nie dziala", NULL, NULL);
		return 0;
	}
	if (!al_install_keyboard()) 
	{
		al_show_native_message_box(NULL, NULL, NULL, "keyboard nie dziala", NULL, NULL);
		return 0;
	}
	if (!al_install_mouse()) 
	{
		al_show_native_message_box(NULL, NULL, NULL, "mouse nie dziala", NULL, NULL);
		return 0;
	}
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		al_show_native_message_box(NULL, NULL, NULL, "ttf addon nie dziala", NULL, NULL);
		return 0;
	}
	if (!al_init_primitives_addon()) 
	{
		al_show_native_message_box(NULL, NULL, NULL, "primitives addon nie dziala", NULL, NULL);
		return 0;
	}
	if (!al_init_image_addon())
	{
		al_show_native_message_box(NULL, NULL, NULL, "image addon nie dziala", NULL, NULL);
		return 0;
	}
	al->font = al_load_font("fonty/arial.ttf", 18, NULL);
	al->logo_font = al_load_font("fonty/SFSportsNight.ttf", 60, NULL);
	al->menu_font = al_load_font("fonty/octin stencil rg.ttf", 36, NULL);
	al->title_font = al_load_font("fonty/arial.ttf", 36, NULL);
	al->ball = al_load_bitmap("fonty/soccer_ball_converted.png");
	al->ex = al_load_bitmap("fonty/i3.png");
	al->change = al_load_bitmap("fonty/zmien_usun.bmp");
	al->wstecz = al_load_bitmap("fonty/wstecz.png");
	al->play_now = al_load_bitmap("fonty/play.bmp");
	al->arrow = al_load_bitmap("fonty/arrow.png");
	al->rewanz = al_load_bitmap("fonty/rewanz.bmp");
	al->zakoncz = al_load_bitmap("fonty/zakoncz.bmp");
	al->event_queue = al_create_event_queue();
	al_register_event_source(al->event_queue, al_get_keyboard_event_source());
	al_register_event_source(al->event_queue, al_get_mouse_event_source());
	al_register_event_source(al->event_queue, al_get_display_event_source(al->display));

	al->done = false;
	al->wybor = false;
	al->klik = false;
	al->nick1 = false;
	al->nick2 = false;
	al->StartButton = false;
	al->game = false;
	al->ruch = false;
	al->anuluj = false;
	al->pomeczu = false;
	al->cofanie = false;
	al->StatyMenu = false;
	al->przerwano = false;
	al->width = 640;
	al->height = 640;
	al->move = 40;
	al->x = al->sx;
	al->y = al->sy;
	al->pomx = al->x;
	al->pomy = al->y;
	al->punkt1 = 59;
	al->punkt2 = al->punkt1;
	al->ball_x = al->sx;
	al->ball_y = al->sy;
	al->moveNR = 0;
	al->kolejka = 1;
	al->pomkol = 1;
	al->pom_cofnij = 0;
	al->wygral = 0;
	int i = 0, j = 0;
	for (i = 1;i < 118;i++)
	{
		for (j = 1;j < 118;j++)
		{
			al->tab_pkt[i][j] = 0;
			if (i == j) al->tab_pkt[i][j] = 1;
			if (j % 9 == 0 && j>17 && j < 100) al->tab_pkt[j][j + 9] = 1 ;
			if ((j - 1) % 9 == 0 && j > 9 && j < 92) al->tab_pkt[j][j + 9] = 1;
		}
	}
	al->tab_pkt[4][5] = 1, al->tab_pkt[5][4] = 1, al->tab_pkt[5][6] = 1, al->tab_pkt[6][5] = 1, al->tab_pkt[13][4] = 1, al->tab_pkt[4][13] = 1, al->tab_pkt[15][6] = 1, al->tab_pkt[6][15] = 1, al->tab_pkt[12][4] = 1, al->tab_pkt[16][6] = 1;
	al->tab_pkt[112][113] = 1, al->tab_pkt[113][112] = 1, al->tab_pkt[114][113] = 1, al->tab_pkt[113][114] = 1, al->tab_pkt[112][103] = 1, al->tab_pkt[103][112] = 1, al->tab_pkt[114][105] = 1, al->tab_pkt[105][114] = 1, al->tab_pkt[102][112] = 1, al->tab_pkt[106][114] = 1;
	al->tab_pkt[10][11] = 1, al->tab_pkt[11][12] = 1, al->tab_pkt[12][13] = 1, al->tab_pkt[15][16] = 1, al->tab_pkt[16][17] = 1, al->tab_pkt[17][18] = 1;
	al->tab_pkt[100][101] = 1, al->tab_pkt[101][102] = 1, al->tab_pkt[102][103] = 1, al->tab_pkt[105][106] = 1, al->tab_pkt[106][107] = 1, al->tab_pkt[107][108] = 1;
	al->tab_xy[0][0] = al->sx;
	al->tab_xy[0][1] = al->sy;
	al->pomtab_xy[0][0] = al->tab_xy[0][0];
	al->pomtab_xy[0][1] = al->tab_xy[0][1];
	for (i = 1;i < 308;i++)
	{
		for (j = 0;j < 2;j++)
		{
			al->tab_xy[i][j] = 0;
			al->pomtab_xy[i][j] = 0;
		}
	}
	/////////// do AI
	int wsx = 80, wsy = 0, wsk=1;
	for (i = 0;i < 13;i++)
	{
		wsx = 40;
		wsy += 40;
		for (j = 0;j < 9;j++)
		{
			wsx += 40;
			al->pkt_na_xy[wsk][0] = wsx;
			al->pkt_na_xy[wsk][1] = wsy;
			wsk++;
		}
	}
	for (i = 0;i < 118;i++)
	{
		al->odw[i] = false;
		al->sciezka[i] = 0;
		al->droga[i] = 0;
		al->zbior[i] = 0;
		for (j = 0;j < 118;j++) al->pom_tab_pkt[i][j] = 0;
	}
	al->ZnalezionoDroge = false;
	al->ZnalezionoDroge2 = false;
	al->ZnalezionoDroge3 = false;
	al->grazAI = false;

	return 1;
}

void destroy_all(al_defs* al)
{
	al_destroy_font(al->font);
	al_destroy_font(al->title_font);
	al_destroy_font(al->logo_font);
	al_destroy_font(al->menu_font);
	al_destroy_bitmap(al->ball);
	al_destroy_bitmap(al->ex);
	al_destroy_bitmap(al->wstecz);
	al_destroy_bitmap(al->play_now);
	al_destroy_bitmap(al->change);
	al_destroy_bitmap(al->arrow);
	al_destroy_bitmap(al->rewanz);
	al_destroy_bitmap(al->zakoncz);
	al_destroy_display(al->display);
	al_destroy_event_queue(al->event_queue);
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
}