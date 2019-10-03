#include "main.h"

#pragma warning( disable: 4996 )
#pragma warning( disable: 4244 )

pfnUserMsgHook pTeamInfo = NULL;
pfnUserMsgHook pDeathMsg = NULL;
pfnUserMsgHook pCurWeapon = NULL;
pfnUserMsgHook pSetFOV = NULL;
pfnUserMsgHook pHudText = NULL;

int g_PlayerTeam[33];

int TeamInfo( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );
	int iIndex = READ_BYTE();
	char *szTeam = READ_STRING();
	_strlwr( szTeam );
	if( !strcmp( szTeam, "terrorist" ) )
	{
		g_Player[iIndex].iTeam = 1;
		if( iIndex == g_Local.iIndex ) { g_Local.iTeam = 1; }
		g_PlayerTeam[iIndex] = 1;
	}
	else if( !strcmp( szTeam, "ct" ) )
	{
		g_Player[iIndex].iTeam = 2;
		if( iIndex == g_Local.iIndex ) { g_Local.iTeam = 2; }
		g_PlayerTeam[iIndex]=2;
	}
	else
	{
		g_Player[iIndex].iTeam = 0;
		if( iIndex == g_Local.iIndex ) { g_Local.iTeam = 0; }
		g_PlayerTeam[iIndex] = 0;
	}
	return (*pTeamInfo)( pszName, iSize, pbuf );
}

int DeathMsg( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );
	int iKiller = READ_BYTE();
	int iVictim = READ_BYTE();
	int iHeadshot = READ_BYTE();
	char* pszWeaponName = READ_STRING();
	g_Player[iVictim].bAlive = false;
	g_Player[iVictim].bVisible = false;
	if( iVictim == g_Local.iIndex ) { g_Local.bAlive = false; }
	return (*pDeathMsg)( pszName, iSize, pbuf );
}

int CurWeapon( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );
	int iState = READ_BYTE();
	int iWeaponID = READ_CHAR();
	int iClip = READ_CHAR();
	if( iState )
	{
		g_Local.iClip = iClip;
		g_Local.iWeaponID = iWeaponID;
	}
	return (*pCurWeapon)( pszName, iSize, pbuf );
}

int SetFOV( const char *pszName, int iSize, void *pbuf )
{
	BEGIN_READ( pbuf, iSize );
	g_Local.iFOV = READ_BYTE();
	if( !g_Local.iFOV ) { g_Local.iFOV = 90; }
	return (*pSetFOV)( pszName, iSize, pbuf );
}

int pfnHookUserMsg( char *szMsgName, pfnUserMsgHook pfn )
{
	#define HOOK_MSG(name) \
	if( !strcmp( szMsgName, #name ) ) \
	{ \
		p##name = pfn; \
		return g_Engine.pfnHookUserMsg( szMsgName, ##name ); \
	}

	HOOK_MSG(TeamInfo)
	HOOK_MSG(DeathMsg)
	HOOK_MSG(CurWeapon)
	HOOK_MSG(SetFOV)

	return g_Engine.pfnHookUserMsg( szMsgName, pfn );
}