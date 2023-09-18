#include "cprocessing.h"
#include "utils.h"
#include "game.h"

#define NUM_PLAYER 3

CP_Color redColor;
CP_Color greenColor;
CP_Color blueColor;
CP_Color whiteColor;
CP_Color colors[NUM_PLAYER + 1];

float diameter;
float width;
float height;


CP_Vector player[NUM_PLAYER];

void Game_Init(void)
{
	width = CP_System_GetDisplayWidth() * 0.9;
	height = CP_System_GetDisplayHeight() * 0.85;

	redColor = CP_Color_Create(255, 0, 0, 255);
	greenColor = CP_Color_Create(0, 255, 0, 255);
	blueColor = CP_Color_Create(0, 0, 255, 255);
	whiteColor = CP_Color_Create(255, 255, 255, 255);

	colors[0] = redColor;
	colors[1] = greenColor;
	colors[2] = blueColor;
	colors[3] = whiteColor;
	
	diameter = 50;

	for (int i = 0; i < NUM_PLAYER; i++) {
		player[i].x = width * (i + 1) / (NUM_PLAYER + 1);
		player[i].y = height / 2;
	}

}


void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	draw_player();
	
}

void Game_Exit(void)
{

}

void draw_player(void) {
	for (int i = 0; i < NUM_PLAYER; i++) {
		CP_Settings_Fill(colors[i]);
		CP_Graphics_DrawCircle(player[i].x, player[i].y, diameter);
	}
}
