#include "TXLib.h"

int main()
{
    txCreateWindow (700, 500);


    HDC h = txLoadImage("h.bmp");
    bool drawH = false;
    bool drawHr = false;


    HDC g = txLoadImage("g.bmp");
    bool drawG = false;


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txBegin();
    txClear();


    txSetColor(TX_WHITE);
    txSetFillColor(TX_BLACK);
//ìåíþ ñîçäàíèå ïåðñîíàæà


//ïàíåëü ãäå âûáèðàåòüñÿ åëåìåíò
    txRectangle(530,20,690,490);




//âñòàâêà ãîëîâû (íàäî áû íà âîëîñû çàìåíèòü)
    txRectangle(10,20,170,60);
    txDrawText (10,20,170,60, "ãîëîâà");
    if (txMouseX()>= 10 && txMouseX()<= 170 &&
        txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
         drawG=true;
    }


   if(drawG)
    {
         Win32::TransparentBlt  (txDC(), 540, 200,134,181,g,0,0,126,184,TX_WHITE);
    }


//òóò áóäåò ðàçíàÿ ôèãíÿ ââèäå ntkf îäåæäû è îáóâè
    txRectangle(180,20,340,60);
    txDrawText (180,20,340,60, "òåëî");
    if (txMouseX()>= 180 && txMouseX()<= 340 &&
    txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
          drawH=true;
    }


        if (txMouseX()>= 540 && txMouseX()<= 590 &&
    txMouseY()>= 30 && txMouseY()<= 217 &&    txMouseButtons()==1)
    {
          drawHr=true;
    }

  if(drawH)
    {
         Win32::TransparentBlt  (txDC(), 540, 30,50,187,h,0,0,50,187,TX_WHITE);
    }

  if(drawHr)
    {
         Win32::TransparentBlt  (txDC(), 100, 80,100,374,h,0,0,50,187,TX_WHITE);
    }




//óêðàøåíèÿ(àêñåñóàðû ëèáî ôîí äîïóñòèì)
    txRectangle(350,20,520,60);
    txDrawText (350,20,520,60, "óêðàøåíèÿ");
    if (txMouseX()>= 640 && txMouseX()<= 690 &&
    txMouseY()>= 10 && txMouseY()<= 40 &&    txMouseButtons()==1)
    {

    }

    txSleep(10);
    txEnd();

    }
txDeleteDC(h);
txDeleteDC(g);
return 0;
}
