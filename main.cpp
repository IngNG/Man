#include "TXLib.h"

struct Head
{
    int x;
    int y;
    HDC picture;
    int height;
    int width;
    string category;
};

struct Button
{
    int x;
    int y;
    const char* text
};

void drawButton(Button button)
{
    txRectangle(button.x, button.y, button.x+160, button.y+40);
    txDrawText (button.x, button.y, button.x+160, button.y+40, button.text);
}

bool clickButton()
{
    txMouseX()>= x && txMouseX()<= x &&
    txMouseY()>= y && txMouseY()<= y &&    txMouseButtons()==1
}

int main()
{
    txCreateWindow (700, 500);



    string vybrannaya_category = "";

    Head head[10];
    head[0] = {550,   0,txLoadImage("pictures/g.bmp"),120,150, "Голова"};
    head[1] = {550, 100,txLoadImage("pictures/голова 1.bmp"),622,690, "Голова"};
    head[2] = {550, 200,txLoadImage("pictures/шрек.bmp"),900,900, "Голова"};
    head[3] = {550, 300,txLoadImage("pictures/голова) 2.bmp"),540,712, "Голова"};
    head[4] = {550, 400,txLoadImage("pictures/петр 1.bmp"),215,283, "Голова"};
    head[5] = {550,  50,txLoadImage("pictures/цветы какие-то.bmp"),1238,583, "Цветы"};
    head[6] = {540, 150,txLoadImage("pictures/цветы2.bmp"),1529,664, "Цветы"};
    head[7] = {530, 250,txLoadImage("pictures/цветы3.bmp"),1835,914, "Цветы"};



    Button button[3];
    button[0] = { 10, 20,"голова"};
    button[1] = {180, 20,"тело"};
    button[2] = {350, 20,"украшения"};


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
    txBegin();
    txClear();


    txSetColor(TX_WHITE);
    txSetFillColor(TX_BLACK);
//меню создание персонажа


//панель где выбираеться елемент
    txRectangle(530,20,690,490);

    for (int i=0;i<3;i= i+1)
        drawButton(button[i]);


//вставка головы (надо бы на волосы заменить)
    if (txMouseX()>= 10 && txMouseX()<= 170 &&
        txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
         vybrannaya_category="Голова";
    }


//тут будет разная фигня ввиде тела одежды и обуви
    if (txMouseX()>= 180 && txMouseX()<= 340 &&
    txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {

    }


//украшения(аксесуары либо фон допустим)
    if (txMouseX()>= 350 && txMouseX()<= 520 &&
        txMouseY()>= 20 && txMouseY()<= 60 &&    txMouseButtons()==1)
    {
          vybrannaya_category="Цветы";
    }

    for (int i = 0; i < 8; i++)
        if(head[i].category == vybrannaya_category)
        {
             Win32::TransparentBlt  (txDC(), head[i].x, head[i].y, head[i].height/11, head[i].width/11, head[i].picture, 0, 0, head[i].height, head[i].width, TX_WHITE);
        }

    txSleep(10);
    txEnd();
}
txDeleteDC(head[0].picture);
return 0;
}
