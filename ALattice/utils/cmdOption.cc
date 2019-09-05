#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
#include <cctype>
#include "vector.h"

bool cmdOptionExists(char **begin, char **end, const std::string &option)
{
  return std::find(begin, end, option) != end;
}

std::string getCmdOption(char **begin, char **end, const std::string &option)
{
  char **p = std::find(begin, end, option);
  assert(p != end);
  if(++p != end) return *p;
  else return {}; //empty string
}

std::vector<int> strToIntVector(const std::string &str)
{
  std::stringstream ss(str);
  int i;
  std::vector<int> v;
  while(ss>>i)
  {
    v.push_back(i);
    while(std::ispunct(ss.peek()))
      ss.ignore();
  }
  return v;
}

double strToDouble(const std::string &str)
{
  std::stringstream ss(str);
  double d;
  ss >> d;
  return d;
}

int strToInt(const std::string &str)
{
  std::stringstream ss(str);
  int i;
  ss >> i;
  return i;
}

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  // cout << getCmdOption(argv, argv+argc, "--m");
  // stringstream ss("4.5.6.7");
  cout << strToDouble("7");
  // int i;
  // ss >> i;
  // cout << i << endl;;
  // cout << char(ss.peek()) <<endl;
  //
  // ss >> i;
  // cout << i <<endl;
}
