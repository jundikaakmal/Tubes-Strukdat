#include "music.h"

int main() {
    ListLibrary Library;
    ListPlaylist Playlist;

    createListLibrary(Library);
    createListPlaylist(Playlist);

    bool isPlay = false;
    addressLibrary current = nullptr;

    // Untuk mode playlist tracking
    addressPlaylist currentPlaylistNode = nullptr;
    bool inPlaylist = false;

    int menuUtama = 1;

    while (menuUtama != 0) {
        cout << endl;
        cout << "===== MENU UTAMA =====" << endl;
        cout << "\n1. Menu Admin" << endl;
        cout << "2. Menu User" << endl;
        cout << "0. Keluar" << endl;
        cout << "\nPilih: ";
        cin >> menuUtama;

        /* ================= MENU ADMIN ================= */
        if (menuUtama == 1) {
            int menuAdmin = 1;

            while (menuAdmin != 0) {
                cout << endl;
                cout << "===== MENU ADMIN =====" << endl;
                cout << "\n1. Tambah Lagu" << endl;
                cout << "2. Lihat Library" << endl;
                cout << "3. Update Lagu" << endl;
                cout << "4. Hapus Lagu" << endl;
                cout << "0. Kembali" << endl;
                cout << "\nPilih: ";
                cin >> menuAdmin;

                if (menuAdmin == 1) {
                    Lagu x;
                    cout << "ID: ";
                    cin >> x.id;
                    cout << "Judul: ";
                    cin >> x.judul;
                    cout << "Artis: ";
                    cin >> x.artis;
                    cout << "Genre: ";
                    cin >> x.genre;
                    cout << "Tahun: ";
                    cin >> x.tahun;

                    insertFirstLibrary(Library, allocateLibrary(x));
                    cout << "Lagu sudah ditambahkan" << endl;
                }

                if (menuAdmin == 2) {
                    if (Library.first != nullptr) {
                        printLibrary(Library);
                    } else {
                        cout << "Maaf library tidak tersedia" << endl;
                    }
                }

                if (menuAdmin == 3) {
                    int id;
                    cout << "ID Lagu: ";
                    cin >> id;

                    addressLibrary p = searchLibrary(Library, id);
                    if (p != nullptr) {
                        updateLibrary(Library, p);
                        cout << "Lagu sudah diperbarui" << endl;
                    } else {
                        cout << "Maaf lagu tidak tersedia" << endl;
                    }
                }

                if (menuAdmin == 4) {
                    int id;
                    cout << "ID Lagu: ";
                    cin >> id;

                    addressLibrary p = searchLibrary(Library, id);
                    if (p != nullptr) {
                        // hapus dari playlist (semua referensi)
                        deletePlaylistByLibrary(Playlist, p);
                        // hapus dari library
                        deleteLibrary(Library, p);
                        // jika yang diputar adalah lagu ini, hentikan
                        if (current == p) {
                            stopLagu(isPlay);
                            current = nullptr;
                            currentPlaylistNode = nullptr;
                            inPlaylist = false;
                        }
                        cout << "Lagu berhasil dihapus" << endl;
                    } else {
                        cout << "Maaf lagu tidak tersedia" << endl;
                    }
                }
            }
        }

        /* ================= MENU USER ================= */
        if (menuUtama == 2) {
            int menuUser = 1;

            while (menuUser != 0) {
                cout << endl;
                cout << "===== MENU USER =====" << endl;
                cout << "\n1. Cari Lagu" << endl;
                cout << "2. Play Lagu" << endl;
                cout << "3. Stop Lagu" << endl;
                cout << "4. Next Lagu" << endl;
                cout << "5. Prev Lagu" << endl;
                cout << "6. Tambah ke Playlist" << endl;
                cout << "7. Lihat Playlist" << endl;
                cout << "8. Hapus dari Playlist" << endl;
                cout << "0. Kembali" << endl;
                cout << "\nPilih: ";
                cin >> menuUser;

                if (menuUser == 1) {
                    string judul;
                    cout << "Judul: ";
                    cin >> judul;

                    addressLibrary p = searchLibraryByJudul(Library, judul);
                    if (p != nullptr) {
                        cout << "===== DATA LAGU =====" << endl;
                        cout << "\nID: " << p->info.id << endl;
                        cout << "Judul: " << p->info.judul << endl;
                        cout << "Artis: " << p->info.artis << endl;
                        cout << "Genre: " << p->info.genre << endl;
                        cout << "Tahun: " << p->info.tahun << endl;
                    } else {
                        cout << "Maaf lagu tidak tersedia" << endl;
                    }
                }

                if (menuUser == 2) {
                    int id;
                    cout << "ID Lagu: ";
                    cin >> id;

                    addressLibrary p = searchLibrary(Library, id);
                    if (p != nullptr) {
                        // Cek apakah lagu ada di playlist -> jika ya, set mode playlist
                        addressPlaylist pn = searchPlaylistNodeByLibrary(Playlist, p);
                        if (pn != nullptr) {
                            currentPlaylistNode = pn;
                            inPlaylist = true;
                        } else {
                            currentPlaylistNode = nullptr;
                            inPlaylist = false;
                        }
                        playLagu(p, isPlay, current);
                    } else {
                        cout << "Maaf lagu tidak tersedia" << endl;
                    }
                }

                if (menuUser == 3) {
                    if (isPlay == true) {
                        stopLagu(isPlay);
                    } else {
                        cout << "Maaf tidak ada lagu yang sedang diputar" << endl;
                    }
                }

                if (menuUser == 4) { // NEXT
                    if (inPlaylist && currentPlaylistNode != nullptr) {
                        if (currentPlaylistNode->next != nullptr) {
                            currentPlaylistNode = currentPlaylistNode->next;
                            playLagu(currentPlaylistNode->info, isPlay, current);
                        } else {
                            cout << "Maaf lagu tidak tersedia" << endl;
                        }
                    } else {
                        // non-playlist mode: cari lagu mirip
                        if (current != nullptr) {
                            addressLibrary sim = findSimilarSong(Library, current);
                            if (sim != nullptr) {
                                // not in playlist mode
                                currentPlaylistNode = nullptr;
                                inPlaylist = false;
                                playLagu(sim, isPlay, current);
                            } else {
                                cout << "Maaf lagu tidak tersedia" << endl;
                            }
                        } else {
                            cout << "Maaf lagu tidak tersedia" << endl;
                        }
                    }
                }

                if (menuUser == 5) { // PREV
                    if (inPlaylist && currentPlaylistNode != nullptr) {
                        // cari prev node di playlist (sll)
                        addressPlaylist q = Playlist.first;
                        addressPlaylist prev = nullptr;
                        while (q != nullptr && q != currentPlaylistNode) {
                            prev = q;
                            q = q->next;
                        }
                        if (prev != nullptr) {
                            currentPlaylistNode = prev;
                            playLagu(currentPlaylistNode->info, isPlay, current);
                        } else {
                            cout << "Maaf lagu tidak tersedia" << endl;
                        }
                    } else {
                        // non-playlist mode: prev = previous in library
                        if (current != nullptr) {
                            // cari prev in library
                            addressLibrary p = Library.first;
                            addressLibrary prevL = nullptr;
                            while (p != nullptr && p != current) {
                                prevL = p;
                                p = p->next;
                            }
                            if (prevL != nullptr) {
                                playLagu(prevL, isPlay, current);
                            } else {
                                cout << "Maaf lagu tidak tersedia" << endl;
                            }
                        } else {
                            cout << "Maaf lagu tidak tersedia" << endl;
                        }
                    }
                }

                if (menuUser == 6) {
                    int id;
                    cout << "ID Lagu: ";
                    cin >> id;
                    addressLibrary p = searchLibrary(Library, id);
                    if (p != nullptr) {
                        insertLastPlaylist(Playlist, allocatePlaylist(p));
                        cout << "Lagu sudah ditambahkan" << endl;
                    } else {
                        cout << "Maaf lagu tidak tersedia" << endl;
                    }
                }

                if (menuUser == 7) {
                    if (Playlist.first != nullptr) {
                        printPlaylist(Playlist);
                    } else {
                        cout << "Maaf playlist tidak tersedia" << endl;
                    }
                }

                if (menuUser == 8) {
                    if (Playlist.first != nullptr) {
                        int id;
                        cout << "ID Lagu: ";
                        cin >> id;
                        bool ok = deletePlaylistByID(Playlist, id);
                        if (ok) {
                            cout << "Lagu sudah terhapus" << endl;
                            // jika yang diputar adalah lagu ini, hentikan
                            if (current != nullptr && current->info.id == id) {
                                stopLagu(isPlay);
                                current = nullptr;
                                currentPlaylistNode = nullptr;
                                inPlaylist = false;
                            }
                        } else {
                            cout << "Maaf lagu tidak tersedia" << endl;
                        }
                    } else {
                        cout << "Maaf playlist tidak tersedia" << endl;
                    }
                }
            }
        }
    }

    return 0;
}
