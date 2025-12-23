#include "music.h"

/* ================= LIBRARY ================= */

void createListLibrary(listLibrary &L) {
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyLibrary(listLibrary L) {
    return (L.first == nullptr);
}

adrLibrary allocateLibrary(Lagu x) {
    adrLibrary p = new elmLib;
    p->info = x;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insertLastLibrary(listLibrary &L, adrLibrary p) {
    bool idC = false;
    adrLibrary q = L.first;

    while (q != nullptr && idC == false) {
        if (q->info.id == p->info.id) {
            idC = true;
        }
        q = q->next;
    }

    if (idC == true) {
        cout << "\nID telah digunakan, tidak bisa menambahkan lagu" << endl;
    } else {
        if (isEmptyLibrary(L)) {
            L.first = p;
            L.last = p;
        } else {
            p->prev = L.last;
            L.last->next = p;
            L.last = p;
        }
        cout << "\nLagu sudah ditambahkan" << endl;
    }
}

void deleteLibrary(listLibrary &L, adrLibrary p) {
    if (isEmptyLibrary(L)) {
        return;
    }

    if (L.first == p && L.last == p) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (L.first == p) {
        L.first = p->next;
        L.first->prev = nullptr;
    } else if (L.last == p) {
        L.last = p->prev;
        L.last->next = nullptr;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    delete p;
}

void printLibrary(listLibrary L) {
    adrLibrary p = L.first;

    cout << "\n=======================================" << endl;
    cout << " ID | JUDUL LAGU | ARTIS | GENRE | TAHUN " << endl;
    cout << "=========================================" << endl;

    while (p != nullptr) {
        cout << p->info.id << "  | "
             << p->info.judul << " | "
             << p->info.artis << " | "
             << p->info.genre << " | "
             << p->info.tahun << endl;
        p = p->next;
    }
    cout << endl;
}

adrLibrary searchLibrary(listLibrary L, int id) {
    adrLibrary p = L.first;
    bool found = false;

    while (p != nullptr && found == false) {
        if (p->info.id == id) {
            found = true;
        } else {
            p = p->next;
        }
    }
    return p;
}

adrLibrary searchLibraryByJudul(listLibrary L, string judul) {
    adrLibrary p = L.first;
    bool found = false;

    while (p != nullptr && found == false) {
        if (p->info.judul == judul) {
            found = true;
        } else {
            p = p->next;
        }
    }
    return p;
}

void updateLibrary(listLibrary &L, adrLibrary p) {
    cout << "Judul baru: ";
    cin >> p->info.judul;
    cout << "Artis baru: ";
    cin >> p->info.artis;
    cout << "Genre baru: ";
    cin >> p->info.genre;
    cout << "Tahun baru: ";
    cin >> p->info.tahun;
}

adrLibrary findSimilarSong(listLibrary L, adrLibrary current) {
    adrLibrary p = L.first;

    while (p != nullptr) {
        if (p->info.genre == current->info.genre && p != current) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

/* ================= PLAYLIST ================= */

void createListPlaylist(listPlaylist &L) {
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyPlaylist(listPlaylist L) {
    return (L.first == nullptr);
}

adrPlaylist allocatePlaylist(adrLibrary p) {
    adrPlaylist q = new elmPlay;
    q->info = p;
    q->next = nullptr;
    q->prev = nullptr;
    return q;
}

bool isPlaylistContain(listPlaylist L, adrLibrary pLib) {
    adrPlaylist q = L.first;
    bool found = false;

    while (q != nullptr && found == false) {
        if (q->info->info.id == pLib->info.id) {
            found = true;
        } else {
            q = q->next;
        }
    }
    return found;
}

void insertLastPlaylist(listPlaylist &L, adrPlaylist p) {
    if (isPlaylistContain(L, p->info)) {
        cout << "ID telah digunakan di playlist, tidak bisa menambahkan lagu" << endl;
    } else {
        if (isEmptyPlaylist(L)) {
            L.first = p;
            L.last = p;
        } else {
            p->prev = L.last;
            L.last->next = p;
            L.last = p;
        }
        cout << "Lagu sudah ditambahkan" << endl;
    }
}

bool deletePlaylistByID(listPlaylist &L, int id) {
    adrPlaylist q = L.first;
    bool found = false;

    while (q != nullptr && found == false) {
        if (q->info->info.id == id) {
            found = true;
        } else {
            q = q->next;
        }
    }

    if (found == false) return false;

    if (L.first == q && L.last == q) {
        L.first = nullptr;
        L.last = nullptr;
    } else if (L.first == q) {
        L.first = q->next;
        L.first->prev = nullptr;
    } else if (L.last == q) {
        L.last = q->prev;
        L.last->next = nullptr;
    } else {
        q->prev->next = q->next;
        q->next->prev = q->prev;
    }

    delete q;
    return true;
}

void deletePlaylistByLibrary(listPlaylist &L, adrLibrary pLib) {
    adrPlaylist q = L.first;
    bool found = false;

    while (q != nullptr && found == false) {
        if (q->info == pLib) {
            found = true;
        } else {
            q = q->next;
        }
    }

    if (found == true) {
        if (L.first == q && L.last == q) {
            L.first = nullptr;
            L.last = nullptr;
        } else if (L.first == q) {
            L.first = q->next;
            L.first->prev = nullptr;
        } else if (L.last == q) {
            L.last = q->prev;
            L.last->next = nullptr;
        } else {
            q->prev->next = q->next;
            q->next->prev = q->prev;
        }
        delete q;
    }
}

void printPlaylist(listPlaylist L) {
    adrPlaylist p = L.first;

    while (p != nullptr) {
        cout << "\nID: " << p->info->info.id << endl;
        cout << "Judul: " << p->info->info.judul << endl;
        cout << "Artis: " << p->info->info.artis << endl;
        cout << "Genre: " << p->info->info.genre << endl;
        cout << "Tahun: " << p->info->info.tahun << endl;

        p = p->next;
    }
}

adrPlaylist searchPlaylistByLibrary(listPlaylist L, adrLibrary p) {
    adrPlaylist q = L.first;
    bool found = false;

    while (q != nullptr && found == false) {
        if (q->info == p) {
            found = true;
        } else {
            q = q->next;
        }
    }
    return q;
}

/* ================= PLAYER ================= */

void playLagu(adrLibrary p, bool &isPlay, adrLibrary &current) {
    isPlay = true;
    current = p;

    cout << "\nSedang memutar...\n";
    cout << "Judul: " << p->info.judul << endl;
    cout << "Artis: " << p->info.artis << endl;
}

void stopLagu(bool &isPlay) {
    isPlay = false;
    cout << "Lagu dihentikan" << endl;

bool loginAdmin() {
    string u, p;
    cout << "===== LOGIN ADMIN =====\n";
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    if (u == "admin" && p == "admin123") {
        cout << "\nLogin berhasil!\n";
        system("pause");
        return true;
    }
    cout << "\nUsername atau password salah!\n";
    system("pause");
    return false;
}

bool loginUser() {
    string u, p;
    cout << "===== LOGIN USER =====\n";
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    if (u == "user" && p == "user123") {
        cout << "\nLogin berhasil!\n";
        system("pause");
        return true;
    }
    cout << "\nUsername atau password salah!\n";
    system("pause");
    return false;
}

void laguDummy(listLibrary &Library) {
    Lagu x;

    /* 15 DATA LAGU DUMMY */
    x = {1, "ShapeOfYou", "EdSheeran", "Pop", 2017};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {2, "Believer", "ImagineDragons", "Rock", 2017};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {3, "Havana", "CamilaCabello", "Pop", 2017};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {4, "Attention", "CharliePuth", "Pop", 2018};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {5, "Lovely", "BillieEilish", "Indie", 2018};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {6, "Faded", "AlanWalker", "EDM", 2016};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {7, "Senorita", "ShawnMendes", "Pop", 2019};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {8, "BadGuy", "BillieEilish", "Pop", 2019};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {9, "Thunder", "ImagineDragons", "Rock", 2017};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {10, "Perfect", "EdSheeran", "Pop", 2017};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {11, "Starboy", "TheWeeknd", "Synth", 2016};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {12, "Photograph", "EdSheeran", "Pop", 2015};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {13, "StressedOut", "TwentyOnePilots", "Alternative", 2015};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {14, "TalkingToTheMoon", "BrunoMars", "Pop", 2010};
    insertLastLibrary(Library, allocateLibrary(x));
    x = {15, "Sugar", "Maroon5", "Pop", 2015};
    insertLastLibrary(Library, allocateLibrary(x));
}

void menuAdmin(listLibrary &Library, listPlaylist &Playlist) {
    int menuAdmin = 1;

    while (menuAdmin != 0) {
        system("cls");
        cout << "===== MENU ADMIN =====\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Lihat Library\n";
        cout << "3. Update Lagu\n";
        cout << "4. Hapus Lagu\n";
        cout << "5. Hitung Jumlah Lagu\n";
        cout << "0. Kembali\n";
        cout << "\nPilih: ";
        cin >> menuAdmin;

        system("cls");
        if (menuAdmin == 1) {
            Lagu x;
            cout << "=== Isi Data Lagu ===" << endl;
            cout << "\nID: "; cin >> x.id;
            cout << "Judul: "; cin >> x.judul;
            cout << "Artis: "; cin >> x.artis;
            cout << "Genre: "; cin >> x.genre;
            cout << "Tahun: "; cin >> x.tahun;

            insertLastLibrary(Library, allocateLibrary(x));
            system("pause");
        }
        if (menuAdmin == 2) {
            if (!isEmptyLibrary(Library)) {
                printLibrary(Library);
            } else {
                cout << "Maaf library tidak tersedia\n";
            }
            system("pause");
        }
        if (menuAdmin == 3) {
            cout << "=== Isi Data Lagu ===" << endl;
            int id;
            cout << "\nID Lagu: ";
            cin >> id;

            adrLibrary p = searchLibrary(Library, id);
            if (p != nullptr) {
                updateLibrary(Library, p);
                cout << "\nLagu sudah di update\n";
            } else {
                cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
        }
        if (menuAdmin == 4) {
            cout << "=== Isi Data Lagu ===" << endl;
            int id;
            cout << "\nID Lagu: ";
            cin >> id;

            adrLibrary p = searchLibrary(Library, id);
            if (p != nullptr) {
                deletePlaylistByLibrary(Playlist, p);
                deleteLibrary(Library, p);
                cout << "Lagu berhasil dihapus\n";
            } else {
                cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
        }

        if (menuAdmin == 5) {
            int total = countLibrary(Library);
            cout << "\nTotal lagu di library: " << total << endl;
            system("pause");
        }

    }
}

void menuUser(listLibrary &Library, listPlaylist &Playlist) {
    bool isPlay = false;
    adrLibrary current = nullptr;
    adrPlaylist currentPlayNode = nullptr;
    bool inPlaylist = false;

    int menuUser = 1;

    while (menuUser != 0) {
        cout << "===== MENU USER =====\n";
        cout << "1. Cari Lagu\n";
        cout << "2. Play Lagu\n";
        cout << "3. Stop Lagu\n";
        cout << "4. Next Lagu\n";
        cout << "5. Prev Lagu\n";
        cout << "6. Tambah ke Playlist\n";
        cout << "7. Lihat Playlist\n";
        cout << "8. Hapus dari Playlist\n";
        cout << "9. Filter Lagu (Genre / Artis)\n";
        cout << "0. Kembali\n";
        cout << "\nPilih: ";
        cin >> menuUser;

        system("cls");
        if (menuUser == 1) {
            string judul;
            cout << "Masukkan judul lagu yang ingin dicari: ";
            cin >> judul;

            adrLibrary p = searchLibraryByJudul(Library, judul);
            if (p != nullptr) {
                cout << "\n===== DATA LAGU =====\n";
                cout << "ID: " << p->info.id << endl;
                cout << "Judul: " << p->info.judul << endl;
                cout << "Artis: " << p->info.artis << endl;
                cout << "Genre: " << p->info.genre << endl;
                cout << "Tahun: " << p->info.tahun << endl;
            } else {
                cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 2) {
            int id;
            cout << "ID Lagu: ";
            cin >> id;

            adrLibrary p = searchLibrary(Library, id);
            if (p != nullptr) {
                adrPlaylist pl = searchPlaylistByLibrary(Playlist, p);

                if (pl != nullptr) {
                    currentPlayNode = pl;
                    inPlaylist = true;
                } else {
                    currentPlayNode = nullptr;
                    inPlaylist = false;
                }

                playLagu(p, isPlay, current);
            } else {
                cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 3) {
            if (isPlay) {
                stopLagu(isPlay);
            } else {
                cout << "Maaf tidak ada lagu yang sedang diputar\n";
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 4) { // NEXT
            if (inPlaylist && currentPlayNode != nullptr) {
                if (currentPlayNode->next != nullptr) {
                    currentPlayNode = currentPlayNode->next;
                    playLagu(currentPlayNode->info, isPlay, current);
                } else {
                    cout << "Maaf lagu tidak tersedia\n";
                }
            } else {
                if (current != nullptr) {
                    adrLibrary sim = findSimilarSong(Library, current);
                    if (sim != nullptr) playLagu(sim, isPlay, current);
                    else cout << "Maaf lagu tidak tersedia\n";
                } else {
                    cout << "Maaf lagu tidak tersedia\n";
                }
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 5) { // PREV
            if (inPlaylist && currentPlayNode != nullptr) {
                if (currentPlayNode->prev != nullptr) {
                    currentPlayNode = currentPlayNode->prev;
                    playLagu(currentPlayNode->info, isPlay, current);
                } else {
                    cout << "Maaf lagu tidak tersedia\n";
                }
            } else {
                adrLibrary p = Library.first;
                adrLibrary prev = nullptr;

                while (p != nullptr && p != current) {
                    prev = p;
                    p = p->next;
                }

                if (prev != nullptr) {
                    playLagu(prev, isPlay, current);
                } else {
                    cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
            }
        }
        system("cls");
        if (menuUser == 6) {
            int id;
            cout << "Masukkan ID Lagu: ";
            cin >> id;

            adrLibrary p = searchLibrary(Library, id);
            if (p != nullptr) {
                insertLastPlaylist(Playlist, allocatePlaylist(p));
            } else {
                cout << "Maaf lagu tidak tersedia\n";
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 7) {
            if (!isEmptyPlaylist(Playlist)) {
                printPlaylist(Playlist);
            } else {
                cout << "Maaf playlist tidak tersedia\n";
            }
            system("pause");
        }
        system("cls");
        if (menuUser == 8) {
            if (!isEmptyPlaylist(Playlist)) {
                int id;
                cout << "ID Lagu: ";
                cin >> id;

                bool ok = deletePlaylistByID(Playlist, id);
                if (ok) {
                    cout << "Lagu sudah terhapus\n";
                } else {
                    cout << "Maaf lagu tidak tersedia\n";
                }
            } else {
                cout << "Maaf playlist tidak tersedia\n";
            }
            system("pause");
        }

        if (menuUser == 9) {
            int pilih;
            string key;

            cout << "1. Filter berdasarkan Genre\n";
            cout << "2. Filter berdasarkan Artis\n";
            cout << "Pilih: ";
            cin >> pilih;

            if (pilih == 1) {
                cout << "Masukkan genre: ";
                cin >> key;
                filterByGenre(Library, key);
            }else if (pilih == 2) {
                cout << "Masukkan nama artis: ";
                cin >> key;
                filterByArtis(Library, key);
            }

            system("pause");
        }

    }
}

void filterByGenre(listLibrary L, string genre) {
    adrLibrary p = L.first;
    bool found = false;

    cout << "\n=== Lagu dengan Genre: " << genre << " ===\n";

    while (p != nullptr) {
        if (p->info.genre == genre) {
            cout << p->info.id << " | "
                 << p->info.judul << " | "
                 << p->info.artis << " | "
                 << p->info.tahun << endl;
            found = true;
        }
        p = p->next;
    }

    if (!found) {
        cout << "Tidak ada lagu dengan genre tersebut\n";
    }
}

void filterByArtis(listLibrary L, string artis) {
    adrLibrary p = L.first;
    bool found = false;

    cout << "\n=== Lagu oleh Artis: " << artis << " ===\n";

    while (p != nullptr) {
        if (p->info.artis == artis) {
            cout << p->info.id << " | "
                 << p->info.judul << " | "
                 << p->info.genre << " | "
                 << p->info.tahun << endl;
            found = true;
        }
        p = p->next;
    }

    if (!found) {
        cout << "Tidak ada lagu dari artis tersebut\n";
    }
}

int countLibrary(listLibrary L) {
    int count = 0;
    adrLibrary p = L.first;

    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}



