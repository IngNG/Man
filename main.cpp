///\file main.cpp
#include "TXLib.h"
#include "Button.cpp"
#include "Picture.cpp"
#include <cstdlib>
#include <cstring>
using namespace std;
#include <stdio.h>
#include <windows.h>


inline int GetFilePointer(HANDLE FileHandle)
{
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height){
    bool Success=0;
    HBITMAP OffscrBmp=NULL;
    HDC OffscrDC=NULL;
    LPBITMAPINFO lpbi=NULL;
    LPVOID lpvBits=NULL;
    HANDLE BmpFile=INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFileA(filename,
                        GENERIC_WRITE,
                        0, NULL,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
                      (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if(lpbi->bmiHeader.biClrUsed)
    PalEntries = lpbi->bmiHeader.biClrUsed;
    if(PalEntries){
    if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
        return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle (BmpFile);

    delete [] (char*)lpvBits;
    delete [] lpbi;

    DeleteDC (OffscrDC);
    DeleteObject (OffscrBmp);


    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename, HWND hwnd)
{
    HDC hDC= GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);


    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);


    HGDIOBJ old= SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);


    SelectObject(hDc, old);

    DeleteObject(hBmp);

    DeleteDC (hDc);
    ReleaseDC (hwnd, hDC);

    return ret;
}


int main()
{
    txCreateWindow (900, 780);

    txTextCursor (false);

    //выбранная категория
    string vybrannaya_category = "";

    int N_variants = 0;
    variants variants[1000], center[1000];

    N_variants = readFiles("pictures/Фон/", variants, N_variants);
    N_variants = readFiles("pictures/Тело/", variants, N_variants);
    N_variants = readFiles("pictures/Низ/", variants, N_variants);
    N_variants = readFiles("pictures/юбки/", variants, N_variants);
    N_variants = readFiles("pictures/причёски/", variants, N_variants);
    N_variants = readFiles("pictures/Верх/", variants, N_variants);
    N_variants = readFiles("pictures/Украшения/", variants, N_variants);


    ///Считаем категорию, ширину, высоту
    for (int i = 0; i < N_variants; i = i + 1)
    {
        string address = variants[i].address;
        int pos1 = address.find("/",1);
        int pos2 = address.find("/",pos1 + 1);
        int pos3 = address.find(".",pos2 + 1);

        variants[i].category = address.substr(pos1 + 1, pos2-pos1-1);
        variants[i].visible = false;

        variants[i].picture = txLoadImage(variants[i].address.c_str());
        variants[i].height = getHeight(variants[i].address.c_str());
        variants[i].width = getWidth(variants[i].address.c_str());
        variants[i].width2 = getWidth(variants[i].address.c_str());
        variants[i].x = 750 + 10 * variants[i].height / variants[i].width;
    }

    /// это "все котегории"
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
        if (variants[i].category == "Фон")
        {
            variants[i].y = Y_Fone;
            Y_Fone = Y_Fone + 100;
        }
        if (variants[i].category == "юбки")
        {
            variants[i].y = y_Yubki;
            y_Yubki = y_Yubki + 100;
        }
        if (variants[i].category == "Низ")
        {
            variants[i].y = y_Niza;
            y_Niza = y_Niza + 100;
        }

        if (variants[i].category == "причёски")
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

         if (variants[i].category == "Верх")
        {
            variants[i].y = y_Verxa;
            y_Verxa = y_Verxa + 100;
        }
        if (variants[i].category == "Украшения")
        {
            variants[i].y = Y_Ykrashenia;
            Y_Ykrashenia = Y_Ykrashenia + 100;
        }

    }



    int n_active = -1;

///где будут находится картинки когда станут видимыми
    for (int i = 0; i < N_variants; i++)
    {
        center[i].category=variants[i].category;
        center[i].height=variants[i].height;
        center[i].picture=variants[i].picture;
        center[i].address=variants[i].address;
        center[i].width=variants[i].width;
        center[i].width2=variants[i].width2;
        center[i].visible = false;

        if (center[i].category == "Фон")
        {
            center[i].x = 0;
            center[i].y = 125;
        }

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
            center[i].y = 300;
        }

        if (center[i].category == "причёски")
        {
            center[i].x = 111;
            center[i].y = 125;
        }

        if (center[i].category == "юбки")
        {
            center[i].x = 140;
            center[i].y = 300;
        }

        if (center[i].category == "Украшения")
        {
            center[i].x = 150;
            center[i].y = 320;
        }
    }


///кнопки
    const int N_BUTTON=10;
    Button button[N_BUTTON];
    button[0] = { 10, 20,"Волосы", "причёски"};
    button[1] = {150, 20,"Тело", "Тело"};
    button[2] = {290, 20,"?", ""};
    button[3] = {430, 20,"Юбки ", "юбки"};
    button[4] = {570, 20,"Верх", "Верх"};
    button[5] = { 10, 80,"Низ", "Низ"};
    button[6] = {150, 80,"Фон", "Фон"};
    button[7] = {290, 80,"Украшения", "Украшения"};

    button[8] = {430, 80, "Сохранение"};
    button[9] = {570,80,"Загрузка"};


    string PAGE = "Редактор";

    int scroll_y = 0;

///Само редактирование
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();


        if (PAGE == "Справка")
        {
            txSetFillColor(TX_BLACK);
            txSetColor(TX_WHITE);
            txClear();
            txDrawText(100, 100, 800, 500,
                "Привет \n"
                "Это конструктор человека!!\n"
                "Для то чтобы сделать человека тебе нужно только мозги и компютер!!!\n"
                "У нас есть большой выбор одежды\n"
                "Создатели: Полина Никитина,Плешаков Артём и Паша Кечуткин\n"
            );

            txDrawText(800, 600, 900, 700, "Начать!");
            if (txMouseButtons() == 1 &&
                txMouseX() >= 800 && txMouseY() >= 600 &&
                txMouseX() <= 900 && txMouseY() <= 700)
            {
                PAGE = "Редактор";
                txSleep(500);
            }
        }

        if (PAGE == "Редактор")
        {
            if (clickButton(button[2].x, button[2].y))
            {
                PAGE = "Справка";
                txSleep(500);
            }

            txSetColor(TX_WHITE);
            txSetFillColor(TX_BLACK);
    ///меню создание персонажа


    ///панель где выбираеться элемент
            txRectangle(730,20,890,700);



    ///листаем вверх и вниз
            txRectangle(850,20,890,60);
            txDrawText (850,20,890,60, "^");
            if (txMouseX()>= 830 && txMouseX()<= 890&&
                txMouseY()>= 20 && txMouseY()<= 60&&    txMouseButtons()==1)
            {
                scroll_y = scroll_y +10;
            }

            txRectangle(850,660,890,700);
            txDrawText (850,660,890,700, "v");
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

    ///картинки на панели

            ///клик на "кнопку"
            for (int i=0;i<N_BUTTON;i= i+1)
                if (clickButton(button[i].x, button[i].y))
                {
                     vybrannaya_category=button[i].category;
                     scroll_y = 0;
                }

    ///Диалог сохранение файла
            if (clickButton(button[8].x, button[8].y))
            {
                OPENFILENAME ofn;       /// common dialog box structure
                char szFile[260];       /// buffer for file name

                /// Initialize OPENFILENAME
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = txWindow();
                ofn.lpstrFile = szFile;
                /// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
                /// use the contents of szFile to initialize itself.
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "Текстовые(*.txt)\0*.txt\0";
                ofn.nFilterIndex = 0;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                /// Display the Open dialog box.

                if (GetSaveFileName(&ofn)==TRUE)
                {
                    ofstream file2(ofn.lpstrFile);
                    for (int i = 0; i < N_variants; i++)
                    {
                        if (center[i].visible == true)
                        {
                            file2 << center[i].x << endl;
                            file2 << center[i].y << endl;
                            file2 << center[i].address << endl;
                            file2 << center[i].width2 << endl;
                        }
                    }
                    file2.close();

                }

            }





    /// Диалог загрузки файла
            if (clickButton(button[9].x, button[9].y))
            {
                OPENFILENAME ofn;       /// common dialog box structure
                char szFile[260];       /// buffer for file name

                /// Initialize OPENFILENAME
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = txWindow();
                ofn.lpstrFile = szFile;
                /// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
                /// use the contents of szFile to initialize itself.
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "Текстовые(*.txt)\0*.txt\0";
                ofn.nFilterIndex = 0;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                /// Display the Open dialog box.

                if (GetOpenFileName(&ofn)==TRUE)
                {
                    for (int i = 0; i < N_variants; i++)
                    {
                        center[i].visible = false;
                    }


                    string stroka_x;
                    string stroka_y;
                    string stroka_address;
                    string width2;
                    ifstream file (ofn.lpstrFile);

                    while (file.good())
                    {
                        getline(file, stroka_x);
                        if (stroka_x.size() > 0)
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
                                    center[i].width2 = atoi(stroka_x.c_str());
                                }
                            }
                        }
                    }
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



     ///движение картинки
            for (int i = N_variants - 1; i >= 0; i--)
            {
                if( ///картинка видна
                    txMouseX()>= center[i].x && txMouseX()<= center[i].x + center[i].width &&
                    txMouseY()>= center[i].y && txMouseY()<= center[i].y + center[i].height  &&
                    txMouseButtons()==1 && n_active < 0 &&

                    center[i].visible && center[i].category != "Фон" )
                {
                    n_active = i;
                }
            }

            if (n_active >= 0)
            {
                center[n_active].x = txMouseX() - 10;
                center[n_active].y = txMouseY() - 10;
            }



            if(txMouseButtons()==0)
                n_active = -100;

        ///Клик на "вариант"
            for (int i = 0; i < N_variants; i++)
                if(variants[i].category == vybrannaya_category &&
                   txMouseX()>= variants[i].x && txMouseX()<= variants[i].x + 100  &&
                   txMouseY()>= variants[i].y - scroll_y && txMouseY()<= variants[i].y + 100 - scroll_y &&    txMouseButtons()==1)
                {
                    ///Все хед1 с такой же категорией скрыть
                    for (int k = 0; k < N_variants; k++)
                        if (center[i].category == center[k].category)
                            center[k].visible = false;

                    center[i].visible = true;
                }


            for (int i = 0; i < N_variants; i++)
                if (center[i].visible)
                     Win32::TransparentBlt  (txDC(), center[i].x, center[i].y, center[i].width2, center[i].height, center[i].picture, 0, 0, center[i].width, center[i].height, TX_WHITE);


    ///расширение и уменьшение тела
            for (int i = 0; i < N_variants; i++)
            {
                txRectangle(10,660,50,700);
                txDrawText (10,660,50,700, "-");
                if (txMouseX()>= 10 && txMouseX()<= 50&&
                    txMouseY()>= 650 && txMouseY()<= 700&&    txMouseButtons()==1 && center[i].category != "Фон")
                {
                    center[i].width2 = center[i].width2 * 0.99;
                }

                txRectangle(50,660,90,700);
                txDrawText (50,660,90,700, "+");
                if (txMouseX()>= 50 && txMouseX()<= 100&&
                    txMouseY()>= 650&& txMouseY()<= 700&&    txMouseButtons()==1 && center[i].category != "Фон")
                {
                    center[i].width2 = center[i].width2 * 1.01;
                }
            }


            if (GetAsyncKeyState(VK_SNAPSHOT))
            {
                ScreenCapture(0, 150, 700, 700, "screen.bmp", txWindow());
                txMessageBox ("Сохранено");
            }
        }


        txSleep(10);
        txEnd();
    }
    ///Да удалите вы уже остальные
     for (int i=0; i < N_variants; i = i + 1)
         txDeleteDC (variants[i].picture);
    return 0;
}
