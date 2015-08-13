/* fix the mod function */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<gmp.h>
#include<gmpxx.h>
#include<assert.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
 
  mpf_class half, full;

  full = 25;

  cout << "full is " << full << endl;

  half = full/2;

  cout << "half is " << half << endl;

  return 0;
}
