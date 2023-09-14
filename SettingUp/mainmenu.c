#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"

CP_Font font;
CP_Color redColor;
CP_Color fontColor;
float width;
float height;

void Main_Menu_Init(void)
{
	width = CP_System_GetDisplayWidth() * 0.9;
	height = CP_System_GetDisplayHeight() * 0.85;
	CP_System_SetWindowSize(width, height);
	Setting_Font();
	redColor = CP_Color_Create(180, 0, 0, 255);
	fontColor = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void Main_Menu_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	Play_Button();
	Exit_Button();

}

void Main_Menu_Exit(void)
{

}

void Setting_Font(void) {
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(font);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(50.f);
}

void Play_Button(void) {
	CP_Settings_Fill(redColor);
	float position_x = width / 2;
	float position_y = height * 3 / 10;
	float rect_width = 200;
	float rect_height = 125;
	CP_Graphics_DrawRect(position_x, position_y, rect_width, rect_height);

	CP_Settings_Fill(fontColor);
	CP_Font_DrawText("Play", position_x, position_y);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		int clicked = IsAreaClicked(position_x, position_y, rect_width, rect_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
			if (clicked == 1) {
				CP_Engine_Terminate();
		}

	}
}

void Exit_Button(void) {
	CP_Settings_Fill(redColor);
	float position_x = width / 2;
	float position_y = height * 7 / 10;
	float rect_width = 200;
	float rect_height = 125;
	CP_Graphics_DrawRect(position_x, position_y, rect_width, rect_height);

	CP_Settings_Fill(fontColor);
	CP_Font_DrawText("Exit", position_x, position_y);

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		int clicked = IsAreaClicked(position_x, position_y, rect_width, rect_height, CP_Input_GetMouseX(), CP_Input_GetMouseY());
		if (clicked == 1) {
			CP_Engine_Terminate();
			int i = 1;
			
		}  
	}      
}
