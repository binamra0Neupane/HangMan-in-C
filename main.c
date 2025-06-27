#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

#define MAX_WORD_LENGTH 100 // DEfining max word lenght
#define MAX_TRIES 5  // Max number of chances given to the user

/*Prototypes*/

char* getRandomWord(const char*); // Gets Random character from
void hideWord(const char[]); //  Hiding the random words in the form of asteriks
int checkCharacter(const char[], char, char[]); // Compares user input( character ) with the guess_word.
void print_body(int);

void introscreen() // Introduction screen
{
    printf("\n\n");
    printf(" ***     ***  ************  ****      ***  **************  ****      ****   ************  ****      ***\n");
    printf(" ***     ***  ***      ***  ****      ***  ****            *****    *****   ***      ***  ****      ***\n");
    printf(" ***     ***  ***      ***  *** *     ***  ****            *** ** **  ***   ***      ***  *** *     ***\n");
    printf(" ***     ***  ***      ***  *** **    ***  ****            ***   **   ***   ***      ***  *** **    ***\n");
    printf(" *** *** ***  *** **** ***  ***  **   ***  ****   *******  ***        ***   ************  ***  **   ***\n");
    printf(" ***     ***  ***      ***  ***   **  ***  ****      ****  ***        ***   ***      ***  ***   **  ***\n");
    printf(" ***     ***  ***      ***  ***    ** ***  ****      ****  ***        ***   ***      ***  ***    ** ***\n");
    printf(" ***     ***  ***      ***  ***     *****  **************  ***        ***   ***      ***  ***     *****\n");

    printf("\n\n");

    printf("\n                          *** Welcome to  HANG MAN ***                      \n");
    printf("\n***************************       R U L E S      ***************************\n");
    printf("\n1.   THE COMPUTER WILL GIVE YOU A RANDOM WORD TO GUESS.\n");
    printf("\n2.   YOU WILL GET A TOTAL OF FIVE CHANCE TO GUESS THE WORD.\n");
    printf("\n****************************************************************************\n");
    
    
    
}
int main()
{
    char play_again;
    do
    {
    introscreen();
    // Taking a random word from the text file.
    char* guess_word = getRandomWord("random.txt");

    printf("\n Your word is: ");
    hideWord(guess_word);      
    printf("\n\n\n");

    int length = strlen(guess_word);
    char hidden_string[MAX_WORD_LENGTH];

    for(int i = 0; i < length; i++)
    {
        if(guess_word[i] != ' ')
        {
            hidden_string[i] = '*';
        }
        else{
            hidden_string[i] = ' ';
        }

    }
    hidden_string[length] = '\0';  //Null Terminator
    // Taking user's guess.
    char user_input;
    int chances = MAX_TRIES;
    printf("\n*** MAKE SURE YOUR CAPS LOCK IS ON ***\n\"YOU ARE ONLY ALLOWED TO ENTER ONE CHARACTER AT A TIME\"\n");

    while (chances > 0)
    {
        
        printf("\nENTER YOUR GUESS: ");  //Asking for user input.
        scanf(" %c", &user_input);
        if(checkCharacter(guess_word, user_input, hidden_string))
        {
            printf("\nCORRECT!!\n");
            printf("YOUR CURRENT STATUS IS: %s \n", hidden_string);

            if(strcmp(hidden_string, guess_word)==0)
            {
                printf("\n\n\n\n");
                printf("\n*** CONGRATULATIONS  ***\nYOU GUESSED THE WORD CORRECTLY.\n");
                break;
            }
        }
        else
        {
            printf("\nINCORRECT! TRY AGAIN.\n");
            chances--;
            print_body(chances);

            if(chances>0)
            {
                printf("CHANCES LEFT: %d\n", chances);
            }
            else{
                printf("YOU'VE RUN OUT OF CHANCES. THE WORD WAS:\'%s\'\n", guess_word);
            }
        }
    }
    free(guess_word); 
    printf("\n\nDO YOU WANT TO PLAY AGAIN? (Y/N): ");
    scanf(" %c", &play_again);
    }
    while(play_again == 'Y' || play_again == 'y');
    if(play_again == 'n' || play_again == 'N')
    {
        printf("\n*** GOOD GAME ***\n");
    }
    return 0;
}
    
// Picking a random word
char* getRandomWord(const char*filname)
{
    FILE* fptr;
    char word[MAX_WORD_LENGTH];
    int num_words = 0; // Number of words in the file. 
    int chosenWordIndex;
    char* chosenWord = (char*)malloc(MAX_WORD_LENGTH * sizeof(char)); 

    
    fptr = fopen("random.txt", "r");

    if (fptr == NULL) {
        printf("Unable to open the file.\n");
        return NULL;
    }

    // Read words from the file and count the number of words.
    while (fscanf(fptr, "%s", word) == 1) {
        num_words++;
    }

    // Generate a random number within the range of number of words within the file.
    srand(time(NULL)); 
    chosenWordIndex = rand() % num_words;

    
    fseek(fptr, 0, SEEK_SET);

    // Reading and storing the randomly chosen word
    num_words = 0;
    while (fscanf(fptr, "%s", word) == 1) {
        if (num_words == chosenWordIndex) {
            strcpy(chosenWord, word);
            break;
        }
        num_words++;
    }

    fclose(fptr);

    return chosenWord;
}

// Function to Check User input
int checkCharacter(const char guess_word[], char user_input, char hidden_string[])
{
    int correct = 0;
    int length = strlen(guess_word);

    for(int i = 0; i<length; i++)
    {
        if(guess_word[i]==user_input)
        {
            correct = 1;
            hidden_string[i] = user_input; // Reveals correctly the guessed  character
        }
        
    }

    return correct;

}

// Function to Hide the word in Asteriks
void hideWord(const char guess_word[]) {
     int length = strlen(guess_word);

     for(int i = 0; i<length; i++)
     {
        if(guess_word[i] != ' ')
        {
            printf("* ");
        }
        else
        {
            printf(" ");
        }

     }
    printf("\nThe word contains %d letters. The word starts with %c.\n\n", length, toupper(guess_word[0]));
}

void print_body(int chances) 
{
    char* body_parts[] = {
        "  O  ",
        " /|\\ ",
        " / \\ ",
        " ^^^ "
    };

    if (chances == 4)
    {
        printf("%s\n", body_parts[0]);
    }
    else if (chances == 3) 
    {
        printf("%s\n%s\n", body_parts[0], body_parts[1]);
    } 
    else if (chances == 2)
    {
        printf("%s\n%s\n%s\n", body_parts[0], body_parts[1], body_parts[2]);
    } 
    else if (chances == 1) 
    {
        printf("%s\n%s\n%s\n", body_parts[0], body_parts[1], body_parts[3]);
    } 
    else if (chances == 0) 
    {
         printf("%s\n%s\n%s\n%s\nGAME OVER - You've been hanged!\n", body_parts[0], body_parts[1], body_parts[3], body_parts[2]);
    }
}

