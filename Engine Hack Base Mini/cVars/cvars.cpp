#include "cvars.h"

CVars cvar;
CFunc cfunc;

cvar_s* CFunc::reg(char *szName, char *szValue)
{
	return g_Engine.pfnRegisterVariable(szName,szValue,0);
}

void CFunc::Init()
{
	cvar.menu = reg("menu","0");
	cvar.camera = reg("camera","0");
	cvar.radar = reg("radar","0");
	cvar.radar_fovdist = reg("radar_fovdist","0");
	cvar.menu_x = reg("menu_x","10");
	cvar.menu_y = reg("menu_y","10");
	cvar.camera_x = reg("camera_x","0");
	cvar.camera_y = reg("camera_y","0");
	cvar.camera_width = reg("camera_width","0");
	cvar.camera_height = reg("camera_height","0");
	cvar.radar_x = reg("radar_x","0");
	cvar.radar_y = reg("radar_y","0");
	cvar.radar_size = reg("radar_size","10");
	cvar.mouse_sens = reg("mouse_sens","7");
}