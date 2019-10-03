#include "drawing.h"
#include "main.h"
#include <gl/GL.H>

#pragma warning( disable:4996 )

void CDrawing::FillArea( int x, int y, int w, int h, int r, int g, int b, int a )
{
	g_Engine.pfnTintRGBA( x, y, w, h, r, g, b, a );
}

void CDrawing::DrawBox( int x, int y, int w, int h, int linewidth, int r, int g, int b, int a )
{
	//        X						Y					W					H				R  G  B  A
	FillArea( x,					y,					w,					linewidth,		r, g, b, a ); // top
	FillArea( x + w - linewidth,	y + linewidth,		linewidth,			h - linewidth,	r, g, b, a ); // right
	FillArea( x,					y + linewidth,		linewidth,			h - linewidth,	r, g, b, a ); // left
	FillArea( x + linewidth,		y + h - linewidth,	w - linewidth * 2,	linewidth,		r, g, b, a ); // bottom
}

int CDrawing::iStringLen( const char *fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start( va_alist, fmt );
	_vsnprintf( buf, sizeof( buf ), fmt, va_alist );
	va_end( va_alist );
	int iWidth, iHeight;
	g_Engine.pfnDrawConsoleStringLen( buf, &iWidth, &iHeight );
	return iWidth;
}

int CDrawing::iStringHeight( void )
{
	int iWidth, iHeight;
	g_Engine.pfnDrawConsoleStringLen( "F", &iWidth, &iHeight );
	return iHeight;
}

void CDrawing::DrawString( int x, int y, int r, int g, int b, const char *fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start( va_alist, fmt );
	_vsnprintf( buf, sizeof( buf ), fmt, va_alist );
	va_end( va_alist );
	g_Engine.pfnDrawSetTextColor( (float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f );
	g_Engine.pfnDrawConsoleString( x, y, buf );
}

void CDrawing::DrawStringCenter( int x, int y, int r, int g, int b, const char *fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start( va_alist, fmt );
	_vsnprintf( buf, sizeof( buf ), fmt, va_alist );
	va_end( va_alist );
	int iWidth = iStringLen( "%s", buf );
	g_Engine.pfnDrawSetTextColor( (float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f );
	g_Engine.pfnDrawConsoleString( x - iWidth / 2, y, buf );
}
void CDrawing::fillrgba(GLfloat x, GLfloat y, int w, int h, int r, int g, int b, int a)
{
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub(r,g,b,a);
      glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+w,y);
        glVertex2f(x+w,y+h);
        glVertex2f(x,y+h);
      glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}

CDrawing g_Drawing;