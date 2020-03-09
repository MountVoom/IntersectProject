#include "IntersectProject.h"

int lineIntersectionWithLine(const Line& L1, const Line& L2) {
	if (!dcmp(L1.v ^ L2.v)) return 0;
	Vector u = L1.u - L2.u;
	double t = (L2.v ^ u) / (L1.v ^ L2.v);
	globalIntersection = L1.u + L1.v * t;
	s.insert(globalIntersection);
	return 1;
}

void lineIntersectionWithCircle(const Line& L, const Circle& C) {
	double t1, t2;
	double a = L.v.x, b = L.u.x - C.c.x, c = L.v.y, d = L.u.y - C.c.y;
	double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
	double delta = f * f - 4 * e * g;
	if (dcmp(delta) < 0) return;
	if (dcmp(delta) == 0) {
		s.insert(L.point(-f / (2 * e)));
	}
	else {
		t1 = (-f - sqrt(delta)) / (2 * e); s.insert(L.point(t1));
		t2 = (-f + sqrt(delta)) / (2 * e); s.insert(L.point(t2));
	}
}

double calLength(Vector x) {
	return sqrt(x * x);
}

double angle(Vector vec) {
	return atan2(vec.y, vec.x);
}

void circleIntersectionWithCircle(const Circle& C1, const Circle& C2) {
	double d = calLength(C1.c - C2.c);
	if (dcmp(d) == 0)  return;
	if (dcmp(C1.r + C2.r - d) < 0) return;
	if (dcmp(fabs(C1.r - C2.r) - d) > 0) return;
	double a = angle(C2.c - C1.c);
	double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
	Point p1 = C1.point(a - da), p2 = C1.point(a + da);
	s.insert(p1);
	if (p1 == p2) return;
	s.insert(p2);
}

int solveBasic() {
	//line & line
	for (int i = 1; i <= cnt_l; ++i)
		for (int j = i + 1; j <= cnt_l; ++j) {
			lineIntersectionWithLine(line[i], line[j]);
		}
	//circle & circle
	for (int i = 1; i <= cnt_c; ++i)
		for (int j = i + 1; j <= cnt_c; ++j) {
			circleIntersectionWithCircle(circle[i], circle[j]);
		}
	//line & circle
	for (int i = 1; i <= cnt_l; ++i)
		for (int j = 1; j <= cnt_c; ++j) {
			lineIntersectionWithCircle(line[i], circle[j]);
		}
	return s.size();
}

double calY(const Point& A, const Point& B, double x) {
	//(x - A.x) * (y - B.y) = (x - B.x) * (y - A.y)
	double k1 = x - A.x, k2 = x - B.x;
	return (k1 * B.y - k2 * A.y) / (k1 - k2);
}

void getPoints() {
	Point B;
	double lx = -1e11, rx = 1e11, ly, ry;
	for (int i = 1; i <= cnt_l; ++i) {
		B = line[i].u + line[i].v;
		if (!dcmp(line[i].u.x - B.x)) {
			pq.push(Node(Point(B.x, rx), i, 0));
			pq.push(Node(Point(B.x, lx), i, 1));
			upperPoint[i] = Point(B.x, rx);
		}
		else {
			ly = calY(line[i].u, B, lx);
			ry = calY(line[i].u, B, rx);
			if (dcmp(ly - ry) >= 0) {
				pq.push(Node(Point(lx, ly), i, 0));
				pq.push(Node(Point(rx, ry), i, 1));
				upperPoint[i] = Point(lx, ly);
			}
			else {
				pq.push(Node(Point(lx, ly), i, 1));
				pq.push(Node(Point(rx, ry), i, 0));
				upperPoint[i] = Point(rx, ry);
			}
		}
	}
}

set<pii> has;

void updateInsertion(int x, int y) {
	if (lineIntersectionWithLine(line[x], line[y])) {
		if (has.find(mp(x, y)) == has.end()) {
			has.insert(mp(x, y));
			pq.push(Node(globalIntersection, x, -y));
		}
	}
}

int scanLine() {
	getPoints();
	while (!pq.empty()) {
		auto node = pq.top(); pq.pop();
		if (node.tp == 0) {
			auto node2 = Node2(node.x, node.id);
			tree.insert(node2);
			auto it = tree.find(node2);
			if (it != tree.begin()) {
				updateInsertion(prev(it)->id, it->id);
			}
			if (next(it) != tree.end()) {
				updateInsertion(it->id, next(it)->id);
			}
		}
		else if (node.tp == 1) {
			auto node2 = Node2(upperPoint[node.id], node.id);
			auto it = tree.find(node2);
			if (it != tree.begin() && next(it) != tree.end()) {
				updateInsertion(prev(it)->id, next(it)->id);
			}
			tree.erase(it);
		}
		else {
			//node.id -> pl -node.tp -> pr
			auto pl = Node2(upperPoint[node.id], node.id);
			auto pr = Node2(upperPoint[-node.tp], -node.tp);
			auto itl = tree.find(pl);
			auto itr = tree.find(pr);
			if (itl != tree.begin()) {
				updateInsertion(prev(itl)->id, itr->id);
			}
			if (next(itr) != tree.end()) {
				updateInsertion(itl->id, next(itr)->id);
			}
		}
	}
	return s.size();
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
		printf("%d\n", solveBasic());
	}
	else {
		if (cnt_c) {
			printf("%d\n", solveBasic());
		}
		else {
			printf("%d\n", scanLine());
		}
	}
	return 0;
}