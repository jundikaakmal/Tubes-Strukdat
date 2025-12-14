#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <iostream>
using namespace std;

struct Lagu {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

/* ===== SLL - LIBRARY ===== */
typedef struct elmlibrary* addressLibrary;

struct elmlibrary {
    Lagu info;
    addressLibrary next;
};

struct ListLibrary {
    addressLibrary first;
};

void createListLibrary(ListLibrary &L);
addressLibrary allocateLibrary(Lagu x);
void insertFirstLibrary(ListLibrary &L, addressLibrary p);
void deleteLibrary(ListLibrary &L, addressLibrary p);
void printLibrary(ListLibrary L);
addressLibrary searchLibrary(ListLibrary L, int id);
addressLibrary searchLibraryByJudul(ListLibrary L, string judul);
void updateLibrary(ListLibrary &L, addressLibrary p);
addressLibrary findSimilarSong(ListLibrary L, addressLibrary current); // cari mirip

/* ===== SLL - PLAYLIST (simpan reference ke addressLibrary) ===== */
typedef struct elmplaylist* addressPlaylist;

struct elmplaylist {
    addressLibrary info;    // pointer ke node library
    addressPlaylist next;
};

struct ListPlaylist {
    addressPlaylist first;
};

void createListPlaylist(ListPlaylist &L);
addressPlaylist allocatePlaylist(addressLibrary p);
void insertLastPlaylist(ListPlaylist &L, addressPlaylist p);
bool deletePlaylistByID(ListPlaylist &L, int id); // return true jika dihapus
void deletePlaylistByLibrary(ListPlaylist &L, addressLibrary p);
void printPlaylist(ListPlaylist L);
addressPlaylist searchPlaylistNodeByLibrary(ListPlaylist &L, addressLibrary p); // cari node playlist

/* ===== TAMBAHAN ===== */
void playLagu(adrLibrary p, bool &isPlay, adrLibrary &current);
void stopLagu(bool &isPlay);
bool loginAdmin();
bool loginUser();
void laguDummy(listLibrary &Library);
void menuAdmin(listLibrary &Library, listPlaylist &Playlist);
void menuUser(listLibrary &Library, listPlaylist &Playlist);

#endif

