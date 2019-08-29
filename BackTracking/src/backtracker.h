#ifndef BACKTRACKER_H
#define BACKTRACKER_H

#include <vector>

using namespace std;

template <class T=int, class U=int>
class BackTracker
{
public:
    BackTracker();
protected:
    bool finished_;

  public:
    BackTracker():finished_(true){}
    virtual ~BackTracker(){}

    void Backtrack(vector<T>& a, U input){
      vector<T> candidates;
      int num_candidates;
      if(IsSolution(a,input))
        ProcessSolution(a,input);
      else{
        ConstructCandidates(a,c);
        for(auto it = c.begin(); it != c.end(); it++){
          a.push_back((*it)); // k = k+1; a[k] = c[i]
          MakeMove(a,input); // make the move
          Backtrack(a,input); // backtrack
          UnMakeMove(a,input); // after back track, gets complete, unmake move
          if(finished_) return; // early termination
        }
      }
    }

    virtual bool IsSolution(vector<T>& a, U input){

    }

    virtual void ProcessSolution(vector<T>& a, U input){

    }

    virtual void ConstructCandidates(vector<T>& a, vector<T>& c){

    }

    virtual void MakeMove(vector<T>& a, U input){

    }

    virtual void UnMakeMove(vector<T>& a, U input){

    }
};

#endif // BACKTRACKER_H
