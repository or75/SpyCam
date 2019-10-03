#include "locals.h"

// Engine by _or_75, don't edit this file

int pfnHookUserMsg( char *szMsgName, pfnUserMsgHook pfn );
void HookClient( void );
void HookEngine( void );
void HookStudio( void );
void HookOpenGL( void );
void SetupHooks( void );
int AddCommand( char *cmd_name, void (*function)(void) );
cvar_t* RegisterVariable ( char *szName, char *szValue, int flags );

#pragma comment(lib,"HackBase.lib")

namespace HackBase
{
	class COffsets
	{
	private:
		DWORD ClBase, ClSize;
		DWORD HwBase, HwSize, HwEnd;

	public:
		DWORD SpeedPtr;
		DWORD SoundPtr;
		bool Initialize(void);
		void *SpeedHackPtr(void);
		void *ClientFuncs(void);
		void *EngineFuncs(void);
		DWORD EngineStudio(cl_clientfunc_t *g_pClient);
		DWORD ClientBase(void);
	};
	extern COffsets gOffsets;

	void HideModuleFromPEB(HINSTANCE hInstance);
	void RemovePeHeader(DWORD ModuleBase);
	void HideModule(HANDLE hModule);
	void HideModuleXta(HINSTANCE hModule);
	bool DestroyModuleHeader(HMODULE hModule);

	BOOL __comparemem(const UCHAR *buff1, const UCHAR *buff2, UINT size);
	ULONG __findmemoryclone(const ULONG start, const ULONG end, const ULONG clone, UINT size);
	ULONG __findreference(const ULONG start, const ULONG end, const ULONG address);
}

#define AddCommandInitalize(); \
	int AddCommand( char *cmd_name, void (*function)(void) ){return 0;}

#define RegisterVariableInitalize(); \
	cvar_t* RegisterVariable ( char *szName, char *szValue, int flags ) \
	{ \
		cvar_t* pResult = g_Engine.pfnGetCvarPointer(szName); \
		if(pResult != NULL) \
			return pResult; \
		return g_Engine.pfnRegisterVariable(szName, szValue, flags); \
	}

#define SetupHookInitialize(); \
	while(!HackBase::gOffsets.Initialize()) \
		Sleep(500);	\
	Sleep(2000);

#define HookFunction(); \
	g_pClient = (cl_clientfunc_t*)HackBase::gOffsets.ClientFuncs(); \
	g_pEngine = (cl_enginefunc_t*)HackBase::gOffsets.EngineFuncs(); \
	g_pStudio = (engine_studio_api_t*)HackBase::gOffsets.EngineStudio(g_pClient);

#define CopyHook(); \
	if(!g_pClient || !g_pEngine || !g_pStudio) return; \
	RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t)); \
	RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t)); \
	RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));

#define HookInitalize(); \
	g_pEngine->pfnHookUserMsg = &pfnHookUserMsg; \
	g_pEngine->pfnAddCommand = &AddCommand; \
	g_pEngine->pfnRegisterVariable = &RegisterVariable; \
	g_Client.Initialize(g_pEngine, CLDLL_INTERFACE_VERSION); \
	g_Client.HUD_Init(); \
	g_pEngine->pfnHookUserMsg = g_Engine.pfnHookUserMsg; \
	g_pEngine->pfnAddCommand = g_Engine.pfnAddCommand; \
	g_pEngine->pfnRegisterVariable = g_Engine.pfnRegisterVariable;