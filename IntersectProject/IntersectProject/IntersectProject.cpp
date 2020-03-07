#include<set>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 500010;

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
}line[maxn];
set<Point> s;
int n, cnt_l, cnt_c;

Point lineIntersection(const Line& L1, const Line& L2) {
	Vector u = L1.u - L2.u;
	double t = (L2.v ^ u) / (L1.v ^ L2.v);
	return L1.u + L1.v * t;
}

void solveBasic() {
	//line & line
	for (int i = 1; i <= cnt_l; ++i)
		for (int j = i + 1; j <= cnt_l; ++j) {
			s.insert(lineIntersection(line[i], line[j]));
		}
	//circle & circle
	//line & circle
	printf("%d\n", s.size());
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

		}
	}
	if (n <= 1000) {
		solveBasic();
	}
	else {

	}
	return 0;
}