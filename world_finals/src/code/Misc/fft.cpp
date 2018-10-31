using double = ld; // can always try long double if you are concerned
using complex < ld >= cplx;
using vector < cplx >= vc;
// Compute the (I)FFT of f, store in v.
// f.size() *MUST* be a power of 2
void fft(const vc &f, vc &v, bool invert) {
  int n = f.size();
  assert(n > 0 && (n & (n - 1)) == 0);
  v.resize(n);
  for(int i = 0; i < n; ++i) {
    int r = 0, k = i;
    for(int j = 1; j < n; j <<= 1, r = (r << 1) | (k & 1), k >>= 1)
      ;
    v[i] = f[r];
  }
  for(int m = 2; m <= n; m <<= 1) {
    int mm = m >> 1;
    cplx zeta = polar<ld>(1, (invert ? 2 : -2) * M_PI / m);
    for(int k = 0; k < n; k += m) {
      cplx om = 1;
      for(int j = 0; j < mm; ++j, om *= zeta) {
        cplx tl = v[k + j], th = om * v[k + j + mm];
        v[k + j] = tl + th;
        v[k + j + mm] = tl - th;
      }
    }
  }
  if(invert)
    for(auto &z: v) z /= ld(n); // normalize for ifft
}
// Convolve f and g, placing the result in res.
// f and g should be the same length. If they are not, just pad them
// up to the nearest power of two after your desired output size.
void convolve(vc &f, vc &g, vc &res) {
  vc tmp;
  fft(f, tmp, false);
  fft(g, res, false);
  for(int i = 0; i < n; ++i) tmp[i] *= res[i];
  fft(tmp, res, true);
}
