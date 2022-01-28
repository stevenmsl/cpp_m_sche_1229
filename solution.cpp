#include <iostream>

#include <algorithm>
#include <vector>

#include <tuple>
using namespace std;

/* takeaways
   - given any two slots one from each person
     find a overlapping between them that is
     longer than the duration
   - the overlapping is calculated by checking
     what are the later start time and earlier
     end time among the two slots
   - example
     s1:[10,50]
     s2:[0,15]
     - so the overlapping is [10,15]
       - 10 is the later start time between
         the two slots
       - 15 is the earlier end time between
         the two slots
     - if the duration is 8 this overlapping
       won't qualify
   - two pointers; one each person's slots
     - if a match can't be found move the pointer
       per the rules here
       - move the one wit earlier start time
         - no chance to find a match as the
           next slot from another person will
           starts even later than the current
           one you are comparing
       - if the start times are the same,
         move the one with earlier end time
         - the duration of the shorter slot
           can't accommodate the required
           duration; move on
*/

/* 
  - pass in parameter by refernce: 
    - vector<vector<int>> &  
*/

class Solution
{
public:
  /* C++ Note:
     - pass in vector by reference so you won't
       make a copy of it
     - you need to include <algorithm> to use
       sort
     - [], indicates that the body of the lambda
       expression accesses no variables in the 
       enclosing scope 
  */
  vector<int> earliestTimeSlot(vector<vector<int>> &s1,
                               vector<vector<int>> &s2, int duration)

  {
    /* 
      - sort the slots to make sure we get the earliest time slot
        if there is one available 
    */
    sort(s1.begin(), s1.end(), [](const vector<int> &a, const vector<int> &b)
         {
           /* 
             - there will be no overlapping among slots 
             - checking start time is good enough
           */
           return a[0] < b[0];
         });

    sort(s2.begin(), s2.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });

    int p1 = 0, p2 = 0;
    while (p1 < s1.size() && p2 < s2.size())
    {
      /* 
        - find the overlapping
          - pick who starts later
          - and who finishes earlier
      */
      int start = max(s1[p1][0], s2[p2][0]);
      int end = min(s1[p1][1], s2[p1][1]);

      /* 
        - find a match
        - also you don't need to check if end > start
          as end - start should cover it already 
      */
      if (end - start >= duration)
        return {start, start + duration};

      //move pointer

      /* move who starts eariler */
      if (s1[p1][0] < s2[p2][0])
        p1++;
      else if (s1[p1][0] > s2[p2][0])
        p2++;
      /* start times are the same */
      else
      {
        /* move who finishs earlier */
        if (s1[p1][1] < s2[p2][1])
          p1++;
        else if (s1[p1][1] > s2[p2][1])
          p2++;
        /* both have to move on */
        else
        {
          p1++;
          p2++;
        }
      }
    }

    return {};
  }
};

// [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
tuple<vector<vector<int>>, vector<vector<int>>, int> testFixture1()
{

  vector<vector<int>> vec1{{10, 50},
                           {60, 120},
                           {140, 210}};
  vector<vector<int>> vec2{{0, 15},
                           {60, 70}};

  return make_tuple(vec1, vec2, 8);
}
// Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
tuple<vector<vector<int>>, vector<vector<int>>, int> testFixture2()
{

  vector<vector<int>> vec1{{10, 50},
                           {60, 120},
                           {140, 210}};
  vector<vector<int>> vec2{{0, 15},
                           {60, 70}};

  return make_tuple(vec1, vec2, 12);
}

void printVec(vector<int> &vec)
{
  if (vec.size() == 0)
  {
    cout << "[]";
    return;
  }

  for (int i = 0; i < vec.size(); i++)
  {
    cout << "[" << vec[i];
    if (i < vec.size() - 1)
      cout << ",";
    cout << "]";
  }
}

void test1()
{
  tuple<vector<vector<int>>, vector<vector<int>>, int> fixture = testFixture1();
  vector<vector<int>> s1 = std::get<0>(fixture);
  vector<vector<int>> s2 = std::get<1>(fixture);
  int duration = std::get<2>(fixture);
  Solution sol;
  vector<int> found = sol.earliestTimeSlot(s1, s2, duration);
  cout << "Test 1 - expect to see [60,68]" << endl;
  cout << "result:";
  printVec(found);
  cout << endl;
}

void test2()
{
  tuple<vector<vector<int>>, vector<vector<int>>, int> fixture = testFixture2();
  vector<vector<int>> s1 = std::get<0>(fixture);
  vector<vector<int>> s2 = std::get<1>(fixture);
  int duration = std::get<2>(fixture);
  Solution sol;
  vector<int> found = sol.earliestTimeSlot(s1, s2, duration);
  cout << "Test 2 - expect to see []" << endl;
  cout << "result:";
  printVec(found);
  cout << endl;
}

main()
{
  test1();
  test2();
  return 0;
}