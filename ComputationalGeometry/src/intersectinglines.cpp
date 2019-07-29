#include "segment.h"

template <typename T>
bool IsLineSetIntersecting(vector<Segment<T> >& lines){
  vector<pair<Point<T>,typename Segment<T>::iterator> > end_pts = ExtractEndPointsFromSegments(lines);
  set<typename Segment<T>::iterator> sweep_line_status_set;
  SegmentPtComparison<T> comp_seg_endpts();
  // Step 1 : sort them according to (x,e,y)
  sort(end_pts.begin(), end_pts.end(), comp_seg_endpts);
  // Step 2 :
  for(auto it = end_pts.begin(); it!= end_pts.end(); it++){
    auto seg_it = it->second;
    if(it->first[1] == 0){// left end point
      //  pair< set<Segment<T>::iterator>::iterator,bool>
      auto sweep_ptr_pair = sweep_line_status_set.insert(seg_it); // pair of set pointer and flag to indicate new value
      // check if segment above intersects with current segment
      if(sweep_ptr_pair.first != sweep_line_status_set.end()-1){
        auto seg_it_above = *(sweep_ptr_pair.first+1);
        if(SegmentIntersection(*seg_it_above,*seg_it))
          return true;
      }
      // check if segment intersects below
      if(sweep_ptr_pair.first != sweep_line_status_set.begin()){
        auto seg_it_below = *(sweep_ptr_pair.first-1);
        if(SegmentIntersection(*seg_it_below,*seg_it))
          return true;
      }
    }
    else if(it->first[1] == 1){ // right end point
      auto sweep_ptr = sweep_line_status_set.find(seg_it);
      if(sweep_ptr == sweep_line_status_set.end()) continue;
      if(sweep_ptr != sweep_line_status_set.end()-1 &&
        sweep_ptr != sweep_line_status_set.begin()){
        auto seg_it_above = *(sweep_ptr+1);
        auto seg_it_below = *(sweep_ptr-1);
        if(SegmentIntersection(*seg_it_below,*seg_it_above))
          return true;
      }
      sweep_line_status_set.erase(sweep_ptr);
    }
  }
  return false;
}
