#include "music.h"
#include <iostream>

using namespace std;

int main() {
    listLibrary Library;
    listPlaylist Playlist;

    createListLibrary(Library);
    createListPlaylist(Playlist);

    laguDummy(Library);

    int menuUtama = 1;

    system("cls");
    cout << "=========================================\n";
    cout << "                                         \n";
    cout << " SELAMAT DATANG DI APLIKASI PEMUTAR MUSIK\n";
    cout << "                                         \n";
    cout << "=========================================\n";
    system("pause");

    while (menuUtama != 0) {
        system("cls");
        cout << "===== MENU UTAMA =====\n";
        cout << "1. Menu Admin\n";
        cout << "2. Menu User\n";
        cout << "0. Keluar\n";
        cout << "\nPilih: ";
        cin >> menuUtama;

        if (menuUtama == 1) {
            system("cls");
            if (loginAdmin() == true) {
                menuAdmin(Library, Playlist);
            }
            system("cls");
        }

        if (menuUtama == 2) {
            system("cls");
            if (loginUser() == true) {
                system("cls");
                menuUser(Library, Playlist);
            }
        }
    }

    system("cls");
    cout << "=========================================\n";
    cout << " TERIMA KASIH TELAH MENGGUNAKAN APLIKASI \n";
    cout << "      sampai bertemu di lain waktu!      \n";
    cout << "=========================================\n";

    return 0;
}
