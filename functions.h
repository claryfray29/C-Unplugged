#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct playlist{
    char song_name[50];
    char artist_name[50];
    char duration[10];
    struct playlist* next;
    struct playlist* prev;
} playlist;

//commands(char prog[5]);
void list_songs(int k);
void print_list(playlist* list);
playlist* add_song(char new_song_name[50], playlist* list);
playlist* delete_song(int pos, playlist* list);
playlist* prev_next_song(char move[10], playlist* list);
void command_log(char log[10]);



typedef struct album{
    char song_name[50];
    char artist_name[50];
    char duration[10];
    struct album* next;
    struct album* prev;
}album;

typedef struct albumofalbum{
    char name[50];
    struct album* albumhead;
    struct albumofalbum* next;
    struct albumofalbum* prev;
}albumofalbum;

albumofalbum* add_album(char album_name[50],albumofalbum* head);
albumofalbum* delete_album(char album_name[50], albumofalbum* head);
void list_albums(albumofalbum* head);
void free_album_songs(album* albumhead);
album* album_add_song(char song_name[50], album* albumhead);
album* album_delete_song(int pos, album* albumhead);
void list_album_songs(album* albumhead);
album* album_move_song(char move[10], album* albumhead);
void save_albums(albumofalbum* head);
albumofalbum* load_albums();

void list_commands(int k);

#endif