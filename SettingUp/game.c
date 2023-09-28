#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "mainmenu.h"

#define NUM_PLAYER 3
#define DIR_NUM 4

CP_Color redColor, greenColor, blueColor, whiteColor;
CP_Color colors[NUM_PLAYER];

float diameter, width, height;
float triangle_width, triangle_height;

float rotation[DIR_NUM];

int selected_player;
int selected;
int velocity;

players player[NUM_PLAYER];
CP_Vector direction[DIR_NUM];


void Game_Init(void)
{
	CP_System_SetFrameRate(60);
	width = CP_System_GetDisplayWidth() * 0.9f;
	height = CP_System_GetDisplayHeight() * 0.85f;

	set_color();
	set_direction();
	set_rotation();
	init_player();
}


void Game_Update(void)
{
	check_for_input();
	movement();
	draw_player();
}

void Game_Exit(void)
{

}

void draw_player(void) {
	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

	for (int i = 0; i < NUM_PLAYER; i++) {
		//draw circle
		CP_Settings_Fill(player[i].color);
		CP_Graphics_DrawCircle(player[i].position.x, player[i].position.y, player[i].diameter);
		//draw triangle
		if (player[i].moving == TRUE) {
			CP_Settings_Fill(whiteColor);
			CP_Graphics_DrawTriangleAdvanced(player[i].position.x, player[i].position.y - triangle_height,
				player[i].position.x - triangle_width, player[i].position.y + triangle_height / 2,
				player[i].position.x + triangle_width, player[i].position.y + triangle_height / 2, 
				player[i].rotation);
		}
	}
}


void check_for_input(void) {
	if (CP_Input_KeyTriggered(KEY_Q)) {
		return_to_menu();
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		for (int i = NUM_PLAYER - 1; i >= 0; i--) {
			int clicked = IsCircleClicked(player[i].position.x,
				player[i].position.y, player[i].diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY());
			if (clicked == 1) {
				selected_player = i;
				selected = 1;
				for (int j = 0; j < NUM_PLAYER; j++) {
					if (j != i) {
						player[j].selected = 0;
						continue;
					}
					player[j].selected = 1;
				}
				break;
			}
		}
	}
}

void movement(void) {

	float delta = CP_System_GetDt();
	float movement_speed = velocity * delta;

	for (int i = 0; i < NUM_PLAYER; i++) {
		if (!player[i].selected) {

			CP_Vector dir = direction[player[i].direction_index];
			CP_Vector movement = CP_Vector_Scale(dir, movement_speed);
			player[i].moving = TRUE;

			for (int j = 0; j < DIR_NUM; j++) {

				int wall_collided = wall_collision(player[i].position, direction[j], movement,
					player[i].diameter, (int)width, (int)height);
				if (wall_collided) {
					player[i].can_move[j] = FALSE;
				}
				else {
					player[i].can_move[j] = TRUE;
				}
			}

			for (int k = 0; k < DIR_NUM; k++) {
				if (i != k) {
					int object_collision = AreCirclesIntersecting(player[i].position.x, player[i].position.y,
						player[i].diameter, player[k].position.x, player[k].position.y, player[k].diameter);
					if (object_collision) {
						if (player[k].position.x > player[i].position.x) {
							player[i].can_move[1] = FALSE;
						}
						else if (player[k].position.x < player[i].position.x) {
							player[i].can_move[3] = FALSE;
						}
						if (player[k].position.y < player[i].position.y) {
							player[i].can_move[0] = FALSE;
						}
						else if (player[k].position.y > player[i].position.y) {
							player[i].can_move[2] = FALSE;
						}
					}
				}
			}

			int index = player[i].direction_index;
			if (player[i].can_move[index] == TRUE) {

				player[i].position = CP_Vector_Add(player[i].position, movement);

			}
			else {
				for (int k = 0; k < 4; k++) {
					index = (index + 1) % 4 ;
					if (player[i].can_move[index] == TRUE) {
						player[i].direction_index = index;
						dir = direction[index];
						movement = CP_Vector_Scale(dir, movement_speed);
						player[i].position = CP_Vector_Add(player[i].position, movement);
						player[i].rotation = rotation[index];
						break;
					}	
				}
				player[i].moving = FALSE;
			}
		}
	}		

	if (selected) {
		int input_x = CP_Input_KeyDown(KEY_D) - CP_Input_KeyDown(KEY_A);
		int input_y = CP_Input_KeyDown(KEY_S) - CP_Input_KeyDown(KEY_W);

		if (input_x != 0) {
			player[selected_player].position.x += input_x * velocity * CP_System_GetDt();
			if (input_x > 0) {
				player[selected_player].rotation = 90;
				player[selected_player].direction_index = 1;
			}
			else {
				player[selected_player].rotation = 270;
				player[selected_player].direction_index = 3;
			}
		}
		else if (input_y != 0) {
			player[selected_player].position.y += input_y * velocity * CP_System_GetDt();
			if (input_y > 0) {
				player[selected_player].rotation = 180;
				player[selected_player].direction_index = 2;
			}
			else {
				player[selected_player].rotation = 0;
				player[selected_player].direction_index = 0;
			}
		}
		else {
			int index = player[selected_player].direction_index;
			player[selected_player].position.x += direction[index].x * velocity * CP_System_GetDt();
			player[selected_player].position.y += direction[index].y * velocity * CP_System_GetDt();
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
	whiteColor = CP_Color_Create(255, 255, 255, 255);
}

void set_direction(void) {
	direction[0] = Vector_UP = CP_Vector_Set(0, -1);
	direction[1] = Vector_RIGHT = CP_Vector_Set(1, 0);
	direction[2] = Vector_DOWN = CP_Vector_Set(0, 1);
	direction[3] = Vector_LEFT = CP_Vector_Set(-1, 0);
}

void set_rotation(void) {
	rotation[0] = 0;
	rotation[1] = 90;
	rotation[2] = 180;
	rotation[3] = 270;
}

void init_player(void) {

	diameter = 50;
	triangle_width = 20;
	triangle_height = 25;
	selected = 0;
	velocity = 200;

	for (int i = 0; i < NUM_PLAYER; i++) {
		player[i].rotation = 0;
		player[i].diameter = diameter;
		player[i].position = CP_Vector_Set(width * (i + 1) / (NUM_PLAYER + 1), height / 2);
		player[i].color = colors[i];
		player[i].direction_index = 0;
		player[i].selected = 0;
		player[i].moving = TRUE;
		for (int j = 0; j < 4; j++) {
			player[i].can_move[j] = TRUE;
		}
	}
}