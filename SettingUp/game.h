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

float calculate_rotation(CP_Vector dir);

int wall_collision(CP_Vector position, CP_Vector movement_speed);

void init_player(void);

CP_Vector Vector_UP, Vector_RIGHT, Vector_DOWN, Vector_LEFT;

typedef struct players {
	CP_Vector position;
	CP_Vector direction;
	CP_Color color;
	float rotation;
	float diameter;
	float selected;
	CP_BOOL can_move[4];

} players;

