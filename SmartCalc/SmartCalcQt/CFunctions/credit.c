#include "../CHeader.h"

// int arrDaysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
// char *arrMonthNames[12] = {"January", "February", "March", "April","May",
// "June", "July", "August", "September","October", "November", "December"};
/*
typeTime: 0 - years, 1 - month
type: 0 - annuity, 1 - differentiated

*/
int creditCalc(long double percent, long double sum, int typeTime, int time,
               int type, long double **monthPayment, long double *over,
               long double *total) {
  int ret = 0;
  int month = (typeTime == 0 ? time * 12 : time);
  if (type == 0) {
    *monthPayment = calloc(month, sizeof(long double));
    ret = annuityCreditCalc(percent, sum, month, *monthPayment, over, total);
  } else {
    *monthPayment = calloc(month, sizeof(long double));
    ret = differCreditCalc(percent, sum, month, *monthPayment, over, total);
  }
  return ret;
}

int isLeapYear(int year) {
  return (year % 4 == 0) ? 1 : 0;  // 0 - обычный (365), 1 - високосный (366)
}

int annuityCreditCalc(long double percent, long double sum, int month,
                      long double *monthPayment, long double *over,
                      long double *total) {
  int ret = 1;  // 1 - all good
  long double monthlyPercent = percent / (100 * 12);
  monthPayment[0] = roundl((sum * monthlyPercent /(1 - 1 / pow((1 + monthlyPercent), month))) *100.0) /100.0;  //округлить до копеек
  *total = *monthPayment * month;
  *over = *total - sum;
  return ret;
}

int differCreditCalc(long double percent, long double sum, int month,
                     long double *monthPayment, long double *over,
                     long double *total) {
  int ret = 1;  // 1 - all good
  long double base = sum, basePayment = (sum / month * 100.0) / 100, monthPaymentCalc = 0;
  long double total1 = 0, over1 = 0;
  basePayment = roundl(basePayment * 100.0)/100.0;//округлить до сотых

  time_t currentTime;
  time(&currentTime);
  struct tm *timeInfo = localtime(&currentTime);
  int curMonth = timeInfo->tm_mon, curYear = timeInfo->tm_year + 1900;

  for (int i = 0; i < month; i++) {
    monthPaymentCalc = basePayment + (base * percent / 100 / 12);
    monthPaymentCalc = roundl(monthPaymentCalc*100.0)/100.0;
    monthPayment[i] = monthPaymentCalc;
    total1 = total1 + monthPayment[i];
    base -= basePayment;
    curMonth = (curMonth + 1) % 12;
    if (curMonth == 0) curYear += 1;
  }
  over1 = total1 - sum;
  *total = total1;
  *over = over1;
  return ret;
}

// void quickSort(double *monthPayment, int size)
//{
//     int i = 0;
//     int j = size - 1;

//    long double mid = monthPayment[size/2];
//    do
//    {
//        while(monthPayment[i]<mid){
//            i++;
//        }
//        while(monthPayment[j]>mid){
//            j--;
//        }
//        if(i <= j){
//            double temp = monthPayment[i];
//            monthPayment[i] = monthPayment[j];
//            monthPayment[j] = temp;
//            i++;
//            j--;
//        }
//    } while (i <= j);

//    if(j > 0){
//        //left part
//        quickSort(monthPayment, j+1);
//    }
//    if(i < size){
//        //right part
//        quickSort(&monthPayment[i], size-1);
//    }
//}
