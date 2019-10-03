#include "main.h"
#include "poly.h"

HackBase::COffsets HackBase::gOffsets;

char g_szHackDir[256];

cl_clientfunc_t *g_pClient = NULL;
cl_clientfunc_t g_Client;
cl_enginefunc_t *g_pEngine = NULL;
cl_enginefunc_t g_Engine;
engine_studio_api_t *g_pStudio = NULL;
engine_studio_api_t g_Studio;

AddCommandInitalize();
RegisterVariableInitalize();

void SetupHooks(void)
{
	PolyBase* Poly;
	PolyBase1 P1;
	PolyBase2 P2;
	PolyBase3 P3;
	PolyBase4 P4;
	PolyBase5 P5;
	PolyBase6 P6;
	PolyBase7 P7;
	
	Poly = &P1;
	P1.load();

	Poly = &P2;
	P2.load();

	Poly = &P3;
	P3.load();

	Poly = &P4;
	P4.load();

	Poly = &P5;
	P5.load();

	Poly = &P6;
	P6.load();

	Poly = &P7;
	P7.load();
}

BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		hInst = hModule;

		PolyBase* Poly;
		PolyBase8 P8;
		PolyBase9 P9;
		PolyBase10 P10;

		Poly = &P8;
		P8.load();

		Poly = &P9;
		P9.load();

		Poly = &P10;
		P10.load();
	}
	return TRUE;
}