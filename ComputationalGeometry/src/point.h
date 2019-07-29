#ifndef POINT_H
#define POINT_H

#include <vector>
#include <cmath>

using namespace std;

template <class T, class U=int>
class Point{
  private:
    vector<T> val_;

  public:
    Point(){
    }

    Point(const T& a){
      val_.push_back(a);
    }

    Point(const T& a,const T& b){
      val_.push_back(a);
      val_.push_back(b);
    }

    Point(const vector<T>& a){
      val_ = a;
    }

    // copy constructor
    Point(const Point& p){
        for(U i = 0; i < p.length(); i++)
            val_.push_back(p[i]);
    }

    U length() const{
      return val_.size();
    }

    // element wise access
    T& operator[](U index){
      if(index < length()) return val_[index];
      else return val_[length()-1];
    }

    // element wise access
    const T& operator[](U index) const{
      if(index < length()) return val_[index];
      else return val_[length()-1];
    }


    bool operator<(const Point& p){
      for(U i=0; i<length(); i++)
        if(val_[i] < p[i]) return true;
        else if(val_[i] > p[i]) return false;
        else continue;
      return false; // if all are equal
    }

    bool operator<=(const Point& p){
      for(U i=0; i<length(); i++)
        if(val_[i] < p[i]) return true;
        else if(val_[i] > p[i]) return false;
        else continue;
      return true; // if all are equal
    }

    bool operator>(const Point& p){
      for(U i=0; i<length(); i++)
        if(val_[i] > p[i]) return true;
        else if(val_[i] < p[i]) return false;
        else continue;
      return false;
    }

    bool operator>=(const Point& p){
      for(U i=0; i<length(); i++)
        if(val_[i] > p[i]) return true;
        else if(val_[i] < p[i]) return false;
        else continue;
      return true;
    }

    // + operator for Point
    Point operator+(Point& b){
      Point sum(vector<T>(length(),0));
      for(U ind = 0; ind < length(); ind++)
        sum[ind] = val_[ind] + b[ind];
      return sum;
    }

    Point operator-(Point& b){
      Point diff(vector<T>(length(),0));
      for(U ind = 0; ind < length(); ind++)
        diff[ind] = val_[ind] - b[ind];
      return diff;
    }

    friend bool operator==(Point const& a, Point const& b){
      if(a.length() == b.length()){
        for(U i = 0 ; i < b.length(); i++)
          if(a[i] != b[i]) return false;
        return true;
      }
      else
        return false;
    }

    // cross product
    // this->Point p1 x p2
    friend T operator*(const Point& p1, const Point& p2){
      T val = 0;
      if(p1.length() == p2.length() && p1.length() <= 2){
        val = p1[0]*p2[1]-p2[0]*p1[1];
      }
      return val;
    }

    // dot product
    friend T dot(Point p1, Point p2){
      T val = 0;
      if(p1.length() != p2.length())
        return val;
      for(U i=0; i < p1.length(); i++)
        val += p1[i]*p2[i];
      return val;
    }

    friend float Norm(Point p){
        T norm = 0.0;
          for(int i = 0 ; i < p.length(); i++)
            norm += p[i]*p[i];
          return std::sqrt(norm);
    }
};

template <class T>
class PointPolarAngleComparison{
  public:
    Point<T> p_ref;
    PointPolarAngleComparison(Point<T> ref){
      p_ref = ref;
    }
    bool operator()(Point<T> p1, Point<T> p2){
      T dir_comp = (p1-p_ref)*(p2-p_ref);
      return (dir_comp >= 0)? true : false;
    }
};

#endif // POINT_H
