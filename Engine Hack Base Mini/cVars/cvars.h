#ifndef __CVARS__
#define __CVARS__

#pragma once

#include <Windows.h>
#include "../locals.h"

struct CVars
{
	Vector camera_vieworg;
	Vector camera_viewangles;
	cvar_s * camera;
	cvar_s * menu;
	cvar_s * radar;
	cvar_s * radar_fovdist;
	cvar_s * menu_x;
	cvar_s * menu_y;
	cvar_s * camera_x;
	cvar_s * camera_y;
	cvar_s * camera_width;
	cvar_s * camera_height;
	cvar_s * radar_x;
	cvar_s * radar_y;
	cvar_s * radar_size;
	cvar_s * mouse_sens;

};
extern CVars cvar;

struct CFunc
{
public:
	cvar_s* reg(char *szName, char *szValue);
	void Init();
};
extern CFunc cfunc;

#endif