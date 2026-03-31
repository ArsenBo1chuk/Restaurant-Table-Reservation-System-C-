#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE_NAME 30
#define DATE 11
#define TIME 6
#define MAX_SIZE_OF_RESERV 20
typedef struct reservation
{
  char m_name[SIZE_NAME];
  int m_guest;
  int m_tableNumber;
  char m_date[DATE];
  char m_time[TIME];
} reservation;
void printAllReservs(reservation reserv[MAX_SIZE_OF_RESERV])
{
  int isEmpty = 1;
  for (int i = 0; i < MAX_SIZE_OF_RESERV; i++)
  {
    if (reserv[i].m_name[0] != '\0')
    {
      isEmpty = 0;
      printf("\n ________________________________\n");
      printf("|Reservation №%d                  |\n", i + 1);
      printf("|________________________________|\n");
      printf("|Client name         |%-11s|\n", reserv[i].m_name);
      printf("|Number of guests    |%-11d|\n", reserv[i].m_guest);
      printf("|Table number        |%-11d|\n", reserv[i].m_tableNumber);
      printf("|Date of reservation |%-11s|\n", reserv[i].m_date);
      printf("|Reservation time    |%-11s|\n", reserv[i].m_time);
      printf("|____________________|___________|\n");
    }
  }
  if (isEmpty)
  {
    printf("\033[31mThere are no reservations\033[0m\n");
  }
}
void printReserv(reservation reserv[MAX_SIZE_OF_RESERV], int n)
{

      printf("\n ________________________________\n");
      printf("|Reservation №%d                  |\n", n + 1);
      printf("|________________________________|\n");
      printf("|Client name         |%-11s|\n", reserv[n].m_name);
      printf("|Number of guests    |%-11d|\n", reserv[n].m_guest);
      printf("|Table number        |%-11d|\n", reserv[n].m_tableNumber);
      printf("|Date of reservation |%-11s|\n", reserv[n].m_date);
      printf("|Reservation time    |%-11s|\n", reserv[n].m_time);
      printf("|____________________|___________|\n");
}

void printMenuOfFunc(void)
{
    const char *menu[] = {
        "[1] Add a new reservation",
        "[2] Display all reservations",
        "[3] Search for a reservation by customer name",
        "[4] Display reservation for a specific date",
        "[5] Delete reservation by table number",
        "[6] Edit an existing reservation",
        "[0] Exit"
    };

    printf("\n========== MENU ==========\n");
    for (int i = 0; i < 7; i++)
        printf("%s\n", menu[i]);
}

void addNewReservation(reservation reserv[MAX_SIZE_OF_RESERV])
{
  char mName[SIZE_NAME];
  int mGuest;
  int mTableNumber;
  char mDate[DATE];
  char mTime[TIME];

  int index = -1;
  for (int i = 0; i < MAX_SIZE_OF_RESERV; i++)
  {
    if (reserv[i].m_name[0] == '\0')
    {
      index = i;
      break;
    }
  }

  if (index == -1)
  {
    printf("\033[31mThere are no free seats\033[0m\n");
    return;
  }

  printf("Enter the customer's name: ");
  scanf("%s", mName);
  printf("Enter the number of guests: ");
  scanf("%d", &mGuest);

  printf("Enter table number: ");
  scanf("%d", &mTableNumber);
  while (1)
  {
    int isPreviosDate = 0;
    int conflict = 0;

    printf("Enter the booking date (dd.mm.yyyy): ");
    scanf("%s", mDate);

    printf("Enter the booking time (hh:mm): ");
    scanf("%s", mTime);
    int day, month, year;
    sscanf(mDate, "%d.%d.%d", &day, &month, &year);
    time_t now = time(NULL);
    struct tm today = *localtime(&now);


    struct tm booking = {0};
    booking.tm_mday = day;
    booking.tm_mon = month - 1;   
    booking.tm_year = year - 1900; 
    booking.tm_hour = 0;
    booking.tm_min = 0;
    booking.tm_sec = 0;

    time_t booking_time = mktime(&booking);


    today.tm_hour = 0;
    today.tm_min = 0;
    today.tm_sec = 0;
    time_t today_time = mktime(&today);

    if (booking_time < today_time)
    {
      printf("\033[31mUnable to book for past date\033[0m\n");
      continue;
    }

    for (int i = 0; i < MAX_SIZE_OF_RESERV; i++)
    {
      if (reserv[i].m_name[0] != '\0' &&
          reserv[i].m_tableNumber == mTableNumber &&
          strcmp(reserv[i].m_date, mDate) == 0 &&
          strcmp(reserv[i].m_time, mTime) == 0)
      {
        conflict = 1;
        break;
      }
    }

    if (conflict)
    {
      printf("\033[31mThe table is already booked at this time! Try another time.\033[0m\n");
      continue;
    }

    strcpy(reserv[index].m_name, mName);
    reserv[index].m_guest = mGuest;
    reserv[index].m_tableNumber = mTableNumber;
    strcpy(reserv[index].m_date, mDate);
    strcpy(reserv[index].m_time, mTime);

    printf("\033[32mThe table has been successfully booked!\033[0m\n");
    break;
  }
}

void searchReservationByNameOfClient(reservation reserv[MAX_SIZE_OF_RESERV])
{
  char mName[SIZE_NAME];
  printf("Enter the customer's name:");
  scanf("%s", mName);
  int nobody = 0;
  for (int count = 0; count < MAX_SIZE_OF_RESERV; count++)
  {
    if (reserv[count].m_name[0] != '\0' && strcmp(reserv[count].m_name, mName) == 0)
    {
      printReserv(reserv, count);
      nobody = 1;
    }
  }
  if (!nobody)
  {
    printf("\033[31mCould not find a customer with that name\033[0m\n");
  }
}

void searchReservationByDate(reservation reserv[MAX_SIZE_OF_RESERV])
{
  char mDate[SIZE_NAME];
  printf("Enter the date of the reservation (dd.mm.yyyy):");
  scanf("%s", mDate);
  int time = 0;
  for (int count = 0; count < MAX_SIZE_OF_RESERV; count++)
  {
    if (reserv[count].m_name[0] != '\0' && strcmp(reserv[count].m_date, mDate) == 0)
    {
      printReserv(reserv, count);
      time = 1;
    }
  }
  if (!time)
  {
    printf("\033[31mNo reservations found for this date\033[0m\n");
  }
}

void deleteReservation(reservation reserv[MAX_SIZE_OF_RESERV])
{
    int tableNumber;
    char date[DATE];
    char time[TIME];
    int found = -1;

    printf("Enter table number: ");
    scanf("%d", &tableNumber);

    printf("Enter the date of the reservation (dd.mm.yyyy): ");
    scanf("%s", date);

    printf("Enter the time of the reservation (hh:mm): ");
    scanf("%s", time);

    for (int i = 0; i < MAX_SIZE_OF_RESERV; i++)
    {
        if (reserv[i].m_name[0] != '\0' &&
            reserv[i].m_tableNumber == tableNumber &&
            strcmp(reserv[i].m_date, date) == 0 &&
            strcmp(reserv[i].m_time, time) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\033[31mReservation not found\033[0m\n");
        return;
    }


    for (int i = found; i < MAX_SIZE_OF_RESERV - 1; i++)
    {
        reserv[i] = reserv[i + 1];
    }


    reserv[MAX_SIZE_OF_RESERV - 1].m_name[0] = '\0';

    printf("\033[32mDeleted successfully!\033[0m\n");
}


void editReservation(reservation reserv[MAX_SIZE_OF_RESERV])
{
  int count = 0;
  int nomer;
  int n;
  int edited = 0;

  char mName[SIZE_NAME];
  char mDate[DATE];
  char mTime[TIME];
  int mGuest;
  int mTableNumber;
  char element[30];

  for (int i = 0; i < MAX_SIZE_OF_RESERV; i++)
  {
    if (reserv[i].m_name[0] != '\0')
      count++;
  }

  if (count == 0)
  {
    printf("\033[31mThere are no reservations\033[0m\n");
    return;
  }

  do
  {
    printf("Enter the reservation number (1-%d): ", count);
    scanf("%d", &nomer);
  } while (nomer < 1 || nomer > count);

  do
  {
    printf("Enter the number of items to edit (1-5): ");
    scanf("%d", &n);
  } while (n < 1 || n > 5);

  for (int i = 0; i < n; i++)
  {
    printf(
        "Enter the element (Customer_name; Number_of_guests; Table_number; Date; Time): ");
    scanf("%s", element);

    if (strcmp(element, "Customer_name") == 0)
    {
      printf("New name: ");
      scanf("%s", mName);
      strcpy(reserv[nomer - 1].m_name, mName);
    }
    else if (strcmp(element, "Number_of_guests") == 0)
    {
      printf("New number of guests: ");
      scanf("%d", &mGuest);
      reserv[nomer - 1].m_guest = mGuest;
    }
    else if (strcmp(element, "Table_number") == 0)
    {
      printf("New table number: ");
      scanf("%d", &mTableNumber);
      reserv[nomer - 1].m_tableNumber = mTableNumber;
    }
    else if (strcmp(element, "Date") == 0)
    {
      printf("New date: ");
      scanf("%s", mDate);
      strcpy(reserv[nomer - 1].m_date, mDate);
    }
    else if (strcmp(element, "Time") == 0)
    {
      printf("New time: ");
      scanf("%s", mTime);
      strcpy(reserv[nomer - 1].m_time, mTime);
    }
    else
    {
      printf("\033[31mUnknown element\033[0m\n");
      i--;
    }

    edited = 1;
    getchar(); 
  }

  if (edited)
    printf("\033[32mReservation successfully changed\033[0m\n");
}
int main()
{
  reservation reserv[MAX_SIZE_OF_RESERV] = {0};
  printMenuOfFunc();
  int nomerDii = 10;
  while (nomerDii)
  {
    printf("\033[34mEnter the reservation action number and press ENTER:\033[0m");
    scanf("%d", &nomerDii);
    if (nomerDii < 0 || nomerDii > 6)
    {
      printf("\033[31The action number you entered is incorrect. Please try again.\033[0m\n");
      continue;
    }
    if (nomerDii == 1)
    {
      addNewReservation(reserv);
    }
    if (nomerDii == 2)
    {
      printAllReservs(reserv);
    }
    if (nomerDii == 3)
    {
      searchReservationByNameOfClient(reserv);
    }
    if (nomerDii == 4)
    {
      searchReservationByDate(reserv);
    }
    if (nomerDii == 5)
    {
      deleteReservation(reserv);
    }
    if (nomerDii == 6)
    {
      editReservation(reserv);
    }
  }
  return 0;
}