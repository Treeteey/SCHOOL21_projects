#include "../s21_string.h"

#include "s21_string_test.h"

int size = sizeof(s21_NULL);

START_TEST(fun_s21_memchr) {
  char mass1[100] = "1234567890";
  char mass2[100] = "Have_a_nice_day!";
  char mass3[100] = "1010011010";
  char mass4[100] = "GJMyFriend";
  char mass5[100] = "qwerty";
  char mass6[] = "";
  char *mass7 =
      "Searches for the first pass of the character c (an unsigned type) in "
      "the first n bytes of the string that the str argument was approaching.";
  char *mass8 = "fun_s21_memchr";

  fail_unless(s21_memchr(mass1, '4', 9) == memchr(mass1, '4', 9));
  fail_unless(s21_memchr(mass2, 'a', 9) == memchr(mass2, 'a', 9));
  fail_unless(s21_memchr(mass3, '0', 9) == memchr(mass3, '0', 9));
  fail_unless(s21_memchr(mass4, 'Y', 9) == memchr(mass4, 'Y', 9));
  fail_unless(s21_memchr(mass5, 'y', 9) == memchr(mass5, 'y', 9));
  ck_assert_ptr_eq(s21_memchr(mass6, ' ', 1), memchr(mass6, ' ', 1));
  ck_assert_ptr_eq(s21_memchr(mass7, 'f', 20), memchr(mass7, 'f', 20));
  ck_assert_ptr_eq(s21_memchr(mass8, 'f', 20), memchr(mass8, 'f', 20));
  ck_assert_ptr_eq(s21_memchr(mass7, '.', 2), memchr(mass7, '.', 2));
  ck_assert_ptr_eq(s21_memchr(mass7, '.', 40), memchr(mass7, '.', 40));
  ck_assert_ptr_eq(s21_memchr("wasd", 'a', 0), memchr("wasd", 'a', 0));
  ck_assert_ptr_eq(s21_memchr("wasd", 'a', 1), memchr("wasd", 'a', 1));
  ck_assert_ptr_eq(s21_memchr("wasd", 'a', 2), memchr("wasd", 'a', 2));
  ck_assert_ptr_eq(s21_memchr("wasd", '\0', 5), memchr("wasd", '\0', 5));
  ck_assert_ptr_null(s21_memchr(s21_NULL, '0', 1));
  ck_assert_ptr_null(s21_memchr(s21_NULL, '0', size));
}
END_TEST

START_TEST(fun_s21_memcmp) {
  char str1[] = "qwerty";
  char str2[] = "qwerty";
  char str3[] = "qwertyu";
  char str4[] = "qwert";
  char str5[] = "";
  char str6[] = "\n";
  // ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
  ck_assert_int_eq(s21_memcmp(str1, str3, 9), memcmp(str1, str3, 9));
  ck_assert_int_eq(s21_memcmp(str1, str3, 5), memcmp(str1, str3, 5));
  ck_assert_int_eq(s21_memcmp(str1, str4, 1), memcmp(str1, str4, 1));
  ck_assert_int_eq(s21_memcmp(str1, str5, 1), memcmp(str1, str5, 1));
  ck_assert_int_eq(s21_memcmp(str5, str6, 1), memcmp(str5, str6, 1));
}
END_TEST

START_TEST(fun_s21_memcpy) {
  char str1[] = "qwerty";
  char str2[] = "wasd";
  char str3[] = "123456";
  char str4[] = "ƒ∑ƒ®ƒ©®å´∂∑å∂";
  char str5[] = "\n";
  char mass1[10] = "";

  int len = s21_strlen(str1);

  ck_assert_str_eq(s21_memcpy(mass1, str1, len), memcpy(mass1, str1, len));
  ck_assert_str_eq(s21_memcpy(mass1, str2, len), memcpy(mass1, str2, len));
  ck_assert_str_eq(s21_memcpy(mass1, str3, len), memcpy(mass1, str3, len));
  ck_assert_str_eq(s21_memcpy(mass1, str4, len), memcpy(mass1, str4, len));
  ck_assert_str_eq(s21_memcpy(mass1, str5, len), memcpy(mass1, str5, len));
  ck_assert_str_eq(s21_memcpy(str1, mass1, len), memcpy(str1, mass1, len));
  ck_assert_str_eq(s21_memcpy(str1, str2, len), memcpy(str1, str2, len));
  ck_assert_str_eq(s21_memcpy(str1, str3, len), memcpy(str1, str3, len));
  ck_assert_str_eq(s21_memcpy(str1, str4, len), memcpy(str1, str4, len));
  ck_assert_str_eq(s21_memcpy(str4, str5, len), memcpy(str4, str5, len));
}
END_TEST

START_TEST(fun_s21_memset) {
  char mass0[] = "RandomText";
  char mass1[] = "123456";
  char mass2[] = "AEZAKMI";
  char mass3[] = "wasd";
  char mass4[] =
      "Copies the character c (unsigned type) to the first n characters of the "
      "string specified by the str argument.";
  char mass5[] =
      "´®©ß´´ßƒ˙®ß¬ß´π˚ˆ∆ˆå∆∑π˚å∑…≤ç¬ç≤åæπ¬ ∑π¬∂“π¬∑∂åπ“¬“πå†® "
      "®µ˚®ß´ƒππß´ƒ å∑∂µå∂≈≤≥≥µ≤µç√µπå∑œ∑´©®†≤≥÷≈";

  ck_assert_str_eq(s21_memset(mass0, '0', 4), memset(mass0, '0', 4));
  ck_assert_str_eq(s21_memset(mass1, 'Z', 4), memset(mass1, 'Z', 4));
  ck_assert_str_eq(s21_memset(mass2, '6', 6), memset(mass2, '6', 6));
  ck_assert_str_eq(s21_memset(mass3, 'Q', 1), memset(mass3, 'Q', 1));
  ck_assert_str_eq(s21_memset(mass4, 'F', 6), memset(mass4, 'F', 6));
  ck_assert_pstr_eq(s21_memset(mass5, 'z', 6), memset(mass5, 'z', 6));
}
END_TEST

START_TEST(fun_s21_strncat) {
  char my_str1[100] = "Hello my friend!";
  char orig_str1[100] = "Hello my friend!";

  char my_str2[100] = "What you want?";
  char orig_str2[100] = "What you want?";

  char my_str3[100] = "1q_2w_3e_4r_5y";
  char orig_str3[100] = "1q_2w_3e_4r_5y";

  char my_str4[10] = "12345";
  char orig_str4[10] = "12345";

  char my_str5[100] = "∑çåœ®ç¬å≠œ≤ç√";
  char orig_str5[100] = "∑çåœ®ç¬å≠œ≤ç√";

  char my_str6[3] = "\n";
  char orig_str6[3] = "\n";

  char my_str7[3] = "\0";
  char orig_str7[3] = "\0";

  char my_str8[100] = "https://edu.21-school.ru/";
  char orig_str8[100] = "https://edu.21-school.ru/";

  char my_str9[100] = "Dream Team";
  char orig_str9[100] = "Dream Team";

  char my_str10[10] = "";
  char orig_str10[10] = "";

  ck_assert_str_eq(s21_strncat(my_str1, "qwrteturyit", 12),
                   strncat(orig_str1, "qwrteturyit", 12));
  ck_assert_str_eq(s21_strncat(my_str8, "q w e r t y", 12),
                   strncat(orig_str8, "q w e r t y", 12));
  ck_assert_str_eq(s21_strncat(my_str10, my_str7, 5),
                   strncat(orig_str10, orig_str7, 5));
  ck_assert_str_eq(s21_strncat(my_str2, my_str6, 5),
                   strncat(orig_str2, orig_str6, 5));
  ck_assert_str_eq(s21_strncat(my_str9, "ANDGIGAMEGATEST", 20),
                   strncat(orig_str9, "ANDGIGAMEGATEST", 20));
  ck_assert_str_eq(s21_strncat(my_str3, my_str4, 10),
                   strncat(orig_str3, orig_str4, 10));
  ck_assert_str_eq(s21_strncat(my_str3, "not 1q_2w_3e_4r_5y - qwerty", 28),
                   strncat(orig_str3, "not 1q_2w_3e_4r_5y - qwerty", 28));
  ck_assert_str_eq(s21_strncat(my_str5, "strncat", 3),
                   strncat(orig_str5, "strncat", 3));
}
END_TEST

START_TEST(fun_s21_strchr) {
  char array1[32] = "Hello my friend!";
  char array2[32] = "What you want?";
  char array3[128] = "https://rocketchat-student.21-school.ru/";

  ck_assert_pstr_eq(s21_strchr(array1, '!'), strchr(array1, '!'));
  ck_assert_pstr_eq(s21_strchr(array1, ' '), strchr(array1, ' '));
  ck_assert_pstr_eq(s21_strchr(array2, '?'), strchr(array2, '?'));
  ck_assert_pstr_eq(s21_strchr(array2, 32), strchr(array2, 32));
  ck_assert_pstr_eq(s21_strchr(array2, 31), strchr(array2, 31));
  ck_assert_pstr_eq(s21_strchr(array3, '/'), strchr(array3, '/'));
  ck_assert_pstr_eq(s21_strchr(array3, '}'), strchr(array3, '}'));
  ck_assert_pstr_eq(s21_strchr(array3, 'a'), strchr(array3, 'a'));
}
END_TEST

START_TEST(fun_s21_strncmp) {
  char str[] = "Compares at most the first n bytes of str1 and str2.";
  char exam1[] = "str1";
  char exam2[] = "str2";
  char exam3[] = " ";
  char exam4[] = "\n";
  char exam5[] = "\0";
  char exam6[] = ".";
  char exam7[] = "C";
  int n = -53;

  ck_assert_int_eq(s21_strncmp(str, exam1, 0), strncmp(str, exam1, 0));
  ck_assert_int_eq(s21_strncmp(str, exam1, 53), strncmp(str, exam1, 53));
  ck_assert_int_eq(s21_strncmp(str, exam2, 12), strncmp(str, exam2, 12));
  ck_assert_int_eq(s21_strncmp(str, exam3, 34), strncmp(str, exam3, 34));
  ck_assert_int_eq(s21_strncmp(str, exam4, n), strncmp(str, exam4, n));
  ck_assert_int_eq(s21_strncmp(str, exam5, 55), strncmp(str, exam5, 55));
  ck_assert_int_eq(s21_strncmp(str, exam6, 1), strncmp(str, exam6, 1));
  ck_assert_int_eq(s21_strncmp(str, exam7, 4), strncmp(str, exam7, 4));
  ck_assert_int_eq(s21_strncmp(exam3, exam4, 3), strncmp(exam3, exam4, 3));
  ck_assert_int_eq(s21_strncmp(exam3, exam5, 5), strncmp(exam3, exam5, 5));
}
END_TEST

START_TEST(fun_s21_strncpy) {
  char empty_array1[20] = "";
  char empty_array2[20] = "";
  char empty_array3[20] = "";
  char empty_array4[20] = "";
  char *str1 = "qwerty";

  ck_assert_str_eq(s21_strncpy(empty_array1, str1, 6),
                   strncpy(empty_array2, str1, 6));
  ck_assert_str_eq(s21_strncpy(empty_array3, "But now not empty", 18),
                   strncpy(empty_array4, "But now not empty", 18));

  char my_str1[] = "first str";
  char orig_str1[] = "first str";
  int n1 = 2;

  ck_assert_str_eq(s21_strncpy(my_str1, str1, n1),
                   strncpy(orig_str1, str1, n1));

  char my_str2[20] = "first str or not?";
  char orig_str2[20] = "first str or not?";
  int n2 = 5;

  ck_assert_str_eq(s21_strncpy(my_str2, "Really?", n2),
                   strncpy(orig_str2, "Really?", n2));
}
END_TEST

START_TEST(fun_s21_strcspn) {
  char str1[] = "qwerty";
  char str2[] = "123456789";
  char str3[] = "";
  char str4[] = "987";
  char str5[] = "rgdsherpokwp oekopwpoq";
  char str6[] = "END";
  char str7[] = "THE_END";
  char str8[] = "_";
  char str9[] = " ";

  ck_assert_int_eq(s21_strcspn(str1, str3), strcspn(str1, str3));
  ck_assert_int_eq(s21_strcspn(str2, str4), strcspn(str2, str4));
  ck_assert_int_eq(s21_strcspn(str5, str1), strcspn(str5, str1));
  ck_assert_int_eq(s21_strcspn(str5, str3), strcspn(str5, str3));
  ck_assert_int_eq(s21_strcspn(str5, str9), strcspn(str5, str9));
  ck_assert_int_eq(s21_strcspn(str7, str6), strcspn(str7, str6));
  ck_assert_int_eq(s21_strcspn(str7, str8), strcspn(str7, str8));
  ck_assert_int_eq(s21_strcspn(str7, str9), strcspn(str7, str9));
  ck_assert_int_eq(s21_strcspn(str9, "\n"), strcspn(str9, "\n"));
  ck_assert_int_eq(s21_strcspn(str9, "\0"), strcspn(str9, "\0"));
}
END_TEST

START_TEST(fun_s21_strerror) {
  for (int i = -10; i < 150; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(fun_s21_strlen) {
  char str1[] = "qwerty";
  char str2[] = "";
  char str3[] = "STOP! PLS!";
  char str4[] = "Hello my dear peer!\n\n\n\n\n\n";
  char str5[] = "123456789";
  char str6[] = "\n";
  char str7[] = "\0";

  ck_assert_uint_eq(s21_strlen("qwe_123_rty"), strlen("qwe_123_rty"));
  ck_assert_uint_eq(s21_strlen("\n"), strlen("\n"));
  ck_assert_uint_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_uint_eq(s21_strlen("        "), strlen("        "));
  ck_assert_uint_eq(s21_strlen("GSPD, DEAD BLONDE"),
                    strlen("GSPD, DEAD BLONDE"));
  ck_assert_uint_eq(s21_strlen("åƒ≤©´øœµç˙å¥œ´π®≤ç"),
                    strlen("åƒ≤©´øœµç˙å¥œ´π®≤ç"));
  ck_assert_ptr_null((void *)s21_strlen(s21_NULL));
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
  ck_assert_int_eq(s21_strlen(str5), strlen(str5));
  ck_assert_int_eq(s21_strlen(str6), strlen(str6));
  ck_assert_int_eq(s21_strlen(str7), strlen(str7));
}
END_TEST

START_TEST(fun_s21_strpbrk) {
  char test1[] = "test1";
  char test2[] =
      "Finds the first character in str1 that matches any character in str2.";
  char test3[] = "\n";
  char test4[] = "\0";
  char test5[] = "1234567890";
  char test6[] = "88005553535";

  ck_assert_ptr_eq(s21_strpbrk(test1, test2), strpbrk(test1, test2));
  ck_assert_ptr_eq(s21_strpbrk(test1, test5), strpbrk(test1, test5));
  ck_assert_ptr_eq(s21_strpbrk(test1, test6), strpbrk(test1, test6));
  ck_assert_ptr_eq(s21_strpbrk(test2, test1), strpbrk(test2, test1));
  ck_assert_ptr_eq(s21_strpbrk(test2, test5), strpbrk(test2, test5));
  ck_assert_ptr_eq(s21_strpbrk(test2, test6), strpbrk(test2, test6));
  ck_assert_ptr_eq(s21_strpbrk(test5, test3), strpbrk(test2, test3));
  ck_assert_ptr_eq(s21_strpbrk(test6, test4), strpbrk(test6, test4));
  ck_assert_ptr_eq(s21_strpbrk(test6, ""), strpbrk(test6, ""));
  ck_assert_ptr_eq(s21_strpbrk("", test2), strpbrk("", test2));
  ck_assert_ptr_null(s21_strpbrk("", test2));
  ck_assert_ptr_null(s21_strpbrk(test6, ""));
  ck_assert_ptr_eq(s21_strpbrk(test2, "S"), strpbrk(test2, "S"));
  ck_assert_ptr_eq(s21_strpbrk(test2, "s"), strpbrk(test2, "s"));
}
END_TEST

START_TEST(fun_s21_strrchr) {
  char test1[] =
      "Searches for the last occurrence of the character c (unsigned type) in "
      "the string pointed to by str.";
  char test2[] = "1234567890";
  char test3[] = "88005553535";
  char test4[] = "edu.21-school.ru";

  ck_assert_pstr_eq(s21_strrchr(test1, 'a'), strrchr(test1, 'a'));
  ck_assert_pstr_eq(s21_strrchr(test1, 32), strrchr(test1, 32));
  ck_assert_pstr_eq(s21_strrchr(test1, '.'), strrchr(test1, '.'));
  ck_assert_pstr_eq(s21_strrchr(test1, '\n'), strrchr(test1, '\n'));
  ck_assert_pstr_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
  ck_assert_pstr_eq(s21_strrchr(test2, '0'), strrchr(test2, '0'));
  ck_assert_pstr_eq(s21_strrchr(test3, '3'), strrchr(test3, '3'));
  ck_assert_pstr_eq(s21_strrchr(test4, '.'), strrchr(test4, '.'));
  ck_assert_pstr_eq(s21_strrchr(test4, '3'), strrchr(test4, '3'));
}
END_TEST

START_TEST(fun_s21_strstr) {
  char text1[] =
      "Finds the first occurrence of the entire string needle (not including "
      "the terminating null character) that appears in the string haystack.";
  char text2[] = "This is my text";
  char text3[] = "Peer 2 peer / beer 2 beer";

  char scan1[] = " ";
  char scan2[] = "2";
  char scan3[] = "in";
  char scan4[] = "is";
  char scan5[] = "a";
  char scan6[] = "21";
  char scan7[] = "\0";
  char scan8[] = "\n";

  ck_assert_pstr_eq(s21_strstr(text1, scan1), strstr(text1, scan1));
  ck_assert_pstr_eq(s21_strstr(text1, scan2), strstr(text1, scan2));
  ck_assert_pstr_eq(s21_strstr(text1, scan3), strstr(text1, scan3));
  ck_assert_pstr_eq(s21_strstr(text1, scan3), strstr(text1, scan3));
  ck_assert_pstr_eq(s21_strstr(text1, scan5), strstr(text1, scan5));
  ck_assert_pstr_eq(s21_strstr(text2, scan1), strstr(text2, scan1));
  ck_assert_pstr_eq(s21_strstr(text2, scan4), strstr(text2, scan4));
  ck_assert_pstr_eq(s21_strstr(text2, scan7), strstr(text2, scan7));
  ck_assert_pstr_eq(s21_strstr(text2, scan8), strstr(text2, scan8));
  ck_assert_pstr_eq(s21_strstr(text3, scan2), strstr(text3, scan2));
  ck_assert_pstr_eq(s21_strstr(text3, scan6), strstr(text3, scan6));
  ck_assert_pstr_eq(s21_strstr(text1, "first"), strstr(text1, "first"));
  ck_assert_pstr_eq(s21_strstr("School21", scan6), strstr("School21", scan6));
}

START_TEST(fun_s21_strtok) {
  char array_1[100] = "My name is Root. Hello world!";
  char *parr1 = array_1;
  char array_2[100] = "My name is Root. Hello world!";
  char *parr2 = array_2;
  char array_3[100] = "\0";
  char *parr3 = array_3;
  char array_4[100] = "\0";
  char *parr4 = array_4;

  s21_strtok(parr1, " .");
  strtok(parr2, " .");
  ck_assert_pstr_eq(parr1, parr2);

  parr1 = s21_strtok(s21_NULL, " .");
  parr2 = strtok(s21_NULL, " .");
  ck_assert_pstr_eq(parr1, parr2);

  parr1 = s21_strtok(parr1, "o");
  parr2 = strtok(parr2, "o");
  ck_assert_pstr_eq(parr1, parr2);

  parr1 = s21_strtok(parr1, "x");
  parr2 = strtok(parr2, "x");
  ck_assert_pstr_eq(parr1, parr2);

  parr3 = s21_strtok(parr3, "\0");
  parr4 = strtok(parr4, "\0");
  ck_assert_pstr_eq(parr3, parr4);

  char *test1 = " ";
  char *test2 = "";
  char *test3 = "o";
  char *test4 = "M";
  char *test5 = "ƒ";

  ck_assert_pstr_eq(s21_strtok(parr1, test1), strtok(parr1, test1));
  ck_assert_pstr_eq(s21_strtok(parr1, test2), strtok(parr1, test2));
  ck_assert_pstr_eq(s21_strtok(parr1, test3), strtok(parr1, test3));
  ck_assert_pstr_eq(s21_strtok(parr1, test4), strtok(parr1, test4));
  ck_assert_pstr_eq(s21_strtok(parr1, test5), strtok(parr1, test5));
}
END_TEST

START_TEST(fun_s21_to_upper) {
  char text1[] = "he boy";
  char text2[] = "HE-HE BOOOOY";
  char text3[] = "not HE-HE";
  char text4[] = "123qwertY";
  char text5[] = "Why not X?";

  char *test_result1 = s21_to_upper(text1);
  char *test_result2 = s21_to_upper(text2);
  char *test_result3 = s21_to_upper(text3);
  char *test_result4 = s21_to_upper(text4);
  char *test_result5 = s21_to_upper(text5);

  ck_assert_str_eq(test_result1, "HE BOY");
  free(test_result1);
  ck_assert_str_eq(test_result2, "HE-HE BOOOOY");
  free(test_result2);
  ck_assert_str_eq(test_result3, "NOT HE-HE");
  free(test_result3);
  ck_assert_str_eq(test_result4, "123QWERTY");
  free(test_result4);
  ck_assert_str_eq(test_result5, "WHY NOT X?");
  free(test_result5);

  char *result = s21_to_upper("©∑œ´®∑ßƒç");
  ck_assert_str_eq(result, "©∑œ´®∑ßƒç");
  free(result);

  result = s21_to_upper("qwerty");
  ck_assert_str_eq(result, "QWERTY");
  free(result);

  result = s21_to_upper(" ");
  ck_assert_str_eq(result, " ");
  free(result);
}
END_TEST

START_TEST(fun_s21_to_lower) {
  char text1[] = "he boy";
  char text2[] = "HE-HE BOOOOY";
  char text3[] = "not HE-HE";
  char text4[] = "123qwertY";
  char text5[] = "Why not X?";

  char *test_result1 = s21_to_lower(text1);
  char *test_result2 = s21_to_lower(text2);
  char *test_result3 = s21_to_lower(text3);
  char *test_result4 = s21_to_lower(text4);
  char *test_result5 = s21_to_lower(text5);

  ck_assert_str_eq(test_result1, "he boy");
  free(test_result1);
  ck_assert_str_eq(test_result2, "he-he booooy");
  free(test_result2);
  ck_assert_str_eq(test_result3, "not he-he");
  free(test_result3);
  ck_assert_str_eq(test_result4, "123qwerty");
  free(test_result4);
  ck_assert_str_eq(test_result5, "why not x?");
  free(test_result5);

  char *result = s21_NULL;

  result = s21_to_lower("©∑œ´®∑ßƒç");
  ck_assert_str_eq(result, "©∑œ´®∑ßƒç");
  free(result);

  result = s21_to_lower("qWErty");
  ck_assert_str_eq(result, "qwerty");
  free(result);

  result = s21_to_lower(" ");
  ck_assert_str_eq(result, " ");
  free(result);
}
END_TEST

START_TEST(fun_s21_insert) {
  char *result = s21_NULL;

  char text1[] = "he boy";
  char dop_text1[] = " or bububob";
  result = s21_insert(text1, dop_text1, 6);
  ck_assert_str_eq(result, "he boy or bububob");
  free(result);

  char text2[] = "HE-HE BOOOOY";
  char dop_text2[] = "-HE";
  result = s21_insert(text2, dop_text2, 2);
  ck_assert_str_eq(result, "HE-HE-HE BOOOOY");
  free(result);

  char text3[] = "not HE-HE";
  char dop_text3[] = "HE-";
  result = s21_insert(text3, dop_text3, 4);
  ck_assert_str_eq(result, "not HE-HE-HE");
  free(result);

  char text4[] = "";
  char dop_text4[] = " ";
  result = s21_insert(text4, dop_text4, 0);
  ck_assert_str_eq(result, " ");
  free(result);

  char text5[] = "Network";
  char dop_text5[] = "\n";
  result = s21_insert(text5, dop_text5, 4);
  ck_assert_str_eq(result, "Netw\nork");
  free(result);

  char text6[] = "not Finish";
  char dop_text6[] = "Start ";
  result = s21_insert(text6, dop_text6, 0);
  ck_assert_str_eq(result, "Start not Finish");
  free(result);

  char text7[] = "not Finish";
  char dop_text7[] = "Start ";
  result = s21_insert(text7, dop_text7, 20);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(fun_s21_trim) {
  char *result = s21_NULL;

  result = s21_trim("12345qwerty12345", "12345");
  ck_assert_str_eq(result, "qwerty");
  free(result);

  result = s21_trim("my test good!", "!");
  ck_assert_str_eq(result, "my test good");
  free(result);

  result = s21_trim(" ", " ");
  ck_assert_str_eq(result, "");
  free(result);

  char *test1 = "S21";
  char *test2 = "kidneyha";
  char *test3 = "ha-ha-ha";
  char *test4 = "-0-0-";
  char *test5 = "";
  char *test6 = s21_NULL;

  char *test_result1 = s21_trim(test1, test5);
  char *test_result2 = s21_trim(test1, test6);
  char *test_result3 = s21_trim(test2, test3);
  char *test_result4 = s21_trim(test3, test2);
  char *test_result5 = s21_trim(test3, test4);

  ck_assert_str_eq(test_result1, "S21");
  ck_assert_str_eq(test_result2, "S21");
  ck_assert_str_eq(test_result3, "kidney");
  ck_assert_str_eq(test_result4, "-ha-");
  ck_assert_str_eq(test_result5, "ha-ha-ha");

  free(test_result1);
  free(test_result2);
  free(test_result3);
  free(test_result4);
  free(test_result5);
}
END_TEST

START_TEST(fun_s21_sprintf) {
  long int num1 = 123456789;
  int num2 = -42, num3 = 0;
  short int num4 = -42;
  unsigned int u_num1 = 12342314;
  unsigned long int u_num2 = 12342314123123;
  unsigned short int u_num3 = 21546;
  double d1 = 3.14159, d2 = 123.321, d3 = 9999.9998212, d4 = 0;
  char c1 = 'A', c2 = 48;
  char str1[100] = "Hello", str2[100] = "", str3[100] = "%q%d";
  char expected_output[1000];
  char actual_output[1000];
  int expected_len = 0, actual_len = 0;

  char format1[100] = "%d";
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%u");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, u_num1);
  actual_len = s21_sprintf(actual_output, format1, u_num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, u_num3);
  actual_len = s21_sprintf(actual_output, format1, u_num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%lu");
  expected_len = sprintf(expected_output, format1, u_num1);
  actual_len = s21_sprintf(actual_output, format1, u_num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, u_num3);
  actual_len = s21_sprintf(actual_output, format1, u_num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%.d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%.0d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%.50d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%15.50d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%+-15.50ld");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4);
  actual_len = s21_sprintf(actual_output, format1, num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%.0f");
  expected_len = sprintf(expected_output, format1, d1);
  actual_len = s21_sprintf(actual_output, format1, d1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d2);
  actual_len = s21_sprintf(actual_output, format1, d2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d3);
  actual_len = s21_sprintf(actual_output, format1, d3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d4);
  actual_len = s21_sprintf(actual_output, format1, d4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%-12f %%");
  expected_len = sprintf(expected_output, format1, (double)num1);
  actual_len = s21_sprintf(actual_output, format1, (double)num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, (double)num2);
  actual_len = s21_sprintf(actual_output, format1, (double)num2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, (double)num3);
  actual_len = s21_sprintf(actual_output, format1, (double)num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, (double)num4);
  actual_len = s21_sprintf(actual_output, format1, (double)num4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d1);
  actual_len = s21_sprintf(actual_output, format1, d1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d2);
  actual_len = s21_sprintf(actual_output, format1, d2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d3);
  actual_len = s21_sprintf(actual_output, format1, d3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d4);
  actual_len = s21_sprintf(actual_output, format1, d4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  //проверка флага # для f
  strcpy(format1, "%-#12.f");
  expected_len = sprintf(expected_output, format1, d1);
  actual_len = s21_sprintf(actual_output, format1, d1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, d4);
  actual_len = s21_sprintf(actual_output, format1, d4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  //проверка * для ширины и точности
  strcpy(format1, "%-+#*.*f");
  expected_len = sprintf(expected_output, format1, 10, 10, d1);
  actual_len = s21_sprintf(actual_output, format1, 10, 10, d1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, 0, 0, d4);
  actual_len = s21_sprintf(actual_output, format1, 0, 0, d4);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  strcpy(format1, "%.*f%c%+.2d");
  expected_len = sprintf(expected_output, format1, 3, d1, 'e', 10);
  actual_len = s21_sprintf(actual_output, format1, 3, d1, 'e', 10);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  //проверка краевого значения 0 при точности 0 и не заданной точности
  strcpy(format1, "%-+10.d");
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  strcpy(format1, "%-+10.0d");
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  //проверка флага # и X lX hX
  strcpy(format1, "%#-15.10X");  //рассмотреть длины l и h
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "%#lX");
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "%#hX");
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  //подаю тип int
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);

  //проверка флага # и o lo ho
  strcpy(format1, "%#-15.10o");  //рассмотреть длины l и h
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "%#.lo");
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "%#.0ho");
  expected_len = sprintf(expected_output, format1, u_num2);
  actual_len = s21_sprintf(actual_output, format1, u_num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  //подаю тип int
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  expected_len = sprintf(expected_output, format1, num2);
  actual_len = s21_sprintf(actual_output, format1, num2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  expected_len = sprintf(expected_output, format1, num3);
  actual_len = s21_sprintf(actual_output, format1, num3);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);

  // long double
  long double ld = 123124124214214.213141;
  strcpy(format1, "%-#12.Lf");
  expected_len = sprintf(expected_output, format1, ld);
  actual_len = s21_sprintf(actual_output, format1, ld);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);

  //спецификаторы e и E
  strcpy(format1, "%-e");
  expected_len = sprintf(expected_output, format1, d1);
  actual_len = s21_sprintf(actual_output, format1, d1);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  double ddd = -d1, ddd2 = 0.003214;
  expected_len = sprintf(expected_output, format1, ddd);
  actual_len = s21_sprintf(actual_output, format1, ddd);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  expected_len = sprintf(expected_output, format1, ddd2);
  actual_len = s21_sprintf(actual_output, format1, ddd2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "% E");
  expected_len = sprintf(expected_output, format1, d2);
  actual_len = s21_sprintf(actual_output, format1, d2);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  strcpy(format1, "%-+10.4e");
  expected_len = sprintf(expected_output, format1, d1);
  actual_len = s21_sprintf(actual_output, format1, d1);
  ck_assert_str_eq(actual_output, expected_output);
  ck_assert_int_eq(actual_len, expected_len);
  // double dd1 = 132.23124, dd2 = -dd1, dd3 = 0.0032124;
  //  double dd1 = 1.23124;
  //  expected_len = sprintf(expected_output, format1, dd1);
  //  actual_len = s21_sprintf(actual_output, format1, dd1);
  //  ck_assert_str_eq(actual_output, expected_output);
  //  ck_assert_int_eq(actual_len, expected_len);
  //  expected_len = sprintf(expected_output, format1, dd2);
  //  actual_len = s21_sprintf(actual_output, format1, dd2);
  //  ck_assert_str_eq(actual_output, expected_output);
  //  ck_assert_int_eq(actual_len, expected_len);
  //  expected_len = sprintf(expected_output, format1, dd3);
  //  actual_len = s21_sprintf(actual_output, format1, dd3);
  //  ck_assert_str_eq(actual_output, expected_output);
  //  ck_assert_int_eq(actual_len, expected_len);

  strcpy(format1, "%p");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  //проверка флага 0 для d
  strcpy(format1, "%012.14d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  strcpy(format1, "%0-12.3d");
  expected_len = sprintf(expected_output, format1, num1);
  actual_len = s21_sprintf(actual_output, format1, num1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%s");
  expected_len = sprintf(expected_output, format1, str1);
  actual_len = s21_sprintf(actual_output, format1, str1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str2);
  actual_len = s21_sprintf(actual_output, format1, str2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str3);
  actual_len = s21_sprintf(actual_output, format1, str3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%+15.3s");
  expected_len = sprintf(expected_output, format1, str1);
  actual_len = s21_sprintf(actual_output, format1, str1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str2);
  actual_len = s21_sprintf(actual_output, format1, str2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str3);
  actual_len = s21_sprintf(actual_output, format1, str3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "%+-15.100s");
  expected_len = sprintf(expected_output, format1, str1);
  actual_len = s21_sprintf(actual_output, format1, str1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str2);
  actual_len = s21_sprintf(actual_output, format1, str2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, str3);
  actual_len = s21_sprintf(actual_output, format1, str3);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1, "int:%-12.8hd float:% 8.8f string:%-+8.2s char:%-7.3c");
  expected_len = sprintf(expected_output, format1, num1, d1, str1, c1);
  actual_len = s21_sprintf(actual_output, format1, num1, d1, str1, c1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num2, d2, str2, c2);
  actual_len = s21_sprintf(actual_output, format1, num2, d2, str2, c2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num3, d3, str3, c2);
  actual_len = s21_sprintf(actual_output, format1, num3, d3, str3, c2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len = sprintf(expected_output, format1, num4, d4, str2, c1);
  actual_len = s21_sprintf(actual_output, format1, num4, d4, str2, c1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);

  strcpy(format1,
         "int:%-12.8hd long int:%.ld short int:%+10.3hd float:% 8.8f "
         "string:%-+8.2s char:%-7.3c");
  expected_len =
      sprintf(expected_output, format1, num2, num1, num4, d1, str1, c1);
  actual_len =
      s21_sprintf(actual_output, format1, num2, num1, num4, d1, str1, c1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len =
      sprintf(expected_output, format1, num2, num4, num4, d2, str2, c2);
  actual_len =
      s21_sprintf(actual_output, format1, num2, num4, num4, d2, str2, c2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len =
      sprintf(expected_output, format1, num1, num3, num4, d3, str3, c2);
  actual_len =
      s21_sprintf(actual_output, format1, num1, num3, num4, d3, str3, c2);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
  expected_len =
      sprintf(expected_output, format1, num2, num2, num4, d4, str2, c1);
  actual_len =
      s21_sprintf(actual_output, format1, num2, num2, num4, d4, str2, c1);
  ck_assert_int_eq(actual_len, expected_len);
  ck_assert_str_eq(actual_output, expected_output);
}
END_TEST

Suite *suite_fun_string(void) {
  Suite *suite;
  TCase *all_tcase;

  suite = suite_create("fun_string");
  all_tcase = tcase_create("All_case");

  tcase_add_test(all_tcase, fun_s21_memchr);
  tcase_add_test(all_tcase, fun_s21_memcmp);
  tcase_add_test(all_tcase, fun_s21_memcpy);
  tcase_add_test(all_tcase, fun_s21_memset);
  tcase_add_test(all_tcase, fun_s21_strncat);
  tcase_add_test(all_tcase, fun_s21_strchr);
  tcase_add_test(all_tcase, fun_s21_strncmp);
  tcase_add_test(all_tcase, fun_s21_strncpy);
  tcase_add_test(all_tcase, fun_s21_strcspn);
  tcase_add_test(all_tcase, fun_s21_strerror);
  tcase_add_test(all_tcase, fun_s21_strlen);
  tcase_add_test(all_tcase, fun_s21_strpbrk);
  tcase_add_test(all_tcase, fun_s21_strrchr);
  tcase_add_test(all_tcase, fun_s21_strstr);
  tcase_add_test(all_tcase, fun_s21_strtok);
  tcase_add_test(all_tcase, fun_s21_to_upper);
  tcase_add_test(all_tcase, fun_s21_to_lower);
  tcase_add_test(all_tcase, fun_s21_insert);
  tcase_add_test(all_tcase, fun_s21_trim);
  tcase_add_test(all_tcase, fun_s21_sprintf);

  suite_add_tcase(suite, all_tcase);
  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite;
  SRunner *srunner;

  suite = suite_fun_string();
  srunner = srunner_create(suite);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  failed_count = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}