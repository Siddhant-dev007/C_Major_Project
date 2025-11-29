#include "exchange.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int colorchoice = 0;
CurrencyInfo structCountry[MAX_COUNTRIES];

const char ShowRatesForYear_Title[100] = "Display Exchange Rate for Code/Country for a month";
const char ShowRatesForMonth_Title[100] = "Display Exchange Rate for Code/Country for a Year";
const char AnalyzeCountryBetweenYears_Title[100] = "Analyze Exchange Rate for Code/Country between Years";
const char ShowRatesForAllCountriesInYear_Title[100] = "Exchange Rate for All Countries for a Year";

void ShowRatesForYear(FILE *fp)
{
    char line[1024];
    char *columns[MAX_COLS];
    int targetCol = -1;
    char message[100];
    char country[10], year[10];

    ClearScreen();
    Display(ShowRatesForYear_Title);
    Display("\nEnter Country Code (e.g. USD, INR, AED): ");
    scanf("%s", country);
    strupr(country);

    Display("Enter Year (YYYY): ");
    scanf("%s", year);

    rewind(fp);   // go back to top of CSV file

    // ========= Read Header to Locate Country Column =========
    if (!fgets(line, sizeof(line), fp)) {
        printf("Error reading header row.\n");
        return;
    }
    line[strcspn(line, "\r\n")] = '\0';

    int colCount = parseCSV(line, columns, MAX_COLS);

    for (int i = 0; i < colCount; i++) {
        if (strcmp(columns[i], country) == 0) {
            targetCol = i;
            break;
        }
    }

    if (targetCol == -1)
    {
        printf("Country code '%s' not found.\n", country);
        return;
    }

    sprintf(message, "Exchange Rates for %s in %s\n", country, year);
    Display(message);
    Display("----------------------------------------");

    // ========= Read Monthly Rows =========
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = '\0';

        int count = parseCSV(line, columns, MAX_COLS);
        if (count <= targetCol) continue;

        // date is in columns[0], e.g. "2024-03"
        if (strncmp(columns[0], year, 4) == 0)
        {
            sprintf(message, "%s : %s\n", columns[0], columns[targetCol]);
            Display(message);
        }
    }

    Display("----------------------------------------");
}
void ShowRatesForMonth(FILE *fp)
{
    char line[1024];
    char *columns[MAX_COLS];
    int targetCol = -1;
    char message[200];
    char country[10], month[10];
    ClearScreen();
    Display(ShowRatesForMonth_Title);
    Display("\nEnter Country Code (e.g. USD, INR, AED): ");
    scanf("%s", country);
    strupr(country);

    Display("Enter Month (YYYY-MM): ");
    scanf("%s", month);

    rewind(fp);  // Go back to the top of the CSV file

    // ========= Read Header Row to Locate Country Column =========
    if (!fgets(line, sizeof(line), fp))
    {
        Display("Error reading header row.\n");
        return;
    }
    line[strcspn(line, "\r\n")] = '\0';

    int colCount = parseCSV(line, columns, MAX_COLS);

    for (int i = 0; i < colCount; i++) {
        if (strcmp(columns[i], country) == 0) {
            targetCol = i;
            break;
        }
    }

    if (targetCol == -1)
    {
        sprintf(message, "Country code '%s' not found.\n", country);
        Display(message);
        return;
    }

    // ========= Search CSV Rows for the exact month =========
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = '\0';

        int count = parseCSV(line, columns, MAX_COLS);
        if (count <= targetCol) continue;

        // date is in columns[0], e.g. "2024-03"
        if (strcmp(columns[0], month) == 0)
        {

            sprintf(message, "Exchange Rate for %s %s in %s : %s", GetCountryByCode(country), country, month, columns[targetCol]);
            //printf("\nExchange Rate for %s in %s : %s\n", country, month, columns[targetCol]);
            Display(message);
            return;  // stop after finding the month
        }
    }

    sprintf(message, "No exchange rate found for %s in %s.\n", country, month);
}

void AnalyzeCountryBetweenYears(FILE *fp)
{
    ClearScreen();
    Display(AnalyzeCountryBetweenYears_Title);

    char line[2000];
    char *columns[MAX_COLS];
    int targetCol = -1;
    char message[200];
    char country[10];
    char startYear[10];
    char endYear[10];

    Display("\nEnter Country Code (e.g. USD, INR, AED): ");
    scanf("%s", country);
    strupr(country);

    Display("Enter Start Year (YYYY): ");
    scanf("%s", startYear);

    printf("Enter End Year (YYYY): ");
    scanf("%s", endYear);

    rewind(fp);

    // ---------- Read Header ----------
    if (!fgets(line, sizeof(line), fp))
    {
        printf("Error reading header.\n");
        return;
    }
    line[strcspn(line, "\r\n")] = '\0';
    int colCount = parseCSV(line, columns, MAX_COLS);

    // Find country index
    for (int i = 0; i < colCount; i++)
    {
        if (strcmp(columns[i], country) == 0) {
            targetCol = i;
            break;
        }
    }

    if (targetCol == -1)
    {
        printf("Country code '%s' not found.\n", country);
        return;
    }

    printf("\nAnalyzing Exchange Rate for %s between %s and %s\n",
           country, startYear, endYear);
    printf("------------------------------------------------------\n");

    double minRate = 1e18, maxRate = -1e18, sum = 0;
    int count = 0;

    // ---------- Read Each Row ----------
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = '\0';
        int colCnt = parseCSV(line, columns, MAX_COLS);
        if (colCnt <= targetCol) continue;

        char yearPart[5];
        strncpy(yearPart, columns[0], 4);
        yearPart[4] = '\0';

        // If year within range
        if (strcmp(yearPart, startYear) >= 0 && strcmp(yearPart, endYear) <= 0)
        {
            sprintf(message, "%s : %s", columns[0], columns[targetCol]);

            Display(message);
            count++;

            double rate;

            if (sscanf(columns[targetCol], "%lf", &rate) != 1)
            { rate = 0; }

            if (rate > 0)
            {      // ignore empty or invalid
                if (rate < minRate) minRate = rate;
                if (rate > maxRate) maxRate = rate;
                sum += rate;
                count++;
            }
        }
    }

    Display("------------------------------------------------------\n");

    if (count == 0)
    {
        Display("No data found for the selected range.");
        return;
    }

    sprintf(message,
    "Summary for %s (%s–%s):\n"
    "  Minimum Rate : %.4f\n"
    "  Maximum Rate : %.4f\n"
    "  Average Rate : %.4f\n"
    "------------------------------------------------------\n",
    country, startYear, endYear,
    minRate, maxRate, sum / count);
    Display(message);
}

void StoreRatesForAllCountriesInYear(FILE *fp, int MonthorYear)
{
    int MAX_HEADER_LEN = 16;
    char line[MAX_LINE];
    char *columns[MAX_COLS];
    char headers[MAX_COLS][MAX_HEADER_LEN];  // persistent storage for headers
    int colCount = 0;
    char year[10];
    char storeFilename[100] = "C:/Personal/Siddhant/";
    char message[100];

    ClearScreen();
    Display(ShowRatesForAllCountriesInYear_Title);

    if(MonthorYear == 4)
    {
    Display("Enter Year (YYYY): ");
    scanf("%s", year);
    strcpy(storeFilename, "C:/Personal/Siddhant/ExchangeRate_Year.txt");
    }
    else if(MonthorYear == 7)
    {
    Display("Enter Year & Month (YYYY-MM): ");
    scanf("%s", year);
    strcpy(storeFilename, "C:/Personal/Siddhant/ExchangeRate_Month.txt");
    }


    // ========= Read header row =========
    if (!fgets(line, sizeof(line), fp)) {
        printf("Error reading header row.\n");
        return;
    }
    line[strcspn(line, "\r\n")] = '\0';
    char *tempCols[MAX_COLS];
    colCount = parseCSV(line, tempCols, MAX_COLS);

    // Copy headers into persistent array
    for (int i = 0; i < colCount; i++)
    {
//        trim(tempCols[i]);
        strncpy(headers[i], tempCols[i], MAX_HEADER_LEN - 1);
        headers[i][MAX_HEADER_LEN - 1] = '\0';
    }

    // Open output file for writing
    FILE *out = fopen(storeFilename, "w");
    if (!out) {
        printf("Error: Cannot open output file %s\n", storeFilename);
        return;
    }

    fprintf(out, "Year: %s\n", year);
    fprintf(out, "Currency   Rate        Country\n");

    // ========= Read monthly rows =========
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = '\0';
        int colsInLine = parseCSV(line, columns, MAX_COLS);

        // Filter by year
        if (strncmp(columns[0], year, MonthorYear) != 0)
            continue;

        // Write each country's rate
        for (int i = 1; i < colCount && i < colsInLine; i++) {
//            trim(columns[i]);
            if (strlen(columns[i]) > 0)
                fprintf(out, "%-8s %-12s  -> %s\n", headers[i], columns[i], GetCountryByCode(headers[i]));
        }
    }

    fclose(out);
    sprintf(message, "Rates for %s stored successfully in %s\n", year, storeFilename);
    Display(message);
}

FILE* OpenCSVFile(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("Error: Cannot open CSV file: %s\n", path);
        return NULL;
    }
    return fp;
}

void Display(const char *msg)
{
//    screenRowCount++;
	switch(colorchoice)
	{

		case 1: // Blue
		printf("\033[1;34m%s\n\033[0m", msg);
		break;
		case 2: // Cyan
        printf("\033[1;36m%s\n\033[0m", msg);
		break;
		case 3: // Mangeta
		printf("\033[1;35m%s\n\033[0m", msg);
		break;

		default:
		printf("\033[1;37m%s\n\033[0m", msg);
	}
}

void ClearScreen()
{
    system("cls"); //clrscr;

}

int parseCSV(char *line, char *cols[], int maxCols)
{
    int col = 0;
    char *start = line;

    while (*line && col < maxCols)
    {
        if (*line == ',')
        {
            *line = '\0';
            cols[col++] = start;
            start = line + 1;
        }
        line++;
    }

    // last column
    if (col < maxCols)
        cols[col++] = start;

    return col;
}

void ReadCountries()
{
    char *filePath= "C:/Personal/Siddhant/ExchangeRate/All-Countries.csv";
    FILE *fp = OpenCSVFile(filePath);
    char line[MAX_LINE];
    int colsInLine = 0;
    int rowCount = 0;
    //CurrencyInfo result[300];

    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = '\0';
        char *tempCols[MAX_COLS];

        colsInLine = parseCSV(line, tempCols, MAX_COLS);

        if(colsInLine >= 3)
        {

            strcpy(structCountry[rowCount].code ,tempCols[0]);
            strcpy(structCountry[rowCount].country , tempCols[2]);
            strcpy(structCountry[rowCount].desc , tempCols[1]);

        }

        rowCount++;
    }

// ===== Print all countries =====
    printf("Code -> Country\n");
    for (int i = 0; i < rowCount; i++)
    {
        printf("%s -> %s  %s\n", structCountry[i].code, structCountry[i].country, structCountry[i].desc);
    }
}

const char* GetCountryByCode(const char *code)
{
    for (int i = 0; i < MAX_COUNTRIES; i++)
    {
        if (strcmp(structCountry[i].code, code) == 0)
            return structCountry[i].country;  // return country string
    }
    return NULL;  // not found
}
