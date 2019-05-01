/* this app is compiled: 
    g++ break_reminder.cpp -o <exe name> `pkg-config --cflags --libs libnotify` */

#include <libnotify/notify.h>
#include <iostream>
#include <time.h>

#define DURATION 30000 // 30 seconds
#define ESC '\x1B' // ascii code
#define MIN_TO_SEC 60

void init();
unsigned get_frequency();
// void info(unigned frequency);
void info();

bool show_notification(NotifyNotification *n);
NotifyNotification* create_notification();

int main()
{
    init();
    unsigned frequency = get_frequency();
    info();

    NotifyNotification* n = create_notification();

    while(true)
    {    
        sleep(frequency);
        show_notification(n);
        
        if (!show_notification(n)) 
        {
            std::cerr << "show has failed" << std::endl;
            return -1;
        }
    }

    
    return 0;
}

void init()
{
    std::system("clear");
    notify_init("First");
}

unsigned get_frequency()
{
    unsigned short freq;

    std::cout << "It is suggested to take 5-10 min break after every 50-60 min.\n";
    std::cout << "Please enter the lenght of your work intervals (in minutes): ";
    std::cin >> freq;

    unsigned int freq_milisec = freq*MIN_TO_SEC;
    return freq;
}
// void info(unsigned frequency)
void info()
{
    std::system("clear");
    // std::cout << "Notification reminders will be send every " << frequency/60000 << " minutes\n";
    std::cout << "Press ESC and ENTER to exit.\n";
}

NotifyNotification* create_notification()
{
    NotifyNotification* n = notify_notification_new ("You need to rest", 
                                                    "Let's take a break",
                                                                    0);
    notify_notification_set_timeout(n, DURATION);

    return n;
}

bool show_notification(NotifyNotification *n)
{
    return notify_notification_show(n, 0);
}