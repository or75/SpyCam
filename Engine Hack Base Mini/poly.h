#pragma once

// Polymerphic Code by _or_75

HINSTANCE hInst;

class PolyBase
{
public:
	virtual void load() = 0;
};
class PolyBase1 : public PolyBase
{
public:
	void load();
};
class PolyBase2 : public PolyBase
{
public:
	void load();
};
class PolyBase3 : public PolyBase
{
public:
	void load();
};
class PolyBase4 : public PolyBase
{
public:
	void load();
};
class PolyBase5 : public PolyBase
{
public:
	void load();
};
class PolyBase6 : public PolyBase
{
public:
	void load();
};
class PolyBase7 : public PolyBase
{
public:
	void load();
};
class PolyBase8 : public PolyBase
{
public:
	void load();
};
class PolyBase9 : public PolyBase
{
public:
	void load();
};
class PolyBase10 : public PolyBase
{
public:
	void load();
};

void PolyBase1::load()
{
	SetupHookInitialize();
}
void PolyBase2::load()
{
	HookFunction();
}
void PolyBase3::load()
{
	CopyHook();
}
void PolyBase4::load()
{
	HookClient();
}
void PolyBase5::load()
{
	HookInitalize();
}
void PolyBase6::load()
{
	HookEngine();
}
void PolyBase7::load()
{
	HookStudio();
}
void PolyBase8::load()
{
	GetModuleFileName( (HMODULE)hInst, g_szHackDir, 256 );
}
void PolyBase9::load()
{
	char *p = g_szHackDir + strlen( g_szHackDir ); \
	while( p >= g_szHackDir && *p != '\\' ) { --p; } \
	p[1] = '\0'; \
}
void PolyBase10::load()
{
	CreateThread( NULL, NULL, (LPTHREAD_START_ROUTINE)SetupHooks, NULL, NULL, NULL );
}