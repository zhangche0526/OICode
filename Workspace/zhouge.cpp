LL N;
int pbnd;
int vbnd;
int l0[SIZE], l[SIZE];
LL g0[SIZE], g[SIZE], f0[SIZE], f[SIZE];

void calcG()
{
	for (int i = 1; i < vbnd; ++i) {
		g0[i] = i;
	}
	for (int i = vbnd - 1; i >= 1; --i) {
		g[i] = N / i;
	}
	for (int i = 0; i < pbnd; ++i) {
		int p = primes[i];
		for (int j = 1; j < vbnd && i < l[j]; ++j) {
			LL y = (N / j) / p;
			g[j] -= (y < vbnd ? g0[y] - std::max(0, i - l0[y]) : g[N / y] - std::max(0, i - l[N / y]));
		}
		for (int j = vbnd - 1; j >= 1 && i < l0[j]; --j) {
			LL y = j / p;
			g0[j] -= g0[y] - std::max(0, i - l0[y]);
		}
	}
	for (int i = 1; i < vbnd; ++i) {
		g[i] -= pbnd - l[i];
	}
}

void calcF()
{
	std::fill(f0 + 1, f0 + vbnd, 1);
	std::fill(f + 1, f + vbnd, 1);
	for (int i = pbnd - 1; i >= 0; --i) {
		int p = primes[i];
		for (int j = 1; j < vbnd && i < l[j]; ++j) {
			LL y = (N / j) / p;
			for (int z = 1; y; ++z, y /= p) {
				f[j] += (3 * z + 1) * (y < vbnd ?
						f0[y] + 4 * std::max(0, sump[y] - std::max(l0[y], i + 1)) :
						f[N / y] + 4 * (pbnd - std::max(l[N / y], i + 1)));
			}
		}
		for (int j = vbnd - 1; j >= 1 && i < l0[j]; --j) {
			int y = j / p;
			for (int z = 1; y; ++z, y /= p) {
				f0[j] += (3 * z + 1) * (f0[y] + 4 * std::max(0, sump[y] - std::max(l0[y], i + 1)));
			}
		}
	}
	for (int i = 1; i < vbnd; ++i) {
		f[i] += 4 * (pbnd - l[i]);
	}
}

LL calcSumS3()
{
	for (vbnd = 1; (LL)vbnd * vbnd <= N; ++vbnd) { }
	for (pbnd = 0; (LL)primes[pbnd] * primes[pbnd] <= N; ++pbnd) { }
	for (int i = 1; i < vbnd; ++i) {
		for (l0[i] = l0[i - 1]; (LL)primes[l0[i]] * primes[l0[i]] <= i; ++l0[i]) { }
	}
	l[vbnd] = 0;
	for (int i = vbnd - 1; i >= 1; --i) {
		LL x = N / i;
		for (l[i] = l[i + 1]; (LL)primes[l[i]] * primes[l[i]] <= x; ++l[i]) { }
	}

	calcG();
	calcF();

	LL ret = f[1];
	for (int i = 1; i < vbnd; ++i) {
		ret += d3[i] * 4 * (g[i] - 1);
	}
	return ret;
}
