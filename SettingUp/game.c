#include "cprocessing.h"
#include "utils.h"
#include "game.h"

#define NUM_PLAYER 3

CP_Color redColor, greenColor, blueColor, whiteColor;
CP_Color colors[NUM_PLAYER + 1];

float diameter, width, height;

int selected_player, selected;
int velocity;

CP_Vector player[NUM_PLAYER];


void Game_Init(void)
{
	width = CP_System_GetDisplayWidth() * 0.9f;
	height = CP_System_GetDisplayHeight() * 0.85f;

	redColor = CP_Color_Create(255, 0, 0, 255);
	greenColor = CP_Color_Create(0, 255, 0, 255);
	blueColor = CP_Color_Create(0, 0, 255, 255);
	whiteColor = CP_Color_Create(255, 255, 255, 255);

	colors[0] = redColor;
	colors[1] = greenColor;
	colors[2] = blueColor;
	colors[3] = whiteColor;
	
	diameter = 50;
	selected = 0;
	velocity = 200;

	for (int i = 0; i < NUM_PLAYER; i++) {
		player[i].x = width * (i + 1) / (NUM_PLAYER + 1);
		player[i].y = height / 2;
	}
}


void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	draw_player();
	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		check_for_input();
	}
	movement();
	
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

void check_for_input(void) {
	for (int i = NUM_PLAYER - 1; i >= 0; i--) {
		int clicked = IsCircleClicked(player[i].x,
			player[i].y, diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (clicked == 1) {
			selected_player = i;
			selected = 1;
			break;
		}
	}
}

void movement(void) {
	if (selected) {
		int input_x = CP_Input_KeyDown(KEY_D) - CP_Input_KeyDown(KEY_A);
		int input_y = CP_Input_KeyDown(KEY_S) - CP_Input_KeyDown(KEY_W);

		if (input_x != 0) {
			player[selected_player].x += input_x * velocity * CP_System_GetDt();
		}
		else if (input_y != 0) {
			player[selected_player].y += input_y * velocity * CP_System_GetDt();
		}
	}
}

