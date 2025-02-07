#ifndef CALC_H
#define CALC_H

//ВАЖНО иначе не пашет
#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //для дифферен калькулятора, чтоб узнать текущую дату

#define MAX_SIZE 255
extern int arrDaysInMonth[12];
extern char *arrMonthNames[12];

// CREDIT CALCULATOR FUNCTIONS
int isLeapYear(int year);  //високосный год или нет: 0 - нет, 1 - да
int annuityCreditCalc(long double percent, long double sum, int month,
                      long double *monthPayment, long double *over,
                      long double *total);
int differCreditCalc(long double percent, long double sum, int month,
                     long double *monthPayment, long double *over,
                     long double *total);
int creditCalc(long double percent, long double sum, int typeTime, int time,
               int type, long double **monthPayment, long double *over,
               long double *total);
int isLeapYear(int year);

// DEPOSIT FUNCTIONS
/*
    in Deposit calculator functions
postingPeriod (срок размещения в каких величинах): 0 - in days, 1 - in month, 2
- in years timeOfPositnd: срок размещения в единицах interest - процентная
ставка payoutPeriod - периодичность выплат: 0 - в конце срока, 1 - каждый день,
2 - каждую неделю, 3 - месяц, 4 - квартал, 5- полгода, 6 - год total - сумма
вклад+проценты gainedInterest - прирост капитала в % taxSum - сумма налога
(зависит от периодичности выплат) Withdraw - структура которая хранит данные о
выплате: дата, сумма, адрес на следующую выплату capitalization(капитализация
процентов): 1 - да, 0 - нет capitalizationPeriod(периодичность капитализации) =
payoutPeriod: 1 - каждый день, 2 - каждую неделю, 3 - месяц, 4 - квартал, 5 -
полгода, 6 - год
*/
void lastDayOfDeposit(int startDay, int startMonth, int startYear,
                      int postingPeriod, int timeOfPosting, int *endDay,
                      int *endMonth, int *endYear);
long double income(
    long double sum, long double interest, int year,
    int days);  //прибыль с вкладов в указанном году за столько дней
int daysTillEndOfYear(int day, int month,
                      int year);  // дней с указанной даты до конца года
int daysTillGivenDate(int day, int month,
                      int year);  // дней с начала года до указанной даты
long double tax(long double sum, long double inputTax);
int daysInMonth(
    int year,
    int month);  //возвращает количество дней по заданному году и месяцу
void calcPayDate(const int startDay, const int startMonth, const int startYear,
                 const int finDay, const int finMonth, const int finYear,
                 int payoutPeriod, int *endDay, int *endMonth, int *endYear);
int dateOverEndDeposit(const int finDay, const int finMonth, const int finYear,
                       int day, int month, int year);
long double calcPayForPeriod(long double sum, long double interest,
                             int startDay, int startMonth, int startYear,
                             int endDay, int endMonth, int endYear);
int daysInYearPeriod(int startDay, int startMonth, int startYear, int endDay,
                     int endMonth);
void depositCalc(int startDay, int startMonth, int startYear, long double sum,
                 int postingPeriod, int timeOfPosting, long double interest,
                 int payoutPeriod, long double *total,
                 long double *gainedInterest, long double *taxSum,
                 int capitalization, long double inputTax);

// PARCER TO REVERSE POLISH NOTATION FUNCTIONS
typedef struct {
  char data[MAX_SIZE];
  int top;
} Stack;
int checkExpres(const char *inputExpr, char *outputExpr);
void printFuncName(char c);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, char c);
char pop(Stack *stack);
char peek(Stack *stack);
int is_operand(char symbol);
int is_function(char symbol);
void change_expr(char *expr);
int priority(char c);
int parsing_to_RPN(const char *expr, char *outputExpr);
int operAfterPow(char c);


// calcExpr.c
int calcExpr(const char *parExpr, long double *result);
int stringToDouble(
    const char *parExpr, int *start,
    long double *number);  //найти конец числа и перевести часть строки от start
                           //- finish в long double
int is_oneOperandFunction(
    char c);  //проверка на функцию требующую 1 операнд (число)
int calcOneOperandFunction(long double numbers[], int topNumber,
                           char c);  //вычисление функции с одним числом
int calcTwoOperandFunction(long double numbers[], int *topNumber,
                           char c);  //вычисление функции с двумя числами
int isXinExpr(const char *parExpr);

// plot GRAPH
int calcPlotExprWithX(const char *expr, long double x, long double *result);
int replaceXinPlotExpr(const char *expr, char *outputExpr, long double x);
int calcInputExprAndX(const char *sendExpr, long double X,
                      long double *calculation);

#ifdef __cplusplus
}
#endif

#endif
