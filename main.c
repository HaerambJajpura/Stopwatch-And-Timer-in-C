#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/select.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif


int kbhit(void) {
    #ifdef _WIN32
        return _kbhit();
    #else
        struct timeval tv = {0L, 0L};
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        return select(1, &fds, NULL, NULL, &tv);
    #endif
}


void stopwatch() {
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    char input;


    printf("Press 's' to start the stopwatch.\n");
    do {
        #ifdef _WIN32
            input = _getch();
        #else
            input = getchar();
        #endif
    } while (input != 's');

    printf("Stopwatch started! Press 'q' to stop.\n");


    while (1) {
 
        printf("Stopwatch: %02d:%02d:%02d\r", hours, minutes, seconds);
        fflush(stdout);
        SLEEP(1000);


        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            hours++;
        }


        if (kbhit()) {
            #ifdef _WIN32
                input = _getch();
            #else
                input = getchar();
            #endif

            if (input == 'q') {
                break;
            }
        }
    }
    printf("\nStopwatch stopped at: %02d:%02d:%02d\n", hours, minutes, seconds);
}


void timer() {
    int hours, minutes, seconds;

    printf("Set the timer (format HH MM SS): ");
    scanf("%d %d %d", &hours, &minutes, &seconds);

    while (hours > 0 || minutes > 0 || seconds > 0) {
    
        printf("Timer: %02d:%02d:%02d\r", hours, minutes, seconds);
        fflush(stdout);
        SLEEP(1000); 


        if (seconds == 0) {
            if (minutes == 0) {
                if (hours == 0) {
                    break;
                } else {
                    hours--;
                    minutes = 59;
                    seconds = 59;
                }
            } else {
                minutes--;
                seconds = 59;
            }
        } else {
            seconds--;
        }
    }
    printf("\nTime's up! \a\n");
    Beep(400, 5000);
    Sleep(50); 
}

int main() {
    int choice;

    while (1) {
        printf("\nStopwatch and Timer\n");
        printf("1. Stopwatch\n");
        printf("2. Timer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                stopwatch();
                break;
            case 2:
                timer();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please select again.\n");
        }
    }
    return 0;
}
