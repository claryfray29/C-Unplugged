#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

albumofalbum* add_album(char album_name[50],albumofalbum* head){
    //FILE* logfptr = fopen("%s.txt","a",album_name);
    albumofalbum* namecheck = head;
    while(namecheck!=NULL){
        if(strcmp(namecheck->name, album_name)==0){
            printf("The album %s already exists!\n", album_name);
            return head;
        }
        namecheck=namecheck->next;
    }

    albumofalbum* new_album = (albumofalbum*)malloc(sizeof(albumofalbum));
    //new->name=album_name;
    if(new_album==NULL){
        printf("Error");
    }

    new_album->next=NULL;
    new_album->prev=NULL;
    new_album->albumhead=NULL;
    strcpy(new_album->name,album_name);

    if(head==NULL){
        head=new_album;
    }
    else{
        albumofalbum* temp = head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next = new_album;
        new_album->prev=temp;
    }
    printf("Album %s created!\n",album_name);
    return head;
}

albumofalbum* delete_album(char album_name[50], albumofalbum* head){

    if(head==NULL){
        printf("No album existing.\n");
        return head;
    }

    
    if(strcmp(head->name, album_name)==0){

        albumofalbum* temp = head;
        head = head->next;
        if(head!=NULL){
            head->prev = NULL;
        }

        free_album_songs(temp->albumhead);
        free(temp);
        printf("Album %s deleted.\n",album_name);

        return head;
    }

    albumofalbum* temp = head->next;
    while(temp!=NULL){
        if(strcmp(temp->name, album_name)==0){
            temp->prev->next=temp->next;

            if(temp->next!=NULL){
                temp->next->prev = temp->prev;
            }

            free_album_songs(temp->albumhead);
            free(temp);
            printf("Album %s deleted!\n", album_name);

            return head;
        }
        temp = temp->next;

    }
    printf("Album not found.\n");
    return head;

}

void list_albums(albumofalbum* head){
    if(head==NULL){
        printf("No albums exist.\n");
    }
    else{
        printf("List of albums:\n");
        while(head!=NULL){
            printf("%s\n",head->name);
            head = head->next;
        }
    }
    return;
}

//linked list of albums done
//now for each album acting as node in ll

album* album_add_song(char song_name[50], album* albumhead){

    FILE* fptr = fopen("songs.txt","r");

    if(fptr==NULL){
        printf("error opening the file");
        return albumhead;
    }

    char s[50],d[50];
    char t[10];

    int song=0;

    while(fscanf(fptr,"%s   %s   %s",s,t,d)==3){
        if(strcmp(song_name,s)==0){
            album* new = (album *)malloc(sizeof(album));

            if(new==NULL){
                printf("Error");
                break;
            }

            new->next=NULL;
            new->prev=NULL;
            strcpy(new->song_name, s);
            strcpy(new->artist_name, d);
            strcpy(new->duration,t);
            //new->next = NULL;

            if(albumhead==NULL){
                albumhead=new;
            }
            else{
                album* i=albumhead;
                while(i->next !=NULL){
                    i=i->next;
                }
                i->next=new;
                new->prev=i;
            }
            song=1;
            break;
            
        }
    
    }
    fclose(fptr);
    if(song==1){
        printf("Song '%s' added to album!\n", song_name);
    }
    else {
        printf("Song '%s' not found in library.\n", song_name);
    }
    return albumhead;
}

album* album_delete_song(int pos, album* albumhead){
    
   if(albumhead==NULL){
    printf("List is empty");
    return albumhead;
   }
    album* temp = albumhead;

    if(pos==0){
        albumhead=temp->next;
        if(albumhead!=NULL){
            albumhead->prev=NULL;
        }
        
        free(temp);
        return albumhead;
    }
    else{
        for(int i=0; temp!=NULL && i<pos-1; i++){
            temp = temp->next;
        }
        if(temp==NULL){
            printf("Position out of bounds.\n");
            return albumhead;
        }
        album* del = temp->next;
        temp->next=del->next;
        if(del->next!=NULL){
            del->next->prev=temp;
        }
        free(del);
        //temp->next=next;
        return albumhead;
    }
    //return list;
}

void free_album_songs(album* albumhead){
    album* current = albumhead;
    while(current != NULL) {
        album* temp = current;
        current = current->next;
        free(temp);
    }
}

void list_album_songs(album* albumhead){
    if(albumhead==NULL){
        printf("Playlist is empty.\n");
        return;
    }

    while(albumhead!=NULL){
        
        printf("%s  %s  %s\n",albumhead->song_name, albumhead->artist_name, albumhead->duration);
        albumhead=albumhead->next;
    }
}

album* album_move_song(char move[10], album* albumhead){

    static album* current_song=NULL;

    //scanf("%s",move);
    if(albumhead==NULL){
        printf("Playlist is empty.\n");
        return albumhead;
    }
    if(strcmp(move,"begin")==0){
        if(current_song==NULL){
            current_song=albumhead;
        }
        else if(current_song!=NULL){
            printf("PLaylist already playing.\n");
        }
    }
    
    else if(strcmp(move,"next")==0){
        if(current_song==NULL){
            printf("Starting the playlist.\n");
            current_song=albumhead;
        }
        else if(current_song->next==NULL){
            printf("Playlist at end. Looping back to the first song.\n");
            current_song=albumhead;
        }
        else{
            current_song=current_song->next;
        }
        //printf("Currently playing: %s\n", current_song->song_name);
        //printf("Aritst: %s\n", current_song->artist_name);
        //printf("Duration: %smins\n",current_song->duration);
    }
    else if(strcmp(move,"prev")==0){
        if(current_song==NULL){
            printf("Starting the playlist.\n");
            current_song=albumhead;
        }
        else if(current_song->prev==NULL){
            printf("Playlist in the beginning. Looping to the last song in the palylist.\n");
            while(current_song->next!=NULL){
                current_song=current_song->next;
            }
        }
        else{
            current_song=current_song->prev;
        }
        //printf("Currently playing: %s\n", current_song->song_name);
        //printf("Aritst: %s\n", current_song->artist_name);
        //printf("Duration: %smins\n",current_song->duration);
    }
    
    printf("Currently playing: %s\n", current_song->song_name);
    printf("Aritst: %s\n", current_song->artist_name);
    printf("Duration: %smins\n",current_song->duration);

    return albumhead;
}

void save_albums(albumofalbum* head) {
    FILE* fp = fopen("albums.txt", "w");
    if (fp == NULL) {
        printf("Error saving albums.\n");
        return;
    }

    albumofalbum* curr_alb = head;
    while (curr_alb != NULL) {
        
        fprintf(fp, "A:%s\n", curr_alb->name);

        album* curr_song = curr_alb->albumhead;
        while (curr_song != NULL) {
            fprintf(fp, "S:%s %s %s\n", 
                    curr_song->song_name, 
                    curr_song->duration, 
                    curr_song->artist_name);
            curr_song = curr_song->next;
        }
        curr_alb = curr_alb->next;
    }
    fclose(fp);
    printf("Albums saved successfully!\n");
}

albumofalbum* load_albums() {
    FILE* fp = fopen("albums.txt", "r");
    if (fp == NULL) return NULL;

    albumofalbum* head = NULL;
    albumofalbum* tail_alb = NULL;

    char line[150];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == 'A' && line[1] == ':') {

            char* name = line + 2;

            albumofalbum* new_alb = (albumofalbum*)malloc(sizeof(albumofalbum));
            strcpy(new_alb->name, name);
            new_alb->next = NULL;
            new_alb->prev = tail_alb;
            new_alb->albumhead = NULL;

            if (head == NULL) {
                head = new_alb;
            } else {
                tail_alb->next = new_alb;
            }
            tail_alb = new_alb;
        } 
        else if (line[0] == 'S' && line[1] == ':') {
            
            if (tail_alb == NULL) continue;

            char* data = line + 2;
            
            album* new_song = (album*)malloc(sizeof(album));
            
            sscanf(data, "%s %s %s", new_song->song_name, new_song->duration, new_song->artist_name);
            
            new_song->next = NULL;
            new_song->prev = NULL;

            if (tail_alb->albumhead == NULL) {
                tail_alb->albumhead = new_song;
            } else {
                album* s_temp = tail_alb->albumhead;
                while (s_temp->next != NULL) {
                    s_temp = s_temp->next;
                }
                s_temp->next = new_song;
                new_song->prev = s_temp;
            }
        }
    }
    fclose(fp);
    return head;
}