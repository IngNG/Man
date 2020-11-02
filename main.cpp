#include "TXLib.h"

struct variants
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
    const int N_variants = 18;
    variants variants[N_variants], center[N_variants];
    variants[0] = {760,  100,txLoadImage("pictures/����/����.bmp"),120,598, "����"};
    variants[1] = {760,  200,txLoadImage("pictures/����/����1.bmp"),120,598, "����"};
    variants[2] = {760,  300,txLoadImage("pictures/����/����2.bmp"),120,598, "����"};

    variants[3] = {760, 100,txLoadImage("pictures/��������/f.bmp"),195,246, "����"};
    variants[4] = {760, 200,txLoadImage("pictures/��������/g.bmp"),195,246, "����"};
    variants[5] = {760, 300,txLoadImage("pictures/��������/w.bmp"),195,246, "����"};
    variants[6] = {760, 400,txLoadImage("pictures/��������/green.bmp"),195,245, "����"};
    variants[7] = {760, 500,txLoadImage("pictures/��������/������.bmp"),251,261, "����"};

    variants[8] = {760, 100,txLoadImage("pictures/�����/�����.bmp"),107,292, "���"};
    variants[9] = {760, 200,txLoadImage("pictures/�����/�����1.bmp"),107,292, "���"};

    variants[10] = {760, 100,txLoadImage("pictures/��������/������/1.bmp"),92,84, "������"};
    variants[11] = {760, 200,txLoadImage("pictures/��������/������/2.bmp"),92,84, "������"};
    variants[12] = {760, 300,txLoadImage("pictures/��������/������/3.bmp"),92,84, "������"};
    variants[13] = {760, 400,txLoadImage("pictures/��������/������/4.bmp"),95,71, "������"};
    variants[14] = {760, 500,txLoadImage("pictures/��������/������/5.bmp"),95,71, "������"};

    variants[15] = {760, 100,txLoadImage("pictures/����/1.bmp"),140,120, "����"};
    variants[16] = {760, 200,txLoadImage("pictures/����/2.bmp"),140,120, "����"};
    variants[17] = {760, 300,txLoadImage("pictures/����/1.bmp"),140,120, "����"};


    for (int i = 0; i < N_variants; i++)
    {
        variants[i].x = 760;
    }


    int n_active = -1;

    for (int i = 0; i < N_variants; i++)
    {
        center[i].category=variants[i].category;
        center[i].height=variants[i].height;
        center[i].picture=variants[i].picture;
        center[i].width=variants[i].width;
        center[i].visible = false;

        if (center[i].category == "����")
        {
            center[i].x = 111;
            center[i].y = 120;
        }

        if (center[i].category == "����")
        {
            center[i].x = 85;
            center[i].y = 290;
        }

        if (center[i].category == "���")
        {
            center[i].x = 111;
            center[i].y = 200;
        }

        if (center[i].category == "������")
        {
            center[i].x = 111;
            center[i].y = 125;
        }

        if (center[i].category == "����")
        {
            center[i].x = 140;
            center[i].y = 200;
        }




    }

    const int N_BUTTON=8;
    Button button[N_BUTTON];
    button[0] = { 10, 20,"������", "������"};
    button[1] = {180, 20,"����", "����"};
    button[2] = {350, 20,"����", ""};
    button[3] = {530, 20,"���� ", "����"};
    button[4] = { 10, 80,"����", "����"};
    button[5] = {180, 80,"���", "���"};
    button[6] = {350, 80,"������", "������"};
    button[7] = {530, 80,"���������", "���������"};

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();


        txSetColor(TX_WHITE);
        txSetFillColor(TX_BLACK);
        //���� �������� ���������


        //������ ��� ����������� �������
        txRectangle(730,20,890,770);

        for (int i=0;i<N_BUTTON;i= i+1)
            drawButton(button[i]);


        //������� ������ (���� �� �� ������ ��������)
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

    //�������� ��������
        for (int i = 0; i < N_variants; i++)
        {
            if( //�������� �����
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
            center[n_active].visible = false; //(���������)
        }

        if(txMouseButtons()==0)
            n_active = -100;


        //���� �� �������
        for (int i = 0; i < N_variants; i++)
            if(variants[i].category == vybrannaya_category &&
               txMouseX()>= variants[i].x && txMouseX()<= variants[i].x + variants[i].x + 100  &&
               txMouseY()>= variants[i].y && txMouseY()<= variants[i].y + variants[i].y + 100  &&    txMouseButtons()==1)
            {
                //��� ���1 � ����� �� ���������� ������

                center[i].visible = true;
            }


        for (int i = 0; i < N_variants; i++)
            if (center[i].visible)
                 Win32::TransparentBlt  (txDC(), center[i].x, center[i].y, center[i].width, center[i].height, center[i].picture, 0, 0, center[i].width, center[i].height, TX_WHITE);



        txSleep(10);
        txEnd();
    }
    //�� �������� �����:)
    txDeleteDC(variants[0].picture);
    return 0;
}
