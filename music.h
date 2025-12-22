#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

/* ===== DATA LAGU ===== */
struct Lagu {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

/* ===== LIBRARY (DOUBLE LINKED LIST) ===== */
typedef struct elmLib* adrLibrary;

struct elmLibrary {
    Lagu info;
    adrLibrary next;
    adrLibrary prev;
};

struct listLibrary {
    adrLibrary first;
    adrLibrary last;
};

/* fungsi library */
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
int countLibrary(listLibrary L);
void filterByGenre(listLibrary L, string genre);
void filterByArtis(listLibrary L, string artis);

/* ===== PLAYLIST (SINGLE LINKED LIST) ===== */
typedef struct elmplaylist* addressPlaylist;

struct elmplaylist {
    adrLibrary info;      // refer ke lagu di library
    addressPlaylist next;
};

struct listPlaylist {
    addressPlaylist first;
};

/* fungsi playlist */
void createListPlaylist(listPlaylist &L);
addressPlaylist allocatePlaylist(adrLibrary p);
void insertLastPlaylist(listPlaylist &L, addressPlaylist p);
bool deletePlaylistByID(listPlaylist &L, int id);
void deletePlaylistByLibrary(listPlaylist &L, adrLibrary p);
addressPlaylist searchPlaylistNodeByLibrary(listPlaylist &L, adrLibrary p);
void printPlaylist(listPlaylist L);
bool isEmptyPlaylist(listPlaylist L);

/* ===== PLAYER ===== */
void playLagu(adrLibrary p, bool &status, adrLibrary &current);
void stopLagu(bool &status);

/* ===== LOGIN & MENU ===== */
bool loginAdmin();
bool loginUser();
void laguDummy(listLibrary &Library);
void menuAdmin(listLibrary &Library, listPlaylist &Playlist);
void menuUser(listLibrary &Library, listPlaylist &Playlist);

#endif




