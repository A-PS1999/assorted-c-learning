#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

bool royal_flush, straight, flush, four, three;
int pairs;

void read_cards(int hand[NUM_CARDS][2]);
void analyze_hand(int hand[NUM_CARDS][2]);
void print_result(void);
bool check_for_duplicates(int rank, int suit, int hand[NUM_CARDS][2], int cards_read);

int main(void)
{
    int hand[NUM_CARDS][2];

    for (;;) {
        read_cards(hand);
        analyze_hand(hand);
        print_result();
    }
}

bool check_for_duplicates(int rank, int suit, int hand[NUM_CARDS][2], int cards_read) {
    for (int i = 0; i < cards_read; i++) {
        if (hand[i][0] == rank && hand[i][1] == suit) {
            return true;
        }
    }
    return false;
}

void read_cards(int hand[NUM_CARDS][2]) {
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
            case '0': exit(EXIT_SUCCESS);
            case '2': rank = 0; break;
            case '3': rank = 1; break;
            case '4': rank = 2; break;
            case '5': rank = 3; break;
            case '6': rank = 4; break;
            case '7': rank = 5; break;
            case '8': rank = 6; break;
            case '9': rank = 7; break;
            case 't':
            case 'T': rank = 8; break;
            case 'j':
            case 'J': rank = 9; break;
            case 'q':
            case 'Q': rank = 10; break;
            case 'k':
            case 'K': rank = 11; break;
            case 'a':
            case 'A': rank = 12; break;
            default: bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c':
            case 'C': suit = 0; break;
            case 'd':
            case 'D': suit = 1; break;
            case 'h':
            case 'H': suit = 2; break;
            case 's':
            case 'S': suit = 3; break;
            default: bad_card = true;
        }

        while ((ch = getchar()) != '\n') {
            if (ch != ' ') bad_card = true;
        }

        if (bad_card) {
            printf("Bad card, ignored.\n");
        } else if (check_for_duplicates(rank, suit, hand, cards_read)) {
            printf("Duplicate card, ignored.\n");
        } else {
            hand[cards_read][0] = rank;
            hand[cards_read][1] = suit;
            cards_read++;
        }
    }
}

void analyze_hand(int hand[NUM_CARDS][2]) {
    int rank, suit, card, pass, run;
    royal_flush = true;
    straight = true;
    flush = true;
    four = false;
    three = false;
    pairs = 0;

    for (pass = 1; pass < NUM_CARDS; pass++) {
        for (card = 0; card < NUM_CARDS - pass; card++) {
            rank = hand[card][0];
            suit = hand[card][1];
            if (hand[card+1][0] < rank) {
                hand[card][0] = hand[card+1][0];
                hand[card][1] = hand[card+1][1];
                hand[card+1][0] = rank;
                hand[card+1][1] = suit;
            }
        }
    }

    suit = hand[0][1];
    for (card = 1; card < NUM_SUITS-1; card++) {
        if (hand[card][1] != suit) {
            flush = false;   
        }
    }

    if (flush) {
        rank = hand[0][0];
        if (rank != 8) royal_flush = false;
        for (card = 1; card < NUM_CARDS-1; card++) {
            if (hand[card+1][0] != hand[card][0]+1) {
                royal_flush = false;
            }
        }
    } else {
        royal_flush = false;
    }

    for (card = 0; card < NUM_CARDS-1; card++) {
        if (hand[card][0]+1 != hand[card+1][0]) {
            straight = false;
        }
    }

    card = 0;
    while (card < NUM_CARDS) {
        rank = hand[card][0];
        run = 0;
        do {
            run++;
            card++;
        } while (card < NUM_CARDS && hand[card][0] == rank);
        switch (run) {
            case 2: pairs++; break;
            case 3: three = true; break;
            case 4: four = true; break;
        }
    }
}

void print_result(void) {
    if (royal_flush) printf("Royal flush");
    else if (straight && flush) printf("Straight flush");
    else if (four) printf("Four of a kind");
    else if (three && pairs == 1) printf("Full house");
    else if (flush) printf("Flush");
    else if (straight) printf("Straight");
    else if (three) printf("Three of a kind");
    else if (pairs == 2) printf("Two pairs");
    else if (pairs == 1) printf("Pair");
    else printf("High card");

    printf("\n\n");
}