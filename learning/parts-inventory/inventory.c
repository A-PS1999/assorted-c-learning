#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "readline.h"

struct part *find_part(int number, struct part **inventory);
void insert(struct part **inventory);
void search(struct part **inventory);
void update(struct part **inventory);
void delete(struct part **inventory);
void print(struct part **inventory);
void dump(struct part **inventory);
void restore(struct part **inventory);

int main(void)
{
    struct part *inventory = NULL;

    char code;

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch (code) {
            case 'i':
                insert(&inventory);
                break;
            case 's':
                search(&inventory);
                break;
            case 'u':
                update(&inventory);
                break;
            case 'e':
                delete(&inventory);
                break;
            case 'p':
                print(&inventory);
                break;
            case 'd':
                dump(&inventory);
                break;
            case 'r':
                restore(&inventory);
                break;
            case 'q':
                return 0;
            default:
                printf("Illegal code\n");
        }
        printf("\n");
    }
}

struct part *find_part(int number, struct part **inventory) {
    struct part *p;

    for (p = *inventory; p != NULL && number > p->number; p = p->next);
    if (p != NULL && p->number == number) {
        return p;
    }

    return NULL;
}

void insert(struct part **inventory) {
    struct part *curr, *prev, *new_node;

    new_node = malloc(sizeof(struct part));
    if (new_node == NULL) {
        printf("Database is full. Unable to add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &new_node->number);

    for (curr = *inventory, prev=NULL; curr != NULL && new_node->number > curr->number; prev = curr, curr = curr->next);

    if (curr != NULL && new_node->number == curr->number) {
        printf("Part already exists.\n");
        free(new_node);
        return;
    }

    printf("Enter part name: ");
    read_line(new_node->name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &new_node->on_hand);
    printf("Enter item price (£25 = 2500): ");
    scanf("%d", &new_node->price);
    
    new_node->next = curr;
    if (prev == NULL) {
        *inventory = new_node;
    } else {
        prev->next = new_node;
    }
}

void search(struct part **inventory) {
    int number;
    struct part *p;

    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(number, inventory);

    if (p != NULL) {
        printf("Part name: %s\n", p->name);
        printf("Quantity on hand: %d\n", p->on_hand);
        printf("Price: £%.2d\n", (p->price/100));
    } else {
        printf("Part not found.\n");
    }
}

void update(struct part **inventory) {
    int number, change, new_price;
    struct part *p;
    char selection1;
    char selection2;

    printf("Enter part number: ");
    scanf("%d", &number);
    p = find_part(number, inventory);

    if (p == NULL) {
        printf("Part not found.\n");
        return;
    }

    printf("Would you like to update the part quantity on hand? (y/n) ");
    scanf(" %c", &selection1);
    if (selection1 == 'y') {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        p->on_hand += change;
    }

    printf("Would you like to update the part price? (y/n) ");
    scanf(" %c", &selection2);
    if (selection2 == 'y') {
        printf("Enter new price (£25 = 2500): ");
        scanf("%d", &new_price);
        p->price = new_price;
    }
}

void delete(struct part **inventory) {
    int part_num_to_delete;
    struct part *curr, *prev, *part_to_delete;

    printf("Please enter the part number you'd like to delete: ");
    scanf("%d", &part_num_to_delete);

    part_to_delete = find_part(part_num_to_delete, inventory);
    if (part_to_delete == NULL) { // if no part with input number exists
        printf("No part with that number exists\n");
        return;
    }
    
    // below iterates through linked list until curr node->number matches number to delete
    for (curr=*inventory, prev=NULL; curr != NULL && curr->number != part_to_delete->number; prev=curr, curr = curr->next);

    if (prev == NULL) { // if this happens it means the entry to delete is at the head node
        *inventory = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr); // free unnecessary memory
}

void print(struct part **inventory) {
    struct part *p;

    printf("Part Number  Part Name  Quantity on Hand  Price\n");
    for (p=*inventory; p != NULL; p = p->next) {
        printf("%7d %15s           %lld        £%.2d\n", p->number, p->name, p->on_hand, (p->price/100));
    }
}

void dump(struct part **inventory) {
    FILE *to_write;
    char output_filename[21];
    struct part *curr_node;

    printf("Enter name of output file (max 20 characters): ");
    read_line(output_filename, 20);

    if ((to_write = fopen(output_filename, "wb")) == NULL) {
        printf("File opening failure. Please quit and try again.\n");
        return;
    }

    for (curr_node = *inventory; curr_node != NULL; curr_node = curr_node->next) {
        // to write everything in struct except 'struct part *next', we make size of fwrite be size of overall struct minus this final element
        fwrite(curr_node, sizeof(struct part) - sizeof(struct part *), 1, to_write);
    }
    fclose(to_write);

    printf("Inventory successfully written to %s\n", output_filename);
}

void restore(struct part **inventory) {
    FILE *input;
    char input_filename[21];
    char yesno;
    struct part curr_part;
    struct part *tempOne; // used for iterating through linked list to empty it
    struct part *tempTwo; // used for rebuilding linked list from data written to curr_part
    struct part *to_add;

    printf("This operation will clear the current inventory if one exists. Would you like to proceed? (y/n) ");
    scanf(" %c", &yesno);

    if (yesno == 'n') return;

    // destroy all nodes in linked list and free memory
    for (struct part *curr = *inventory; curr; curr = tempOne) {
        tempOne = curr->next;
        free(curr);
    }
    *inventory = NULL;

    printf("Enter name of input file: ");
    read_line(input_filename, 20);

    if ((input = fopen(input_filename, "rb")) == NULL) {
        printf("Failed to find or open the file %s\n", input_filename);
        return;
    }

    while ((fread(&curr_part, sizeof(struct part) - sizeof(struct part *), 1, input)) == 1) {
        if ((to_add = malloc(sizeof(struct part))) == NULL) {
            printf("Error: failed to allocate memory for part to restore. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        to_add->number = curr_part.number;
        to_add->on_hand = curr_part.on_hand;
        to_add->price = curr_part.price;
        strcpy(to_add->name, curr_part.name);
        to_add->next = NULL;

        if (*inventory == NULL) {
            *inventory = to_add;
            tempTwo = *inventory;
        } else {
            tempTwo->next = to_add;
        }
    }

    fclose(input);

    printf("Inventory successfully restored from file\n");
}