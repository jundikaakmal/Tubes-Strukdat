#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

/* ========== DATA LAGU ========== */
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

/* ========== PLAYLIST (DLL) ========== */
typedef struct elmPlay *adrPlaylist;
struct elmPlay {
    adrLibrary info;
    adrPlaylist next;
    adrPlaylist prev;
};

struct listPlaylist {
    adrPlaylist first;
    adrPlaylist last;
};

/* ========== LIBRARY ========== */
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

/* ========== PLAYLIST ========== */
void createListPlaylist(listPlaylist &L);
bool isEmptyPlaylist(listPlaylist L);
adrPlaylist allocatePlaylist(adrLibrary p);
void insertLastPlaylist(listPlaylist &L, adrPlaylist p);
bool deletePlaylistByID(listPlaylist &L, int id);
void deletePlaylistByLibrary(listPlaylist &L, adrLibrary p);
void printPlaylist(listPlaylist L);
adrPlaylist searchPlaylistByLibrary(listPlaylist L, adrLibrary p);
bool isPlaylistContain(listPlaylist L, adrLibrary pLib);

/* ========== TAMBAHAN ========== */
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

#endif // MUSIC_H_INCLUDED
