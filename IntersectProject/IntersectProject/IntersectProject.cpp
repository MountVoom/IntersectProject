#include<set>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const double eps = 1e-8;
const int maxn = 500010;

inline int dcmp(double x) {
	return (x > eps) - (x < -eps);
}

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	void read() {
		cin >> x >> y;
	}
	void print() {
		printf("%lf %lf\n", x, y);
	}
};
typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (const Vector& A, const Vector& B) { return Vector(A.x - B.x, A.y - B.y); }
double operator * (const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
Point operator * (const Vector& A, const double& p) { return Point(A.x * p, A.y * p); }
bool operator < (const Point& A, const Point& B) { return A.x < B.x || (A.x == B.x && A.y < B.y); }
double operator ^ (const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }

struct Line {
	Point u;
	Vector v;
	Point point(double t) const {
		return u + v * t;
	}
}line[maxn];

struct Circle {
	Point c;
	double r;
}circle[maxn];

set<Point> s;
int n, cnt_l, cnt_c;

void lineIntersectionWithLine(const Line& L1, const Line& L2) {
	if (!dcmp(L1.v ^ L2.v)) return;
	Vector u = L1.u - L2.u;
	double t = (L2.v ^ u) / (L1.v ^ L2.v);
	s.insert(L1.u + L1.v * t);
}

void lineIntersectionWithCircle(const Line& L, const Circle& C) {
	double t1, t2;
	double a = L.v.x, b = L.u.x - C.c.x, c = L.v.y, d = L.u.y - C.c.y;
	double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
	double delta = f * f - 4 * e * g;
	if (dcmp(delta) < 0) return ;
	if (dcmp(delta) == 0) {
		s.insert(L.point(-f / (2 * e)));
	}
	else {
		t1 = (-f - sqrt(delta)) / (2 * e); s.insert(L.point(t1));
		t2 = (-f + sqrt(delta)) / (2 * e); s.insert(L.point(t2));
	}

}

void solveBasic() {
	//line & line
	for (int i = 1; i <= cnt_l; ++i)
		for (int j = i + 1; j <= cnt_l; ++j) {
			lineIntersectionWithLine(line[i], line[j]);
		}
	for (auto p : s) p.print();
	//circle & circle
	//line & circle
	for (int i = 1; i <= cnt_l; ++i)
		for (int j = 1; j <= cnt_c; ++j) {
			lineIntersectionWithCircle(line[i], circle[j]);
		}
	printf("%d\n", s.size());
}

void scanLine() {

}

int main()
{
	ios::sync_with_stdio(false);
	Point A, B; char tp[10];
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> tp;
		if (tp[0] == 'L') {
			++cnt_l;
			A.read();
			B.read();
			line[cnt_l].u = A;
			line[cnt_l].v = B - A;
		}
		else {
			++cnt_c;
			circle[cnt_c].c.read();
			cin >> circle[cnt_c].r;
		}
	}
	if (n <= 1000) {
		solveBasic();
	}
	else {
		if (cnt_c) {
			solveBasic();
		}
		else {
			scanLine();
		}
	}
	return 0;
}