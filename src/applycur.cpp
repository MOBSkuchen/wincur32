#include <Windows.h>

void setCursor(int pos, const CHAR *filename="PATH/TO/FILE") {
    unsigned long transparent = RGB(255, 255, 255);
    HBITMAP b = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HCURSOR hcursor = CreateCursorBMP(b, transparent, 0,0);
    SetSystemCursor(hcursor,pos);
}
