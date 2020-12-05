#include "TXLib.h"


struct Button
{
    int x;
    int y;
    const char* text;
    string category;
};

void drawButton(Button button)
{
        Win32::RoundRect(txDC(), button.x, button.y, button.x + 130, button.y + 40, 10, 10);
        txDrawText (button.x, button.y, button.x+ 130, button.y+40, button.text);
}

bool clickButton(int x, int y)
{
    if (txMouseX()>= x && txMouseX()<= x + 160&&
        txMouseY()>= y && txMouseY()<= y + 40&&    txMouseButtons()==1)
    return true;
}

