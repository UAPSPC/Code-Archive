// Given side lengths a, b, c, returns area or -1 if triangle is
// impossible
double area_heron(double a, double b, double c) {
  if(a < b) swap(a, b);
  if(a < c) swap(a, c);
  if(b < c) swap(b, c);
  if(a > b + c) return -1;
  return sqrt((a + b + c) * (c - a + b) * (c + a - b) * (a + b - c) / 16.0);
}
