#include "main.h"
#include "drawing.h"
#include "cVars/cvars.h"
#include "TableFont/TableFont.h"

local_s g_Local;
player_s g_Player[33];
gNoFlash NoFlash;
std::vector<entity_s> g_Entity;

static bool Init = false;
static bool spyc = false;
static bool spye = true;
static int  spyi = 0;

SCREENINFO g_Screen;
extern HINSTANCE hInst;

#pragma warning(disable:4996)
#pragma warning(disable:4804)
#pragma warning(disable:4552)
#pragma warning(disable:4244)

void HookEngine( void )
{
	memcpy( &g_Engine, (LPVOID)g_pEngine, sizeof( cl_enginefunc_t ) );
	g_pEngine->pfnHookUserMsg = pfnHookUserMsg;
}

void HookStudio( void )
{
	memcpy( &g_Studio, (LPVOID)g_pStudio, sizeof( engine_studio_api_t ) );
}

static float cl_righthand_fix = 1.0f;

void InitHack()
{
	g_Screen.iSize = sizeof( SCREENINFO );
	g_Engine.pfnGetScreenInfo( &g_Screen );

	char *HackPrint = "SpyCam By _or_75";
	g_Engine.Con_Printf( "\n\n\t\t\t\t\t\t\t%s\n\n", HackPrint );

	NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x17);
	if ( IsBadReadPtr(NoFlash.pScreenFade,sizeof(screenfade_t)) )
		NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x18);

	// Dll Protection
	HackBase::HideModule(hInst);
	HackBase::HideModuleXta(hInst);
	HackBase::HideModuleFromPEB(hInst);
	HackBase::RemovePeHeader((DWORD)hInst);
	HackBase::DestroyModuleHeader(hInst);
}
void HUD_Frame( double time )
{
	if( !Init )
	{
		cfunc.Init();
		InitHack();
		Init = true;
	}
	g_Client.HUD_Frame( time );
}
bool bPathFree( float *pflFrom, float *pflTo )
{
	if( !pflFrom || !pflTo ) { return false; }
	pmtrace_t pTrace;
	g_Engine.pEventAPI->EV_SetTraceHull( 2 );
	g_Engine.pEventAPI->EV_PlayerTrace( pflFrom, pflTo, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &pTrace );
	return ( pTrace.fraction == 1.0f );
}
bool isValidEnt(cl_entity_s *ent)
{
	if( (ent->index!=g_Local.iIndex) && !(ent->curstate.effects & EF_NODRAW) && ent->player && (ent->model->name !=0 || ent->model->name !="")  && !(ent->curstate.messagenum < g_Engine.GetLocalPlayer()->curstate.messagenum))
		return true;
	else
		return false;
}
void HUD_Redraw( float time, int intermission )
{
	g_Client.HUD_Redraw( time, intermission );

	cl_entity_t *pLocal = g_Engine.GetLocalPlayer();
	g_Local.iIndex = pLocal->index;

	// обновление инфы об игроках
	for(int i=1; i<33; i++)
	{
		player_s& p = g_Player[i];
		cl_entity_s *ent = g_Engine.GetEntityByIndex(i);
		g_Engine.pfnGetPlayerInfo(i,&g_Player[i].Info);	 // получаем инфу
		g_Player[i].bAlive = ent && !(ent->curstate.effects & EF_NODRAW) && ent->player && ent->curstate.movetype !=6 && ent->curstate.movetype != 0;
		g_Player[i].bVisible = (bPathFree(g_Local.vEye, Vector(ent->origin[0],ent->origin[1],ent->origin[2]))); // виден ли игрок?
		g_Player[i].bUpdated = isValidEnt(ent);
		g_Player[i].iTeam = g_PlayerTeam[i]; // команда игрока
		g_Player[i].vOrigin = ent->origin; // положения игрока в пространстве
		g_Player[i].fDistance = floor(sqrt(POW(abs(p.vOrigin.x - g_Local.vOrigin.x)) + POW(abs(p.vOrigin.y - g_Local.vOrigin.y)) + POW(abs(p.vOrigin.z - g_Local.vOrigin.z)))-32); // дистанция до игрока
	}

	g_Engine.Cvar_SetValue("cl_righthand",1.0f);

	if(NoFlash.pScreenFade->fadeEnd > g_Engine.GetClientTime())
	{
		NoFlash.FadeEnd = NoFlash.pScreenFade->fadeEnd;
		NoFlash.pScreenFade->fadealpha = 255;
	}

	if(NoFlash.FadeEnd > g_Engine.GetClientTime())
		NoFlash.Flashed = (NoFlash.FadeEnd - g_Engine.GetClientTime()) * NoFlash.pScreenFade->fadeSpeed;
	else
		NoFlash.Flashed = 0.0f;
	
	if(NoFlash.Flashed > 255.0f) NoFlash.Flashed = 255.0f;
	if(NoFlash.Flashed < 0.0f) NoFlash.Flashed = 0.0f;
	int Alpha = NoFlash.Flashed;

	BYTE r,g,b;

	if ( spyc )
	{
		#define CENTER_TEXT (49+g_Screen.iWidth/6+2)/1.7

		if ( g_Player[spyi].iTeam == 1 )
			r = 255,g = 64,b = 64; 
		else
			r = 0,g = 164,b = 255; 

		g_Drawing.fillrgba(49,35,g_Screen.iWidth/6+2,14,64,64,64,255-Alpha);
		g_Drawing.fillrgba(49,g_Screen.iHeight/6+50,g_Screen.iWidth/6+2,15,64,64,64,255-Alpha);
		g_Drawing.fillrgba(47,35,2,g_Screen.iHeight/6+30,64,64,64,255-Alpha);
		g_Drawing.fillrgba(49+g_Screen.iWidth/6+2,35,2,g_Screen.iHeight/6+30,64,64,64,255-Alpha);

		gFont.drawString(true,CENTER_TEXT,40,255,255,0,"spycam by _or_75: %i",Alpha);		
		gFont.drawString(true,CENTER_TEXT,g_Screen.iHeight/6+54,r,g,b,"%s",g_Player[spyi].Info.name);
		gFont.drawString(false,54,g_Screen.iHeight/6+54,0,255,0,"%i",static_cast<int>(g_Player[spyi].fDistance>=0?g_Player[spyi].fDistance:0));
	}
}
void HUD_PlayerMove( struct playermove_s *ppmove, int server )
{
	g_Client.HUD_PlayerMove( ppmove, server );

	g_Local.vOrigin = ppmove->origin;
	g_Engine.pEventAPI->EV_LocalPlayerViewheight(g_Local.vEye);
	g_Local.vEye = g_Local.vEye + ppmove->origin;	
}
void update_min_player()
{
	if ( g_Local.bAlive )
	{
		float fOldDistance = 9999999999.9f;
		for(int iIndex = 1;iIndex < 33;iIndex++)
		if( g_Player[iIndex].fDistance <= fOldDistance && iIndex != g_Local.iIndex && g_Player[iIndex].bAlive )
		{
			fOldDistance = g_Player[iIndex].fDistance;
			spyi = iIndex;
		}
	}
}
void V_CalcRefdef( struct ref_params_s *pparams )
{
	g_Client.V_CalcRefdef(pparams);
	
	if(pparams->nextView == 0 && !pparams->paused)
	{
		spyc = false;
		if(g_pEngine->GetLocalPlayer()->curstate.solid != SOLID_NOT)
		{
			pparams->nextView = 1;
			pparams->onlyClientDraw = 0;
		}
	}
	else if(pparams->nextView == 1 && !pparams->paused)
	{
		if(g_pEngine->GetLocalPlayer()->curstate.solid != SOLID_NOT)
		{
			spyc = true;

			update_min_player();

			pparams->nextView = 0;
			pparams->onlyClientDraw = 0;

			if ( spye || spyc)
			{
				pparams->viewport[0] = 50;
				pparams->viewport[1] = 50;
				pparams->viewport[2] = g_Screen.iWidth/6;
				pparams->viewport[3] = g_Screen.iHeight/6;
			}
			else
			{
				pparams->viewport[0] = 0;
				pparams->viewport[1] = 0;
				pparams->viewport[2] = 0;
				pparams->viewport[3] = 0;
			}

			cl_entity_t* ent = g_Engine.GetEntityByIndex(spyi);
			
			if ( ent->player && g_Player[ent->index].bUpdated )
			{
				VectorCopy(ent->origin, pparams->vieworg);
				VectorCopy(ent->angles, pparams->viewangles);
			}
			else
			{
				ent = g_Engine.GetLocalPlayer();
				spyi = g_Local.iIndex;
				VectorCopy(ent->origin, pparams->vieworg);
				VectorCopy(ent->angles, pparams->viewangles);
			}
		}
	}
}
void CL_CreateMove( float frametime, struct usercmd_s *cmd, int active )
{
	g_Client.CL_CreateMove( frametime, cmd, active );
	cl_entity_s *LocalEnt = g_Engine.GetLocalPlayer();
	g_Local.bAlive = LocalEnt && !(LocalEnt->curstate.effects & EF_NODRAW) && LocalEnt->player && LocalEnt->curstate.movetype !=6 && LocalEnt->curstate.movetype != 0;
}
int HUD_GetStudioModelInterface( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio )
{
	HookOpenGL();
	return g_Client.HUD_GetStudioModelInterface( version, ppinterface, pstudio );
}
int HUD_Key_Event( int down, int keynum, const char *pszCurrentBinding )
{
	 int iRet = g_Client.HUD_Key_Event( down, keynum, pszCurrentBinding );
	 return iRet;
}
void HookClient( void )
{
	memcpy( &g_Client, (LPVOID)g_pClient, sizeof( cl_clientfunc_t ) );
	g_pClient->HUD_Frame = HUD_Frame;
	g_pClient->HUD_Redraw = HUD_Redraw;
	g_pClient->HUD_PlayerMove = HUD_PlayerMove;
	g_pClient->V_CalcRefdef = V_CalcRefdef;
	g_pClient->CL_CreateMove = CL_CreateMove;
	g_pClient->HUD_GetStudioModelInterface = HUD_GetStudioModelInterface;
	g_pClient->HUD_Key_Event = HUD_Key_Event;
}