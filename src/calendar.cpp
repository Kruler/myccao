/*************************************************************************
	> Author: Yqfclid 
	> Email: yqf@blackbird
	> Created Time: 2018-05-08 13:18:42
	> Thanks for your watching
 ************************************************************************/

#include <cstdio>
#include <time.h>
#include <cstring>

using namespace std;

class Calendar
{
private:
	int century;
	int year;
	int month;
	int days;
	int first_weekday;
public:
	Calendar(char *time);
	~Calendar();
	void print_calenday();
};

Calendar::Calendar(char *time)
{
	int monthday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	month = time[5] - '0' + (time[4] - '0') * 10;
	year = time[3] - '0' + (time[2] - '0') * 10;
	century = time[1] - '0' + (time[0] - '0') * 10 + 1;
	int whole_year = century * 100 + year;
	if((whole_year % 4 == 0 && whole_year % 100 != 0) || whole_year % 400 == 0)
	{
		monthday[1] = 29;
	}
	days = monthday[month - 1];
	int y = year;
	int c = century - 1;
	int m = 0;
	if(month <= 2)
		m = month + 12;
	else
		m = month;
	first_weekday = (y+(y/4)+(c/4)-2*c+(26*(m+1)/10)) % 7;
	if(first_weekday < 0)
		first_weekday = -first_weekday;
}

Calendar::~Calendar(){}

void Calendar::print_calenday()
{
	char *month_name[12] = {(char*)"January", 
							(char*)"February", 
							(char*)"May", 
							(char*)"March", 
							(char*)"April", 
							(char*)"June", 
							(char*)"July", 
							(char*)"August", 
							(char*)"Septermber", 
							(char*)"October", 
							(char*)"November", 
							(char*)"December"};
	printf("This is Calendar of %d %s\n", (century - 1) * 100 + year,month_name[month - 1]);
	printf("========================================\n");
	printf("Sun   Mon   Tue   Wed   Thu   Fri   Sat\n");
	for(int day = 1, line = -1; day <= days; day++)
	{
		if(day == 1)
		{
			int j = 0;
			while(j < first_weekday)
			{
				printf("      ");
				j++;
				line++;
			}
		}
		printf("%3d   ", day);
		line++;
		if(line % 7 == 6)
			printf("\n");
	}
	printf("\n");
	printf("========================================\n"); 
}

int main(int argc, char *argv[])
{
	char *timestr = new char[10];
	if(argc > 2)
	{
		printf("bad arg\n");
		return -1;
	}
	else if(argc == 2)
		strcpy(timestr, argv[1]);
	else
	{
    	time_t t = time(0);
    	struct tm* stime=localtime(&t); 
    	sprintf(timestr, "%d%02d", 1900 + stime->tm_year, 1 + stime -> tm_mon); 
	}
	for(int i = 0; i < 6;i++)
		if(*(timestr+i) - '0'>= 10 || *(timestr + i) - '0' < 0)
		{
			printf("bad arg\n");
			return -1;
		}
	Calendar a(timestr);
	a.print_calenday(); 
	delete []timestr;
	return 0;
}