#include <Windows.h>

static HCURSOR CreateCursorBMP(HBITMAP hSourceBitmap,
                               COLORREF clrTransparent,
                               HBITMAP hAndMaskBitmap,
                               HBITMAP hXorMaskBitmap) {
    HDC hDC = ::GetDC(NULL);
    HDC hMainDC = ::CreateCompatibleDC(hDC);
    HDC hAndMaskDC = ::CreateCompatibleDC(hDC);
    HDC hXorMaskDC = ::CreateCompatibleDC(hDC);

    BITMAP bm;
    ::GetObject(hSourceBitmap, sizeof(BITMAP), &bm);


    hAndMaskBitmap = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);
    hXorMaskBitmap = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);

    HBITMAP hOldMainBitmap = (HBITMAP) ::SelectObject(hMainDC, hSourceBitmap);
    HBITMAP hOldAndMaskBitmap = (HBITMAP) ::SelectObject(hAndMaskDC,
                                                         hAndMaskBitmap);
    HBITMAP hOldXorMaskBitmap = (HBITMAP) ::SelectObject(hXorMaskDC,
                                                         hXorMaskBitmap);

    COLORREF MainBitPixel;
    for (int x = 0; x < bm.bmWidth; ++x) {
        for (int y = 0; y < bm.bmHeight; ++y) {
            MainBitPixel = ::GetPixel(hMainDC, x, y);
            if (MainBitPixel == clrTransparent) {
                ::SetPixel(hAndMaskDC, x, y, RGB(255, 255, 255));
                ::SetPixel(hXorMaskDC, x, y, RGB(0, 0, 0));
            } else {
                ::SetPixel(hAndMaskDC, x, y, RGB(0, 0, 0));
                ::SetPixel(hXorMaskDC, x, y, MainBitPixel);
            }
        }
    }

    ::SelectObject(hMainDC, hOldMainBitmap);
    ::SelectObject(hAndMaskDC, hOldAndMaskBitmap);
    ::SelectObject(hXorMaskDC, hOldXorMaskBitmap);

    ::DeleteDC(hXorMaskDC);
    ::DeleteDC(hAndMaskDC);
    ::DeleteDC(hMainDC);

    ::ReleaseDC(NULL, hDC);

    ICONINFO iconinfo = {0};
    iconinfo.fIcon        = FALSE;
    iconinfo.xHotspot       = 0;
    iconinfo.yHotspot       = 0;
    iconinfo.hbmMask        = hAndMaskBitmap;
    iconinfo.hbmColor       = hXorMaskBitmap;
    HCURSOR hCursor = ::CreateIconIndirect(&iconinfo);
    return hCursor;
}
