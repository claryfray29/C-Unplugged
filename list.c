#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


void list_songs(int k){
    FILE* fptr = fopen("songs.txt","r");
    if(fptr==NULL){
        printf("error opening the file");
        return;
    }
    //char s[50],d[50];
    //int t;
    char inpt[50];
    while(fgets( inpt, sizeof(inpt), fptr)!=NULL){
        
        printf("%s",inpt);
        
        //inpt[strcspn(inpt, "\n")] = 0;
    }
    fclose(fptr);
}

void print_list(playlist* list){
    if(list==NULL){
        printf("Playlist is empty.\n");
        return;
    }

    while(list!=NULL){
        printf("%s  %s  %s\n",list->song_name, list->artist_name, list->duration);
        list=list->next;
    }
}

playlist* add_song(char new_song_name[50], playlist* list){

    FILE* fptr = fopen("songs.txt","r");

    if(fptr==NULL){
        printf("error opening the file");
        return list;
    }

    char s[50],d[50];
    char t[10];

    int song=0;

    while(fscanf(fptr,"%s   %s   %s",s,t,d)==3){
        if(strcmp(new_song_name,s)==0){
            playlist* new = (playlist *)malloc(sizeof(playlist));

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

            if(list==NULL){
                list=new;
            }
            else{
                playlist* i=list;
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

    if (song==1) {
        printf("Song '%s' added to playlist!\n", new_song_name);
    } else {
        printf("Song '%s' not found in library.\n", new_song_name);
    }

    return list;
}

playlist* delete_song(int pos, playlist* list){
    
   if(list==NULL){
    printf("Playlist is empty\n");
    return list;
   }
    playlist* temp = list;

    if(pos==0){
        list=temp->next;
        if(list!=NULL){
            list->prev=NULL;
        }
        free(temp);
        return list;
    }
    else{
        for(int i=0; temp!=NULL && i<pos-1; i++){
            temp = temp->next;
        }
        if(temp==NULL||temp->next==NULL){
            printf("Position out of bounds.\n");
            return list;
        }
        playlist* del = temp->next;
        temp->next=del->next;
        if(del->next!=NULL){
            del->next->prev=temp;
        }
        free(del);
        //temp->next=next;
        printf("Song deleted from the playlist.\n");
        return list;
    }
    //return list;
}


playlist* prev_next_song(char move[10], playlist* list){

    static playlist* current_song=NULL;

    //scanf("%s",move);
    if(list==NULL){
        printf("Playlist is empty.\n");
        return list;
    }
    if(strcmp(move,"begin")==0){
        if(current_song==NULL){
            current_song=list;
        }
        else if(current_song!=NULL){
            printf("PLaylist already playing.\n");
        }
    }
    
    else if(strcmp(move,"next")==0){
        if(current_song==NULL){
            printf("Starting the playlist.\n");
            current_song=list;
        }
        else if(current_song->next==NULL){
            printf("Playlist at end. Looping back to the first song.\n");
            current_song=list;
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
            current_song=list;
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
    else{
        printf("Invalid input!\n");
    }
    
    if(current_song!=NULL){
        printf("Currently playing: %s\n", current_song->song_name);
        printf("Aritst: %s\n", current_song->artist_name);
        printf("Duration: %smins\n",current_song->duration);
    }
    printf("(To go to next or previous song enter 5 again)\n");
    return list;
}


void command_log(char log[10]){
    
    FILE* logfptr = fopen("command_log.txt","a");

    if(logfptr==NULL){
        printf("error opening the file");
        return;
    }
    char abc[100];


    if(strcmp(log,"help")==0){
        strcpy(abc," ");
    }
    else if(strcmp(log,"1")==0){
        strcpy(abc,": List of all songs in the library");
    }
    else if(strcmp(log,"2")==0){
        strcpy(abc, ": Add songs to the playlist");
    }
    else if(strcmp(log,"3")==0){
        strcpy(abc,": Delete songs from the playlist");
    }
    else if(strcmp(log,"4")==0){
        strcpy(abc,": List of songs in playlist");
    }
    else if(strcmp(log,"5")==0){
        strcpy(abc,": To begin, move to next or previous song in a playlist");
    }
    else if(strcmp(log,"6")==0){
        strcpy(abc,": Create an album");
    }
    else if(strcmp(log,"7")==0){
        strcpy(abc,": To delete an album");
    }
    else if(strcmp(log,"8")==0){
        strcpy(abc,": To list all albums");
    }
    else if(strcmp(log,"9")==0){
        strcpy(abc,": Add songs to an album");
    }
    else if(strcmp(log,"10")==0){
        strcpy(abc,": Delete song from an album");
    }
    else if(strcmp(log,"11")==0){
        strcpy(abc,": List all songs from an album");
    }
    else if(strcmp(log,"12")==0){
        strcpy(abc,": To begin, move to next or previous song in an album");
    }
    else if(strcmp(log,"13")==0){
        strcpy(abc,": To see the command log");
    }
    else if(strcmp(log,"exit")==0){
        strcpy(abc," ");
    }
    else if(strcmp(log,"begin")==0){
        strcpy(abc," ");
    }
    else if(strcmp(log,"next")==0){
        strcpy(abc," ");
    }
    else if(strcmp(log,"prev")==0){
        strcpy(abc," ");
    }
    /*else if(strcmp(log,"")==0){
        strcpy(abc,"");
    }*/

    fprintf(logfptr, "%s %s\n", log, abc);

    fclose(logfptr);
    
}

void list_commands(int k){
    FILE* fptr = fopen("command_log.txt","r");
    if(fptr==NULL){
        printf("error opening the file");
        return;
    }
    //char s[50],d[50];
    //int t;
    char inpt[50];
    while(fgets( inpt, sizeof(inpt), fptr)!=NULL){
        
        printf("%s",inpt);
        
        //inpt[strcspn(inpt, "\n")] = 0;
    }
    fclose(fptr);
}