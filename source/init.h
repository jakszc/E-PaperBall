#ifndef INIT_H
#define INIT_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "al_defs.h"
#include <cstdio>
bool init_allegro(al_defs* al);
void destroy_all(al_defs* al);
#endif
