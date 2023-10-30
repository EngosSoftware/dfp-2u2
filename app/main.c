#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../library/src/bid_conf.h"
#include "../library/src/bid_functions.h"

void display(char *fname, BID_UINT128 x) {
  char buffer[500];
  printf("\n%s\n", fname);
  printf("=====================================================================\n");
  printf("[%016llx,%016llx] ", x.w[1], x.w[0]);
  printf("%02x ", *pfpsf);
  bid128_to_string(buffer, x);
  printf("%s\n", buffer);
}

void display_from_string_rnd(char *input, int rnd) {
  char buffer[500];
  printf("%d \"%s\" ", rnd, input);
  *pfpsf = 0;
  clock_t start, end;
  start = clock();
  BID_UINT128 x = bid128_from_string(input, rnd);
  end = clock();
  printf("[%016llx,%016llx] ", x.w[1], x.w[0]);
  printf("%02x ", *pfpsf);
  bid128_to_string(buffer, x);
  printf("%s ", buffer);
  double time_spent = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f[s]\n", time_spent);
}

void display_from_string(char *input) {
  display_from_string_rnd(input, BID_ROUNDING_TO_NEAREST);
}

void test_bid128_scalbn() {
  BID_UINT128 bid128;
  bid128.w[1] = 0x000000028a080400;
  bid128.w[0] = 0x8002020024000000;
  BID_UINT128 res = bid128_scalbn(bid128, -9, BID_ROUNDING_TO_NEAREST);
  display("bid128_scalbn", res);
}

void test_bid128_zeros() {
  int rnd = BID_ROUNDING_TO_NEAREST;
  display_from_string("0e-6211");
  display_from_string("0e-6210");
  display_from_string("0e-6209");
  display_from_string("0e-6177");
  display_from_string("0e-6176");
  display_from_string("0e-6175");
  display_from_string("0e-6174");
  printf("\n");
  display_from_string("0e+6110");
  display_from_string("0e+6111");
  display_from_string("0e+6112");
  display_from_string("0e+6209");
  display_from_string("0e+6210");
  display_from_string("0e+6211");
  display_from_string("0e+6212");
  display_from_string("0e+6212");
  display_from_string("0e+6500");
}

void test_bid128_ones() {
  display_from_string("1e-6211");
  display_from_string("1e-6210");
  display_from_string("1e-6209");
  display_from_string("1e-6177");
  display_from_string("1e-6176");
  display_from_string("1e-6175");
  display_from_string("1e-6174");
  printf("\n");
  display_from_string("1e+6110");
  display_from_string("1e+6112");
  display_from_string("1e+6113");
  display_from_string("1e+6143");
  display_from_string("1e+6144");
  display_from_string("1e+6145");
  display_from_string("1e+6210");
  display_from_string("1e+6211");
  display_from_string("1e+6500");
}

void bench_from_string() {
  display_from_string_rnd("12", BID_ROUNDING_TO_NEAREST);
  display_from_string_rnd("938475E-03", BID_ROUNDING_TO_NEAREST);
  display_from_string_rnd("0.00003E-02", BID_ROUNDING_TO_NEAREST);
  display_from_string_rnd("9999999999999999999999999999999999", BID_ROUNDING_TO_NEAREST);
  display_from_string_rnd("+9999999999999999999999999999999999e+6111", BID_ROUNDING_TO_NEAREST);
  display_from_string_rnd("+1000000000000000000000000000000000e-6176", BID_ROUNDING_TO_NEAREST);
}

void test() {
  BID_UINT64 x = 0x8000000000000000ull;
  BID_UINT128 v = bid128_from_uint64(x);
  display("a", v);

}

int main() {

  //bench_from_string();

  test();

  //test_bid128_scalbn();

  //test_bid128_zeros();

  //test_bid128_ones();

  return EXIT_SUCCESS;
}