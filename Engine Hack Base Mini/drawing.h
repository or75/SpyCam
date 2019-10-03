typedef float GLfloat;

class CDrawing
{
public:
	void FillArea( int x, int y, int w, int h, int r, int g, int b, int a );
	void DrawBox( int x, int y, int w, int h, int linewidth, int r, int g, int b, int a );
	int iStringLen( const char *fmt, ... );
	int iStringHeight( void );
	void fillrgba(GLfloat x, GLfloat y, int w, int h, int r, int g, int b, int a);
	void DrawString( int x, int y, int r, int g, int b, const char *fmt, ... );
	void DrawStringCenter( int x, int y, int r, int g, int b, const char *fmt, ... );
private:
};

extern CDrawing g_Drawing;