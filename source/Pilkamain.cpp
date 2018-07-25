#include <allegro5\allegro.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>
#include "al_defs.h"
#include "init.h"
#include "start.h"
#include <stdio.h>

int main(void)
{
	FreeConsole();
	al_defs al;
	if (!init_allegro(&al))
	{

		al_show_native_message_box(NULL, NULL, "Gra nie dzia³a", NULL, NULL, NULL);
		return -1;
	}
	start(&al);
	destroy_all(&al);

/*	al->done = false;
	while (!al->done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			pomx = x;
			pomy = y;
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_PAD_8:
				y -= move;
				if (x > 2 * (width / 16) && x < 10 * (width / 16) && x != 6 * (width / 16) && y == 1 * (height / 16)) y += move;							//gorna krawedz - bramka
				else if (x == 2 * (width / 16) || x == 10 * (width / 16)) y += move;																		//boczne krawedzie
				else if ((x == 5 * (width / 16) || x == 7 * (width / 16)) && (y == 1 * (height / 16) || y == 12 * (height / 16))) y += move;				//bramki pion
				else if (y == 0) y += move;																													//gorna bramka poziom
				break;

			case ALLEGRO_KEY_PAD_2:
				y += move;
				if (x > 2 * (width / 16) && x < 10 * (width / 16) && x != 6 * (width / 16) && y == 13 * (height / 16)) y -= move;							//dolna krawedz - bramka
				else if (x == 2 * (width / 16) || x == 10 * (width / 16)) y -= move;																		//boczne krawedzie
				else if ((x == 5 * (width / 16) || x == 7 * (width / 16)) && (y == 2 * (height / 16) || y == 13 * (height / 16))) y -= move;				//bramki pion
				else if (y == 14 * (height / 16)) y -= move;																								//dolna bramka poziom
				break;

			case ALLEGRO_KEY_PAD_4:
				x -= move;
				if (y > 2 * (height / 16) && y < 12 * (height / 16) && x == 1 * (width / 16)) x += move;													//lewa krawedz
				if ((y == 2 * (height / 16) || y == 12 * (height / 16)) && x != 5 * (width / 16) && x != 6 * (width / 16)) x += move;						//gora i dol - bramki
				if (y == 1 * (height / 16) || y == 13 * (height / 16)) x += move;																			//bramki poziom
				break;

			case ALLEGRO_KEY_PAD_6:
				x += move;
				if (y > 2 * (height / 16) && y < 12 * (height / 16) && x == 11 * (width / 16)) x -= move;													//prawa krawedz
				if ((y == 2 * (height / 16) || y == 12 * (height / 16)) && x != 6 * (width / 16) && x != 7 * (width / 16)) x -= move;						//gora i dol - bramki
				if (y == 1 * (height / 16) || y == 13 * (height / 16)) x -= move;																			//bramki poziom
				break;

			case ALLEGRO_KEY_PAD_7:
				x -= move;
				y -= move;
				if (x == 1 * (width / 16))																													//lewa krawedz
				{
					y += move;
					x += move;
				}
				else if (x > 1 * (width / 16) && (y == 1 * (height / 16) || y == 12 * (height / 16)) && x != 5 * (width / 16) && x != 6 * (width / 16))		//gorna krawedz - bramka
				{
					y += move;
					x += move;
				}
				else if (y == 0)																															//bramka
				{
					y += move;
					x += move;
				}
				break;

			case ALLEGRO_KEY_PAD_9:
				x += move;
				y -= move;
				if (x == 11 * (width / 16))																													//prawa krawedz
				{
					y += move;
					x -= move;
				}
				else if (x < 11 * (width / 16) && (y == 1 * (height / 16) || y == 12 * (height / 16)) && x != 6 * (width / 16) && x != 7 * (width / 16))	//gorna krawedz - bramka
				{
					y += move;
					x -= move;
				}
				else if (y == 0)																															//bramka
				{
					y += move;
					x -= move;
				}
				break;

			case ALLEGRO_KEY_PAD_1:
				x -= move;
				y += move;
				if (x == 1 * (width / 16))																													//lewa krawedz
				{
					y -= move;
					x += move;
				}
				else if (x > 1 * (width / 16) && (y == 2 * (height / 16) || y == 13 * (height / 16)) && x != 5 * (width / 16) && x != 6 * (width / 16))		//dolna krawedz - bramka
				{
					y -= move;
					x += move;
				}
				else if (y == 14 * (height / 16))																											//bramka
				{
					y -= move;
					x += move;
				}
				break;

			case ALLEGRO_KEY_PAD_3:
				x += move;
				y += move;
				if (x == 11 * (width / 16))																													//prawa krawedz
				{
					y -= move;
					x -= move;
				}
				else if (x < 11 * (width / 16) && (y == 2 * (height / 16) || y == 13 * (height / 16)) && x != 6 * (width / 16) && x != 7 * (width / 16))	//dolna krawedz - bramka
				{
					y -= move;
					x -= move;
				}
				else if (y == 14 * (height / 16))																											//bramka
				{
					y -= move;
					x -= move;
				}
				break;

			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			int value = al_show_native_message_box(display, "Zakoncz gre", "Uwaga", "Czy na pewno chcesz zakonczyc?", NULL, ALLEGRO_MESSAGEBOX_YES_NO | ALLEGRO_MESSAGEBOX_QUESTION);
			if (value == 1)
			{
				done = true;
				break;
			}
		}
		al_draw_filled_circle(x, y, 4, white);
		al_flip_display();
		update_pitch(pomx, pomy, x, y);
	}


	//	al_draw_triangle(10, 10, 200, 10, 100, 500, black, 5);
	//	al_draw_rectangle(100, 100, 500, 500, white, 3);
	//	al_draw_rounded_rectangle(300, 300, 400, 400, 10, 10, black,3);
	//	al_draw_filled_rounded_rectangle(300, 300, 400, 400, 10, 10, black);
	//	al_draw_circle(300, 300, 50, red, 3);
	//	al_draw_ellipse(100, 100, 50, 30, blue, 2);
	//	al_draw_arc(100, 500, 100, 0, 6, blue, 3);
	//	al_draw_spline(points, red, 3);

	al_flip_display();
	al_rest(0.5);
	destroy_all(&al);
	return 0;
*/	
}