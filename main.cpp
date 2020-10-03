#include "TXLib.h"

struct Button
{
    int x;
    int y;
    const char* text;

    void drawButton()
    {
        txSetColor(TX_BLACK, 4);
        txSetFillColor(TX_YELLOW);
        txSelectFont("Comic Sans MS", 40);
        txRectangle(x, y, x + 200, y + 100);
        txDrawText (x, y, x + 200, y + 100, text);
    }
};

void drawButton(Button btn)
{
    txSetColor(TX_BLACK, 4);
    txSetFillColor(TX_YELLOW);
    txSelectFont("Comic Sans MS", 40);
    txRectangle(btn.x, btn.y, btn.x + 200, btn.y + 100);
    txDrawText (btn.x, btn.y, btn.x + 200, btn.y + 100, btn.text);
}



struct Picture
{
    int x;
    int y;
    HDC image;
};


void drawPicture(Picture pct)
{
    Win32::TransparentBlt(txDC(), pct.x, pct.y, 100, 100, pct.image, 0, 0, 100, 100, TX_WHITE);
}
void drawPicture2(Picture pct)
{
    Win32::TransparentBlt(txDC(), pct.x, pct.y, 100, 100, pct.image, 0, 0, 400, 300, TX_WHITE);
}


int main()
{
    txCreateWindow(1200,800);


    Picture leftPictures[10];
    leftPictures[0] = {100, 100, txLoadImage("Pictures/���/���1.bmp")};
    leftPictures[1] = {100, 250, txLoadImage("Pictures/���/���2.bmp")};
    leftPictures[2] = {100, 400, txLoadImage("Pictures/���/���3.bmp")};
    leftPictures[3] = {100, 100, txLoadImage("Pictures/������/������1.bmp")};
    leftPictures[4] = {100, 250, txLoadImage("Pictures/������/������2.bmp")};
    leftPictures[5] = {100, 400, txLoadImage("Pictures/������/������3.bmp")};



    Button btn1 = {100, 0, "���� ����"};
    Button btn2 = {300, 0, "����"};
    Button btn3 = {500, 0, "��������"};
    Button btn4 = {700, 0, "�����"};

    bool nosVisible = false;
    bool volosyVisible = false;

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetFillColor(TX_YELLOW);
        txClear();


        drawButton(btn1);
        drawButton(btn2);
        drawButton(btn3);
        drawButton(btn4);

        //����
        if (txMouseButtons() == 1 &&
            txMouseX() >= btn2.x &&
            txMouseX() <= btn2.x + 200 &&
            txMouseY() >= btn2.y &&
            txMouseY() <= btn2.y + 100)
        {
            nosVisible = true;
            volosyVisible = false;
        }

        if (nosVisible)
        {
            drawPicture(leftPictures[0]);
            drawPicture(leftPictures[1]);
            drawPicture(leftPictures[2]);
        }
        if (volosyVisible)
        {
            drawPicture2(leftPictures[3]);
            drawPicture2(leftPictures[4]);
            drawPicture2(leftPictures[5]);
        }


        //������
        if (txMouseButtons() == 1 &&
            txMouseX() >= btn3.x &&
            txMouseX() <= btn3.x + 200 &&
            txMouseY() >= btn3.y &&
            txMouseY() <= btn3.y + 100)
        {
            nosVisible = false;
            volosyVisible = true;
        }

        txSleep(10);
        txEnd();
    }


    return 0;
}
