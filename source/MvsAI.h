#ifndef MVSAI_H
#define MVSAI_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "al_defs.h"
#include <cstdio>
void menuMvsAI(al_defs* al);
void menu_wpr_nick_AI(al_defs* al);
void wpr_nick_AI(al_defs* al);
bool sprawdzRuch_AI(int pkt1, int pk2, al_defs* al);
bool odwiedzony_AI(int pkt2, al_defs* al);
bool zablokowany_AI(int pk2, al_defs* al);
void StworzZbior(int pkt, al_defs* al);
void DrogaDoPkt(int pkt, int pktx, al_defs* al);
void DrogaDoWlasnejBramki(int pkt, int pktx, al_defs* al);
bool SprDCh(int pkt1, int pkt2, al_defs* al);
void BlokDrogaDoPkt(int pkt, int pktx, int i, al_defs* al);
void IdzDoPkt(int pktx, al_defs* al);
void UciekajDoPkt(int pktx, al_defs* al);
void BezZnaczenia(al_defs* al);
void AI(al_defs* al);
void begin_game_AI(al_defs* al);
#endif
