#include "TXLib.h"

struct Head
{
    int x;
    int y;
    HDC picture;
    int height;
    int width;
    string category;
    bool visible;
};

struct Button
{
    int x;
    int y;
    const char* text;
    string category;
};

void drawButton(Button button)
{
    txRectangle(button.x, button.y, button.x+160, button.y+40);
    txDrawText (button.x, button.y, button.x+160, button.y+40, button.text);
}

bool clickButton(int x, int y)
{
    if (txMouseX()>= x && txMouseX()<= x + 160&&
        txMouseY()>= y && txMouseY()<= y + 40&&    txMouseButtons()==1)
    return true;
}

int main()
{
    txCreateWindow (700, 500);



    string vybrannaya_category = "";

    Head head[15];
    head[0] = {550,   0,txLoadImage("pictures/причёски/волосы/каре1.bmp"),119,121, "Голова"};
    head[1] = {550, 100,txLoadImage("pictures/голова 1.bmp"),622,690, "Голова"};
    head[2] = {550, 200,txLoadImage("pictures/шрек.bmp"),900,900, "Голова"};
    head[3] = {550, 300,txLoadImage("pictures/голова) 2.bmp"),540,712, "Голова"};
    head[4] = {550, 400,txLoadImage("pictures/петр 1.bmp"),215,283, "Голова"};
    head[5] = {550,  50,txLoadImage("pictures/цветы какие-то.bmp"),1238,583, "Цветы"};
    head[6] = {540, 150,txLoadImage("pictures/цветы2.bmp"),1529,664, "Цветы"};
    head[7] = {530, 250,txLoadImage("pictures/цветы3.bmp"),1835,914, "Цветы"};
    head[8] = {550,   0,txLoadImage("pictures/n/n.bmp"),670,1080, "Тело"};
    head[9] = {550,   0,txLoadImage("pictures/n/тело.bmp"),670,1080, "Тело"};
    head[10] = {550,   0,txLoadImage("pictures/n/тело2.bmp"),670,1080, "Тело"};
    head[11] = {550,   0,txLoadImage("pictures/n/тело4.bmp"),670,1080, "Тело"};

    Head head1[15];
    head1[0] = {100, 100,txLoadImage("pictures/причёски/волосы/каре1.bmp"),119,121, "Голова"};
    head1[1] = {100, 100,txLoadImage("pictures/голова 1.bmp"),622,690, "Голова"};
    head1[2] = {100, 100,txLoadImage("pictures/шрек.bmp"),900,900, "Голова"};
    head1[3] = {100, 100,txLoadImage("pictures/голова) 2.bmp"),540,712, "Голова"};
    head1[4] = {100, 100,txLoadImage("pictures/петр 1.bmp"),215,283, "Голова"};
    head1[5] = {100, 100,txLoadImage("pictures/цветы какие-то.bmp"),1238,583, "Цветы"};
    head1[6] = {100, 100,txLoadImage("pictures/цветы2.bmp"),1529,664, "Цветы"};
    head1[7] = {100, 100,txLoadImage("pictures/цветы3.bmp"),1835,914, "Цветы"};
    head1[8] = {100, 100,txLoadImage("pictures/n/n.bmp"),670,1080, "Тело"};
    head1[9] = {100, 100,txLoadImage("pictures/n/тело.bmp"),670,1080, "Тело"};
    head1[10] = {100,100,txLoadImage("pictures/n/тело2.bmp"),670,1080, "Тело"};
    head1[11] = {100,100,txLoadImage("pictures/n/тело4.bmp"),670,1080, "Тело"};



    Button button[3];
    button[0] = { 10, 20,"голова", "Голова"};
    button[1] = {180, 20,"тело", "Тело"};
    button[2] = {350, 20,"украшения", "Цветы"};


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
        for (int i=0;i<3;i= i+1)
        if (clickButton(button[i].x, button[i].y))
        {
             vybrannaya_category=button[i].category;
        }






    for (int i = 0; i < 8; i++)
        if(head[i].category == vybrannaya_category)
        {
             Win32::TransparentBlt  (txDC(), head[i].x, head[i].y, head[i].height/11, head[i].width/11, head[i].picture, 0, 0, head[i].height, head[i].width, TX_WHITE);
        }




    for (int i = 0; i < 12; i++)
        if(head[i].category == vybrannaya_category &&
           txMouseX()>= head[i].x && txMouseX()<= head[i].x + head[i].height &&
           txMouseY()>= head[i].y && txMouseY()<= head[i].y + head[i].width  &&    txMouseButtons()==1)
        {
            head1[i].visible = true;
        }


    for (int i = 0; i < 12; i++)
        if (head1[i].visible)
             Win32::TransparentBlt  (txDC(), head1[i].x, head1[i].y, head1[i].height/11, head1[i].width/11, head1[i].picture, 0, 0, head1[i].height, head1[i].width, TX_WHITE);






    txSleep(10);
    txEnd();
}
txDeleteDC(head[0].picture);
return 0;
}
