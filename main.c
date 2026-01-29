#include<stdio.h>
#include<stdlib.h>
#include "hotel.h"

int main() {
    int choice;

    while (1) {
        printf("1. Show Available Rooms");
        printf("\n2. Book Room");
        printf("\n3. Check In");
        printf("\n4. Check Out");
        printf("\n5. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: show_available_rooms(); break;
            case 2: book_room(); break;
            case 3: check_in(); break;
            case 4: check_out(); break;
            case 5: exit(0);
        }
    }
}
