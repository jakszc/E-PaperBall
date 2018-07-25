#ifndef RULES_AND_STATS_H
#define RULES_AND_STATS_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "al_defs.h"
#include <cstdio>
void rules(al_defs* al);
void dane_p1(al_defs* al);
void dane_p2(al_defs* al);
void menu_stats(al_defs* al);
void stats(al_defs* al);
void update_rangi(al_defs* al);
bool fileExists(const char* fileName);
void pliki_odczyt(al_defs* al);
void pliki_zapis(al_defs* al);
#endif
