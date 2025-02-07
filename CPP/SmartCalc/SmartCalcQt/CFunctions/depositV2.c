#include "../CHeader.h"

int arrDaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *arrMonthNames[12] = {"January",   "February", "March",    "April",
                           "May",       "June",     "July",     "August",
                           "September", "October",  "November", "December"};

/*
ЕСЛИ СУММАРНАЯ ПРИБЫЛЬ ЗА ВЕСЬ ПЕРИОД БОЛЬШЕ НЕОБЛАГАЕМОЙ СУММЫ, ТО РАССМОТРЕТЬ
СНЯТИЕ РАЗ В МЕСЯЦ/ПОЛГОДА/ГОД допустим за 2 года суммарная прибыль 320к: 1)
если снять в конце 320к то надо заплатить налог: 320-150(необлагаемая сумма) =
170к * 13% = 22.1к   - НАЛОГ ЗА ВЕСЬ ПЕРИОД (2 ГОДА) 2) если снимать каждый год
то: 320/2 - 150 = 10к * 13% = 1.3к (за год) * 2 = 2.6к !!!! НАЛОГ ЗА 2 ГОДА


НАДО СЧИТАТЬ КАЖДУЮ ВЫПЛАТУ

    Вход: сумма вклада, срок размещения, процентная ставка,
налоговая ставка, периодичность выплат, капитализация процентов,
список пополнений, список частичных снятий
    Выход: начисленные проценты, сумма налога, сумма на вкладе к концу срока

    проценты начисляются каждый день, поэтому 17/365 - столько процентов в день
приходит от вложенной суммы interestCharges - начисленные проценты Выплаты
каждый месяц: если дата вложения 31е к примеру то будут выплаты 31го числа
каждого месяца, если в месяце например 28 дней то выплата в последний день
месяца окончание выплат аналогично в день вклада проценты не начисляются - так
как логично что деньги работали не целый день
*/

void depositCalc(int startDay, int startMonth, int startYear, long double sum,
                 int postingPeriod, int timeOfPosting, long double interest,
                 int payoutPeriod, long double *total,
                 long double *gainedInterest, long double *taxSum,
                 int capitalization, long double inputTax) {
  int finDay = 0, finMonth = 0, finYear = 0;
  lastDayOfDeposit(startDay, startMonth, startYear, postingPeriod,
                   timeOfPosting, &finDay, &finMonth, &finYear);
  int tempDay = startDay, tempMonth = startMonth, tempYear = startYear,
      endDay = 0, endMonth = 0, endYear = 0, taxedYear = startYear;
  long double payout = 0, yearPayout = 0, initialSum = sum, addTax = 0;
  *total = sum;

  while (!(tempYear == finYear && tempMonth == finMonth && tempDay == finDay)) {
    calcPayDate(tempDay, tempMonth, tempYear, finDay, finMonth, finYear,
                payoutPeriod, &endDay, &endMonth, &endYear);
    payout = calcPayForPeriod(sum, interest, tempDay, tempMonth, tempYear,
                              endDay, endMonth, endYear);
    *total += payout;
    if (capitalization == 1) sum += payout;
    if (tempYear == endYear)  //если начало и конец периода в одном году, то
                              //добавить к сумме за год
      yearPayout += payout;  //чтоб посчитать налог за год
    else {
      addTax = tax(yearPayout, inputTax);
      *taxSum += addTax;
      taxedYear = tempYear;
      yearPayout = payout;
    }
    tempDay = endDay;
    tempMonth = endMonth;
    tempYear = endYear;
  }
  if (taxedYear != finYear) {
    addTax = tax(yearPayout, inputTax);
    *taxSum += addTax;
  }
  if (*taxSum == 0) {
    addTax = tax(yearPayout, inputTax);
    *taxSum += addTax;
  }
  //    *gainedInterest = (*total - initialSum)/initialSum * 100;
  *gainedInterest = (*total - initialSum);
}

/*
НАЛОГ ЗАВИСИТ ОТ ПЕРИОДИЧНОСТИ ВЫПЛАТ !!!

если выплаты за определенные период то надо задавать для каждого периода начало
и конец и отдельно считать прибыль за этот период - закинуть в структуру
withdraw если период начинается в 1 году а заканчивается в следующем и то
отдельно считать и сложить прибыль (если года обчный и високосный) если выплата
в след году и начало в текущем, то эта выплата засчитывается на след год

надо сделать функцию расчета след даты выплаты, принимает периодичность выплаты
и текущую дату - сделать проверку чтоб не выйти за дату окончания вклада считаем
с ней доход за указанный промежуток времени
*/

long double income(long double sum, long double interest, int year, int days) {
  long double incomeSum = 0;
  if (days == -1) {  //когда за полный год нужна прибыль
    incomeSum = interest / 100 * sum;
  } else {  //когда за часть года нужна прибыль
    if (isLeapYear(year)) {
      incomeSum = days / 366.0 * interest / 100.0 * sum;
    } else
      incomeSum = days / 365.0 * interest / 100.0 * sum;
  }
  return incomeSum;
}

long double tax(long double sum, long double inputTax) {
  long double noTaxSum = 1000000 * inputTax / 100.0, taxsum = 0;
  if (sum > noTaxSum) taxsum = (sum - noTaxSum) * 13 / 100.0;
  return taxsum;
}

//с заданной даты до конца года не включая заданного дня
int daysTillEndOfYear(int day, int month, int year) {
  int days = arrDaysInMonth[month] - day;
  if (isLeapYear(year) && (month < 1 || (month == 1 && days < 29))) days += 1;
  for (int i = month + 1; i < 12; i++) {
    days += arrDaysInMonth[i];
  }
  return days;
}

//с начала года до заданной даты
int daysTillGivenDate(int day, int month, int year) {
  int days = day;
  for (int i = 0; i < month; i++) {
    days += arrDaysInMonth[i];
  }
  if (isLeapYear(year) && (month > 1 || (month == 1 && day == 29))) days += 1;
  return days;
}

// working perfectly
//рассчитывает дату выплаты по начальной дате и периодичности выплат и записывае
//их в глобальные переменные
void calcPayDate(const int startDay, const int startMonth, const int startYear,
                 const int finDay, const int finMonth, const int finYear,
                 int payoutPeriod, int *endDay, int *endMonth, int *endYear) {
  if (payoutPeriod == 0) {  //выплата в конце срока
    *endDay = finDay;
    *endMonth = finMonth;
    *endYear = finYear;
  } else if (payoutPeriod == 1)  //выплаты каждый день
  {
    *endDay = startDay + 1;
    *endMonth = startMonth;
    *endYear = startYear;
    if (*endDay > daysInMonth(*endYear, *endMonth)) {
      *endDay = 1;
      *endMonth = *endMonth + 1;
    }
    if (*endMonth == 12) {
      *endYear += 1;
      *endMonth = 0;
    }
  } else if (payoutPeriod == 2) {  //выплаты каждую неделю
    *endDay = startDay + 7;
    *endMonth = startMonth;
    *endYear = startYear;
    if (*endDay > daysInMonth(*endYear, *endMonth)) {
      *endDay = *endDay - daysInMonth(*endYear, *endMonth);
      *endMonth = *endMonth + 1;
    }
    if (*endMonth == 12) {
      *endYear += 1;
      *endMonth = 0;
    }
  } else if (payoutPeriod == 3 || payoutPeriod == 4 ||
             payoutPeriod == 5) {  //выплаты каждый месяц|квартал|полгода
                                   /*
                                   пример: если начало вклада 31 января а выплаты каждый месяц, то в след
                                   месяце тоже должна быть выплата 31го, но если
                                   в след месяце 28 дней например, то выплата
                                   будет 31января + 31 день(в текущем месяце) = 28дней в феврале + (31-28) дней
                                   после, получается выплата будет 3 марта
                                   */
    int addMonth = 0;
    if (payoutPeriod == 3)
      addMonth = 1;
    else if (payoutPeriod == 4)
      addMonth = 3;
    else if (payoutPeriod == 5)
      addMonth = 6;

    *endDay = startDay;
    *endMonth = startMonth + addMonth;
    *endYear = startYear;
    if (*endMonth > 11) {
      *endMonth = *endMonth - 12;
      *endYear += 1;
    }
    if (*endDay > daysInMonth(*endYear, *endMonth)) {
      *endDay = *endDay - daysInMonth(*endYear, *endMonth);
      *endMonth += 1;
    }
    if (*endMonth > 11) {
      *endMonth = 0;
      *endYear += 1;
    }
  } else if (payoutPeriod == 6) {  //выплаты каждый год
    *endDay = startDay;
    *endMonth = startMonth;
    *endYear = startYear + 1;
  }

  /*надо сделать проверку что полученная дата не позже конца вклада
  если это так то конец периода просто будет концом вклада
  */
  if (dateOverEndDeposit(finDay, finMonth, finYear, *endDay, *endMonth,
                         *endYear)) {
    *endDay = finDay;
    *endMonth = finMonth;
    *endYear = finYear;
  }
}

int dateOverEndDeposit(const int finDay, const int finMonth, const int finYear,
                       int day, int month, int year) {
  int ret = 0;  // OK - date is less than finish day
  if (finYear < year)
    ret = 1;  // not OK  year is over finish year
  else if (finYear == year) {
    if (finMonth < month)
      ret = 1;  // not OK years are equal but month are over finish month
    else if (finMonth == month) {
      if (finDay < day)
        ret = 1;  // not OK years and month are equal but day is over finish day
    }
  }
  return ret;
}

//возвращает количество дней в месяце
int daysInMonth(int year, int month) {
  int days = arrDaysInMonth[month];
  if (month == 1 && isLeapYear(year)) days += 1;
  return days;
}

//рассчиывает размер выплаты по дате начала и конца периода и ставке
long double calcPayForPeriod(long double sum, long double interest,
                             int startDay, int startMonth, int startYear,
                             int endDay, int endMonth, int endYear) {
  long double payoutForPeriod = 0;
  int days = 0;
  if (startYear == endYear) {
    days = daysInYearPeriod(startDay, startMonth, startYear, endDay, endMonth);
    payoutForPeriod = income(sum, interest, startYear, days);
  } else {
    days = daysTillEndOfYear(startDay, startMonth, startYear);
    payoutForPeriod += income(sum, interest, startYear, days);
    for (int i = startYear + 1; i < endYear; i++) {
      days = 365;
      if (isLeapYear(i)) days += 1;
      payoutForPeriod += income(sum, interest, i, days);
    }
    days = daysTillGivenDate(endDay, endMonth, endYear);
    payoutForPeriod += income(sum, interest, endYear, days);
  }
  return payoutForPeriod;
}

//возвращает количество дней в заданном временном периоде внутри одного года
int daysInYearPeriod(int startDay, int startMonth, int startYear, int endDay,
                     int endMonth) {
  int days = 0;
  if (startMonth == endMonth)
    days = endDay - startDay;
  else {
    days = daysInMonth(startYear, startMonth) - startDay;
    // if(isLeapYear(startYear) && startMonth == 1 && days != 0) days += 1;
    for (int i = startMonth + 1; i < endMonth; i++) {
      days += daysInMonth(startYear, i);
    }
    days += endDay;
  }
  return days;
}

void lastDayOfDeposit(int startDay, int startMonth, int startYear,
                      int postingPeriod, int timeOfPosting, int *endDay,
                      int *endMonth, int *endYear) {
  if (postingPeriod == 0) {  //в днях
    *endDay = startDay + timeOfPosting;
    while (*endDay >= arrDaysInMonth[startMonth]) {
      *endDay -= arrDaysInMonth[startMonth];
      if (startMonth % 12 == 1 &&
          isLeapYear(
              startYear))  //если високосный год и февраль то вычесть еще 1 день
        *endDay -= 1;
      startMonth += 1;
      if (startMonth % 12 == 0) {
        ++startYear;
        startMonth = 0;
      }
    }
    *endMonth = startMonth;
    *endYear = startYear;
  } else if (postingPeriod == 1) {  //в месяцах
    *endDay = startDay;
    *endMonth = startMonth + timeOfPosting;
    *endYear = startYear + (*endMonth / 12);
    *endMonth = *endMonth % 12;
    /*
    если начало было N числа и количество дней в месяце окончания меньше N
    то день окончания будет число дней в месяце окончания
    (тип начало 31 октября и вложили на 1 месяц, а в ноябре 30 дней ->
    окончание 30.11)
    */
    if (startDay > arrDaysInMonth[*endMonth])
      *endDay = arrDaysInMonth[*endMonth];
  } else if (postingPeriod == 2) {  //в годах
    *endYear = startYear + timeOfPosting;
    *endDay = startDay;
    *endMonth = startMonth;
    /*если начало было 29 февраля високосного года,
        если год окончания високосный -
            день окончания будет 29февраля
        если год оконания обычный -
            день окончания 1 марта  ,
    !!!такая система на сайте calcus.ru
    */
    if (isLeapYear(startYear) && !isLeapYear(*endYear) && startMonth == 1 &&
        startDay == 29) {
      *endDay = 1;    // 1 - число
      *endMonth = 2;  // 3 - месяц (март)
    };
  }
}
