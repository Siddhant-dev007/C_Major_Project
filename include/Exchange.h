#include <stdio.h>

#define MAX_COLS 200
#define MAX_LINE 2000
#define MAX_COUNTRIES 300

typedef struct
{
    char code[4];
    char country[200];
    char desc[50];
} CurrencyInfo;

extern int colorchoice;

extern const char ShowRatesForYear_Title[100];
extern const char ShowRatesForMonth_Title[100];
extern const char AnalyzeCountryBetweenYears_Title[100];
extern const char PreferencesColor_Title[100];


extern const char ShowRatesForAllCountriesInYear_Title[100];
extern const char outputFilePath[100];

void ShowRatesForYear(FILE *fp);
void ShowRatesForMonth(FILE *fp);
void AnalyzeCountryBetweenYears(FILE *fp);
void StoreRatesForAllCountriesInYear(FILE *fp, int MonthorYear);

FILE* OpenCSVFile(const char *path);

void Display(const char *msg);
void ClearScreen();
void ReadCountries();

int parseCSV(char *line, char *cols[], int maxCols);

const char* GetCountryByCode(const char *code);
