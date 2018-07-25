#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include "al_defs.h"
#include "init.h"
#include "start.h"
#include "MvsM.h"
#include "MvsAI.h"
#include "rules_and_stats.h"
#include <cstdio>

void start(al_defs* al)
{
	main_menu(al);
	opcja(al);
	if (al->klik && !al->wybor) opcja(al);
}

void main_menu(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	al_draw_text(al->logo_font, al_map_rgb(255, 0, 0), al->width / 2, al->height / 2 - 200, ALLEGRO_ALIGN_CENTER, "E-Paper Ball");
	al_draw_bitmap(al->ball, 420, 200, NULL);
	al_draw_text(al->menu_font, al_map_rgb(0, 0, 0), al->width / 2 - 250, al->height / 2 - 100, ALLEGRO_ALIGN_LEFT, "2 graczy");
	al_draw_text(al->menu_font, al_map_rgb(0, 0, 0), al->width / 2 - 250, al->height / 2 - 50, ALLEGRO_ALIGN_LEFT, "gracz vs komputer");
	al_draw_text(al->menu_font, al_map_rgb(0, 0, 0), al->width / 2 - 250, al->height / 2, ALLEGRO_ALIGN_LEFT, "zasady gry");
	al_draw_text(al->menu_font, al_map_rgb(0, 0, 0), al->width / 2 - 250, al->height / 2 + 50, ALLEGRO_ALIGN_LEFT, "statystyki");
	al_flip_display();
}

void opcja(al_defs* al)
{
	int x, y, i = 0;
	al->wybor = false;

	while (!al->wybor)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				if (x >= 70 && x <= 214 && y >= 228 && y <= 255)
				{
					menuMvsM(al);
				}
				else if (x >= 70 && x <= 380 && y >= 278 && y <= 305)
				{
					menuMvsAI(al);
				}
				else if (x >= 70 && x <= 250 && y >= 328 && y <= 355)
				{
					rules(al);
				}
				else if (x >= 70 && x <= 238 && y >= 378 && y <= 405)
				{
					stats(al);
				}
			}
		}
		else if (al->events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			int value = al_show_native_message_box(al->display, "Zakoncz gre", "Uwaga", "Czy na pewno chcesz zakonczyc?", NULL, ALLEGRO_MESSAGEBOX_YES_NO | ALLEGRO_MESSAGEBOX_QUESTION);
			if (value == 1)
			{
				al->wybor = true;
				al->done = true;
				break;
			}
		}
		else if (al->events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (x >= 70 && x <= 214 && y >= 228 && y <= 255)
			{
				i++;
				al_draw_rectangle(70, 228, 214, 255, al_map_rgb(0, 0, 0), 1);
				al_flip_display();
			}
			else if (x >= 70 && x <= 380 && y >= 278 && y <= 305)
			{
				i++;
				al_draw_rectangle(70, 278, 380, 305, al_map_rgb(0, 0, 0), 1);
				al_flip_display();
			}
			else if (x >= 70 && x <= 250 && y >= 328 && y <= 355)
			{
				i++;
				al_draw_rectangle(70, 328, 250, 355, al_map_rgb(0, 0, 0), 1);
				al_flip_display();
			}
			else if (x >= 70 && x <= 238 && y >= 378 && y <= 405)
			{
				i++;
				al_draw_rectangle(70, 378, 238, 405, al_map_rgb(0, 0, 0), 1);
				al_flip_display();
			}
			else if (i != 0) main_menu(al);
		}
	}
}

void make_pitch(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	int pom_w = 3 * (al->width / 16), pom_h = al->height / 16;
	int i = 0, j = 0;
	for (i = 0;i < 13;i++)
	{
		pom_w = al->width / 16;
		for (j = 0;j < 11;j++)
		{
			al_draw_pixel(pom_w, pom_h, al_map_rgb(255, 255, 255));
			pom_w += (al->width / 16);
		}
		pom_h += al->height / 16;
	}
	al_draw_line(2 * (al->width / 16), 2 * (al->height / 16), 2 * (al->width / 16), 12 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//lewy pion
	al_draw_line(10 * (al->width / 16), 2 * (al->height / 16), 10 * (al->width / 16), 12 * (al->height / 16), al_map_rgb(255, 255, 255), 3);	//prawy pion
	al_draw_line(2 * (al->width / 16), 2 * (al->height / 16), 5 * (al->width / 16), 2 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//gora poziom1
	al_draw_line(7 * (al->width / 16), 2 * (al->height / 16), 10 * (al->width / 16), 2 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//gora poziom2
	al_draw_line(2 * (al->width / 16), 12 * (al->height / 16), 5 * (al->width / 16), 12 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//dol poziom1
	al_draw_line(7 * (al->width / 16), 12 * (al->height / 16), 10 * (al->width / 16), 12 * (al->height / 16), al_map_rgb(255, 255, 255), 3);	//dol poziom2
	al_draw_line(5 * (al->width / 16), 1 * (al->height / 16), 7 * (al->width / 16), 1 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//gora bramka poziom
	al_draw_line(5 * (al->width / 16), 13 * (al->height / 16), 7 * (al->width / 16), 13 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//dol bramka poziom
	al_draw_line(5 * (al->width / 16), 1 * (al->height / 16), 5 * (al->width / 16), 2 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//gora bramka pion1
	al_draw_line(7 * (al->width / 16), 1 * (al->height / 16), 7 * (al->width / 16), 2 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//gora bramka pion2
	al_draw_line(5 * (al->width / 16), 12 * (al->height / 16), 5 * (al->width / 16), 13 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//dol bramka pion1
	al_draw_line(7 * (al->width / 16), 12 * (al->height / 16), 7 * (al->width / 16), 13 * (al->height / 16), al_map_rgb(255, 255, 255), 3);		//dol bramka pion2
	al_draw_filled_circle(al->ball_x, al->ball_y, 4, al_map_rgb(255, 255, 255));																//pozycja pilki
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 290, 50, NULL, al->nazwa1);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 290, 490, NULL, al->nazwa2);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 440, 200, NULL, "Gracz1: ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 440, 220, NULL, "Poziom: ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 440, 320, NULL, "Gracz2: ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 440, 340, NULL, "Poziom: ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 200, NULL, al->nazwa1);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 320, NULL, al->nazwa2);
	if (true)
	{
		if (al->ranga1>2100) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "HOLYsh*t");
		else if (al->ranga1>2000) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "arcymistrz");
		else if (al->ranga1>1900) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "mistrz");
		else if (al->ranga1>1700) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "pro");
		else if (al->ranga1>1500) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "ekspert");
		else if (al->ranga1>1350) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "sredniak");
		else if (al->ranga1>1250) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "noob");
		else if (al->ranga1>999) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 220, NULL, "amator");

		if (al->ranga2>2100) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "HOLYsh*t");
		else if (al->ranga2>2000) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "arcymistrz");
		else if (al->ranga2>1900) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "mistrz");
		else if (al->ranga2>1700) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "pro");
		else if (al->ranga2>1500) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "ekspert");
		else if (al->ranga2>1350) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "sredniak");
		else if (al->ranga2>1250) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "noob");
		else if (al->ranga2>999) al_draw_text(al->font, al_map_rgb(0, 0, 0), 510, 340, NULL, "amator");
	}
	al_draw_rectangle(438, 200, 630, 240, al_map_rgb(0, 0, 0), 2);
	al_draw_rectangle(438, 320, 630, 360, al_map_rgb(0, 0, 0), 2);
	al_draw_filled_rounded_rectangle(436, 265, 500, 295, 8, 8, al_map_rgb(90, 115, 190));
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 445, 270, NULL, "Cofnij");
	if (al->kolejka % 2 == 1) al_draw_bitmap(al->arrow, 400, 205, NULL);
	else al_draw_bitmap(al->arrow, 400, 325, NULL);
	i = 1;
	while (al->tab_xy[i][0] != 0)
	{
		al_draw_line(al->tab_xy[i - 1][0], al->tab_xy[i - 1][1], al->tab_xy[i][0], al->tab_xy[i][1], al_map_rgb(255, 255, 255), 1);
		i++;
	}
	for (i = 1;i < 308;i++)
	{
		if (al->pomtab_xy[i][0] != 0 && al->pomtab_xy[i - 1][0] != 0)	al_draw_line(al->pomtab_xy[i - 1][0], al->pomtab_xy[i - 1][1], al->pomtab_xy[i][0], al->pomtab_xy[i][1], al_map_rgb(255, 255, 255), 3);
	}
	al_flip_display();
}
