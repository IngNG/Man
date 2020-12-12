///\file Picture.cpp
#include "TXLib.h"
#include <fstream>
#include <dirent.h>
using namespace std;

///��������� "��������"
struct variants
{
    string address;
    string category;
    ///��������
    HDC picture;
    /// ������ ��������
    int width;
    int width2;
    /// ������ ��������
    int height;

    bool visible;
    ///  ��� " ��������� x � y"
    int x;
    int y;
};

/// ������������� "������"
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

/// ������������� "������"
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
     ///* print all the files and directories within directory */
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
