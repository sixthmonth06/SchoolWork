#include "cprocessing.h"
#include <math.h>

CP_Image logo;
int alpha = 255;
double delta;
double totalTime = 0;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void splash_screen_update(void)
{
	delta = CP_System_GetDt();
	totalTime += delta;
	double time = (int)(totalTime) * 128 % 256;
	
	double elapsedTime = fmod(totalTime, 2.0);
	alpha = (int)(elapsedTime * 255 / 2.0);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo) / 1.2, CP_Image_GetHeight(logo) / 1.2, alpha);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}