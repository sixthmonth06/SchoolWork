#pragma once

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);

void draw_player(void);

void check_for_input(void);

void movement(void);

void return_to_menu(void);

void set_color(void);

typedef struct players {
	CP_Vector position;
	CP_Vector direction;
	CP_Color color;
	float rotation;
	float diameter;

} players;

