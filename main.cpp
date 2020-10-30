#include "TXLib.h"

struct variants
{
    HDC picture;
    int width;
    int height;
    string category;
    bool visible;
    int x;
    int y;
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
    const int N_variants = 18;
    variants variants[N_variants], center[N_variants];
    variants[0] = {txLoadImage("pictures/Тело/тело.bmp"),120,598, "Тело"};
    variants[1] = {txLoadImage("pictures/Тело/тело1.bmp"),120,598, "Тело"};
    variants[2] = {txLoadImage("pictures/Тело/тело2.bmp"),120,598, "Тело"};

    variants[3] = {txLoadImage("pictures/курточка/f.bmp"),195,246, "Верх"};
    variants[4] = {txLoadImage("pictures/курточка/g.bmp"),195,246, "Верх"};
    variants[5] = {txLoadImage("pictures/курточка/w.bmp"),195,246, "Верх"};
    variants[6] = {txLoadImage("pictures/курточка/green.bmp"),195,245, "Верх"};
    variants[7] = {txLoadImage("pictures/кофточка/желтая.bmp"),251,261, "Верх"};

    variants[8] = {txLoadImage("pictures/штаны/штаны.bmp"),107,292, "Низ"};
    variants[9] = {txLoadImage("pictures/штаны/штаны1.bmp"),107,292, "Низ"};

    variants[10] = {txLoadImage("pictures/причёски/волосы/1.bmp"),92,84, "Голова"};
    variants[11] = {txLoadImage("pictures/причёски/волосы/2.bmp"),92,84, "Голова"};
    variants[12] = {txLoadImage("pictures/причёски/волосы/3.bmp"),92,84, "Голова"};
    variants[13] = {txLoadImage("pictures/причёски/волосы/4.bmp"),95,71, "Голова"};
    variants[14] = {txLoadImage("pictures/причёски/волосы/5.bmp"),95,71, "Голова"};

    variants[15] = {txLoadImage("pictures/юбки/1.bmp"),140,120, "Юбки"};
    variants[16] = {txLoadImage("pictures/юбки/2.bmp"),140,120, "Юбки"};
    variants[17] = {txLoadImage("pictures/юбки/1.bmp"),140,120, "Юбки"};

    //Цикл, в котором считаются координаты, ширина, высота

    int y_Yubki = 100;
    int y_Niza = 100;
    int y_Golova = 100;
    int y_Volosi = 100;
    int y_Telo = 100;

    for (int i = 0; i < N_variants; i++)
    {
        variants[i].x = 760;
        if (variants[i].category == "Юбки")
        {
            variants[i].y = y_Yubki;
            y_Yubki = y_Yubki + 100;
        }
        if (variants[i].category == "Низ")
        {
            variants[i].y = y_Niza;
            y_Niza = y_Niza + 100;
        }

        if (variants[i].category == "Голова")
        {
            variants[i].y = y_Golova;
            y_Golova = y_Golova + 100;
        }

        if (variants[i].category == "Волосы")
        {
            variants[i].y = y_Volosi;
            y_Volosi = y_Volosi + 100;
        }

        if (variants[i].category == "Тело")
        {
            variants[i].y = y_Telo;
            y_Telo = y_Telo + 100;
        }
    }


    int n_active = -1;

    for (int i = 0; i < N_variants; i++)
    {
        center[i].category=variants[i].category;
        center[i].height=variants[i].height;
        center[i].picture=variants[i].picture;
        center[i].width=variants[i].width;
        center[i].visible = false;

        if (center[i].category == "Тело")
        {
            center[i].x = 111;
            center[i].y = 120;
        }

        if (center[i].category == "Верх")
        {
            center[i].x = 85;
            center[i].y = 290;
        }

        if (center[i].category == "Низ")
        {
            center[i].x = 111;
            center[i].y = 200;
        }

        if (center[i].category == "Голова")
        {
            center[i].x = 111;
            center[i].y = 125;
        }

        if (center[i].category == "Юбки")
        {
            center[i].x = 140;
            center[i].y = 200;
        }




    }

    const int N_BUTTON=8;
    Button button[N_BUTTON];
    button[0] = { 10, 20,"Волосы", "Голова"};
    button[1] = {180, 20,"Тело", "Тело"};
    button[2] = {350, 20,"Лицо", ""};
    button[3] = {530, 20,"Юбки ", "Юбки"};
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

        for (int i = 0; i < N_variants; i++)
            if (variants[i].category == vybrannaya_category)
            {
                 Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y, 100, 100, variants[i].picture, 0, 0, variants[i].width,variants[i].height,  TX_WHITE);
            }

    //движение картинки
        for (int i = 0; i < N_variants; i++)
        {
            if( //картинка видна
                txMouseX()>= center[i].x && txMouseX()<= center[i].x + center[i].width &&
                txMouseY()>= center[i].y && txMouseY()<= center[i].y + center[i].height  &&
                txMouseButtons()==1 && n_active < 0 &&
                center[i].visible)
            {
                n_active = i;
            }
        }

        if (n_active >= 0)
        {
            center[n_active].x = txMouseX() - 10;
            center[n_active].y = txMouseY() - 10;
        }


        if (n_active >= 0 && txMouseX() < 10)
        {
            center[n_active].visible = false; //(невидемый)
        }

        if(txMouseButtons()==0)
            n_active = -100;


        //Клик на вариант
        for (int i = 0; i < N_variants; i++)
            if(variants[i].category == vybrannaya_category &&
               txMouseX()>= variants[i].x && txMouseX()<= variants[i].x + variants[i].height &&
               txMouseY()>= variants[i].y && txMouseY()<= variants[i].y + variants[i].width  &&    txMouseButtons()==1)
            {
                //Все хед1 с такой же категорией скрыть

                center[i].visible = true;
            }


        for (int i = 0; i < N_variants; i++)
            if (center[i].visible)
                 Win32::TransparentBlt  (txDC(), center[i].x, center[i].y, center[i].width, center[i].height, center[i].picture, 0, 0, center[i].width, center[i].height, TX_WHITE);



        txSleep(10);
        txEnd();
    }
    //Их побольше одной:)
    txDeleteDC(variants[0].picture);
    return 0;
}
