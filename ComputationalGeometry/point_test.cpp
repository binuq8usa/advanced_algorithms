#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <algorithm>

#include "computation_geometry.h"

TEMPLATE_TEST_CASE("Point Operators","[Point][template]",int,float){
  Point<TestType> p1(2,3);
  Point<TestType> p2(3,4);
  REQUIRE(p1+p2==Point<TestType>(5,7));
  REQUIRE(dot(p1,p2)==18);
  REQUIRE(p1*p2==-1);
  REQUIRE(p1-p2==Point<TestType>(-1,-1));
  REQUIRE(p2-p1==Point<TestType>(1,1));
  REQUIRE(abs(Norm(p1)-std::sqrt(2*2+3*3)) < 10e-3);
  REQUIRE(abs(Norm(p2)-std::sqrt(3*3+4*4)) < 10e-3);
}

TEMPLATE_TEST_CASE("Polar Angle Comparison","[PointPolarComparison][template]",float,double){
    Point<TestType> p_ref(0.5,0.75);
    PointPolarAngleComparison<TestType> comp(p_ref);
    SECTION("Simple test case"){
        REQUIRE(comp(Point<TestType>(4,0),Point<TestType>(2,3.5)) == true);
        REQUIRE(comp(Point<TestType>(2.5,3.24),Point<TestType>(6.4,-3)) == false);
    }
    SECTION("Sorting Test"){
        vector<Point<TestType>> pts;
        pts.push_back(Point<TestType>(2.5,3.24));
        pts.push_back(Point<TestType>(6.4,3));
        pts.push_back(Point<TestType>(1,3.5));
        pts.push_back(Point<TestType>(1.5,1.5));
        pts.push_back(Point<TestType>(4,0.25));
        sort(pts.begin(),pts.end(),comp);
        vector<Point<TestType>> result_pts;
        result_pts.push_back(Point<TestType>(4,0.25));
        result_pts.push_back(Point<TestType>(6.4,3));
        result_pts.push_back(Point<TestType>(1.5,1.5));
        result_pts.push_back(Point<TestType>(2.5,3.24));
        result_pts.push_back(Point<TestType>(1,3.5));
        REQUIRE(pts==result_pts);
    }
}

TEMPLATE_TEST_CASE("Finding left most point","[FindLowestPoint][template]",float,double){
    vector<Point<TestType>> pts;
    pts.push_back(Point<TestType>(2.5,3.24));
    pts.push_back(Point<TestType>(6.4,3));
    pts.push_back(Point<TestType>(1,3.5));
    pts.push_back(Point<TestType>(1.5,1.5));
    pts.push_back(Point<TestType>(0.5,0.75));
    pts.push_back(Point<TestType>(4,0.25));
    auto it = FindLowestPoint<TestType>(pts);
    REQUIRE((*it)==Point<TestType>(4,0.25));
}

TEMPLATE_TEST_CASE("Convex hull","[ComputeConvexHull][template]",float,double){
    vector<Point<TestType>> pts;
    pts.push_back(Point<TestType>(2.5,3.24));
    pts.push_back(Point<TestType>(6.4,3));
    pts.push_back(Point<TestType>(1,3.5));
    pts.push_back(Point<TestType>(1.5,1.5));
    pts.push_back(Point<TestType>(0.5,0.75));
    pts.push_back(Point<TestType>(4,0.25));

    vector<Point<TestType>> convex_pts = ComputeConvexHull<TestType>(pts);
     vector<Point<TestType>> result_pts;
     result_pts.push_back(Point<TestType>(4,0.25));
     result_pts.push_back(Point<TestType>(6.4,3));
     result_pts.push_back(Point<TestType>(1,3.5));
     result_pts.push_back(Point<TestType>(0.5,0.75));
     REQUIRE(convex_pts==result_pts);
}
