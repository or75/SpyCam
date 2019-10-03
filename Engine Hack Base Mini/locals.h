#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

#include "ValveSDK/engine/wrect.h"
#include "ValveSDK/engine/cl_dll.h"
#include "ValveSDK/engine/r_studioint.h"
#include "ValveSDK/engine/cl_entity.h"
#include "ValveSDK/misc/com_model.h"
#include "ValveSDK/engine/triangleapi.h"
#include "ValveSDK/engine/pmtrace.h"
#include "ValveSDK/engine/pm_defs.h"
#include "ValveSDK/engine/pm_info.h"
#include "ValveSDK/common/ref_params.h"
#include "ValveSDK/common/studio_event.h"
#include "ValveSDK/common/net_api.h"
#include "ValveSDK/common/r_efx.h"
#include "ValveSDK/engine/cvardef.h"
#include "ValveSDK/engine/util_vector.h"
#include "ValveSDK/misc/parsemsg.h"
#include "ValveSDK/engine/studio.h"
#include "ValveSDK/engine/event_args.h"
#include "ValveSDK/engine/event_flags.h"
#include "ValveSDK/common/event_api.h"
#include "ValveSDK/common/screenfade.h"
#include "ValveSDK/engine/keydefs.h"

typedef struct cl_clientfuncs_s
{
	int ( *Initialize ) ( cl_enginefunc_t *pEnginefuncs, int iVersion );
	int ( *HUD_Init ) ( void );
	int ( *HUD_VidInit ) ( void );
	void ( *HUD_Redraw ) ( float time, int intermission );
	int ( *HUD_UpdateClientData ) ( client_data_t *pcldata, float flTime );
	int ( *HUD_Reset ) ( void );
	void ( *HUD_PlayerMove ) ( struct playermove_s *ppmove, int server );
	void ( *HUD_PlayerMoveInit ) ( struct playermove_s *ppmove );
	char ( *HUD_PlayerMoveTexture ) ( char *name );
	void ( *IN_ActivateMouse ) ( void );
	void ( *IN_DeactivateMouse ) ( void );
	void ( *IN_MouseEvent ) ( int mstate );
	void ( *IN_ClearStates ) ( void );
	void ( *IN_Accumulate ) ( void );
	void ( *CL_CreateMove ) ( float frametime, struct usercmd_s *cmd, int active );
	int ( *CL_IsThirdPerson ) ( void );
	void ( *CL_CameraOffset ) ( float *ofs );
	struct kbutton_s *( *KB_Find ) ( const char *name );
	void ( *CAM_Think ) ( void );
	void ( *V_CalcRefdef ) ( struct ref_params_s *pparams );
	int ( *HUD_AddEntity ) ( int type, struct cl_entity_s *ent, const char *modelname );
	void ( *HUD_CreateEntities ) ( void );
	void ( *HUD_DrawNormalTriangles ) ( void );
	void ( *HUD_DrawTransparentTriangles ) ( void );
	void ( *HUD_StudioEvent ) ( const struct mstudioevent_s *event, const struct cl_entity_s *entity );
	void ( *HUD_PostRunCmd ) ( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
	void ( *HUD_Shutdown ) ( void );
	void ( *HUD_TxferLocalOverrides ) ( struct entity_state_s *state, const struct clientdata_s *client );
	void ( *HUD_ProcessPlayerState ) ( struct entity_state_s *dst, const struct entity_state_s *src );
	void ( *HUD_TxferPredictionData ) ( struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd );
	void ( *Demo_ReadBuffer ) ( int size, unsigned char *buffer );
	int ( *HUD_ConnectionlessPacket ) ( struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
	int ( *HUD_GetHullBounds ) ( int hullnumber, float *mins, float *maxs );
	void ( *HUD_Frame ) ( double time );
	int ( *HUD_Key_Event ) ( int down, int keynum, const char *pszCurrentBinding );
	void ( *HUD_TempEntUpdate ) ( double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int ( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void ( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
	struct cl_entity_s *( *HUD_GetUserEntity ) ( int index );
	int ( *HUD_VoiceStatus ) ( int entindex, qboolean bTalking );
	int ( *HUD_DirectorMessage ) ( unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags );
	int ( *HUD_GetStudioModelInterface ) ( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio );
	void ( *HUD_CHATINPUTPOSITION_FUNCTION ) ( int *x, int *y );
	int ( *HUD_GETPLAYERTEAM_FUNCTION ) ( int iplayer );
	void ( *CLIENTFACTORY ) ( void );
} cl_clientfunc_t;

extern cl_clientfunc_t *g_pClient;
extern cl_clientfunc_t g_Client;
extern cl_enginefunc_t *g_pEngine;
extern cl_enginefunc_t g_Engine;
extern engine_studio_api_t *g_pStudio;
extern engine_studio_api_t g_Studio;
extern SCREENINFO g_Screen;
extern char g_szHackDir[256];

#define M_PI 3.14159265358979323846
#define POW(x) ((x)*(x))
#define VectorLengthSquared(v) ((v)[0]*(v)[0]+(v)[1]*(v)[1]+(v)[2]*(v)[2])
#define VectorDistance(a,b) sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define VectorLength(a) sqrt(POW((a)[0])+POW((a)[1])+POW((a)[2]))
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define Square(a) ((a)*(a))

#define WEAPONLIST_P228			1
#define	WEAPONLIST_UNKNOWN1		2
#define	WEAPONLIST_SCOUT		3
#define	WEAPONLIST_HEGRENADE	4
#define	WEAPONLIST_XM1014		5
#define	WEAPONLIST_C4			6
#define	WEAPONLIST_MAC10		7
#define	WEAPONLIST_AUG			8
#define	WEAPONLIST_SMOKEGRENADE	9
#define	WEAPONLIST_ELITE		10
#define	WEAPONLIST_FIVESEVEN	11
#define	WEAPONLIST_UMP45		12
#define	WEAPONLIST_SG550		13
#define	WEAPONLIST_GALIL		14
#define	WEAPONLIST_FAMAS		15
#define	WEAPONLIST_USP			16
#define	WEAPONLIST_GLOCK18		17
#define	WEAPONLIST_AWP			18
#define	WEAPONLIST_MP5			19
#define	WEAPONLIST_M249			20
#define	WEAPONLIST_M3			21
#define	WEAPONLIST_M4A1			22
#define	WEAPONLIST_TMP			23
#define	WEAPONLIST_G3SG1		24
#define	WEAPONLIST_FLASHBANG	25
#define	WEAPONLIST_DEAGLE		26
#define	WEAPONLIST_SG552		27
#define	WEAPONLIST_AK47			28
#define	WEAPONLIST_KNIFE		29
#define	WEAPONLIST_P90			30

/* ------------------Начало Структур Информации об Игроках----------------------------------- */

struct local_s
{
	int iIndex;
	int iTeam;
	int iClip;
	int iWeaponID;
	int iFOV;
	bool bAlive;
	Vector vOrigin;
	Vector vEye;
};
extern local_s g_Local;

struct gNoFlash
{
public:
	float Flashed;
	float FadeEnd;
	screenfade_t* pScreenFade;
};

struct player_s
{
	int iTeam;
	bool bAlive;
	bool bVisible;
	bool bUpdated;
	float fDistance;
	vec3_t vOrigin;
	hud_player_info_t Info;
};
extern player_s g_Player[33];

struct entity_s
{
	int iImportant;
	vec3_t vOrigin;
	char szName[32];
};
extern std::vector<entity_s> g_Entity;

extern char g_szHackDir[256];

inline std::string szDirFile( char* pszName )
{
	string szRet = g_szHackDir;
	return ( szRet + pszName );
}

extern int g_PlayerTeam[33];


/* ------------------Конец Структур Информации об Игроках----------------------------------- */