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

/* ========== LIBRARY (DLL) ========== */
typedef struct elmLib *adrLibrary;
struct elmLib {
    Lagu info;
    adrLibrary next;
    adrLibrary prev;
};

struct listLibrary {
    adrLibrary first;
    adrLibrary last;
};

void createListLibrary(listLibrary &L);
bool isEmptyLibrary(listLibrary L);
adrLibrary allocateLibrary(Lagu x);
void insertLastLibrary(listLibrary &L, adrLibrary p);
void deleteLibrary(listLibrary &L, adrLibrary p);
void printLibrary(listLibrary L);
adrLibrary searchLibrary(listLibrary L, int id);
adrLibrary searchLibraryByJudul(listLibrary L, string judul);
void updateLibrary(listLibrary &L, adrLibrary p);
adrLibrary findSimilarSong(listLibrary L, adrLibrary current);

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

/* ========== FILTER & COUNT ========== */
void filterByGenre(listLibrary L, string genre);
void filterByArtis(listLibrary L, string artis);
int countLibrary(listLibrary L);

#endif


