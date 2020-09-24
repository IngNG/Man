#include "TXLib.h"

//сохран€й картинки в папки!!!

struct Head
{
    int x;
    int y;
    HDC picture;
    int height;
    int width;
};
int main()
{
    txCreateWindow (700, 500);


    bool drawH = false;
    bool drawHr = false;
    bool drawG = false;

    Head head[5];
    head[0] = {550,   0,txLoadImage("g.bmp"),/* введЄшь сюда длинну и высоту */};
    head[1] = {550, 100,txLoadImage("голова 1.bmp")};
    head[2] = {550, 200,txLoadImage("шрек.bmp")};
    head[3] = {550, 300,txLoadImage("голова) 2.bmp")};
    head[4] = {550, 400,txLoadImage("петр 1.bmp")};


    HDC hr = txLoadImage("цветы какие-то.bmp");

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txBegin();
    txClear();


    txSetColor(TX_WHITE);
    txSetFillColor(TX_BLACK);
//меню создание персонажа


//панель где выбираетьс€ елемент
    txRectangle(530,20,690,490);




//вставка головы (надо бы на волосы заменить)
    txRectangle(10,20,170,60);
    txDrawText (10,20,170,60, "голова");
    if (txMouseX()>= 10 && txMouseX()<= 170 &&
        txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
         drawG=true;
         drawH=false;
         drawHr=false;
    }


//тут будет разна€ фигн€ ввиде ntkf одежды и обуви
    txRectangle(180,20,340,60);
    txDrawText (180,20,340,60, "тело");
    if (txMouseX()>= 180 && txMouseX()<= 340 &&
    txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
          drawH=true;
         drawG=false;
         drawHr=false;
    }


//украшени€(аксесуары либо фон допустим)
    txRectangle(350,20,520,60);
    txDrawText (350,20,520,60, "украшени€");
    if (txMouseX()>= 350 && txMouseX()<= 520 &&
        txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
          drawHr=true;
    }
//golovy

   if(drawG)
    {
        for (int i = 0; i < 5; i++)
         Win32::TransparentBlt  (txDC(), head[i].x, head[i].y,134,100,head[i].picture,0,0,640,792,TX_WHITE);
    }



  if(drawH)
    {
         Win32::TransparentBlt  (txDC(), 540, 30,50,187,h,0,0,50,187,TX_WHITE);
    }

  if(drawHr)
    {
         Win32::TransparentBlt  (txDC(), 550, 000,134,100,hr,0,0,1238,583,TX_WHITE);
    }

    txSleep(10);
    txEnd();

    }
txDeleteDC(h);
txDeleteDC(g);
txDeleteDC(hr);
return 0;
}

// € сдохну с этим проектом
