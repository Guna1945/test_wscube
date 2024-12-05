#include <stdio.h>
#include <string.h>

#define MAX_SONGS 10
#define MAX_TITLE_LENGTH 100
#define MAX_ARTIST_LENGTH 100
#define MAX_GENRE_LENGTH 50


typedef struct {
    char title[MAX_TITLE_LENGTH];
    char artist[MAX_ARTIST_LENGTH];
    char genre[MAX_GENRE_LENGTH];
} Song;


typedef struct {
    Song songs[MAX_SONGS];
    int count;   
    int currentIndex;  
} Playlist;


void addSong(Playlist *playlist);
void playNext(Playlist *playlist);
void playPrevious(Playlist *playlist);
void switchToSong(Playlist *playlist);
void displaySongsByGenre(Playlist *playlist);
void displayCurrentSong(Playlist *playlist);
void displayMenu();

int main() {
    Playlist playlist = {0};  
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                addSong(&playlist);
                break;
            case 2:
                playNext(&playlist);
                break;
            case 3:
                playPrevious(&playlist);
                break;
            case 4:
                switchToSong(&playlist);
                break;
            case 5:
                displaySongsByGenre(&playlist);
                break;
            case 6:
                displayCurrentSong(&playlist);
                break;
            case 7:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


void displayMenu() {
    printf("\n--- Playlist Management System ---\n");
    printf("1. Add a new song\n");
    printf("2. Play next song\n");
    printf("3. Play previous song\n");
    printf("4. Switch to a specific song\n");
    printf("5. Display songs by genre\n");
    printf("6. Display current song\n");
    printf("7. Exit\n");
}


void addSong(Playlist *playlist) {
    if (playlist->count >= MAX_SONGS) {
        printf("Playlist is full! Cannot add more songs.\n");
        return;
    }

    Song *newSong = &playlist->songs[playlist->count];

    printf("Enter song title: ");
    fgets(newSong->title, MAX_TITLE_LENGTH, stdin);
    newSong->title[strcspn(newSong->title, "\n")] = '\0';  

    printf("Enter artist name: ");
    fgets(newSong->artist, MAX_ARTIST_LENGTH, stdin);
    newSong->artist[strcspn(newSong->artist, "\n")] = '\0';

    printf("Enter genre: ");
    fgets(newSong->genre, MAX_GENRE_LENGTH, stdin);
    newSong->genre[strcspn(newSong->genre, "\n")] = '\0';

    playlist->count++;
    printf("Song added: %s by %s (Genre: %s)\n", newSong->title, newSong->artist, newSong->genre);
}


void playNext(Playlist *playlist) {
    if (playlist->currentIndex < playlist->count - 1) {
        playlist->currentIndex++;
        printf("Now playing next song: %s\n", playlist->songs[playlist->currentIndex].title);
    } else {
        printf("You are already at the last song.\n");
    }
}


void playPrevious(Playlist *playlist) {
    if (playlist->currentIndex > 0) {
        playlist->currentIndex--;
        printf("Now playing previous song: %s\n", playlist->songs[playlist->currentIndex].title);
    } else {
        printf("You are already at the first song.\n");
    }
}


void switchToSong(Playlist *playlist) {
    int index;
    printf("Enter the song index (0 to %d): ", playlist->count - 1);
    scanf("%d", &index);

    if (index >= 0 && index < playlist->count) {
        playlist->currentIndex = index;
        printf("Switched to song: %s\n", playlist->songs[playlist->currentIndex].title);
    } else {
        printf("Invalid song index!\n");
    }
}


void displaySongsByGenre(Playlist *playlist) {
    char genre[MAX_GENRE_LENGTH];
    printf("Enter genre to display: ");
    fgets(genre, MAX_GENRE_LENGTH, stdin);
    genre[strcspn(genre, "\n")] = '\0';  
    int found = 0;
    for (int i = 0; i < playlist->count; i++) {
        if (strcmp(playlist->songs[i].genre, genre) == 0) {
            printf("%d. %s by %s\n", i, playlist->songs[i].title, playlist->songs[i].artist);
            found = 1;
        }
    }
    if (!found) {
        printf("No songs found in genre: %s\n", genre);
    }
}


void displayCurrentSong(Playlist *playlist) {
    if (playlist->count == 0) {
        printf("No songs in the playlist.\n");
        return;
    }
    printf("Currently playing: %s by %s (Genre: %s)\n", 
           playlist->songs[playlist->currentIndex].title,
           playlist->songs[playlist->currentIndex].artist,
           playlist->songs[playlist->currentIndex].genre);
}

