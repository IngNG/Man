#include "TXLib.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include <dirent.h>
#include <stdio.h>
#include <windows.h>


struct variants
{
    string address;
    string category;
    HDC picture;
    int width;
    int height;
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
        Win32::RoundRect(txDC(), button.x, button.y, button.x + 130, button.y + 40, 10, 10);
        txDrawText (button.x, button.y, button.x+ 130, button.y+40, button.text);
}

bool clickButton(int x, int y)
{
    if (txMouseX()>= x && txMouseX()<= x + 160&&
        txMouseY()>= y && txMouseY()<= y + 40&&    txMouseButtons()==1)
    return true;
}


//���� ������ � ������ �������
int getWidth(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int width;
    memcpy(&width, &header[18], sizeof(width));
    return width;
}

int getHeight(const char* address)
{
    char header[54];
    ifstream bmp;
    bmp.open(address, ios::in | ios::binary);
    bmp.read(header, 54);
    int height;
    memcpy(&height, &header[22], sizeof(height));
    return height;
}



int readFiles(const char* address, variants* variants, int N_variants)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (address)) != NULL) {
     /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            string s = ent->d_name;
            s = address + s;
            if(s.find (".bmp") != -1 )
            {
                 variants[N_variants] = {s};
                 N_variants = N_variants + 1;
            }
         }
        closedir (dir);
     }
     return  N_variants;
}


int main()
{
    txCreateWindow (900, 780);

    txTextCursor (false);

    string vybrannaya_category = "";

    int N_variants = 0;
    variants variants[1000], center[1000];

    N_variants = readFiles("pictures/���/", variants, N_variants);
    N_variants = readFiles("pictures/����/", variants, N_variants);
    N_variants = readFiles("pictures/���/", variants, N_variants);
    N_variants = readFiles("pictures/����/", variants, N_variants);
    N_variants = readFiles("pictures/��������/", variants, N_variants);
    N_variants = readFiles("pictures/����/", variants, N_variants);
    N_variants = readFiles("pictures/���������/", variants, N_variants);


//������� ���������, ������, ������
    for (int i = 0; i < N_variants; i = i + 1)
    {
        string address = variants[i].address;
        int pos1 = address.find("/",1);
        int pos2 = address.find("/",pos1 + 1);
        int pos3 = address.find(".",pos2 + 1);

        variants[i].category = address.substr(pos1 + 1, pos2-pos1-1);
        variants[i].visible = false;

        variants[i].x = 760;
        variants[i].picture = txLoadImage(variants[i].address.c_str());
        variants[i].height = getHeight(variants[i].address.c_str());
        variants[i].width = getWidth(variants[i].address.c_str());
    }


    int Y_Fone = 50;
    int y_Yubki = 50;
    int y_Niza = 50;
    int y_Golova = 50;
    int y_Volosi = 50;
    int y_Telo = 50;
    int y_Verxa = 50;
    int Y_Ykrashenia = 50;


    for (int i = 0; i < N_variants; i++)
    {
        if (variants[i].category == "���")
        {
            variants[i].y = Y_Fone;
            Y_Fone = Y_Fone + 100;
        }
        if (variants[i].category == "����")
        {
            variants[i].y = y_Yubki;
            y_Yubki = y_Yubki + 100;
        }
        if (variants[i].category == "���")
        {
            variants[i].y = y_Niza;
            y_Niza = y_Niza + 100;
        }

        if (variants[i].category == "��������")
        {
            variants[i].y = y_Golova;
            y_Golova = y_Golova + 100;
        }

        if (variants[i].category == "������")
        {
            variants[i].y = y_Volosi;
            y_Volosi = y_Volosi + 100;
        }

        if (variants[i].category == "����")
        {
            variants[i].y = y_Telo;
            y_Telo = y_Telo + 100;
        }

         if (variants[i].category == "����")
        {
            variants[i].y = y_Verxa;
            y_Verxa = y_Verxa + 100;
        }
        if (variants[i].category == "���������")
        {
            variants[i].y = Y_Ykrashenia;
            Y_Ykrashenia = Y_Ykrashenia + 100;
        }

    }



    int n_active = -1;

//��� ����� ��������� �������� ����� ������ ��������
    for (int i = 0; i < N_variants; i++)
    {
        center[i].category=variants[i].category;
        center[i].height=variants[i].height;
        center[i].picture=variants[i].picture;
        center[i].address=variants[i].address;
        center[i].width=variants[i].width;
        center[i].visible = false;

        if (center[i].category == "���")
        {
            center[i].x = 0;
            center[i].y = 125;
        }

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
            center[i].y = 300;
        }

        if (center[i].category == "��������")
        {
            center[i].x = 111;
            center[i].y = 125;
        }

        if (center[i].category == "����")
        {
            center[i].x = 140;
            center[i].y = 300;
        }

        if (center[i].category == "���������")
        {
            center[i].x = 150;
            center[i].y = 320;
        }
    }


//������
    const int N_BUTTON=10;
    Button button[N_BUTTON];
    button[0] = { 10, 20,"������", "��������"};
    button[1] = {150, 20,"����", "����"};
    button[2] = {290, 20,"����", ""};
    button[3] = {430, 20,"���� ", "����"};
    button[4] = {570, 20,"����", "����"};
    button[5] = { 10, 80,"���", "���"};
    button[6] = {150, 80,"���", "���"};
    button[7] = {290, 80,"���������", "���������"};

    button[8] = {430, 80, "����������"};
    button[9] = {570,80,"��������"};

    string stroka_x;
    string stroka_y;
    string stroka_address;

    ifstream file ("1.txt");

    while (file.good())
    {
        getline(file, stroka_x);
        if (stroka_x.size() > 1)
        {
            getline(file, stroka_y);
            getline(file, stroka_address);

            for (int i = 0; i < N_variants; i++)
            {
                if (stroka_address == center[i].address)
                {
                    center[i].x = atoi(stroka_x.c_str());
                    center[i].y = atoi(stroka_y.c_str());
                    center[i].visible = true;
                }
            }

        }
    }





    int scroll_y = 0;
//���� ��������������
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();


        txSetColor(TX_WHITE);
        txSetFillColor(TX_BLACK);
//���� �������� ���������


 //������ ��� ����������� �������
        txRectangle(730,20,890,700);




        txRectangle(850,20,890,60);

        if (txMouseX()>= 830 && txMouseX()<= 890&&
            txMouseY()>= 20 && txMouseY()<= 60&&    txMouseButtons()==1)
        {
            scroll_y = scroll_y +10;
        }

        txRectangle(850,670,890,700);
        if (txMouseX()>= 850 && txMouseX()<= 890&&
            txMouseY()>= 660 && txMouseY()<= 700&&    txMouseButtons()==1)
        {
            scroll_y = scroll_y -10;
        }



        for (int i=0;i<N_BUTTON;i= i+1)
        {
            txSetColor(TX_WHITE);
            if (vybrannaya_category==button[i].category)
            {
                txSetColor(TX_WHITE, 8);
            }

            drawButton(button[i]);
        }

//�������� �� ������
        for (int i=0;i<N_BUTTON;i= i+1)
            if (clickButton(button[i].x, button[i].y))
            {
                 vybrannaya_category=button[i].category;
            }

        //������ ���������� �����
        if (clickButton(button[8].x, button[8].y))
        {
            OPENFILENAME ofn;       // common dialog box structure
            char szFile[260];       // buffer for file name

            // Initialize OPENFILENAME
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = txWindow();
            ofn.lpstrFile = szFile;
            // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
            // use the contents of szFile to initialize itself.
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "Excel files 2003(*.xls)\0*.xls\0Excel files 2007(*.xlsx)\0*.xlsx\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // Display the Open dialog box.

            if (GetOpenFileName(&ofn)==TRUE)
            {


            }
        }



        for (int i = 0; i < N_variants; i++)
            if (variants[i].category == vybrannaya_category)
            {
                if(variants[i].width > variants[i].height)
                    Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y - scroll_y , 100 , 100*variants[i].height/variants[i].width, variants[i].picture, 0, 0, variants[i].width,variants[i].height,  TX_WHITE);
                else
                    Win32::TransparentBlt  (txDC(), variants[i].x, variants[i].y - scroll_y , 100 * variants[i].width/variants[i].height, 100, variants[i].picture, 0, 0, variants[i].width,variants[i].height,  TX_WHITE);
            }



 //�������� ��������
        for (int i = N_variants - 1; i >= 0; i--)
        {
            if( //�������� �����
                txMouseX()>= center[i].x && txMouseX()<= center[i].x + center[i].width &&
                txMouseY()>= center[i].y && txMouseY()<= center[i].y + center[i].height  &&
                txMouseButtons()==1 && n_active < 0 &&

                center[i].visible && center[i].category != "���" )
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
               txMouseX()>= variants[i].x && txMouseX()<= variants[i].x + 100  &&
               txMouseY()>= variants[i].y - scroll_y && txMouseY()<= variants[i].y + 100 - scroll_y &&    txMouseButtons()==1)
            {
                //��� ���1 � ����� �� ���������� ������
                for (int k = 0; k < N_variants; k++)
                    if (center[i].category == center[k].category)
                        center[k].visible = false;

                center[i].visible = true;
            }


        for (int i = 0; i < N_variants; i++)
            if (center[i].visible)
                 Win32::TransparentBlt  (txDC(), center[i].x, center[i].y, center[i].width, center[i].height, center[i].picture, 0, 0, center[i].width, center[i].height, TX_WHITE);


        txRectangle(10,670,100,700);
        for (int i = 0; i < N_variants; i++)
        if (txMouseX()>= 10 && txMouseX()<= 670&&
            txMouseY()>= 100 && txMouseY()<=700&&    txMouseButtons()==1)
        {
            center[i].visible = false;
        }



        txSleep(10);
        txEnd();
    }
    //�� �������� �����:)    ������� �������� ����!!!
    txDeleteDC(variants[0].picture);


//���������� � ����
    ofstream file2("1.txt");
    for (int i = 0; i < N_variants; i++)
    {
        if (center[i].visible == true)
        {
            file2 << center[i].x << endl;
            file2 << center[i].y << endl;
            file2 << center[i].address << endl;
        }
    }
    file2.close();


    return 0;
}
