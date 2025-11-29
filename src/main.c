#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exchange.h"
#include <conio.h>

int main()
{
    char choice;
	char msg[100] = "You selected option:";
	FILE *fp;
	const char *filePath= "C:/Personal/Siddhant/ExchangeRate/rates.csv";

  ReadCountries();
	while(1==1)
	{
        ClearScreen();
		Display("=============================================");
		Display("              Exchange Rate Menu");
		Display("=============================================");
		Display("1.  Display Exchange Rate for Code/Country for a month: yyyy-mm"); // 1 RECORD
		Display("2.  Display Exchange Rate for Code/Country for a Year: yyyy"); // 12 RECORD
		Display("3.  Display Exchange Rate for ALL Countries for a Year: YYYY");
		Display("4.  Display Exchange Rate for ALL for a month: yyyy-mm"); // show data for particular Year/Month
		Display("5.  Analyze Exchange Rate for Code/Country between Years: YYYY-YYYY");
		Display("6.  Change Color");
		Display("0.  Exit");
		Display("=============================================");

		Display("Enter your choice: ");
		scanf("%c", &choice);
  	switch(choice)
		{
			case '1':
			    fp = OpenCSVFile(filePath);

                if (!fp)
                {
                    Display("Error: Cannot open file.");
                    return 1;
                }
                ShowRatesForMonth(fp);
                getch();
                break;
			case '2':
				fp = OpenCSVFile(filePath);

				if (!fp)
				{
					Display("Error: Cannot open file.");
					return 1;
				}

				ShowRatesForYear(fp);
				fclose(fp);
				getch();
				break;
			case '3':
                fp = OpenCSVFile(filePath);

                if (!fp)
                {
                    Display("Error: Cannot open file.");
                    return 1;
                }
                ClearScreen();
//                currentScreen = 3;
                StoreRatesForAllCountriesInYear(fp, 4);
                fclose(fp);
				getch();
				break;
			case '4':
				fp = OpenCSVFile(filePath);

                if (!fp)
                {
                    Display("Error: Cannot open file.");
                    return 1;
                }
                ClearScreen();
//                currentScreen = 3;

                StoreRatesForAllCountriesInYear(fp, 7);
                fclose(fp);
				getch();
				break;
			case '5':
                fp = OpenCSVFile(filePath);
                if (!fp)
				{
					Display("Error: Cannot open file.");
					return 1;
				}

                AnalyzeCountryBetweenYears(fp);
                fclose(fp);
                getch();
				break;
			case '6':
				Display("Enter your Color choice: ");
				scanf("%d", &colorchoice);
                sprintf(msg, "You selected option: %d", colorchoice);
				Display(msg);
				getch();
				break;
			case '0':
			    exit(0);
     } 
	}
}
