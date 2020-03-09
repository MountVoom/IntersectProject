#include "pch.h"
#include "CppUnitTest.h"
#include "../IntersectProject/IntersectProject.h"
#include "../IntersectProject/IntersectProject.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntersectProjectUnitTest
{
	TEST_CLASS(IntersectProjectUnitTest)
	{
	public:
		
		TEST_METHOD(line_line)
		{
			Line L1, L2;
			s.clear();
			L1 = Line(Point(0, 0), Vector(3, 6));
			L2 = Line(Point(10, 0), Vector(-7, 6));
			lineIntersectionWithLine(L1, L2);
			Assert::AreEqual((int) s.size(), (int)1);
			s.insert(Point(3, 6));
			Assert::AreEqual((int)s.size(), (int)1);

			s.clear();
			L1 = Line(Point(0, 0), Vector(1, 1));
			L2 = Line(Point(1, 0), Vector(1, 1));
			lineIntersectionWithLine(L1, L2);
			Assert::AreEqual((int)s.size(), (int)0);
		}
		TEST_METHOD(line_circle)
		{
			Line L = Line(Point(0, 0), Vector(1, 1));
			Circle C;

			s.clear();
			C = Circle(Point(4, 2), 1);
			lineIntersectionWithCircle(L, C);
			Assert::AreEqual((int)s.size(), (int)0);

			s.clear();
			C = Circle(Point(3, 1), sqrt(2.));
			lineIntersectionWithCircle(L, C);
			Assert::AreEqual((int)s.size(), (int)1);
			s.insert(Point(2, 2));
			Assert::AreEqual((int)s.size(), (int)1);

			s.clear();
			C = Circle(Point(3, 3), sqrt(2.));
			lineIntersectionWithCircle(L, C);
			Assert::AreEqual((int)s.size(), (int)2);
			s.insert(Point(4, 4)); s.insert(Point(4, 4));
			Assert::AreEqual((int)s.size(), (int)2);

		}
		TEST_METHOD(circle_circle)
		{
			Circle C1, C2;

			s.clear();
			C1 = Circle(Point(3, 3), 1);
			C2 = Circle(Point(3, 3), 2);
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)0);

			s.clear();
			C1 = Circle(Point(0, 0), 1);
			C2 = Circle(Point(3, 3), 1);
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)0);

			s.clear();
			C1 = Circle(Point(0, 0), 100);
			C2 = Circle(Point(3, 3), 1);
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)0);

			s.clear();
			C1 = Circle(Point(1, 0), 1);
			C2 = Circle(Point(2, 0), 2);
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)1);
			s.insert(Point(0, 0));
			Assert::AreEqual((int)s.size(), (int)1);

			s.clear();
			C1 = Circle(Point(-1, 0), 1);
			C2 = Circle(Point(2, 0), 2);
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)1);
			s.insert(Point(0, 0));
			Assert::AreEqual((int)s.size(), (int)1);

			s.clear();
			C1 = Circle(Point(-4, 4), sqrt(5.));
			C2 = Circle(Point(-4, 1), sqrt(2.));
			circleIntersectionWithCircle(C1, C2);
			Assert::AreEqual((int)s.size(), (int)2);
			s.insert(Point(-5, 2)); s.insert(Point(-3, 2));
			Assert::AreEqual((int)s.size(), (int)2);
		}
	};
}
