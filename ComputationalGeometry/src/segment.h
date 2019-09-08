#ifndef SEGMENT_H
#define SEGMENT_H
#include <utility>
#include "point.h"
#include <set>

// EXAMPLE!!!!

using namespace std;

template <class T, class U=int>
class Segment{
private:
    Point<T> p_start;
    Point<T> p_end;
public:
    Segment(){}
    Segment(Point<T> p1, Point<T> p2) : p_start(p1),p_end(p2){}
    ~Segment(){}

    friend pair< Point<T>,Point<T> > GetEndPoints(const Segment& seg){
      return make_pair(seg.p_start, seg.p_end);
    }

    // embed coordinate e in between x and y.
    // pair of (x,e,y) and Segment s* -> link to segment
    friend vector< pair<Point<T>,typename Segment<T>::iterator> > ExtractEndPointsFromSegments(const vector<Segment>& segments){
      vector< pair<Point<T>,typename Segment<T>::iterator> > pts;
      for(auto it = segments.begin(); it!= segments.end(); it++){
        auto pp = GetEndPoints(*it);
        auto entry = make_pair(Point<T>(pp.first[0],0,pp.first[1]),it);
        pts.push_back(entry);
        entry = make_pair(Point<T>(pp.second[0],1,pp.second[1]),it);
        pts.push_back(entry);
      }
      return pts;
    }

    friend U FindOrientation(Point<T> p, Segment seg){
      return (p-seg.p_start)*(seg.p_end-seg.p_start);
    }

    friend bool CheckIfPointOnSegment(Point<T> p, Segment seg){
      Point<T> ref_p1(min(seg.p_start[0],seg.p_end[0]));
      Point<T> ref_p2(max(seg.p_start[1],seg.p_end[1]));
      return (p >= ref_p1 && p <= ref_p2);
    }

    friend bool SegmentIntersection(Segment seg1, Segment seg2){
      // find orientation of p1 and p2 with respect to seg p3p4 (seg2)
      U d_seg1_p_start = findOrientation(seg1.p_start, seg2);
      U d_seg1_p_end = findOrientation(seg1.p_end, seg2);

      // find orientation of p3 and p4 with respect to seg p1p2
      U d_seg2_p_start = findOrientation(seg2.p_start, seg1);
      U d_seg2_p_end = findOrientation(seg2.p_end, seg1);

      if( d_seg1_p_start*d_seg1_p_end < 0 && d_seg2_p_start*d_seg2_p_end < 0)
        return true;
      else if(d_seg1_p_start ==0 && checkIfPointOnSegment(seg1.p_start,seg2))
        return true;
      else if(d_seg1_p_end ==0 && checkIfPointOnSegment(seg1.p_end,seg2))
        return true;
      else if(d_seg2_p_start ==0 && checkIfPointOnSegment(seg2.p_start,seg1))
        return true;
      else if(d_seg2_p_end ==0 && checkIfPointOnSegment(seg2.p_end,seg1))
        return true;
      else return false;
    }
};

template <typename T>
struct SegmentPtComparison{
 SegmentPtComparison(){}
  bool operator()(pair<Point<T>,typename Segment<T>::iterator> p1,
                 pair<Point<T>,typename Segment<T>::iterator> p2){
    return (p1.first <= p2.first);
  }
};

#endif // SEGMENT_H
