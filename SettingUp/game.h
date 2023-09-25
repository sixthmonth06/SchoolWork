#pragma once

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);

void draw_player(void);

void check_for_input(void);

void movement(void);

void return_to_menu(void);

void set_color(void);

void set_direction(void);

void set_rotation(void);

void init_player(void);

int choose_new_direction_index(void);

CP_Vector Vector_UP, Vector_RIGHT, Vector_DOWN, Vector_LEFT;

typedef struct players {
	CP_Vector position;
	int direction_index;
	CP_Color color;
	float rotation;
	float diameter;
	float selected;
	CP_BOOL can_move[4];
	CP_BOOL moving;

} players;

