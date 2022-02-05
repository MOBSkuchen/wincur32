#include <Windows.h>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace std::chrono_literals;
using namespace std::this_thread;

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

string getCurrentTime() {
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::stringstream sstm;
    sstm << std::ctime(&end_time);
    std::string result = sstm.str();
    return result;
}

void setCursor(int pos) {
    HBITMAP b = (HBITMAP)LoadImage(0, "C:\\AWC\\img.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HCURSOR hcursor = CreateCursorBMP(b, RGB(255,255,255), 0,0);
    SetSystemCursor(hcursor,pos);
}

int splitFrames(std::string file,std::chrono::milliseconds fps,int size,int cur) {
    cv::Mat img;
    cv::VideoCapture cap = cv::VideoCapture(file);
    while (true) {bool suc = cap.read(img);
        if (suc != true) {
            return 0;
        }
        if (size != -1) {
            cv::resize(img,img,Size(size,size));
        }
        cv::imwrite("C:\\AWC\\img.bmp", img);
        setCursor(cur);
        sleep_for(fps);
    }
}

void applyVideoCursor(std::string file,chrono::milliseconds delay,int size,int cur) {
    while (true) {
        splitFrames(file,delay,size,cur);
    }
}

Mat getVideoFrame(string file) {
    cv::Mat img;
    cv::VideoCapture cap = cv::VideoCapture(file);
    while (true) {
        cap.read(img);
        return img;
    }
}

int main() {
    string file = "C:\\AWC\\video.mp4"; // Target video
    int delay = 30; // Delay between frames (milliseconds)
    int SetSize = 128; // limit the size of the cursor
    int cur = 32512; // Cursor type
    if (SetSize == -1) {
        int x = getVideoFrame(file).cols;
        int y = getVideoFrame(file).rows;
        stringstream arss;
        arss << "AutoResize : OFF (" << x << "x" << y << ")\n";
        string ars = arss.str();
        std::cout << "Open Animated Cursors | SUPRIME LLC : (c) all rights reserved\n" << "Using Video-File : " + file + "\n" << ars << "Delay : " << delay << "ms (~" << 1000/delay << " fps)\n";
    } else {
        stringstream arss;
        arss << "AutoResize : ON (" << SetSize << "x" << SetSize << ")\n";
        string ars = arss.str();
        std::cout << "Open Animated Cursors | SUPRIME LLC : (c) all rights reserved\n" << "Using Video-File : " + file + "\n" << ars << "Delay : " << delay << "ms (~" << 1000/delay << " fps)\n";
    }
    printf("\33[2K\r");
    printf("\33[2K\r");
    auto delay_MS = std::chrono::milliseconds(delay);
    applyVideoCursor(file,delay_MS,SetSize,cur);
    return 0;
}
