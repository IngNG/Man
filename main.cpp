#include "TXLib.h"

struct Head
{
    int x;
    int y;
    HDC picture;
    int width;
    int height;
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
    txCreateWindow (900, 780);



    string vybrannaya_category = "";
    const int N_HEAD=12;
    Head head[N_HEAD], head1[N_HEAD];
    head[0] = {760,  100,txLoadImage("pictures/n/n.bmp"),120,598, "Тело"};
    head[1] = {760,  200,txLoadImage("pictures/n/тело.bmp"),120,598, "Тело"};
    head[2] = {760,  300,txLoadImage("pictures/n/тело1.bmp"),120,598, "Тело"};

    head[3] =  {760, 100,txLoadImage("pictures/курточка/f.bmp"),195,246, "Верх"};
    head[4] =  {760, 200,txLoadImage("pictures/курточка/g.bmp"),195,246, "Верх"};
    head[5] =  {760, 300,txLoadImage("pictures/курточка/w.bmp"),195,246, "Верх"};
    head[6] =  {760, 400,txLoadImage("pictures/кофточка/желтая.bmp"),251,261, "Верх"};

    head[7] =  {760, 100,txLoadImage("pictures/штаны/штаны.bmp"),107,292, "Низ"};
    head[8] =  {760, 200,txLoadImage("pictures/штаны/штаны1.bmp"),107,292, "Низ"};


    head[9] =  {760, 100,txLoadImage("pictures/причёски/волосы/1.bmp"),92,84, "Голова"};
    head[10] =  {760, 200,txLoadImage("pictures/причёски/волосы/2.bmp"),92,84, "Голова"};
    head[11] =  {760, 300,txLoadImage("pictures/причёски/волосы/3.bmp"),92,84, "Голова"};

    int n_active = -1;

    for (int i = 0; i < N_HEAD; i++)
    {
        head1[i].category=head[i].category;
        head1[i].height=head[i].height;
        head1[i].picture=head[i].picture;
        head1[i].width=head[i].width;
        head1[i].visible = false;

        if (head1[i].category == "Тело")
        {
            head1[i].x = 111;
            head1[i].y = 120;
        }

           if (head1[i].category == "Верх")
        {
            head1[i].x = 85;
            head1[i].y = 290;
        }

            if (head1[i].category == "Низ")
        {
            head1[i].x = 111;
            head1[i].y = 200;
        }

            if (head1[i].category == "Голова")
        {
            head1[i].x = 111;
            head1[i].y = 125;
        }

    }

    const int N_BUTTON=8;
    Button button[N_BUTTON];
    button[0] = { 10, 20,"Волосы", "Голова"};
    button[1] = {180, 20,"Тело", "Тело"};
    button[2] = {350, 20,"Лицо", ""};
    button[3] = {530, 20," ", ""};
    button[4] = { 10, 80,"Верх", "Верх"};
    button[5] = {180, 80,"Низ", "Низ"};
    button[6] = {350, 80,"Куртка", "Куртка"};
    button[7] = {530, 80,"Украшения", "Украшения"};

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();


        txSetColor(TX_WHITE);
        txSetFillColor(TX_BLACK);
    //меню создание персонажа


    //панель где выбираеться елемент
        txRectangle(730,20,890,770);

        for (int i=0;i<N_BUTTON;i= i+1)
            drawButton(button[i]);


    //вставка головы (надо бы на волосы заменить)
        for (int i=0;i<N_BUTTON;i= i+1)
        if (clickButton(button[i].x, button[i].y))
        {
             vybrannaya_category=button[i].category;
        }

    for (int i = 0; i < N_HEAD; i++)
        if(head[i].category == vybrannaya_category)
        {
             Win32::TransparentBlt  (txDC(), head[i].x, head[i].y, 100, 100, head[i].picture, 0, 0, head[i].width,head[i].height,  TX_WHITE);
        }

//движение картинки
    for(int i=0; i < N_HEAD; i++)
    {
        if( //картинка видна
            txMouseX()>= head1[i].x && txMouseX()<= head1[i].x + head1[i].width &&
            txMouseY()>= head1[i].y && txMouseY()<= head1[i].y + head1[i].height  &&
            txMouseButtons()==1 && n_active < 0 &&
            head1[i].visible
          )


          {
             n_active = i;
          }
    }

    if(n_active >= 0)
    {
        head1[n_active].x = txMouseX() - 10;
        head1[n_active].y = txMouseY() - 10;
    }

    if(txMouseButtons()==0)
        n_active = -100;


    //Клик на вариант
    for (int i = 0; i < N_HEAD; i++)
        if(head[i].category == vybrannaya_category &&
           txMouseX()>= head[i].x && txMouseX()<= head[i].x + head[i].height &&
           txMouseY()>= head[i].y && txMouseY()<= head[i].y + head[i].width  &&    txMouseButtons()==1)
        {
            //Все хед1 с такой же категорией скрыть

            head1[i].visible = true;
        }


    for (int i = 0; i < N_HEAD; i++)
        if (head1[i].visible)
             Win32::TransparentBlt  (txDC(), head1[i].x, head1[i].y, head1[i].width, head1[i].height, head1[i].picture, 0, 0, head1[i].width, head1[i].height, TX_WHITE);



    txSleep(10);
    txEnd();
}
txDeleteDC(head[0].picture);
return 0;
}
