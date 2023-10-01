#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef enum BetType { ODD = 0, EVEN, NUM } BetType;

int genRandomNum(void);
void handleBetting(int* availableCash, int* bet, BetType* typeOfBet, int* betNum);
void setBetNum(int* betNum);
void handlePayout(int randNum, int* cashOnHand, int betAmount, BetType betType, int betNum);
void handleOddEvenBet(int randNum, int* cashOnHand, int betAmount, BetType type);
void handleNumBet(int randNum, int* cashOnHand, int betAmount, int betNum);
bool isValidBetType(BetType* type);
bool isValidBetAmount(int betAmount, int maxCash);
bool isValidBetNum(int betNum);

int main(void) {

    int cashOnHand = 10000;
    int randomlyGennedNum;
    int betAmount;
    int betNum;
    BetType typeOfBet;

    srand(time(NULL));

    printf("Welcome to the roulette game!\n");
    printf("A number will be randomly selected from 0-35. You can bet on odd or even, or on a specific number.\n");
    printf("A winning odd/even bet is paid off at 2 to 1, except if the selected number is 0 in which case they lose.\n");
    printf("Bets on a specific number pay off at 35 to 1 if you get lucky.\n");
    printf("You start out with £10000 in cash. See how long you can go before you lose it all!\n");

    while (cashOnHand > 0) {
        randomlyGennedNum = genRandomNum();
        handleBetting(&cashOnHand, &betAmount, &typeOfBet, &betNum);
        handlePayout(randomlyGennedNum, &cashOnHand, betAmount, typeOfBet, betNum);
        printf("Your cash on hand is now £%d.\n", cashOnHand);
    }

    printf("Looks like you ran out of cash! Game over.\n");

    return 0;
}

int genRandomNum(void) {
    return rand() % (35 + 1 - 0) + 0;
}

bool isValidBetType(BetType* type) {
    switch (*type) {
        case ODD:
        case EVEN:
        case NUM:
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool isValidBetAmount(int betAmount, int maxCash) {
    if ((betAmount <= 0) || (betAmount > maxCash)) {
        return false;
    } else {
        return true;
    }
}

bool isValidBetNum(int betNum) {
    if (betNum >= 0 && betNum <= 35) {
        return true;
    } else {
        return false;
    }
}

void handleBetting(int* availableCash, int* bet, BetType* typeOfBet, int* betNum) {
    char buffer[256];
    int betAmount = 0;

    printf("What type of bet would you like to make? Enter a number from the below list.\n");
    printf("0 = Bet that the number will be odd.\n");
    printf("1 = Bet that the number will be even.\n");
    printf("2 = Bet on a specific number.\n");

    do {
        if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
            sscanf(buffer, "%d", typeOfBet);
        }
    } while (!isValidBetType(typeOfBet));

    if (*typeOfBet == NUM) {
        setBetNum(betNum);
    } else {
        *betNum = -99;
    }

    printf("Enter the amount you'd like to bet: ");

    while (!isValidBetAmount(betAmount, *availableCash)) {
        if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
            sscanf(buffer, "%d", &betAmount);
        }
    }

    *availableCash -= betAmount;
    *bet = betAmount;
}

void setBetNum(int* betNum) {
    char buffer[5];

    printf("What number would you like to bet on?\n");
    printf("Remember that the number will only ever be between 0-35: ");

    do {
        if((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
            sscanf(buffer, "%d", betNum);
        }
    } while (!isValidBetNum(*betNum));
}

void handlePayout(int randNum, int* cashOnHand, int betAmount, BetType betType, int betNum) {
    switch(betType) {
        case ODD:
        case EVEN:
            handleOddEvenBet(randNum, cashOnHand, betAmount, betType);
            break;
        case NUM:
            handleNumBet(randNum, cashOnHand, betAmount, betNum);
            break;
    }
}

void handleOddEvenBet(int randNum, int* cashOnHand, int betAmount, BetType type) {
    switch (type) {
        case ODD:
            if (randNum % 2 != 0) {
                printf("The roulette ball landed on %d. You won the bet!\n", randNum);
                *cashOnHand += (betAmount*2);
            } else {
                printf("Uh oh, the number was %d. You lost the bet.\n", randNum);
            }
            break;
        case EVEN:
            if (randNum % 2 == 0) {
                printf("The roulette ball landed on %d. You won the bet!\n", randNum);
                *cashOnHand += (betAmount*2);
            } else {
                printf("Uh oh, the number was %d. You lost the bet.\n", randNum);
            }
            break;
        default:
            break;
    }
}

void handleNumBet(int randNum, int* cashOnHand, int betAmount, int betNum) {
    if (randNum == betNum) {
        printf("Congratulations! The number you bet, %d, was precisely what the roulette ball landed on!\n");
        *cashOnHand += (betAmount * 35);
    } else {
        printf("Sorry, you took a risk and it didn't pay off. The ball landed on %d, not %d.\n", randNum, betNum);
    }
}