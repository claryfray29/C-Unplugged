#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(){
    printf("Welcome to C Unplugged\n");

    playlist* list=NULL;
    albumofalbum* head = load_albums(); 
    if (head != NULL) printf("Previous albums restored!\n");

    printf("Type 'help' to get a list of all commands or 'exit' to quit.\n");
    int goback=1;
    while(goback==1){
        char prog[10];
        scanf("%9s",prog);

        command_log(prog);
        
        if(strcmp(prog,"help")==0){
            printf("-----------MENU------------\n");
            printf("1  : List of all songs in the library\n");
            printf("2  : Add songs to the playlist\n");
            printf("3  : Delete songs from the playlist\n");
            printf("4  : List of songs in playlist\n");
            printf("5  : To begin, move to next or previous song in a playlist\n");
            //printf("6 : Move to the previous song in the playlist or album.\n");
            printf("6  : Create an album\n");
            printf("7  : To delete an album\n");
            printf("8  : To list all albums\n");
            printf("9  : Add songs to an album\n");
            printf("10 : Delete song from an album\n");
            printf("11 : List all songs from an album\n");
            printf("12 : To begin, move to next or previous song in an album\n");
            printf("13 : To see the command log\n");

            printf("Enter a number given:\n");

            //int input;
            //scanf("%d",&input);

            

        }
        else if(strcmp(prog,"1")==0){
            printf("Song Library\n");
            list_songs(1);
        }

        else if(strcmp(prog,"2")==0){
            char name[50];
            printf("Please enter <name of the song>\n");
            scanf("%49s",name);
            list = add_song(name,list);
            //printf("Song added to playlist!\n");
            printf("-----------Current Playlist-----------\n");
            print_list(list);
        }

        else if(strcmp(prog,"3")==0){
            int pos;
            printf("Enter position to delete(starting from 0):\n");
            //scanf("%d",&pos);
            if (scanf("%d", &pos) != 1) {
                printf("Invalid input! Please enter a number.\n");
                while (getchar() != '\n'); 
                continue;
            }
            list = delete_song(pos,list);
            //printf("Song deleted from the playlist.\n");
            printf("-----------Current Playlist-----------\n");
            print_list(list);
        }

        else if(strcmp(prog,"4")==0){
            printf("-----------Current Playlist-----------\n");
            print_list(list);
        }

        else if(strcmp(prog,"5")==0){
            char move[10];
            printf("next : Go to the next song.\n");
            printf("prev : Go to the previous song.\n");
            printf("begin : Begin playlist.\n");
            scanf("%9s",move);
            command_log(move);
            prev_next_song(move, list);
        }

        /*else if(strcmp(prog,"6")==0){
            prev_song(list);
        }*/

        else if(strcmp(prog,"6")==0){
            char new_album[50];
            printf("Please enter the name of album to be created: \n");
            printf("(Please use '_' instead of a space)\n");
            scanf("%49s",new_album);
            head = add_album(new_album, head);
            
        }

        else if(strcmp(prog,"7")==0){
            char album_name[50];
            printf("Please enter the name of the album to be deleted.\n");
            scanf("%49s",album_name);
            head = delete_album(album_name, head); 
            //printf("Album %s deleted!\n",album_name);           
        }

        else if(strcmp(prog,"8")==0){
            list_albums(head);
        }

        else if(strcmp(prog,"9")==0){
            char album_name[50];
            char song_name[50];
            printf("Enter name of album to which the song must be added:\n");
            scanf("%49s", album_name);

            albumofalbum* temp = head;

            while(temp!=NULL && strcmp(album_name,temp->name)!=0){
                temp=temp->next;
            }
            if(temp==NULL){
                printf("Album not found!\n");
            }
            else{
                printf("Enter the song to be added to %s:\n",album_name);
                scanf("%49s",song_name);
                temp->albumhead = album_add_song(song_name, temp->albumhead);
                //printf("Song %s added to album %s!\n", song_name, album_name);
            }

        }

        else if(strcmp(prog,"10")==0){
            char album_name[50];
            char song_name[50];
            printf("Enter name of album from which the song needs to be deleted:\n");
            scanf("%49s",album_name);
            albumofalbum* temp = head;
            while(temp!=NULL && strcmp(album_name,temp->name)!=0){
                temp=temp->next;
            }
            if(temp==NULL){
                printf("Album not found!\n");
            }
            else{
                printf("Enter the name of song to be deleted:\n");
                scanf("%49s",song_name);
                int pos=0;
                int flag=0;
                album* tempal = temp->albumhead;
                while(tempal!=NULL){
                    if(strcmp(tempal->song_name,song_name)==0){
                        flag=1;
                        break;
                    }
                    pos++;
                    tempal=tempal->next;

                }
                if(flag==0){
                    printf("Song not found.\n");
                }
                else{
                    temp->albumhead=album_delete_song(pos, temp->albumhead);
                    printf("Song deleted from abum!\n");
                }
                
            }
        }

        else if(strcmp(prog,"11")==0){
            char album_name[50];
            printf("Enter the album name:\n");
            scanf("%49s",album_name);

            albumofalbum* temp = head;

            while(temp!=NULL && strcmp(album_name,temp->name)!=0){
                temp=temp->next;
            }
            if(temp==NULL){
                printf("Album not found!\n");
            }
            else{
                printf("----------------'%s' Album Playlist------------------\n",album_name);
                list_album_songs(temp->albumhead);
            }
        }

        else if(strcmp(prog,"12")==0){
            char album_name[50];
            printf("Enter the album name:\n");
            scanf("%49s",album_name);

            

            albumofalbum* temp = head;

            while(temp!=NULL && strcmp(album_name,temp->name)!=0){
                temp=temp->next;
            }

            if(temp==NULL){
                printf("Album not found!\n");
            }

            else{
                char move[10];
                printf("next : Go to the next song.\n");
                printf("prev : Go to the previous song.\n");
                printf("begin : Begin playlist.\n");
                scanf("%9s",move);
                command_log(move);
                album_move_song(move, temp->albumhead);
            }
        }

        else if(strcmp(prog,"13")==0){
            printf("-----------------COMMAND LOG---------------------\n");
            list_commands(1);
        }

        else if(strcmp(prog,"exit")==0){
            goback=0;
        }
        else{
            printf("Invalid input!\n");
        }
    }

    save_albums(head);
    return 0;
}