#include "music.h"

/* ================= LIBRARY ================= */

void createListLibrary(ListLibrary &L) {
    L.first = nullptr;
}

addressLibrary allocateLibrary(Lagu x) {
    addressLibrary p = new elmlibrary;
    p->info = x;
    p->next = nullptr;
    return p;
}

void insertFirstLibrary(ListLibrary &L, addressLibrary p) {
    p->next = L.first;
    L.first = p;
}

void deleteLibrary(ListLibrary &L, addressLibrary p) {
    if (L.first == nullptr || p == nullptr) return;

    if (L.first == p) {
        L.first = p->next;
        delete p;
    } else {
        addressLibrary q = L.first;
        while (q != nullptr && q->next != p) {
            q = q->next;
        }
        if (q != nullptr && q->next == p) {
            q->next = p->next;
            delete p;
        }
    }
}

void printLibrary(ListLibrary L) {
    addressLibrary p = L.first;
    while (p != nullptr) {
        cout << p->info.id << " | "
             << p->info.judul << " | "
             << p->info.artis << " | "
             << p->info.genre << " | "
             << p->info.tahun << endl;
        p = p->next;
    }
}

addressLibrary searchLibrary(ListLibrary L, int id) {
    addressLibrary p = L.first;
    while (p != nullptr && p->info.id != id) {
        p = p->next;
    }
    return p;
}

addressLibrary searchLibraryByJudul(ListLibrary L, string judul) {
    addressLibrary p = L.first;
    while (p != nullptr && p->info.judul != judul) {
        p = p->next;
    }
    return p;
}

void updateLibrary(ListLibrary &L, addressLibrary p) {
    if (p != nullptr) {
        cout << "Judul Baru : "; cin >> p->info.judul;
        cout << "Artis Baru : "; cin >> p->info.artis;
        cout << "Genre Baru : "; cin >> p->info.genre;
        cout << "Tahun Baru : "; cin >> p->info.tahun;
        // Karena playlist menyimpan pointer ke node library, tidak perlu sinkron tambahan:
        // update otomatis terlihat pada playlist karena referensi sama.
    }
}

/* Cari lagu "mirip" saat tidak di playlist:
   kebijakan sederhana: cari artis sama (prioritas), kalau tidak ada cari genre sama,
   jika tetap tidak ada -> return nullptr (caller akan tangani).
*/
addressLibrary findSimilarSong(ListLibrary L, addressLibrary current) {
    if (current == nullptr) return nullptr;

    // cari artis sama selain current
    addressLibrary p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.artis == current->info.artis) {
            return p;
        }
        p = p->next;
    }

    // cari genre sama selain current
    p = L.first;
    while (p != nullptr) {
        if (p != current && p->info.genre == current->info.genre) {
            return p;
        }
        p = p->next;
    }

    // fallback: cari lagu lain selain current (deterministik: first different)
    p = L.first;
    while (p != nullptr) {
        if (p != current) return p;
        p = p->next;
    }

    // tidak ada lagu lain
    return nullptr;
}

/* ================= PLAYLIST ================= */

void createListPlaylist(ListPlaylist &L) {
    L.first = nullptr;
}

addressPlaylist allocatePlaylist(addressLibrary p) {
    addressPlaylist q = new elmplaylist;
    q->info = p;
    q->next = nullptr;
    return q;
}

void insertLastPlaylist(ListPlaylist &L, addressPlaylist p) {
    if (L.first == nullptr) {
        L.first = p;
    } else {
        addressPlaylist q = L.first;
        while (q->next != nullptr) q = q->next;
        q->next = p;
    }
}

// Hapus node playlist berdasarkan id lagu. Kembalikan true jika berhasil.
bool deletePlaylistByID(ListPlaylist &L, int id) {
    if (L.first == nullptr) return false;

    // jika node pertama
    if (L.first->info != nullptr && L.first->info->info.id == id) {
        addressPlaylist temp = L.first;
        L.first = L.first->next;
        delete temp;
        return true;
    }

    addressPlaylist q = L.first;
    while (q->next != nullptr && q->next->info != nullptr && q->next->info->info.id != id) {
        q = q->next;
    }

    if (q->next != nullptr && q->next->info != nullptr && q->next->info->info.id == id) {
        addressPlaylist temp = q->next;
        q->next = temp->next;
        delete temp;
        return true;
    }

    return false;
}

// Hapus semua node playlist yang merujuk ke node library p
void deletePlaylistByLibrary(ListPlaylist &L, addressLibrary p) {
    addressPlaylist q = L.first;
    addressPlaylist prev = nullptr;
    while (q != nullptr) {
        if (q->info == p) {
            addressPlaylist temp = q;
            if (prev == nullptr) {
                L.first = q->next;
                q = L.first;
            } else {
                prev->next = q->next;
                q = prev->next;
            }
            delete temp;
        } else {
            prev = q;
            q = q->next;
        }
    }
}

void printPlaylist(ListPlaylist L) {
    addressPlaylist q = L.first;
    while (q != nullptr) {
        if (q->info != nullptr) {
            cout << q->info->info.id << " | "
                 << q->info->info.judul << " | "
                 << q->info->info.artis << " | "
                 << q->info->info.genre << " | "
                 << q->info->info.tahun << endl;
        }
        q = q->next;
    }
}

// Cari node playlist yang merujuk ke addressLibrary p
addressPlaylist searchPlaylistNodeByLibrary(ListPlaylist &L, addressLibrary p) {
    addressPlaylist q = L.first;
    while (q != nullptr) {
        if (q->info == p) return q;
        q = q->next;
    }
    return nullptr;
}

/* ================= PLAYER ================= */

void playLagu(addressLibrary p, bool &status, addressLibrary &current) {
    if (p != nullptr) {
        current = p;
        status = true;
        cout << "Memutar: " << p->info.judul << endl;
    }
}

void stopLagu(bool &status) {
    if (status) {
        status = false;
        cout << "Lagu dihentikan" << endl;
    } else {
        cout << "Tidak ada lagu yang sedang diputar" << endl;
    }
}
