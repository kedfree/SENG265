/** @file song_analyzer.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process song
 *  data and printing it in a different format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Angadh S.
 *  @author Juan G.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief The maximum line length.
 *
 */
#define MAX_LINE_LEN 183


struct Track{
    char track_name[MAX_LINE_LEN];
    char artist_name[MAX_LINE_LEN];
    int artist_count;
    int released_year;
    int in_spotify_playlists;
    int streams;
    char key[5];
    char mode[5];
};

int read_file(char *inputFileName, struct Track *tracks);
int output_file(struct Track *tracks, int num_tracks);
int process_args(int argc, char *argv[], int *question, char* file_name);
int question_1(struct Track *tracks, int num_tracks);
int question_2(struct Track *tracks, int num_tracks);
int question_3(struct Track *tracks, int num_tracks);
int question_4(struct Track *tracks, int num_tracks);
int question_5(struct Track *tracks, int num_tracks);

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s --question=<question_number> --data=<filename>\n", argv[0]);
        return 1; // Error
    }

    int question_number;
    char inputFileName[256];

    if (process_args(argc, argv, &question_number, inputFileName) != 0) {
        return 1; // Error
    }

    struct Track tracks[1000];
    int track_count = read_file(inputFileName, tracks);

    if (question_number == 1){
        int new_track_count = question_1(tracks, track_count);
    }else if (question_number == 2){
        int new_track_count = question_2(tracks, track_count);
    }else if (question_number == 3){
        int new_track_count = question_3(tracks, track_count);
    }else if (question_number == 4){
        int new_track_count = question_4(tracks, track_count);
    }else if (question_number == 5){
        int new_track_count = question_5(tracks, track_count);
    }else{
        printf("Invalid question number");
        return 1; // Error
    }

    return 0;
}

int process_args(int argc, char *argv[], int *question_number, char* file_name) {
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--question=", 11) == 0) {
            // Extract question number
            *question_number = atoi(argv[i] + 11);
        } else if (strncmp(argv[i], "--data=", 7) == 0) {
            // Extract filename
            strcpy(file_name, argv[i] + 7);
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 1; // Error
        }
    }

    // printf("Question Number: %d\n", *question_number);
    // printf("Data Filename: %s\n", file_name);

    return 0;
}
int read_file(char *inputFileName, struct Track *tracks) {
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1; // Return -1 to indicate an error
    }

    char line[MAX_LINE_LEN];
    int track_count = 0;

    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        

        // Use strtok to tokenize the CSV line
        char *token = strtok(line, ",");
        if (token == NULL) {
            fprintf(stderr, "Error: Insufficient fields in line.\n");
            fclose(file);
            return -1;
        }
        strcpy(tracks[track_count].track_name, token);

        // Continue extracting other fields using strtok
        token = strtok(NULL, ",");
        strcpy(tracks[track_count].artist_name, token);

        // Example for integer fields
        token = strtok(NULL, ",");
        tracks[track_count].artist_count = atoi(token);

        token = strtok(NULL, ",");
        tracks[track_count].released_year = atoi(token);

        token = strtok(NULL, ",");
        tracks[track_count].in_spotify_playlists = atoi(token);

        token = strtok(NULL, ",");
        tracks[track_count].streams = atoi(token);

        token = strtok(NULL, ",");
        strcpy(tracks[track_count].key, token);

        token = strtok(NULL, ",");
        strcpy(tracks[track_count].mode, token);

        track_count ++;
    }

    fclose(file);
    return track_count;
}

int output_file(struct Track *tracks, int num_tracks) {
    
    FILE *outputFile = fopen("output.csv", "w");
    if (outputFile == NULL) {
        perror("Error creating output file");
        return 1; // Error
    }

    // Write header to the output file
    fprintf(outputFile, "Artist(s),Song\n");

    // Write each record to the output file
    for (int i = 0; i < num_tracks; i++) {
        fprintf(outputFile, "%s,%s\n", tracks[i].artist_name, tracks[i].track_name);
    }

    fclose(outputFile);

    return 0;
}

int question_1(struct Track *tracks, int num_tracks){
    struct Track new_tracks[num_tracks];
    int new_track_count = 0;

    for (int i = 0; i < 1000; i++) {
        if (strcmp(tracks[i].artist_name, "Rae Spoon") == 0 && tracks[i].released_year < 2020){
            new_tracks[new_track_count] = tracks[i];
            new_track_count ++;
        }
    }
    output_file(new_tracks, new_track_count);
    return new_track_count;
}

int question_2(struct Track *tracks, int num_tracks){
    struct Track new_tracks[num_tracks];
    int new_track_count = 0;

    for (int i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].artist_name, "Tate McRae") == 0 && tracks[i].released_year >= 2020){
            new_tracks[new_track_count] = tracks[i];
            new_track_count ++;
        }
    }
    output_file(new_tracks, new_track_count);
    return new_track_count;
}

int question_3(struct Track *tracks, int num_tracks){
    struct Track new_tracks[num_tracks];
    int new_track_count = 0;

    for (int i = 0; i < num_tracks; i++) {
        if (strcmp(tracks[i].artist_name, "The Weeknd") == 0 && strncmp(tracks[i].mode, "Major", 5) == 0){
            new_tracks[new_track_count] = tracks[i];
            new_track_count ++;
        }
    }
    output_file(new_tracks, new_track_count);
    return new_track_count;
}

int question_4(struct Track *tracks, int num_tracks){
    struct Track new_tracks[num_tracks];
    int new_track_count = 0;

    for (int i = 0; i < num_tracks; i++) {
        if (tracks[i].in_spotify_playlists > 5000 && (strncmp(tracks[i].key, "A", 1) == 0 || strncmp(tracks[i].key, "D", 1) == 0)){
            new_tracks[new_track_count] = tracks[i];
            new_track_count ++;
        }
    }
    output_file(new_tracks, new_track_count);
    return new_track_count;
}

int question_5(struct Track *tracks, int num_tracks){
    struct Track new_tracks[num_tracks];
    int new_track_count = 0;

    for (int i = 0; i < num_tracks; i++) {
        // printf("mode: %s\n", tracks[i].mode);
        if ((2021 <= tracks[i].released_year && tracks[i].released_year <= 2022) && strstr(tracks[i].artist_name, "Drake") != NULL){
            new_tracks[new_track_count] = tracks[i];
            new_track_count ++;
        }
    }
    output_file(new_tracks, new_track_count);
    return new_track_count;
}