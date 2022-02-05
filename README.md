# wincur32
Windows Cursor API

The file "wincur32.cpp" uses the directory "C:/AWC" as a tmp storage, make sure to NOT delete this directory.

The variable "SetSize" is automatically set to 128, change to -1 for native size.

The variable "delay" is automatically set to 30, you can change it like this: delay = 1000/fps;

The varibale "cur" is automatically set to 32512, (https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setsystemcursor?redirectedfrom=MSDN)

OCR_APPSTARTING   32650   Standard arrow and small hourglass
OCR_NORMAL        32512   Standard arrow
OCR_CROSS         32515   Crosshair
OCR_HAND          32649   Hand
OCR_HELP 	        32651   Arrow and question mark
OCR_IBEAM 	      32513   I-beam
OCR_NO 		        32648   Slashed circle
OCR_SIZEALL 	    32646   Four-pointed arrow pointing north, south, east, and west
OCR_SIZENESW   	  32643   Double-pointed arrow pointing northeast and southwest
OCR_SIZENS 	      32645   Double-pointed arrow pointing north and south
OCR_SIZENWSE   	  32642   Double-pointed arrow pointing northwest and southeast
OCR_SIZEWE 	      32644   Double-pointed arrow pointing west and east
OCR_UP 		        32516   Vertical arrow
OCR_WAIT 	        32514   Hourglass
