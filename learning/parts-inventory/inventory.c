#include <stdio.h>
#include "inventory.h"
#include "readline.h"
#include "quicksort.h"

int find_part(int number, int num_parts, struct part *inventory);
void insert(int *num_parts, struct part *inventory);
void search(struct part *inventory, int num_parts);
void update(struct part *inventory, int num_parts);
void print(int num_parts, struct part *inventory);

int main(void)
{
    struct part inventory[MAX_PARTS];

    int num_parts = 0;

    char code;

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch (code) {
            case 'i':
                insert(&num_parts, inventory);
                break;
            case 's':
                search(inventory, num_parts);
                break;
            case 'u':
                update(inventory, num_parts);
                break;
            case 'p':
                print(num_parts, inventory);
                break;
            case 'q':
                return 0;
            default:
                printf("Illegal code\n");
        }
        printf("\n");
    }
}

int find_part(int number, int num_parts, struct part *inventory) {
    int i;

    for (i=0; i < num_parts; i++) {
        if (inventory[i].number == number) {
            return i;
        }
    }

    return -1;
}

void insert(int *num_parts, struct part *inventory) {
    int part_number;

    if (*num_parts == MAX_PARTS) {
        printf("Database is full. Cannot add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &part_number);

    if (find_part(part_number, *num_parts, inventory) > 0) {
        printf("Part already exists.\n");
        return;
    }

    inventory[*num_parts].number = part_number;
    printf("Enter part name: ");
    read_line(inventory[*num_parts].name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &inventory[*num_parts].on_hand);
    printf("Enter item price (£25 = 2500): ");
    scanf("%d", &inventory[*num_parts].price);
    (*num_parts)++;
}

void search(struct part *inventory, int num_parts) {
    int i, number;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number, num_parts, inventory);

    if (i >= 0) {
        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity on hand: %d\n", inventory[i].on_hand);
        printf("Price: £%.2d\n", (inventory[i].price/100));
    } else {
        printf("Part not found.\n");
    }
}

void update(struct part *inventory, int num_parts) {
    int i, number, change, new_price;
    char selection1;
    char selection2;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number, num_parts, inventory);

    if (i < 0) {
        printf("Part not found.\n");
        return;
    }

    printf("Would you like to update the part quantity on hand? (y/n) ");
    scanf(" %c", &selection1);
    if (selection1 == 'y') {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inventory[i].on_hand += change;
    }

    printf("Would you like to update the part price? (y/n) ");
    scanf(" %c", &selection2);
    if (selection2 == 'y') {
        printf("Enter new price (£25 = 2500): ");
        scanf("%d", &new_price);
        inventory[i].price = new_price;
    }
}

void print(int num_parts, struct part *inventory) {
    int i;

    quicksort(inventory, 0, num_parts-1);

    printf("Part Number  Part Name  Quantity on Hand  Price\n");
    for (i=0; i < num_parts; i++) {
        printf("%7d %15s           %lld        £%.2d\n", inventory[i].number, inventory[i].name, inventory[i].on_hand, (inventory[i].price/100));
    }
}