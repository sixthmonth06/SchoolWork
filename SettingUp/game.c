#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "mainmenu.h"

#define NUM_PLAYER 3

CP_Color redColor, greenColor, blueColor, whiteColor;
CP_Color colors[NUM_PLAYER + 1];

float diameter, width, height;
float triangle_width, triangle_height;

float rotation[NUM_PLAYER];

int selected_player, selected;
int velocity;

players player[NUM_PLAYER];


void Game_Init(void)
{
	width = CP_System_GetDisplayWidth() * 0.9f;
	height = CP_System_GetDisplayHeight() * 0.85f;
	diameter = 50;

	for (int i = 0; i < NUM_PLAYER; i++) {
		player[i].rotation = 0;
		player[i].diameter = diameter;
		player[i].position = CP_Vector_Set(width * (i + 1) / (NUM_PLAYER + 1), height / 2);
	}

	triangle_width = 20;
	triangle_height = 25;

	set_color();
	
	selected = 0;
	velocity = 200;

	}
}


void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	draw_player();
	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		check_for_input();
	}

	if (CP_Input_KeyTriggered(KEY_Q)) {
		return_to_menu();
	}

	movement();

	
}

void Game_Exit(void)
{

}

void draw_player(void) {
	for (int i = 0; i < NUM_PLAYER; i++) {
		//draw circle
		CP_Settings_Fill(player[i].color);
		CP_Graphics_DrawCircle(player[i].position.x, player[i].position.y, player[i].diameter);
		//draw triangle
		CP_Settings_Fill(whiteColor);
		CP_Graphics_DrawTriangleAdvanced(player[i].position.x, player[i].position.y - triangle_height,
			player[i].position.x - triangle_width, player[i].position.y + triangle_height / 2,
			player[i].position.x + triangle_width, player[i].position.y + triangle_height / 2, rotation[i]
		);
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
			if (input_x > 0) {
				rotation[selected_player] = 90;
			}
			else {
				rotation[selected_player] = 270;
			}
		}
		else if (input_y != 0) {
			player[selected_player].y += input_y * velocity * CP_System_GetDt();
			if (input_y > 0) {
				rotation[selected_player] = 180;
			}
			else {
				rotation[selected_player] = 0;
			}
		}
	}
}

void return_to_menu(void) {

	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
}

void set_color(void) {
	colors[0] = redColor = CP_Color_Create(255, 0, 0, 255);
	colors[1] = greenColor = CP_Color_Create(0, 255, 0, 255);
	colors[2] = blueColor = CP_Color_Create(0, 0, 255, 255);
	colors[3] = whiteColor = CP_Color_Create(255, 255, 255, 255);
}