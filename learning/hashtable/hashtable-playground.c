#include <stdio.h>
#include "hashtable.h"

int main(void)
{
    struct hashtable *hashtable = NULL;
    char code;
    int size_entry = 0;
    char search_name[HASHTABLE_NAME_MAX+1];

    for (;;) {
        printf("Enter option code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch (code) {
            case 'i':
                printf("Input hashtable array size: ");
                while (size_entry < 1) {
                    scanf(" %d", &size_entry);
                }
                hashtable = init_hashtable(size_entry);
                printf("Hashtable successfully initialised\n");
                size_entry = 0;
                break;
            case 'a':
                insert_entry(&hashtable);
                break;
            case 's':
                printf("Enter a name to search for in the hashtable (max 40 characters): ");
                fgets(search_name, HASHTABLE_NAME_MAX, stdin);
                trim_newline(search_name);
                struct list_node* result = search_hashtable(hashtable, search_name);
                if (result != NULL) {
                    print_item(result->data);
                } else {
                    printf("%s not found in the hashtable!\n", search_name);
                }
                break;
            case 'd':
                printf("Enter a name to delete from the hashtable (max 40 characters): ");
                fgets(search_name, HASHTABLE_NAME_MAX, stdin);
                trim_newline(search_name);
                delete_entry(&hashtable, search_name);
                break;
            case 'k':
                printf("Destroying hashtable...\n");
                free_hashtable(hashtable);
                hashtable = NULL;
                break;
            case 'q':
                return 0;
                break;
            default:
                printf("Invalid option code\n");
                break;
        }
    }
}