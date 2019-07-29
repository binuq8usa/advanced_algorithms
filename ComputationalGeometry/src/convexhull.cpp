#include "segment.h"
#include <iostream>

template <typename T>
typename vector<Point<T> >::iterator FindLowestPoint(vector<Point<T> >& pts){
  auto it_lowest = pts.begin();
  for(auto it = pts.begin()+1; it!= pts.end(); it++){
    if( ((*it)[1] < (*it_lowest)[1]) || (((*it)[1] == (*it_lowest)[1]) && ((*it)[0] < (*it_lowest)[0])) ) // check lowest y-coordinate
      it_lowest = it;
  }
  return it_lowest;
}

template <typename T>
vector<Point<T> > ComputeConvexHull(vector<Point<T> >& pts){
  // Step 1: Find the point with the minimum y-coordinate (in case of tie. least x-coordinate)
  auto it_ref = FindLowestPoint<T>(pts);
  iter_swap(it_ref,pts.begin()); // first point will have the left most point
  // Step 2: Sort the remaining points according to polar angle
  PointPolarAngleComparison<T> comp(*pts.begin());
  sort(pts.begin()+1,pts.end(),comp);
  // Step 3: Need to remove points which are the same angle to the reference point - this will be taken
  // care of in the algorithm
  // Push first three points on the stack
  vector<Point<T> > st;
  st.push_back(*pts.begin());
  st.push_back(*(pts.begin()+1));
  st.push_back(*(pts.begin()+2));
  // iterate through the points
  for(auto it = pts.begin()+3; it!= pts.end(); it++){
    T dir = 0;
    while(1){
      Point<T> p_top = *(st.rbegin());
      Point<T> p_next_to_top = *(st.rbegin()+1);
      dir = (p_top - p_next_to_top)*( (*it) - p_next_to_top); // (p_top - p_next_to_top) x (pi - p_next_to_top)
      if(dir>0) break;
      else st.pop_back();
    }
    st.push_back(*it);
  }
  return st;
}
