#ifndef MVSM_H
#define MVSM_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "al_defs.h"
#include <cstdio>
void menu_wpr_nick(al_defs* al);
void menuMvsM(al_defs* al);
void wpr_nick(al_defs* al);
bool sprawdzRuch(al_defs* al);
bool odwiedzony(al_defs* al);
void pomtab2tab(al_defs* al);
void zerujzmienne(al_defs* al);
void czy_gol(al_defs* al);
bool czy_zablokowany(al_defs* al);
void cofnij2(al_defs* al);
void cofnij(al_defs* al);
void make_move(al_defs* al);
void zamiana_graczy(al_defs* al);
void begin_game(al_defs* al);
#endif
