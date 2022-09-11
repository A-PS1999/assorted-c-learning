#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_NAME_LEN 10
#define assign_candidate_name(candidate, Name) strcpy((candidate).name, Name) // macro function to assign argv name to candidate struct name array

struct candidate {
    char name[MAX_NAME_LEN];
    int votes;
} candidates[MAX_CANDIDATES];

int candidate_count;

bool vote(char name[]);
void print_winner(void);

int main(int argc, char *argv[])
{
    int num_voters = 0;
    candidate_count = argc - 1; // first argc is program name, so -1 gives length of candidates supplied

    if (argc < 2) {
        printf("Please ensure you're using the program properly: 'plurality-election candidatename...");
        return -1;
    }

    if (candidate_count > MAX_CANDIDATES) {
        printf("Too many candidates supplied. Max is %d.", MAX_CANDIDATES);
        return -1;
    }

    for (int i=0; i < candidate_count; i++) {
        if (strlen(argv[i+1]) > 9) {
            printf("Name too long. Please ensure names are up to 9 characters long.");
            return -1;
        }
        assign_candidate_name(candidates[i], argv[i+1]); // use macro function, passing current candidate and current name to strcpy
        candidates[i].votes = 0;
    };

    printf("Your candidates are:\n");
    for (int w=0; w < candidate_count; w++) {
        printf("%s\n", candidates[w].name);
    }
    printf("\n");

    printf("Please enter the number of voters: ");
    while (num_voters <= 0) {
        scanf("%d", &num_voters);
    }
    while ((getchar()) != '\n'); // consumes newline left over from scanf

    for (int j=0; j < num_voters; j++) {
        char selected_candidate_name[MAX_NAME_LEN];

        printf("Enter who you'd like to vote for: ");
        fgets(selected_candidate_name, MAX_NAME_LEN, stdin);
        selected_candidate_name[strcspn(selected_candidate_name, "\n")] = 0; // clears newline from end of selected_candidate_name so 
                                                                             // that strcmp in vote function can properly compare names
        if (!vote(selected_candidate_name)) {
            printf("Invalid candidate name.\n");
        }
    }

    print_winner();

    return 0;
}

bool vote(char name[]) {
    for (int i=0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void) {
    int highestVoteCount = 0;

    for (int i=0; i < candidate_count; i++) {
        if (candidates[i].votes > highestVoteCount) {
            highestVoteCount = candidates[i].votes;
        }
    }

    for (int j=0; j < candidate_count; j++) {
        if (candidates[j].votes == highestVoteCount) {
            printf("%s\n", candidates[j].name);
        }
    }
}