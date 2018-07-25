#define _CRT_SECURE_NO_DEPRECATE
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include "al_defs.h"
#include "start.h"
#include "MvsM.h"
#include "rules_and_stats.h"
#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>

void rules(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 10, NULL, "ZASADY GRY:");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 50, NULL, "E-Paper Ball to implementacja kartkowych pilkarzykow.");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 70, NULL, "Zasady sa nastepujace:");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 90, NULL, "-w grze biora udzial dwie osoby,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 110, NULL, "-gra sie do pierwszego gola lub zablokowania jednego z graczy,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 130, NULL, "-gol zostaje uznany w momencie, gdy pilka znajdzie sie na tylniej");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 150, NULL, " scianie bramki (mozna odbic sie najpierw od slupka),");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 170, NULL, "-zablokowanie nastepuje w momencie, gdy gracz nie moze ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 190, NULL, " dojsc do nieodwiedzonego jeszcze punktu ani strzelic gola,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 210, NULL, "-w przypadku gdy gracz dotrze do punktu, ktory nalezy do ");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 230, NULL, " krawedzi boiska lub byl juz odwiedzony, musi wykonac dodatkowy ruch,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 250, NULL, "-dopoki tura nie zostanie zakonczona, gracz moze cofac swoje ruchy,");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 270, NULL, "-gra odbywa sie na boisku o wymiarach 10x8 kratek,");	
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 10, 290, NULL, " z bramkami o szerokosci 2 kratek.");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 110, 390, ALLEGRO_ALIGN_LEFT, "przyklady ruchow:");
	al_draw_bitmap(al->wstecz, 30, 575, NULL);
	al_draw_bitmap(al->ex, 110, 410, NULL);
	al_flip_display();
	al->klik = false;
	int x, y;
	while (!al->klik)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				if (x >= 30 && x <= 115 && y >= 575 && y <= 609)	al->klik = true;
			}
		}
	}
}

void dane_p1(al_defs* al)
{
	if (al->nick1 && al->istnieje1)
	{
		pliki_odczyt(al);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 395, ALLEGRO_ALIGN_RIGHT, "%d", al->lm1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 395, ALLEGRO_ALIGN_LEFT, "(%d)", al->lpm1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 447, ALLEGRO_ALIGN_RIGHT, "%d", al->lz1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 447, ALLEGRO_ALIGN_LEFT, "(%d)", al->lzAI1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 497, ALLEGRO_ALIGN_RIGHT, "%d", al->lp1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 497, ALLEGRO_ALIGN_LEFT, "(%d)", al->lpAI1);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 325, 535, ALLEGRO_ALIGN_CENTER, "%d", al->ranga1);
		al_flip_display();
	}
}

void dane_p2(al_defs* al)
{
	if (al->nick2 && al->istnieje2)
	{
		pliki_odczyt(al);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 395, ALLEGRO_ALIGN_RIGHT, "%d", al->lm2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 395, ALLEGRO_ALIGN_LEFT, "(%d)", al->lpm2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 447, ALLEGRO_ALIGN_RIGHT, "%d", al->lz2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 447, ALLEGRO_ALIGN_LEFT, "(%d)", al->lzAI2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 497, ALLEGRO_ALIGN_RIGHT, "%d", al->lp2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 497, ALLEGRO_ALIGN_LEFT, "(%d)", al->lpAI2);
		al_draw_textf(al->font, al_map_rgb(0, 0, 0), 475, 535, ALLEGRO_ALIGN_CENTER, "%d", al->ranga2);
		al_flip_display();
	}
}

void menu_stats(al_defs* al)
{
	al_clear_to_color(al_map_rgb(30, 115, 55));
	al_draw_text(al->title_font, al_map_rgb(0, 0, 0), 100, 30, NULL, "Statystyki");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 80, NULL, "RANGI:");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 100, NULL, " -<999,1250> = amator");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 120, NULL, " -(1250,1350> = noob");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 140, NULL, " -(1350,1500> = sredniak");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 160, NULL, " -(1500,1700> = ekspert");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 300, 100, NULL, "-(1700,1900> = pro");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 300, 120, NULL, "-(1900,2000> = mistrz");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 300, 140, NULL, "-(2000,2100> = arcymistrz");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 300, 160, NULL, "-(2100, oo)     = HOLYsh*t");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 230, ALLEGRO_ALIGN_LEFT, "Gracz nr 1:");
	al_draw_filled_rectangle(50, 250, 250, 270, al_map_rgb(255, 255, 255));
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 50, 280, ALLEGRO_ALIGN_LEFT, "Gracz nr 2:");
	al_draw_filled_rectangle(50, 300, 250, 320, al_map_rgb(255, 255, 255));
	al_draw_bitmap(al->wstecz, 30, 575, NULL);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 63, 250, NULL, al->nazwa1);
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 63, 300, NULL, al->nazwa2);
	al_draw_bitmap(al->change, 270, 248, NULL);
	al_draw_bitmap(al->change, 270, 298, NULL);

	al_draw_rectangle(50, 340, 550, 560, al_map_rgb(0, 0, 0), 3);
	al_draw_line(250, 340, 250, 560, al_map_rgb(0, 0, 0), 2);
	al_draw_line(400, 340, 400, 560, al_map_rgb(0, 0, 0), 2);
	al_draw_line(50, 380, 550, 380, al_map_rgb(0, 0, 0), 3);
	al_draw_line(50, 430, 550, 430, al_map_rgb(0, 0, 0), 2);
	al_draw_line(50, 480, 550, 480, al_map_rgb(0, 0, 0), 2);
	al_draw_line(50, 530, 550, 530, al_map_rgb(0, 0, 0), 2);

	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 350, ALLEGRO_ALIGN_CENTER, "Dane");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 382, ALLEGRO_ALIGN_CENTER, "Liczba meczy");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 407, ALLEGRO_ALIGN_CENTER, "(w tym walkowery)");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 432, ALLEGRO_ALIGN_CENTER, "Liczba zwyciestw");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 457, ALLEGRO_ALIGN_CENTER, "(w tym z AI)");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 482, ALLEGRO_ALIGN_CENTER, "Liczba porazek");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 507, ALLEGRO_ALIGN_CENTER, "(w tym z AI)");
	al_draw_text(al->font, al_map_rgb(0, 0, 0), 150, 535, ALLEGRO_ALIGN_CENTER, "Punkty rangi");

	pliki_odczyt(al);
	if (al->istnieje1 && al->nick1)
	{
		al_draw_text(al->font, al_map_rgb(0, 0, 0), 325, 350, ALLEGRO_ALIGN_CENTER, al->nazwa1);
		dane_p1(al);
	}
	else if (!al->istnieje1 && al->nick1) al_draw_text(al->font, al_map_rgb(0, 0, 0), 325, 350, ALLEGRO_ALIGN_CENTER, "NIE ISTNIEJE");

	if (al->istnieje2 && al->nick2)
	{
		al_draw_text(al->font, al_map_rgb(0, 0, 0), 475, 350, ALLEGRO_ALIGN_CENTER, al->nazwa2);
		dane_p2(al);
	}
	else if (!al->istnieje2 && al->nick2) al_draw_text(al->font, al_map_rgb(0, 0, 0), 475, 350, ALLEGRO_ALIGN_CENTER, "NIE ISTNIEJE");

	al_flip_display();
}

void stats(al_defs* al)
{
	al->StatyMenu = true;
	menu_stats(al);
	wpr_nick(al);
	menu_stats(al);
	int x, y, i;
	while (al->StatyMenu)
	{
		al_wait_for_event(al->event_queue, &al->events);
		al_get_mouse_state(&al->mouseState);
		if (al->events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = al->events.mouse.x;
			y = al->events.mouse.y;
			if (al->events.mouse.button & 1)
			{
				if (x > 30 && x < 115 && y>575 && y < 610) al->StatyMenu = false;
				else if (x >= 270 && x <= 355 && y >= 248 && y <= 270)
				{
					for (i = 0;i < 10;i++) al->nazwa1[i] = NULL;
					al->nick1 = false;
					menu_stats(al);
					wpr_nick(al);
				}
				else if (x >= 270 && x <= 355 && y >= 298 && y <= 320)
				{
					for (i = 0;i < 10;i++) al->nazwa2[i] = NULL;
					al->nick2 = false;
					menu_stats(al);
					wpr_nick(al);
				}
			}
		}
	}

	zerujzmienne(al);
	main_menu(al);
	opcja(al);
}

void update_rangi(al_defs* al)
{
	int w = 0, l = 0, roznica;
	if (al->wygral == 1) { w = al->ranga1; l = al->ranga2; }
	else if (al->wygral == 2) { w = al->ranga2; l = al->ranga1; }
	if(w>=l) roznica = w - l;
	else roznica = l - w;
	if (roznica > 300)
	{
		if (w > l) { w += 3; l -= 3; }
		else { w += 75; l -= 75; }
	}
	else if (roznica > 200)
	{
		if (w > l) { w += 5; l -= 5; }
		else { w += 50; l -= 50; }
	}
	else if (roznica > 150)
	{
		if (w > l) { w += 10; l -= 10; }
		else { w += 40; l -= 40; }
	}
	else if (roznica > 100)
	{
		if (w > l) { w += 15; l -= 15; }
		else { w += 35; l -= 35; }
	}
	else if (roznica > 50)
	{
		if (w > l) { w += 20; l -= 20; }
		else { w += 30; l -= 30; }
	}
	else
	{
		if (w > l) { w += 25; l -= 25; }
		else { w += 25; l -= 25; }
	}
	if (w < 999) w = 999;
	if (l < 999) l = 999;
	if (al->wygral == 1) { al->ranga1 = w; al->ranga2 = l; }
	else if (al->wygral == 2) { al->ranga2 = w; al->ranga1 = l; }
}

bool fileExists(const char* fileName)
{
	struct stat buf;
	/* Odczytywanie statystyk pliku */
	if (stat(fileName, &buf) == 0)
		return true;
	else
		return false;
}

void pliki_odczyt(al_defs* al)
{
	std::string pliktxt1 = "staty//", pliktxt2 = "staty//";
	if (al->nick1)
	{
		pliktxt1 += al->nazwa1, pliktxt1 += ".txt";
		al->istnieje1 = al_filename_exists(pliktxt1.c_str());
		if (al->istnieje1)
		{
			al->plik1 = fopen(pliktxt1.c_str(), "r");
			if (al->plik1 == NULL) printf("Nie mozna odczytac plik1\n");
			fscanf(al->plik1, "%d", &al->lm1);
			fscanf(al->plik1, "%d", &al->lpm1);
			fscanf(al->plik1, "%d", &al->lz1);
			fscanf(al->plik1, "%d", &al->lzAI1);
			fscanf(al->plik1, "%d", &al->lp1);
			fscanf(al->plik1, "%d", &al->lpAI1);
			fscanf(al->plik1, "%d", &al->ranga1);
			fclose(al->plik1);
		}
		else if (!al->StatyMenu)
		{
			al->plik1 = fopen(pliktxt1.c_str(), "w");
			al->lm1 = 0;
			al->lpm1 = 0;
			al->lz1 = 0;
			al->lzAI1 = 0;
			al->lp1 = 0;
			al->lpAI1 = 0;
			al->ranga1 = 1300;
			fclose(al->plik1);
		}
	}
	if (al->nick2)
	{
		pliktxt2 += al->nazwa2, pliktxt2 += ".txt";
		al->istnieje2 = al_filename_exists(pliktxt2.c_str());
		if (al->istnieje2)
		{
			al->plik2 = fopen(pliktxt2.c_str(), "r");
			if (al->plik2 == NULL) printf("Nie mozna odczytac plik2\n");
			fscanf(al->plik2, "%d", &al->lm2);
			fscanf(al->plik2, "%d", &al->lpm2);
			fscanf(al->plik2, "%d", &al->lz2);
			fscanf(al->plik2, "%d", &al->lzAI2);
			fscanf(al->plik2, "%d", &al->lp2);
			fscanf(al->plik2, "%d", &al->lpAI2);
			fscanf(al->plik2, "%d", &al->ranga2);
			fclose(al->plik2);
		}
		else if (!al->StatyMenu)
		{
			al->plik2 = fopen(pliktxt2.c_str(), "w");
			al->lm2 = 0;
			al->lpm2 = 0;
			al->lz2 = 0;
			al->lzAI2 = 0;
			al->lp2 = 0;
			al->lpAI2 = 0;
			al->ranga2 = 1300;
			fclose(al->plik2);
		}
	}
}

void pliki_zapis(al_defs* al)
{
	std::string pliktxt1 = "staty//", pliktxt2 = "staty//";
	pliktxt1 += al->nazwa1, pliktxt1 += ".txt";
	pliktxt2 += al->nazwa2, pliktxt2 += ".txt";
	al->plik1 = fopen(pliktxt1.c_str(), "w");
	al->plik2 = fopen(pliktxt2.c_str(), "w");
	al->lm1++;
	al->lm2++;
	if (al->przerwano)
	{
		if (al->kolejka % 2 == 1)										// gracz 1 oddal mecz
		{
				al->lz2++;
				al->lp1++;
				al->wygral = 2;
				al->lpm1++;
				if (al->grazAI)
				{
					al->lpAI1++;
				}

		}
		else if (al->kolejka % 2 == 0)									//gracz 2 oddal mecz
		{
			al->lz1++;
			al->lp2++;
			al->wygral = 1;
			al->lpm2++;
		}
	}
	else if (al->dy1 == 520 || (al->kolejka % 2 == 0 && al->dy1 != 40))		//wygra³ gracz nr1
	{ 
		al->lz1++; 
		al->lp2++; 
		al->wygral = 1;
		if (al->grazAI)
		{
			al->lzAI1++;
		}
	}
	else if (al->dy1 == 40 || (al->kolejka % 2 == 1 && al->dy1 != 520)) //wygra³ gracz nr2
	{
		al->lz2++;
		al->lp1++; 
		al->wygral = 2;
		if (al->grazAI)
		{
			al->lpAI1++;
		}
	}
	update_rangi(al);
	fprintf(al->plik1, "%d\n%d\n%d\n%d\n%d\n%d\n%d", al->lm1, al->lpm1, al->lz1, al->lzAI1, al->lp1, al->lpAI1, al->ranga1);
	fprintf(al->plik2, "%d\n%d\n%d\n%d\n%d\n%d\n%d", al->lm2, al->lpm2, al->lz2, al->lzAI2, al->lp2, al->lpAI2, al->ranga2);
	fclose(al->plik1);
	fclose(al->plik2);
}