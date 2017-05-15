// Given digit d and value N, returns # of times d occurs from 1..N
long long digit_count(int digit, int N) {
  long long res = 0;
  char buff[15];
  int i, count;
  if(N <= 0) return 0;
  res += N / 10 + ((N % 10) >= digit ? 1 : 0);
  if(digit == 0) res--;
  res += digit_count(digit, N / 10 - 1) * 10;
  sprintf(buff, "%d", N / 10);
  for(i = 0, count = 0; i < strlen(buff); i++)
    if(buff[i] == digit + '0') count++;
  res += (1 + N % 10) * count;
  return res;
}
