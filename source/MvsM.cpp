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
#include "rules_and_stats.h"
#include <cstdio>
#include <iostream>

void menu_wpr_nick(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	al_draw_text(al->title_font, al_map_rgb(0, 0, 0), 100, 30, NULL, "Wprowadz nazwy graczy:");
	al_draw_text(al->title_font, al_map_rgb(0, 0, 0), 100, 30, NULL, "Wprowadz nazwy graczy:");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 80, NULL, "-dozwolone znaki: [a-z] oraz [0-9]");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 100, NULL, "-max 10 znakow");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 120, NULL, "-zastrzezona nazwa: ''komputer''");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 140, NULL, "-po wprowadzeniu wcisnij enter");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 160, NULL, "-dane zapisywane sa w pliku,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 180, NULL, " jezeli plik o podanej nazwie istnieje, odczyta je,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 200, NULL, " jezeli nie, to utworzy nowy plik");	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 230, ALLEGRO_ALIGN_LEFT, "Gracz nr 1:");
	al_draw_filled_rectangle(50, 250, 250, 270, al_map_rgb(255, 255, 255));
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 280, ALLEGRO_ALIGN_LEFT, "Gracz nr 2:");
	al_draw_filled_rectangle(50, 300, 250, 320, al_map_rgb(255, 255, 255));
	al_draw_bitmap(al->wstecz, 30, 575, NULL);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 63, 250, NULL, al->nazwa1);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 63, 300, NULL, al->nazwa2);
	al_draw_bitmap(al->change, 270, 248, NULL);
	al_draw_bitmap(al->change, 270, 298, NULL);
	al_flip_display();
}

void menuMvsM(al_defs* al)
{
	al->StartButton = false;
	al->game = false;
	al->przerwano = false;
	menu_wpr_nick(al);
	wpr_nick(al);
	menu_wpr_nick(al);

	al_draw_bitmap(al->play_now, 500, 575, NULL);
	al_flip_display();
	int f = 0, pom = 0, pom1 = 0, pom2 = 0, g, h;
	int x, y;
	char zastrzezone[12] = { "komputer" };
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
					//sprawdzenie czy nazwy graczy sa rozne
					pom = 0, pom1 = 0, pom2 = 0, f=-1, g=-1, h=-1;
					do
					{
						f++;
						if (al->nazwa1[f] == al->nazwa2[f]) pom++;
					} while (al->nazwa1[f] != NULL);
					do
					{
						g++;
						if (al->nazwa1[g] == zastrzezone[g]) pom1++;
					} while (al->nazwa1[g] != NULL);
					do
					{
						h++;
						if (al->nazwa2[h] == zastrzezone[h]) pom2++;
					} while (al->nazwa2[h] != NULL);
					if ((pom-1) == f) al_show_native_message_box(al->display, "Blad", "Blad", "Nazwy graczy musza byc rozne", NULL, NULL);
					else if ((pom1 - 1) == g || (pom2 - 1) == h) al_show_native_message_box(al->display, "Blad", "Blad", "Nazwa ''komputer'' jest zastrzezona!", NULL, NULL);
					//od siebie nawzajem oraz od "komputer"
					else
					{
						begin_game(al);
						al->StartButton = true;
					}
				}
				else if (x >= 270 && x <= 355 && y >= 248 && y <= 270)
				{
					for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
					menu_wpr_nick(al);
					al->nick1 = false;
					wpr_nick(al);
					al_draw_bitmap(al->play_now, 500, 575, NULL);
					al_flip_display();
				}
				else if (x >= 270 && x <= 355 && y >= 298 && y <= 320)
				{
					for (i = 0;i < 10;i++) al->nazwa2[i] = NULL;
					menu_wpr_nick(al);
					al->nick2 = false;
					wpr_nick(al);
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
	opcja(al);
}

void wpr_nick(al_defs* al)
{
	al->anuluj = false;
	int x, y, pomx = 0, pomy = 0, pomchar = 0, i = 0;
	while (!al->nick1 || !al->nick2)
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
									al->nazwa1[pomchar] = 'q';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_W:
									al->nazwa1[pomchar] = 'w';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_E:
									al->nazwa1[pomchar] = 'e';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_R:
									al->nazwa1[pomchar] = 'r';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_T:
									al->nazwa1[pomchar] = 't';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_Y:
									al->nazwa1[pomchar] = 'y';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_U:
									al->nazwa1[pomchar] = 'u';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_I:
									al->nazwa1[pomchar] = 'i';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_O:
									al->nazwa1[pomchar] = 'o';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_P:
									al->nazwa1[pomchar] = 'p';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_A:
									al->nazwa1[pomchar] = 'a';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_S:
									al->nazwa1[pomchar] = 's';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_D:
									al->nazwa1[pomchar] = 'd';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_F:
									al->nazwa1[pomchar] = 'f';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_G:
									al->nazwa1[pomchar] = 'g';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_H:
									al->nazwa1[pomchar] = 'h';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_J:
									al->nazwa1[pomchar] = 'j';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_K:
									al->nazwa1[pomchar] = 'k';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_L:
									al->nazwa1[pomchar] = 'l';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_Z:
									al->nazwa1[pomchar] = 'z';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_X:
									al->nazwa1[pomchar] = 'x';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_C:
									al->nazwa1[pomchar] = 'c';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_V:
									al->nazwa1[pomchar] = 'v';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_B:
									al->nazwa1[pomchar] = 'b';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_N:
									al->nazwa1[pomchar] = 'n';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_M:
									al->nazwa1[pomchar] = 'm';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_0:
									al->nazwa1[pomchar] = '0';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_1:
									al->nazwa1[pomchar] = '1';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_2:
									al->nazwa1[pomchar] = '2';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_3:
									al->nazwa1[pomchar] = '3';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_4:
									al->nazwa1[pomchar] = '4';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_5:
									al->nazwa1[pomchar] = '5';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_6:
									al->nazwa1[pomchar] = '6';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_7:
									al->nazwa1[pomchar] = '7';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_8:
									al->nazwa1[pomchar] = '8';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_9:
									al->nazwa1[pomchar] = '9';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_BACKSPACE:
									if (pomchar > 0) al->nazwa1[--pomchar] = ' '; if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_ENTER:
									al->nazwa1[pomchar] = NULL; pomchar++; al->nick1 = true; if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al); break;
								case ALLEGRO_KEY_TAB:
									al->nazwa1[pomchar] = NULL; pomchar++; al->nick1 = true; x = 50, y = 300;
									for (i = 0;i < 10;i++) al->nazwa2[i] = NULL;
									al->nick2 = false;
									if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);
									break;
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
								if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);
							}
						}
					}
				}
				if (x >= 50 && x <= 250 && y >= 300 && y <= 320)
				{
					al_draw_line(50, 310, 60, 310, al_map_rgb(0, 0, 0), 1);
					al_draw_line(60, 310, 55, 305, al_map_rgb(0, 0, 0), 1);
					al_draw_line(60, 310, 55, 315, al_map_rgb(0, 0, 0), 1);
					al_flip_display();
					pomx = 63;	pomy = 300, pomchar = 0;
					while (!al->nick2)
					{
						al_wait_for_event(al->event_queue, &al->events);
						if (al->events.type == ALLEGRO_EVENT_KEY_DOWN)
						{
							if (pomchar < 10)
							{
								switch (al->events.keyboard.keycode)
								{
								case ALLEGRO_KEY_Q:
									al->nazwa2[pomchar] = 'q';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_W:
									al->nazwa2[pomchar] = 'w';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_E:
									al->nazwa2[pomchar] = 'e';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_R:
									al->nazwa2[pomchar] = 'r';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_T:
									al->nazwa2[pomchar] = 't';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_Y:
									al->nazwa2[pomchar] = 'y';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_U:
									al->nazwa2[pomchar] = 'u';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_I:
									al->nazwa2[pomchar] = 'i';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_O:
									al->nazwa2[pomchar] = 'o';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_P:
									al->nazwa2[pomchar] = 'p';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_A:
									al->nazwa2[pomchar] = 'a';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_S:
									al->nazwa2[pomchar] = 's';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_D:
									al->nazwa2[pomchar] = 'd';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_F:
									al->nazwa2[pomchar] = 'f';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_G:
									al->nazwa2[pomchar] = 'g';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_H:
									al->nazwa2[pomchar] = 'h';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_J:
									al->nazwa2[pomchar] = 'j';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_K:
									al->nazwa2[pomchar] = 'k';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_L:
									al->nazwa2[pomchar] = 'l';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_Z:
									al->nazwa2[pomchar] = 'z';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_X:
									al->nazwa2[pomchar] = 'x';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_C:
									al->nazwa2[pomchar] = 'c';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_V:
									al->nazwa2[pomchar] = 'v';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_B:
									al->nazwa2[pomchar] = 'b';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_N:
									al->nazwa2[pomchar] = 'n';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_M:
									al->nazwa2[pomchar] = 'm';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_0:
									al->nazwa2[pomchar] = '0';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_1:
									al->nazwa2[pomchar] = '1';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_2:
									al->nazwa2[pomchar] = '2';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_3:
									al->nazwa2[pomchar] = '3';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_4:
									al->nazwa2[pomchar] = '4';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_5:
									al->nazwa2[pomchar] = '5';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_6:
									al->nazwa2[pomchar] = '6';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_7:
									al->nazwa2[pomchar] = '7';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_8:
									al->nazwa2[pomchar] = '8';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_9:
									al->nazwa2[pomchar] = '9';	pomchar++;	if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_BACKSPACE:
									if (pomchar > 0) al->nazwa2[--pomchar] = ' '; if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);	break;
								case ALLEGRO_KEY_ENTER:
									al->nazwa2[pomchar] = NULL; pomchar++; al->nick2 = true; if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al); break;
								}
							}
							else if (pomchar == 10)
							{
								if (al->events.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) al->nazwa2[--pomchar] = ' ';
								else if (al->events.keyboard.keycode == ALLEGRO_KEY_ENTER)
								{
									al->nazwa2[pomchar] = NULL;
									al->nick2 = true;
								}
								if (!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);
							}
						}
					}
				}
				else if (x >= 270 && x <= 355 && y >= 248 && y <= 270)
				{
					for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
					al->nick1 = false;
					if (!al->StatyMenu) menu_wpr_nick(al); 
					else menu_stats(al);
				}
				else if (x >= 270 && x <= 355 && y >= 298 && y <= 320)
				{
					for (i = 0;i < 10;i++) al->nazwa2[i] = NULL;
					al->nick2 = false;
					if (!al->StatyMenu) menu_wpr_nick(al);
					else menu_stats(al);
				}
				else if (x > 30 && x < 115 && y>575 && y < 610)
				{
					al->anuluj = true;
					al->StatyMenu = false;
					zerujzmienne(al);
					break;
				}
				else
				{
					if(!al->StatyMenu) menu_wpr_nick(al); else menu_stats(al);
				}
			}
		}
	}
}

bool sprawdzRuch(al_defs* al)
{
	if (al->x >65 && al->x <415 && al->y >65 && al->y <495 && al->tab_pkt[al->punkt1][al->punkt2] == 0 && al->tab_pkt[al->punkt2][al->punkt1] == 0) return true;
	else if (al->x > 185 && al->x < 295 && ((al->y >25 && al->y < 55) || (al->y >505 && al->y < 535)) && al->tab_pkt[al->punkt1][al->punkt2] == 0) return true;
	else return false;
}

bool odwiedzony(al_defs* al)
{
	int ile1 = 0;
	if ((al->x > 65 && al->x < 95) || (al->x >385 && al->x < 415)) return true;
	if (((al->y > 65 && al->y < 95) || (al->y >465 && al->y < 495)) && (al->x < 215 || al->x > 295)) return true;
	if (al->tab_pkt[al->punkt2][al->punkt2-9] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2-8] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2+1] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2+10] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2+9] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2+8] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2-1] == 1) ile1++;
	if (al->tab_pkt[al->punkt2][al->punkt2-10] == 1) ile1++;
	if (ile1 > 1) return true;
	else return false;
}

void pomtab2tab(al_defs* al)
{
	int i;
	for (i = 1;i < 308;i++)
	{
		if (al->tab_xy[i][0] == 0) { al->tab_xy[i][0] = al->pomtab_xy[i][0]; al->tab_xy[i][1] = al->pomtab_xy[i][1]; }
		al->pomtab_xy[i][0] = 0; al->pomtab_xy[i][1] = 0;
	}
	al->pomtab_xy[al->moveNR][0] = al->tab_xy[al->moveNR][0];
	al->pomtab_xy[al->moveNR][1] = al->tab_xy[al->moveNR][1];
}

void zerujzmienne(al_defs* al)
{
	int i, j;
	for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
	al->nick1 = false;
	for (i = 0;i < 10;i++) al->nazwa2[i] = NULL;
	al->nick2 = false;
	for (i = 1;i < 118;i++)
	{
		for (j = 1;j < 118;j++)
		{
			al->tab_pkt[i][j] = 0;
			if (i == j) al->tab_pkt[i][j] = 1;
			if (j % 9 == 0 && j>17 && j < 100) al->tab_pkt[j][j + 9] = 1;
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
	al->ball_x = al->sx;
	al->ball_y = al->sy;
	al->punkt1 = 59;
	al->punkt2 = al->punkt1;
	al->moveNR = 0;
	al->kolejka = 1;
	al->pomkol = 1;
	al->x = al->sx;
	al->y = al->sy;
	// AI
	al->przerwano = false;
	al->ZnalezionoDroge = false;
	al->ZnalezionoDroge2 = false;
	al->ZnalezionoDroge3 = false;
	al->grazAI = false;
	int wsx = 80, wsy = 0, wsk = 1;
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
}

void czy_gol(al_defs* al)
{
	if (al->dy1 == 40)
	{
		al_draw_text(al->logo_font, al_map_rgb(255, 0, 0), 240, 120, ALLEGRO_ALIGN_CENTER, "GOOOL!");
		al_draw_rectangle(438, 320, 630, 360, al_map_rgb(255, 0, 0), 3);
		al_draw_text(al->menu_font, al_map_rgb(255, 0, 0), 420, 320, ALLEGRO_ALIGN_RIGHT, "The winner is...");
		al_flip_display();
		al->game = true;
		al->koniec = true;
	}
	else if (al->dy1 == 520)
	{
		al_draw_text(al->logo_font, al_map_rgb(255, 0, 0), 240, 400, ALLEGRO_ALIGN_CENTER, "GOOOL!");
		al_draw_rectangle(438, 200, 630, 240, al_map_rgb(255, 0, 0), 3);
		al_draw_text(al->menu_font, al_map_rgb(255, 0, 0), 420, 200, ALLEGRO_ALIGN_RIGHT, "The winner is...");
		al_flip_display();
		al->game = true;
		al->koniec = true;
	}
}

bool czy_zablokowany(al_defs* al)
{
	int pozostale_ruchy = 0, pom_punkt2, pomx,pomy;
	pom_punkt2 = al->punkt2;
	pomx = al->x;
	pomy = al->y;
	al->punkt2 = al->punkt1 - 9;
	al->y -= 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 - 8;
	al->x += 40;
	al->y -= 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 + 1;
	al->x += 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 + 10;
	al->x += 40;
	al->y += 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 + 9;
	al->y += 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 + 8;
	al->x -= 40;
	al->y += 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 - 1;
	al->x -= 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	al->punkt2 = al->punkt1 - 10;
	al->x -= 40;
	al->y -= 40;
	if (sprawdzRuch(al)) { pozostale_ruchy++;}
	al->punkt2 = pom_punkt2;
	al->x = pomx;
	al->y = pomy;
	if (pozostale_ruchy == 0) return true;
	else return false;
}

void cofnij2(al_defs* al)
{
	if (al->pomtab_xy[al->moveNR - 2][0] == al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] < al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 - 9;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] > al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] < al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 - 8;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] > al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] == al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 + 1;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] > al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] > al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 + 10;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] == al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] > al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 + 9;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] < al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] > al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 + 8;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] < al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] == al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 - 1;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
	else if (al->pomtab_xy[al->moveNR - 2][0] < al->pomtab_xy[al->moveNR - 1][0] && al->pomtab_xy[al->moveNR - 2][1] < al->pomtab_xy[al->moveNR - 1][1])
	{
		al->punkt1 = al->punkt2 - 10;
		al->dx1 = al->pomtab_xy[al->moveNR - 2][0];
		al->dy1 = al->pomtab_xy[al->moveNR - 2][1];
		al->dx2 = al->pomtab_xy[al->moveNR - 1][0];
		al->dy2 = al->pomtab_xy[al->moveNR - 1][1];
		al->ball_x = al->dx2; al->ball_y = al->dy2;
	}
}

void cofnij(al_defs* al)
{
	if (al->kolejka == al->pomkol && al->pom_cofnij > 0)
	{
		al->punkt2 = al->punkt1;
		al->cofanie = true;
		if (al->pom_cofnij == 1)
		{
			al->pomtab_xy[al->moveNR - 2][0] = al->tab_xy[al->moveNR - 2][0];
			al->pomtab_xy[al->moveNR - 2][1] = al->tab_xy[al->moveNR - 2][1];
		}

		if (al->pomtab_xy[al->moveNR - 1][0] == al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] < al->pomtab_xy[al->moveNR][1]) 
		{ 
			al->punkt1 = al->punkt2 - 9;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] > al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] < al->pomtab_xy[al->moveNR][1]) 
		{ 
			al->punkt1 = al->punkt2 - 8;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] > al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] == al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 + 1;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] > al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] > al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 + 10;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] == al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] > al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 + 9;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] < al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] > al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 + 8;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] < al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] == al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 - 1;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		else if (al->pomtab_xy[al->moveNR - 1][0] < al->pomtab_xy[al->moveNR][0] && al->pomtab_xy[al->moveNR - 1][1] < al->pomtab_xy[al->moveNR][1])
		{
			al->punkt1 = al->punkt2 - 10;
			al->tab_pkt[al->punkt1][al->punkt2] = 0;
			al->tab_pkt[al->punkt2][al->punkt1] = 0;
			al->punkt2 = al->punkt1;
			cofnij2(al);
		}
		if (al->pom_cofnij == 1)
		{
			al->pomtab_xy[al->moveNR - 2][0] = 0;
			al->pomtab_xy[al->moveNR - 2][1] = 0;
		}
		al->pomtab_xy[al->moveNR][0] = 0;
		al->pomtab_xy[al->moveNR][1] = 0;
		al->moveNR -= 2;
		al->pom_cofnij -= 2;
		al->x = al->ball_x;
		al->y = al->ball_y;
		al->ruch = true;
	}
}

void make_move(al_defs* al)
{
	al->ruch = false;
	int x, y, pom;
	while (!al->ruch)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			pom = 0;
			al->x = al->events.mouse.x;
			x = al->x;
			al->y = al->events.mouse.y;
			y = al->y;
			if (al->events.mouse.button & 1)
			{
				if (x > al->dx1 - 15 && x < al->dx1 + 15 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 9; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 8; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 - 15 && y < al->dy1 + 15) { al->punkt2 = al->punkt1 + 1; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 10; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 - 15 && x < al->dx1 + 15 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 9; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 8; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 + 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 - 15 && y < al->dy1 + 15) { al->punkt2 = al->punkt1 - 1; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 10; if (sprawdzRuch(al)) { pom++; al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 - 40; al->ball_x = al->dx2; al->ball_y = al->dy2; } }
				else if (x > 436 && x < 500 && y > 265 && y < 295) { cofnij(al); }
				if (pom > 0)
				{
					if (al->kolejka > al->pomkol)
					{
						al->pomkol++;
						pomtab2tab(al);
					}
					al->ruch = true;
				}
			}
		}
		else if (al->events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			int value = al_show_native_message_box(al->display, "Zakoncz gre", "Uwaga", "Spowoduje to oddanie meczu walkowerem przez \naktualnego gracza oraz zakonczenie rozgrywki!", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL | ALLEGRO_MESSAGEBOX_QUESTION);
			if (value == 1)
			{
				al->ruch = true;
				al->game = true;
				al->przerwano = true;
				al->pomeczu = true;
				break;
			}
		}
		else if (al->events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			al->x = al->events.mouse.x;
			x = al->x;
			al->y = al->events.mouse.y;
			y = al->y;
			if (x > al->dx1 - 15 && x < al->dx1 + 15 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 9; if (sprawdzRuch(al)) { al->dx2 = al->dx1; al->dy2 = al->dy1 - 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 8; if (sprawdzRuch(al)) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 - 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 - 15 && y < al->dy1 + 15) { al->punkt2 = al->punkt1 + 1; if (sprawdzRuch(al)) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 + 25 && x < al->dx1 + 55 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 10; if (sprawdzRuch(al)) { al->dx2 = al->dx1 + 40; al->dy2 = al->dy1 + 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 - 15 && x < al->dx1 + 15 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 9; if (sprawdzRuch(al)) { al->dx2 = al->dx1; al->dy2 = al->dy1 + 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 + 25 && y < al->dy1 + 55) { al->punkt2 = al->punkt1 + 8; if (sprawdzRuch(al)) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 + 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 - 15 && y < al->dy1 + 15) { al->punkt2 = al->punkt1 - 1; if (sprawdzRuch(al)) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else if (x > al->dx1 - 55 && x < al->dx1 - 25 && y > al->dy1 - 55 && y < al->dy1 - 25) { al->punkt2 = al->punkt1 - 10; if (sprawdzRuch(al)) { al->dx2 = al->dx1 - 40; al->dy2 = al->dy1 - 40; al_draw_filled_circle(al->dx2, al->dy2, 4, al_map_rgb(0, 0, 255)); al_flip_display(); } }
			else make_pitch(al);
		}
	}
}

void zamiana_graczy(al_defs* al)
{
	char pom1[12], pom2[12];
	int i = 0, p1,p2,p3,p4,p5,p6;
	for (i = 0;i < 12;i++) { pom1[i] = al->nazwa1[i]; pom2[i] = al->nazwa2[i]; }
	zerujzmienne(al);
	for (i = 0;i < 12;i++) { al->nazwa1[i] = pom2[i]; al->nazwa2[i] = pom1[i]; }
	p1 = al->lm1; p2 = al->lz1; p3 = al->lzAI1; p4 = al->lp1; p5 = al->lpAI1; p6 = al->ranga1;
	al->lm1 = al->lm2; al->lz1 = al->lz2;al->lzAI1 = al->lzAI2;al->lp1 = al->lp2;al->lpAI1 = al->lpAI2;al->ranga1 = al->ranga2;
	al->lm2 = p1; al->lz2 = p2; al->lzAI2 = p3; al->lp2 = p4; al->lpAI2 = p5; al->ranga2 = p6;
}

void begin_game(al_defs * al)
{
	al->pomeczu = false;
	pliki_odczyt(al);
	make_pitch(al);

	int i, j;
	al->dx1 = al->sx;
	al->dy1 = al->sy;
	while (!al->game)
	{
		if (!al->cofanie)
		{
			if (czy_zablokowany(al))
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
		make_move(al);
		al->tab_pkt[al->punkt1][al->punkt2] = 1;
		al->tab_pkt[al->punkt2][al->punkt1] = 1;
		al->punkt1 = al->punkt2;
		al->moveNR++;
		al->pom_cofnij++;
		if(!al->cofanie) al->pomtab_xy[al->moveNR][0] = al->dx2; al->pomtab_xy[al->moveNR][1] = al->dy2;
		if (!al->cofanie) { if (!odwiedzony(al)) { al->kolejka++; al->pom_cofnij = 0; } }
		al->cofanie = false;
		make_pitch(al);
		al->dx1 = al->dx2;
		al->dy1 = al->dy2;
		czy_gol(al);
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
					zamiana_graczy(al);
					al->game = false;
					begin_game(al);
					break;
				}
			}
		}
	}
	zerujzmienne(al);
}