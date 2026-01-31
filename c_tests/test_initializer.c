int test(void) {
  int T[] = {0, 1, 2, 3}; // allowed
  int T2[] = {0, 1, 2, 3,}; // also allowed
  return T[1];
}
const char * a = (const char *){"a string"};