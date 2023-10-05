#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())
#define SELF (*this)
template <typename T, typename Cmp = less<T>>
using heap = priority_queue<T,vector<T>,Cmp>;
template <class T, size_t N=0>
using arr = typename conditional<N,array<T,N>,vector<T>>::type;

// pair i/o
template <typename...T> istream& operator>>(istream& is, pair<T...>& v) { return is >> v.ff >> v.ss; }
template <typename...T> ostream& operator<<(ostream& os, const pair<T...>& v) { return os << v.ff << " " << v.ss; }
// tuple i/o
template <typename...T> istream& operator>>(istream& is, tuple<T&...> t) { return apply([&](auto&&... a) { ((is >> a), ...); }, t), is; }
template <typename...T> ostream& operator<<(ostream& os, const tuple<T...>& t) { return apply([&](auto&& f, auto&&... r) { os << f; ((os << " " << r), ...); }, t), os; }

#if (DEBUG && !defined(ONLINE_JUDGE))
#define trace(...) cerr << make_tuple(">> Line",__LINE__,#__VA_ARGS__,"=",__VA_ARGS__,"<<") << endl
#define ifdebug if(1)
#else
#define trace(...)
#define ifdebug if(0)
#endif

/* BOOK CODE */

/* REAL CODE */

const int N = 1e3+3;
int n;
ll x[N];
ll tot_adds = 0;

string solve(ll val) {
  assert(val > 0);
  vi bits;
  for(int b = 0; val; b++) {
    bits.push_back(val & 1);
    val /= 2;
  }
  assert(bits.back() == 1);
  string ans = "1";
  bits.pop_back();
  reverse(all(bits));
  for(int b : bits) {
    ans += "d";
    ans += "+";
    tot_adds++;
    if (b) {
      ans += "1";
      ans += "+";
      tot_adds++;
    }
  }
  return ans;
}

void code() {
  cin >> n;
  rep(i,0,n) cin >> x[i];
  stack<string> ans;
  for(int i=n; i--;) {
    ans.push(solve(x[i]+tot_adds));
  }
  size_t tot_len = 0;
  while(sz(ans)) {
    tot_len += ans.size(); // should be ans.top().size()
    cout << ans.top(); ans.pop();
  }
  trace(tot_len);
  assert(tot_len <= 100000);
  cout << nl;
}

/* MAIN CODE */

int main() { // Emily <3
  atexit([]{ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
  code();
  return 0;
}

