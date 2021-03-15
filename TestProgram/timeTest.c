#define _XOPEN_SOURCE
#include <stdio.h>
#include <time.h>

int timeTest()
{   
    /****** Declarations ******/
    time_t timeInSec;
    time_t timeInSec2;
    struct tm curDate;
    struct tm inputDate;
    int daydiff, retDays;
    char sDate[] = "2020/9/4";
    
    /***** Mainline *****/
    timeInSec = time(NULL);
    printf("Seconds since 01:01:1970: %i\n", (int)timeInSec);
    curDate = *localtime(&timeInSec);
    printf("Today's date: %s", asctime(&curDate));
    printf("Today's month: %i\n", curDate.tm_mon);
    printf("Today's year: %i\n\n", curDate.tm_year);
    
    /*** Move month number by 36 and mktime() it ***/
    curDate.tm_mon += 36;
    printf("Month moved: %i\n", curDate.tm_mon);
    printf("Moved year: %i\n\n", curDate.tm_year);
    timeInSec2 = mktime(&curDate);
    printf("Moved seconds since 1970: %i\n", (int)timeInSec2);
    printf("Moved date: %s", asctime(&curDate));
    printf("Moved month: %i\n", curDate.tm_mon);
    printf("Moved year: %i\n\n", curDate.tm_year);
    
    /*** Format input date and fill inputDate struct ***/
    // strptime(sDate, "%Y/%m/%d", &inputDate);
    // inputDate.tm_hour = 0;
    // inputDate.tm_min = 0;
    // inputDate.tm_sec = 0;
    // printf("Input date: %s", asctime(&inputDate));
    // printf("Input month: %i\n", inputDate.tm_mon);
    // printf("Input year: %i\n", inputDate.tm_year);
    // printf("Input day: %i\n", inputDate.tm_mday);
    
    /*** Compare dates ***/
    printf("Input date: %s", asctime(&inputDate));
    printf("Current date: %s", asctime(localtime(&timeInSec)));
    printf("Input RETAINDAYS value:");
    scanf("%i", &retDays);
    printf("*** Compare dates considering retaindays value ***\n");
    daydiff = difftime(timeInSec, mktime(&inputDate));
    printf("Difference in seconds %i\n", daydiff);
    daydiff = (int)(daydiff / (24*60*60));
    printf("Difference in days %i\n", daydiff);
    if (daydiff > retDays){
        printf("Date is passed...\n");
    }
    else{
        printf("OK to continue...\n");
    }
    
    return 0;
}


