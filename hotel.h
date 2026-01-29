#ifndef HOTEL_H
#define HOTEL_H

#define ROOM_FILE "rooms.dat"

struct Room {
    int room_no;
    int is_booked;
    int is_checked_in;
    char guest_name[30];
    char checkin_date[11];
    char checkout_date[11];
    float rate;
};

int days_in_month(int m, int y);
int date_to_days(int d, int m, int y);
int days_stayed(char *in, char *out);
void init_room(void);
void show_available_rooms(void);
void book_room(void);
void check_in(void);
void check_out(void);

#endif