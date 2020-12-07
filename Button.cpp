#include "TXLib.h"


///Структура "кнопки"
struct Button
{
    ///  это " кординаты x и y"
    int x;
    int y;
    const char* text;
    ///Структура "котегории"
    string category;
};

///Рисование "кнопки"
void drawButton(Button button)
{
    Win32::RoundRect(txDC(), button.x, button.y, button.x + 130, button.y + 40, 10, 10);
    txDrawText (button.x, button.y, button.x+ 130, button.y+40, button.text);
}

///Нажатие "конпки"
bool clickButton(int x, int y)
{
    if (txMouseX()>= x && txMouseX()<= x + 160&&
        txMouseY()>= y && txMouseY()<= y + 40&&    txMouseButtons()==1)
    return true;
}
