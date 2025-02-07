#include "test.h"

int main(void) {
  int fail = 0;
  Suite *SmartCalc[] = {calc_tests(), credit_tests(), deposit_tests(), NULL};

  for (int i = 0; SmartCalc[i] != NULL; i++) {
    SRunner *sr = srunner_create(SmartCalc[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    fail += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("FAILED: %d\n", fail);
  return 0;
}