#ifndef AL_DEFS_H
#define AL_DEFS_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdio>
typedef struct _al_defs {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_FONT *font, *logo_font, *menu_font, *title_font;
	ALLEGRO_BITMAP *ball, *ex, *wstecz, *play_now, *change, *arrow, *rewanz, *zakoncz;
	ALLEGRO_EVENT events;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_MOUSE_STATE mouseState;
	FILE *plik1, *plik2;
	bool done, klik, wybor, nick1, nick2, game, ruch, StartButton, anuluj, pomeczu, cofanie, StatyMenu, istnieje1, istnieje2, przerwano;
	int width, height;
	int moveNR, kolejka, pomkol, pom_cofnij;
	int lm1, lm2, lz1, lz2, lzAI1, lzAI2, lp1, lp2, lpAI1, lpAI2, ranga1, ranga2, wygral, lpm1, lpm2;
	int x, y, pomx, pomy, move, dx1, dx2, dy1, dy2, tab_pkt[118][118], tab_xy[308][2], pomtab_xy[308][2], punkt1, punkt2, ball_x, ball_y;
	const int sx=6*(640/16), sy=7*(640/16);
	char nazwa1[12] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',NULL }, nazwa2[12] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',NULL };
	// wykorzystywane w grze z AI:
	int pkt_na_xy[118][2], sciezka[118], sciezka2[118], droga[118], zbior[118], pom_tab_pkt[118][118];
	bool odw[118], ZnalezionoDroge, ZnalezionoDroge2, ZnalezionoDroge3, koniec, grazAI;
} al_defs;
#endif
