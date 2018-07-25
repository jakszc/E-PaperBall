#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include "al_defs.h"
#include "start.h"
#include "init.h"
#include "MvsM.h"
#include "MvsAI.h"
#include "rules_and_stats.h"
#include <cstdio>
#include <iostream>

void menuMvsAI(al_defs* al)
{
	al->StartButton = false;
	al->game = false;
	al->koniec = false;
	al->przerwano = false;
	al->ZnalezionoDroge = false;
	menu_wpr_nick_AI(al);
	wpr_nick_AI(al);
	menu_wpr_nick_AI(al);
	al->nick2 = true;
	al->nazwa2[0] = 'k'; al->nazwa2[1] = 'o'; al->nazwa2[2] = 'm';al->nazwa2[3] = 'p';al->nazwa2[4] = 'u';al->nazwa2[5] = 't';al->nazwa2[6] = 'e';al->nazwa2[7] = 'r';al->nazwa2[8] = NULL;

	al_draw_bitmap(al->play_now, 500, 575, NULL);
	al_flip_display();

	int x, y, f = 0, pom = 0;;
	while (!al->StartButton)
	{
		if (al->anuluj) break;
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				int i = 0;
				if (x >= 500 && x <= 610 && y >= 575 && y <= 625)
				{
					//sprawdzenie czy
					pom = 0, f = -1;
					do
					{
						f++;
						if (al->nazwa1[f] == al->nazwa2[f]) pom++;
					} while (al->nazwa1[f] != NULL);
					if ((pom - 1) == f) al_show_native_message_box(al->display, "Blad", "Blad", "Nazwa ''komputer'' jest zastrzezona!", NULL, NULL);
					//nazwy gracza rozna od "komputer"
					else
					{
						begin_game_AI(al);
						al->StartButton = true;
					}
				}
				else if (x >= 270 && x <= 355 && y >= 248 && y <= 270)
				{
					for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
					menu_wpr_nick_AI(al);
					al->nick1 = false;
					wpr_nick_AI(al);
					al_draw_bitmap(al->play_now, 500, 575, NULL);
					al_flip_display();
				}
				else if (x > 30 && x < 115 && y>575 && y < 610)
				{
					al->anuluj = true;
					zerujzmienne(al);
					break;
				}
			}
		}
	}
	main_menu(al);
}

void menu_wpr_nick_AI(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	al_draw_text(al->title_font, al_map_rgb(0, 0, 0), 100, 30, NULL, "Wprowadz nazwe gracza:");
	al_draw_text(al->title_font, al_map_rgb(0, 0, 0), 100, 30, NULL, "Wprowadz nazwe gracza:");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 80, NULL, "-dozwolone znaki: [a-z] oraz [0-9]");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 100, NULL, "-max 10 znakow");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 120, NULL, "-zastrzezona nazwa: ''komputer''");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 140, NULL, "-po wprowadzeniu wcisnij enter");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 160, NULL, "-dane zapisywane sa w pliku,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 180, NULL, " jezeli plik o podanej nazwie istnieje, odczyta je,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 200, NULL, " jezeli nie, to utworzy nowy plik");	
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 230, ALLEGRO_ALIGN_LEFT, "Nazwa gracza:");
	al_draw_filled_rectangle(50, 250, 250, 270, al_map_rgb(255, 255, 255));
	al_draw_bitmap(al->wstecz, 30, 575, NULL);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 63, 250, NULL, al->nazwa1);
	al_draw_bitmap(al->change, 270, 248, NULL);

	al_flip_display();
}

void wpr_nick_AI(al_defs* al)
{
	al->anuluj = false;
	int x, y, pomx = 0, pomy = 0, pomchar = 0, i = 0;
	while (!al->nick1)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				if (x >= 50 && x <= 250 && y >= 250 && y <= 270)
				{
					al_draw_line(50, 260, 60, 260, al_map_rgb(0, 0, 0), 1);
					al_draw_line(60, 260, 55, 255, al_map_rgb(0, 0, 0), 1);
					al_draw_line(60, 260, 55, 265, al_map_rgb(0, 0, 0), 1);
					al_flip_display();
					pomx = 63;	pomy = 250, pomchar = 0;
					while (!al->nick1)
					{
						al_wait_for_event(al->event_queue, &al->events);
						if (al->events.type == ALLEGRO_EVENT_KEY_DOWN)
						{
							if (pomchar < 10)
							{
								switch (al->events.keyboard.keycode)
								{
								case ALLEGRO_KEY_Q:
									al->nazwa1[pomchar] = 'q';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_W:
									al->nazwa1[pomchar] = 'w';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_E:
									al->nazwa1[pomchar] = 'e';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_R:
									al->nazwa1[pomchar] = 'r';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_T:
									al->nazwa1[pomchar] = 't';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_Y:
									al->nazwa1[pomchar] = 'y';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_U:
									al->nazwa1[pomchar] = 'u';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_I:
									al->nazwa1[pomchar] = 'i';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_O:
									al->nazwa1[pomchar] = 'o';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_P:
									al->nazwa1[pomchar] = 'p';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_A:
									al->nazwa1[pomchar] = 'a';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_S:
									al->nazwa1[pomchar] = 's';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_D:
									al->nazwa1[pomchar] = 'd';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_F:
									al->nazwa1[pomchar] = 'f';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_G:
									al->nazwa1[pomchar] = 'g';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_H:
									al->nazwa1[pomchar] = 'h';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_J:
									al->nazwa1[pomchar] = 'j';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_K:
									al->nazwa1[pomchar] = 'k';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_L:
									al->nazwa1[pomchar] = 'l';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_Z:
									al->nazwa1[pomchar] = 'z';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_X:
									al->nazwa1[pomchar] = 'x';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_C:
									al->nazwa1[pomchar] = 'c';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_V:
									al->nazwa1[pomchar] = 'v';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_B:
									al->nazwa1[pomchar] = 'b';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_N:
									al->nazwa1[pomchar] = 'n';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_M:
									al->nazwa1[pomchar] = 'm';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_0:
									al->nazwa1[pomchar] = '0';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_1:
									al->nazwa1[pomchar] = '1';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_2:
									al->nazwa1[pomchar] = '2';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_3:
									al->nazwa1[pomchar] = '3';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_4:
									al->nazwa1[pomchar] = '4';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_5:
									al->nazwa1[pomchar] = '5';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_6:
									al->nazwa1[pomchar] = '6';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_7:
									al->nazwa1[pomchar] = '7';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_8:
									al->nazwa1[pomchar] = '8';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_9:
									al->nazwa1[pomchar] = '9';	pomchar++;	menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_BACKSPACE:
									if (pomchar > 0) al->nazwa1[--pomchar] = ' '; menu_wpr_nick_AI(al); break;
								case ALLEGRO_KEY_ENTER:
									al->nazwa1[pomchar] = NULL; pomchar++; al->nick1 = true; menu_wpr_nick_AI(al); break;
								}
							}
							else if (pomchar == 10)
							{
								if (al->events.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) al->nazwa1[--pomchar] = ' ';
								else if (al->events.keyboard.keycode == ALLEGRO_KEY_ENTER)
								{
									al->nazwa1[pomchar] = NULL;
									al->nick1 = true;
								}
								menu_wpr_nick_AI(al);
							}

						}
					}
				}
				else if (x >= 270 && x <= 355 && y >= 248 && y <= 270)
				{
					for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
					al->nick1 = false;
					menu_wpr_nick_AI(al);
				}
				else if (x > 30 && x < 115 && y>575 && y < 610)
				{
					al->anuluj = true;
					zerujzmienne(al);
					break;
				}
				else menu_wpr_nick_AI(al);

			}
		}
	}
}

bool sprawdzRuch_AI(int pkt1, int pkt2, al_defs* al)
{
	int x, y, pom;
	pom = pkt2 - pkt1;
	if (pom == -9) { x = al->pkt_na_xy[pkt1][0]; y = al->pkt_na_xy[pkt1][1] - 40; }
	else if (pom == -8) { x = al->pkt_na_xy[pkt1][0] + 40; y = al->pkt_na_xy[pkt1][1] - 40; }
	else if (pom == 1) { x = al->pkt_na_xy[pkt1][0] + 40; y = al->pkt_na_xy[pkt1][1]; }
	else if (pom == 10) { x = al->pkt_na_xy[pkt1][0] + 40; y = al->pkt_na_xy[pkt1][1] + 40; }
	else if (pom == 9) { x = al->pkt_na_xy[pkt1][0]; y = al->pkt_na_xy[pkt1][1] + 40; }
	else if (pom == 8) { x = al->pkt_na_xy[pkt1][0] - 40; y = al->pkt_na_xy[pkt1][1] + 40; }
	else if (pom == -1) { x = al->pkt_na_xy[pkt1][0] - 40; y = al->pkt_na_xy[pkt1][1]; }
	else if (pom == -10) { x = al->pkt_na_xy[pkt1][0] - 40; y = al->pkt_na_xy[pkt1][1] - 40; }
	if (x >65 && x <415 && y >65 && y <495 && al->tab_pkt[pkt1][pkt2] == 0 && al->tab_pkt[pkt2][pkt1] == 0) return true;
	else if (x > 185 && x < 295 && ((y >25 && y < 55) || (y >505 && y < 535)) && al->tab_pkt[pkt1][pkt2] == 0) return true;
	else return false;
}

bool odwiedzony_AI(int pkt2, al_defs* al)
{
	int ile1 = 0, x, y;
	x = al->pkt_na_xy[pkt2][0];
	y = al->pkt_na_xy[pkt2][1];
	if ((x > 65 && x < 95) || (x >385 && x < 415)) return true;
	if (((y > 65 && y < 95) || (y >465 && y < 495)) && (x < 215 || x > 295)) return true;
	if (al->tab_pkt[pkt2][pkt2 - 9] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 - 8] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 + 1] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 + 10] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 + 9] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 + 8] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 - 1] == 1) ile1++;
	if (al->tab_pkt[pkt2][pkt2 - 10] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 - 9] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 - 8] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 + 1] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 + 10] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 + 9] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 + 8] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 - 1] == 1) ile1++;
	if (al->pom_tab_pkt[pkt2][pkt2 - 10] == 1) ile1++;
	if (ile1 > 1) return true;
	else return false;
}

bool zablokowany_AI(int pkt2, al_defs* al)
{
	int pozostale_ruchy = 0;
	if (sprawdzRuch_AI(pkt2, pkt2 - 9, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 - 8, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 + 1, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 + 10, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 + 9, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 + 8, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 - 1, al)) { pozostale_ruchy++; }
	if (sprawdzRuch_AI(pkt2, pkt2 - 10, al)) { pozostale_ruchy++; }
	if (pozostale_ruchy == 0) return true;
	else return false;
}

void StworzZbior(int pkt, al_defs* al)
{
	int i, j, pktx, q;
	
	q = 0;
	if (!odwiedzony_AI(14, al) && pkt !=14)
		{
			pktx = 14;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 14; q++; }
		}
	if (!odwiedzony_AI(23, al) && pkt != 23)
		{
			pktx = 23;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 23; q++; }
		}
	if (!odwiedzony_AI(22, al) && pkt != 22)
		{
			pktx = 22;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 22; q++; }
		}
	if (!odwiedzony_AI(24, al) && pkt != 24)
		{
			pktx = 24;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 24; q++; }
		}
	if (!odwiedzony_AI(21, al) && pkt != 21)
		{
			pktx = 21;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 21; q++; }
		}
	if (!odwiedzony_AI(25, al) && pkt != 25)
		{
			pktx = 25;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 25; q++; }
		}
	if (!odwiedzony_AI(20, al) && pkt != 20)
		{
			pktx = 20;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 20; q++; }
		}
	if (!odwiedzony_AI(26, al) && pkt != 26)
		{
			pktx = 26;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) { al->zbior[q] = 26; q++; }
		}
	for (i = 29; i < 99;i++)
	{
		if (!odwiedzony_AI(i, al) && pkt != i)
		{
			pktx = i;
			al->sciezka[pkt] = -1;
			al->ZnalezionoDroge = false;
			DrogaDoPkt(pkt, pktx, al);
			for (j = 0;j < 118;j++)
			{
				al->odw[j] = false;
				al->sciezka[j] = 0;
			}
			if (al->ZnalezionoDroge) 
			{ 
				al->zbior[q] = i; 
				q++; 
			}
		}
	}
}

void DrogaDoPkt(int pkt, int pktx, al_defs* al)
{
	al->odw[pkt] = true;
	if (pkt == pktx) al->ZnalezionoDroge = true;
	if (!al->ZnalezionoDroge)
	{
		if (sprawdzRuch_AI(pkt, pkt - 10, al) && !al->odw[pkt - 10])
		{
			if (odwiedzony_AI(pkt - 10, al) || pkt - 10 == pktx) 
			{
				al->sciezka[pkt - 10] = pkt; 
				DrogaDoPkt(pkt - 10, pktx, al); 
			}
		}
		if (sprawdzRuch_AI(pkt, pkt - 8, al) && !al->odw[pkt - 8])
		{
			if (odwiedzony_AI(pkt - 8, al) || pkt - 8 == pktx)
			{
				al->sciezka[pkt - 8] = pkt; 
				DrogaDoPkt(pkt - 8, pktx, al);
			}
		}
		if (sprawdzRuch_AI(pkt, pkt - 9, al) && !al->odw[pkt - 9])
		{
			if (odwiedzony_AI(pkt - 9, al) || pkt - 9 == pktx) 
			{
				al->sciezka[pkt - 9] = pkt;
				DrogaDoPkt(pkt - 9, pktx, al); 
			}
		}
		if (sprawdzRuch_AI(pkt, pkt + 1, al) && !al->odw[pkt + 1])
		{
			if (odwiedzony_AI(pkt + 1, al) || pkt + 1 == pktx)
			{
				al->sciezka[pkt + 1] = pkt;
				DrogaDoPkt(pkt + 1, pktx, al);
			}
		}
		if (sprawdzRuch_AI(pkt, pkt - 1, al) && !al->odw[pkt - 1])
		{
			if (odwiedzony_AI(pkt - 1, al) || pkt - 1 == pktx) 
			{
				al->sciezka[pkt - 1] = pkt;
				DrogaDoPkt(pkt - 1, pktx, al);
			}
		}
		if (sprawdzRuch_AI(pkt, pkt + 8, al) && !al->odw[pkt + 8])
		{
			if (odwiedzony_AI(pkt + 8, al) || pkt + 8 == pktx) 
			{
				al->sciezka[pkt + 8] = pkt;
				DrogaDoPkt(pkt + 8, pktx, al);
			}
		}
		if (sprawdzRuch_AI(pkt, pkt + 9, al) && !al->odw[pkt + 9])
		{
			if (odwiedzony_AI(pkt + 9, al) || pkt + 9 == pktx)
			{
				al->sciezka[pkt + 9] = pkt; 
				DrogaDoPkt(pkt + 9, pktx, al); 
			}
		}
		if (sprawdzRuch_AI(pkt, pkt + 10, al) && !al->odw[pkt + 10])
		{
			if (odwiedzony_AI(pkt + 10, al) || pkt + 10 == pktx)
			{
				al->sciezka[pkt + 10] = pkt;
				DrogaDoPkt(pkt + 10, pktx, al);
			}
		}
	}
}

void DrogaDoWlasnejBramki(int pkt, int pktx, al_defs* al)
{
	al->odw[pkt] = true;
	if (pkt == pktx) al->ZnalezionoDroge2 = true;
	if (!al->ZnalezionoDroge2)
	{
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt + 9, al) && SprDCh(pkt, pkt + 9, al) && !al->odw[pkt + 9])
		{
			if (odwiedzony_AI(pkt + 9, al) || pkt + 9 == pktx) 
			{ 
				DrogaDoWlasnejBramki(pkt + 9, pktx, al);
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt + 8, al) && SprDCh(pkt, pkt + 8, al) && !al->odw[pkt + 8])
		{
			if (odwiedzony_AI(pkt + 8, al) || pkt + 8 == pktx) 
			{ 
				DrogaDoWlasnejBramki(pkt + 8, pktx, al);
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt + 10, al) && SprDCh(pkt, pkt + 10, al) && !al->odw[pkt + 10])
		{
			if (odwiedzony_AI(pkt + 10, al) || pkt + 10 == pktx)
			{
				DrogaDoWlasnejBramki(pkt + 10, pktx, al);
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt + 1, al) && SprDCh(pkt, pkt + 1, al) && !al->odw[pkt + 1])
		{
			if (odwiedzony_AI(pkt + 1, al) || pkt + 1 == pktx)
			{
				DrogaDoWlasnejBramki(pkt + 1, pktx, al); 
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt - 1, al) && SprDCh(pkt, pkt - 1, al) && !al->odw[pkt - 1])
		{
			if (odwiedzony_AI(pkt - 1, al) || pkt - 1 == pktx)
			{
				DrogaDoWlasnejBramki(pkt - 1, pktx, al); 
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt - 10, al) && SprDCh(pkt, pkt - 10, al) && !al->odw[pkt - 10])
		{
			if (odwiedzony_AI(pkt - 10, al) || pkt - 10 == pktx)
			{
				DrogaDoWlasnejBramki(pkt - 10, pktx, al); 
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt - 8, al) && SprDCh(pkt, pkt - 8, al) && !al->odw[pkt - 8])
		{
			if (odwiedzony_AI(pkt - 8, al) || pkt - 8 == pktx) 
			{
				DrogaDoWlasnejBramki(pkt - 8, pktx, al);
			}
		}
		if (!al->ZnalezionoDroge2 && sprawdzRuch_AI(pkt, pkt - 9, al) && SprDCh(pkt, pkt - 9, al) && !al->odw[pkt - 9])
		{
			if (odwiedzony_AI(pkt - 9, al) || pkt - 9 == pktx)
			{
				DrogaDoWlasnejBramki(pkt - 9, pktx, al);
			}
		}
	}
}

bool SprDCh(int pkt1, int pkt2, al_defs* al)
{
	if (al->pom_tab_pkt[pkt1][pkt2] == 0 && al->pom_tab_pkt[pkt2][pkt1] == 0) return true;
	else return false;
}

void BlokDrogaDoPkt(int pkt, int pktx, int i, al_defs* al)
{
	int pkt2;
	if (pkt == pktx)
	{
		al->ZnalezionoDroge3 = true;
	}
	if (!al->ZnalezionoDroge3)
	{
		pkt2 = pkt + 9;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al) && pkt2 != 113)
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx)
			{ 
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt + 8;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al) && pkt2 != 113)
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx)
			{
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt + 10;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al) && pkt2 != 113)
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx)
			{ 
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt + 1;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al))
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx) 
			{ 
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt - 1;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al))
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx) 
			{
				al->sciezka[i] = pkt2; 
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt - 10;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al))
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx)
			{ 
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt - 8;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al))
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx)
			{
				al->sciezka[i] = pkt2; 
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
		pkt2 = pkt - 9;
		if (!al->ZnalezionoDroge3 && sprawdzRuch_AI(pkt, pkt2, al) && SprDCh(pkt, pkt2, al))
		{
			if (odwiedzony_AI(pkt2, al) || pkt2 == pktx) 
			{
				al->sciezka[i] = pkt2;
				al->pom_tab_pkt[pkt][pkt2] = 1;
				al->pom_tab_pkt[pkt2][pkt] = 1;
				BlokDrogaDoPkt(pkt2, pktx, i+1, al);
				if (!al->ZnalezionoDroge3)
				{
					al->pom_tab_pkt[pkt][pkt2] = 0;
					al->pom_tab_pkt[pkt2][pkt] = 0;
				}
			}
		}
	}
}

void IdzDoPkt(int pktx, al_defs* al)
{
	int pkt, pom, roznica, i;
	pkt = pktx;
	pom = 0;
	while (al->sciezka[pkt] != -1)
	{
		pom++;
		al->droga[pom] = pkt;
		pkt = al->sciezka[pkt];
	}
	for (i = pom;i > 0;i--)
	{
		al_rest(0.4);
		al->punkt2 = al->droga[i];
		roznica = al->punkt2 - al->punkt1;
		if (roznica == 8) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 10) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 9) { al->dx2 = al->dx1; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -1) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 1) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -10) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -9) { al->dx2 = al->dx1; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -8) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		al->tab_pkt[al->punkt1][al->punkt2] = 1;
		al->tab_pkt[al->punkt2][al->punkt1] = 1;
		al->punkt1 = al->punkt2;
		al->moveNR++;
		al->pomtab_xy[al->moveNR][0] = al->dx2; al->pomtab_xy[al->moveNR][1] = al->dy2;
		if (!odwiedzony_AI(al->punkt2, al)) al->kolejka++;
		make_pitch(al);
		al->dx1 = al->dx2;
		al->dy1 = al->dy2;
		czy_gol(al);
	}
}

void UciekajDoPkt(int pktx, al_defs* al)
{
	int i = -1, roznica;
	do {
		al_rest(0.4);
		i++;
		al->punkt2 = al->sciezka[i];
		roznica = al->punkt2 - al->punkt1;
		if (roznica == 8) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 10) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 9) { al->dx2 = al->dx1; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -1) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == 1) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -10) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -9) { al->dx2 = al->dx1; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		else if (roznica == -8) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; }
		al->tab_pkt[al->punkt1][al->punkt2] = 1;
		al->tab_pkt[al->punkt2][al->punkt1] = 1;
		al->punkt1 = al->punkt2;
		al->moveNR++;
		al->pomtab_xy[al->moveNR][0] = al->dx2; al->pomtab_xy[al->moveNR][1] = al->dy2;
		if (al->punkt2 == pktx) al->kolejka++;
		make_pitch(al);
		al->dx1 = al->dx2;
		al->dy1 = al->dy2;
		czy_gol(al);

	} while (al->sciezka[i] != pktx && al->sciezka[i] != 0);
}

void BezZnaczenia(al_defs* al)
{
	int los, pkt=al->punkt1;
	while (al->kolejka == al->pomkol && !al->koniec)
	{
		al_rest(0.4);
		al->ruch = false;
		while (!al->ruch)
		{
			los = rand() % 8 + 1;
			if (los == 1 && sprawdzRuch_AI(pkt, pkt - 9, al)) { al->punkt2 = al->punkt1 - 9; al->dx2 = al->dx1; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 2 && sprawdzRuch_AI(pkt, pkt - 8, al)) { al->punkt2 = al->punkt1 - 8; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 3 && sprawdzRuch_AI(pkt, pkt + 1, al)) { al->punkt2 = al->punkt1 + 1; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 4 && sprawdzRuch_AI(pkt, pkt + 10, al)) { al->punkt2 = al->punkt1 + 10; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 5 && sprawdzRuch_AI(pkt, pkt + 9, al)) { al->punkt2 = al->punkt1 + 9; al->dx2 = al->dx1; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 6 && sprawdzRuch_AI(pkt, pkt + 8, al)) { al->punkt2 = al->punkt1 + 8; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 7 && sprawdzRuch_AI(pkt, pkt - 1, al)) { al->punkt2 = al->punkt1 - 1; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
			else if (los == 8 && sprawdzRuch_AI(pkt, pkt - 10, al)) { al->punkt2 = al->punkt1 - 10; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; al->ruch = true; }
		}
		al->tab_pkt[al->punkt1][al->punkt2] = 1;
		al->tab_pkt[al->punkt2][al->punkt1] = 1;
		al->punkt1 = al->punkt2;
		pkt = al->punkt2;
		al->moveNR++;
		al->pomtab_xy[al->moveNR][0] = al->dx2; al->pomtab_xy[al->moveNR][1] = al->dy2;
		if (!odwiedzony_AI(al->punkt2, al)) al->kolejka++;
		make_pitch(al);
		al->dx1 = al->dx2;
		al->dy1 = al->dy2;
		czy_gol(al);
		if (zablokowany_AI(al->punkt2,al))
		{
			break;
		}
	}
}

void AI(al_defs* al)
{
	al->pomkol++;
	pomtab2tab(al);
	int i = 0, j = 0, pkt = al->punkt1, pom = 0, roznica = 0, los, pktx, i1, j1;
	al->ruch = false;
	for (i = 0;i < 118;i++)
	{
		al->odw[i] = false;
		al->sciezka[i] = 0;			
		al->droga[i] = 0;
		al->zbior[i] = 0;
	}
	pktx = 5;
	al->sciezka[pkt] = -1;
	al->ZnalezionoDroge = false;
	DrogaDoPkt(pkt, pktx, al);

	if (al->ZnalezionoDroge) IdzDoPkt(pktx, al);

	else if (!al->ZnalezionoDroge)
	{
		for (i = 0;i < 118;i++)
		{
			al->odw[i] = false;
			al->sciezka[i] = 0;
			al->sciezka2[i] = 0;
			al->droga[i] = 0;
			al->zbior[i] = 0;
		}
		StworzZbior(pkt, al);

		pktx = 113;
		al->sciezka[pkt] = -1;
		al->ZnalezionoDroge2 = false;
		DrogaDoWlasnejBramki(pkt, pktx, al);
		if (al->ZnalezionoDroge2)
		{
			// szukanie punktu z ktorego drogi nie bedzie
			i = 0;
			while (al->zbior[i] != 0)
			{
				for (i1 = 0;i1 < 118;i1++)
				{
					al->sciezka[i1] = 0;
					for (j1 = 0;j1 < 118;j1++)
					{
						al->pom_tab_pkt[i1][j1] = 0;
					}
				}
				al->ZnalezionoDroge3 = false;
				BlokDrogaDoPkt(pkt, al->zbior[i], 0, al);
				int i2 = 0, j2 = 0;
				for (i2 = 0;i2 < 118;i2++)
				{
					al->odw[i2] = false;
				}
				al->ZnalezionoDroge2 = false;
				DrogaDoWlasnejBramki(al->zbior[i], pktx, al);
				if (!al->ZnalezionoDroge2)
				{
					UciekajDoPkt(al->zbior[i], al);
					break;
				}
				i++;
			}
			if (i == 0 && al->zbior[i] == 0)
			{
				BezZnaczenia(al);
			}
			else if (al->ZnalezionoDroge2)
			{
				for (i1 = 0;i1 < 118;i1++)
				{
					al->sciezka[i1] = 0;
					for (j1 = 0;j1 < 118;j1++)
					{
						al->pom_tab_pkt[i1][j1] = 0;
					}
				}
				al->ZnalezionoDroge3 = false;
				BlokDrogaDoPkt(pkt, al->zbior[0], 0, al);
				UciekajDoPkt(al->zbior[0], al);
			}
		}
		else
		{
			i = 0;
			while (al->zbior[i] != 0)
			{
				for (i = 0;i < 118;i++)
				{
					al->odw[i] = false;
					al->sciezka[i] = 0;
					al->droga[i] = 0;
				}
				pktx = 5;
				al->ZnalezionoDroge = false;
				DrogaDoPkt(al->zbior[i], pktx, al);
				if (al->ZnalezionoDroge)
				{
					for (i1 = 0;i1 < 118;i1++)
					{
						al->sciezka[i1] = 0;
						for (j1 = 0;j1 < 118;j1++)
						{
							al->pom_tab_pkt[i1][j1] = 0;
						}
					}
					al->ZnalezionoDroge3 = false;
					BlokDrogaDoPkt(pkt, al->zbior[i], 0, al);
					if (al->ZnalezionoDroge3)
					{
						UciekajDoPkt(al->zbior[i], al);
					}
					break;
				}
			}
			if (i == 0 && al->zbior[i] == 0)
			{
				BezZnaczenia(al);
			}
			else if (!al->ZnalezionoDroge)
			{
				al->ZnalezionoDroge3 = false;
				BlokDrogaDoPkt(pkt, al->zbior[0], 0, al);
				UciekajDoPkt(al->zbior[0], al);
			}
		}
	}
}

void begin_game_AI(al_defs* al)
{
	pliki_odczyt(al);
	make_pitch(al);
	al->pomeczu = false;
	al->grazAI = true;

	al->dx1 = al->sx;
	al->dy1 = al->sy;
	while (!al->game)
	{
		if (!al->cofanie)
		{
			if (czy_zablokowany(al) || zablokowany_AI(al->punkt1,al))
			{
				if (al->kolejka % 2 == 1)
				{
					al_draw_text(al->logo_font, al_map_rgb(255, 0, 0), 240, 120, ALLEGRO_ALIGN_CENTER, "ZABLOKOWANY!");
					al_draw_rectangle(438, 320, 630, 360, al_map_rgb(255, 0, 0), 3);
					al_draw_text(al->menu_font, al_map_rgb(255, 0, 0), 420, 320, ALLEGRO_ALIGN_RIGHT, "The winner is...");
					al_flip_display();
					al->game = true;
				}
				else if (al->kolejka % 2 == 0)
				{
					al_draw_text(al->logo_font, al_map_rgb(255, 0, 0), 240, 400, ALLEGRO_ALIGN_CENTER, "ZABLOKOWANY!");
					al_draw_rectangle(438, 200, 630, 240, al_map_rgb(255, 0, 0), 3);
					al_draw_text(al->menu_font, al_map_rgb(255, 0, 0), 420, 200, ALLEGRO_ALIGN_RIGHT, "The winner is...");
					al_flip_display();
					al->game = true;
				}
				break;
			}
		}

		if (al->kolejka % 2 == 1)
		{
			make_move(al);
			al->tab_pkt[al->punkt1][al->punkt2] = 1;
			al->tab_pkt[al->punkt2][al->punkt1] = 1;
			al->punkt1 = al->punkt2;
			al->moveNR++;
			al->pom_cofnij++;
			if (!al->cofanie) al->pomtab_xy[al->moveNR][0] = al->dx2; al->pomtab_xy[al->moveNR][1] = al->dy2;
			if (!al->cofanie) { if (!odwiedzony(al)) { al->kolejka++; al->pom_cofnij = 0; } }
			al->cofanie = false;
			make_pitch(al);
			al->dx1 = al->dx2;
			al->dy1 = al->dy2;
			czy_gol(al);
		}
		else AI(al);
	}
	pliki_zapis(al);
	al_draw_bitmap(al->zakoncz, 40, 560, NULL);
	al_draw_bitmap(al->rewanz, 436, 255, NULL);
	al_flip_display();
	while (!al->pomeczu)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			al->x = al->events.mouse.x;
			al->y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				if (al->x > 40 && al->x < 160 && al->y > 560 && al->y < 610) al->pomeczu = true;
				else if (al->x > 436 && al->x < 556 && al->y > 255 && al->y < 305)
				{
					char pom1[12], pom2[12];
					int i = 0;
					for (i = 0;i < 12;i++) { pom1[i] = al->nazwa1[i]; pom2[i] = al->nazwa2[i]; }
					zerujzmienne(al);
					for (i = 0;i < 12;i++) { al->nazwa1[i] = pom1[i]; al->nazwa2[i] = pom2[i]; }
					al->game = false;
					al->koniec = false;
					begin_game_AI(al);
					break;
				}
			}
		}
	}
	zerujzmienne(al);
}