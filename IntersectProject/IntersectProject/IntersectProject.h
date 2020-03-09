#pragma once
#include<set>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const double eps = 1e-9;
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
		printf("%.10lf %.10lf\n", x, y);
	}
}upperPoint[maxn];
typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (const Vector& A, const Vector& B) { return Vector(A.x - B.x, A.y - B.y); }
double operator * (const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
Point operator * (const Vector& A, const double& p) { return Point(A.x * p, A.y * p); }
bool operator < (const Point& A, const Point& B) { return dcmp(A.x - B.x) < 0 || (!dcmp(A.x - B.x) && dcmp(A.y - B.y) < 0); }
bool operator == (const Point& A, const Point& B) { return !dcmp(A.x - B.x) && !dcmp(A.y - B.y); }
double operator ^ (const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }

struct Line {
	Point u;
	Vector v;
	Line() {}
	Line(Point u, Vector v) :u(u), v(v) {}

	Point point(double t) const {
		return u + v * t;
	}
}line[maxn];

struct Circle {
	Point c;
	double r;
	Circle() {
		c = Point(0, 0);
		r = 0;
	}
	Circle(Point c, double r) :c(c), r(r) {}
	Point point(double a) const {
		return Point(c.x + cos(a) * r, c.y + sin(a) * r);
	}
}circle[maxn];

Point globalIntersection;
set<Point> s;
int n, cnt_l, cnt_c;

struct Node {
	Point x;
	int id, tp;//0->up 1->down <0 -> intersec (line_{id} & line_{-tp})
	Node(Point x, int id, int tp) : x(x), id(id), tp(tp) { }
	bool operator < (const Node& A) const {
		if (!dcmp(x.y - A.x.y)) {
			if (!dcmp(x.x - A.x.x)) {
				return tp > A.tp;
			}
			return dcmp(x.x - A.x.x) > 0;
		}
		return dcmp(x.y - A.x.y) < 0;
	}
};

struct Node2 {
	Point x;
	int id;
	Node2(Point x, int id) :x(x), id(id) {}
	bool operator < (const Node2& A) const {
		return !dcmp(x.x - A.x.x) ? dcmp(x.y - A.x.y) > 0 : dcmp(x.x - A.x.x) < 0;
	}
};
priority_queue<Node> pq;
set<Node2> tree;

int scanLine();
int solveBasic();
void getPoints();
double angle(Vector vec);
double calLength(Vector x);
void updateInsertion(int x, int y);
double calY(const Point& A, const Point& B, double x);
int lineIntersectionWithLine(const Line& L1, const Line& L2);
void lineIntersectionWithCircle(const Line& L, const Circle& C);
void circleIntersectionWithCircle(const Circle& C1, const Circle& C2);