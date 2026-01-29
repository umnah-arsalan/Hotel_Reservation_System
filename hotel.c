#include<stdio.h>
#include<string.h>
#include "hotel.h"

int days_in_month(int m, int y) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
        return 29;

    return days[m - 1];
}

int date_to_days(int d, int m, int y) {
    int total = 0;

    for (int i = 1; i < y; i++) {
        total += ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) ? 366 : 355;
    }

    for (int i = 1; i < m; i++) {
        total += days_in_month(m, y);
    }

    total += d;

    return total;
}

int days_stayed(char *in, char *out) {
    int d1, m1, y1, d2, m2, y2;

    sscanf(in, "%d-%d-%d", &d1, &m1, &y1);
    sscanf(out, "%d-%d-%d", &d2, &m2, &y2);

    return date_to_days(d2, m2, y2) - date_to_days(d1, m1, y1);
}

void init_room() {
    FILE *fp = fopen(ROOM_FILE, "wb");
    struct Room r;

    for (int i = 1; i <= 20; i++) {
        r.room_no = i;
        r.is_booked = 0;
        r.is_checked_in = 0;
        strcpy(r.guest_name, "");
        strcpy(r.checkin_date, "");
        strcpy(r.checkout_date, "");
        r.rate = 2000.00;

        fwrite(&r, sizeof(r), 1, fp);
    }
    fclose(fp);
}

void show_available_rooms() {
    FILE *fp = fopen(ROOM_FILE, "rb");
    struct Room r;

    printf("\nAvailable Rooms:\n");

    while (fread(&r, sizeof(r), 1, fp)) {
        if (!r.is_booked && !r.is_checked_in) {
            printf("Room %d (%.2f per night)\n",
                   r.room_no, r.rate);
        }
    }
    printf("\n");

    fclose(fp);
}

void book_room() {
    FILE *fp = fopen(ROOM_FILE, "rb+");
    struct Room r;
    int room_no;

    printf("Enter Room Number: ");
    scanf("%d", &room_no);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.room_no == room_no && !r.is_booked) {

            printf("Guest Name: ");
            scanf(" %[^\n]", r.guest_name);

            printf("Check-in Date (DD-MM-YYYY): ");
            scanf("%s", r.checkin_date);

            printf("Check-out Date (DD-MM-YYYY): ");
            scanf("%s", r.checkout_date);

            r.is_booked = 1;

            fseek(fp, -sizeof(r), SEEK_CUR);
            fwrite(&r, sizeof(r), 1, fp);

            printf("\nRoom booked successfully!\n\n");
            fclose(fp);
            return;
        }
    }

    printf("\nRoom unavailable!\n\n");
    fclose(fp);
}

void check_in() {
    FILE *fp = fopen(ROOM_FILE, "rb+");
    struct Room r;
    int room_no;

    printf("\nEnter room Number: ");
    scanf("%d", &room_no);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.room_no == room_no && r.is_booked) {
            r.is_checked_in = 1;

            fseek(fp, -sizeof(r), SEEK_CUR);
            fwrite(&r, sizeof(r), 1, fp);

            printf("\nCheck-in successful!\n\n");
            fclose(fp);
            return;
        }
    }

    printf("\nRoom not booked!\n\n");
    fclose(fp);
}

void check_out() {
    FILE *fp = fopen(ROOM_FILE, "rb+");
    struct Room r;
    int room_no;

    printf("\nEnter room number: ");
    scanf("%d", &room_no);

    while (fread(&r, sizeof(r), 1, fp)) {
        if (r.room_no == room_no && r.is_checked_in) {
            int days = days_stayed(r.checkin_date, r.checkout_date);
            float bill = days * r.rate;

            printf("Guest: %s\n", r.guest_name);
            printf("Days Stayed: %d\n", days);
            printf("Total Bill: %.2f\n", bill);

            r.is_booked = 0;
            r.is_checked_in = 0;
            strcpy(r.guest_name, "");
            strcpy(r.checkin_date, "");
            strcpy(r.checkout_date, "");

            fseek(fp, sizeof(r),SEEK_CUR);
            fwrite(&r, sizeof(r), 1, fp);

            printf("\nCheck-out completed!\n\n");
            fclose(fp);
            return;
        }
    }

    printf("\nRoom not checked!\n\n");
    fclose(fp);
}