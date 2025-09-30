#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum Game {ROCK,PAPER,SCISSORS,SPOCK,LIZARD};
enum GameMode { WIN , CONTINUE , LOST };
int playerPoints = 0;
int computerPoints = 0;
int playerStatus = 0;
int computerStatus = 0;
int compare(enum Game player, enum Game computer);
int computerChoice(void);
const char *gameName[] = {"ROCK","PAPER","SCISSORS","SPOCK","LIZARD"};

enum Game playerChoice(char input[]);

int main(void) {
    srand(time(NULL));
    enum Game hand;
    enum GameMode gameMode;

    printf("welcome to RPSSL! begin game? (Y/N): ");
    
    char choice;
    scanf("%c" , &choice);

    while (1){
        if (choice == 'Y' || choice == 'y'){
            break;
        } else if (choice == 'N' || choice == 'n') {
            printf("have a great day!");
            gameMode = LOST;
            return 0;
        }
    }

    gameMode = CONTINUE;

    while (CONTINUE == gameMode){
        printf("\nchoose your hand: ");
        char userinput[20];
        scanf("%s", userinput);
        userinput[strcspn(userinput, "\n")] = '\0';

        enum Game player = playerChoice(userinput);
        if(player == -1){
            printf("Invalid choice! Try again.\n");
            continue;
        }

        playerStatus = 1;
        printf("Player chose %s\n", gameName[player]);

        enum Game computer = computerChoice();
        computerStatus = 1;

        if(computerStatus && playerStatus) {
            int result = compare(player, computer);
            if(result == 1) {
                playerPoints++;
                printf("Player wins this round. %s beats %s. Player points %d. Computer points %d\n",
                       gameName[player], gameName[computer], playerPoints, computerPoints);
            } else if(result == 2) {
                computerPoints++;
                printf("Computer wins this round. %s beats %s. Player points %d. Computer points %d\n",
                       gameName[computer], gameName[player], playerPoints, computerPoints);
            } else {
                printf("It's a tie!\n");
            }
            playerStatus = 0;
            computerStatus = 0;
        }

        if(playerPoints == 3) {
            printf("Player won. Congratulations.\n");
            gameMode = WIN;
        } else if(computerPoints == 3) {
            gameMode = LOST;
            printf("Computer won. Aw :(\n");
        } else {
            printf("Make new choice:\n");
        }
    }

    return 0;
}

int computerChoice(void){
    enum Game choice = rand() % 5;
    printf("Computer chose %s\n", gameName[choice]);
    return choice;
}

enum Game playerChoice(char input[]){
    if (strcmp(input, "ROCK") == 0 || strcmp(input, "rock") ==0 )
        return ROCK;
    else if (strcmp(input, "SCISSORS") == 0 || strcmp(input, "scissors") == 0 )
        return SCISSORS;
    else if (strcmp(input, "PAPER") == 0 || strcmp(input, "paper") == 0)
        return PAPER;
    else if (strcmp(input, "SPOCK") == 0 || strcmp(input, "spock") == 0)
        return SPOCK;
    else if (strcmp(input, "LIZARD") == 0 || strcmp(input, "lizard") == 0)
        return LIZARD;
    else 
        return -1;
}

int compare(enum Game player, enum Game computer) {
    const enum Game beats[5][2] = {
        {SCISSORS,LIZARD}, // ROCK
        {ROCK,SPOCK},      // PAPER
        {PAPER,LIZARD},    // SCISSORS
        {SCISSORS,ROCK},   // SPOCK
        {SPOCK,PAPER}      // LIZARD
    };

    if (player == computer){
        return 0; // tie
    }

    for(int i = 0; i < 2; i++) {
        if (beats[player][i] == computer){
            return 1;
        }
    }
    return 2;
}
