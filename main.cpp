#include "ArgumentManager.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

string clearString(string line)
{
  for (char & c : line)
  {
    c = std::tolower(c);
    
    if (std::ispunct(c))
    {
      c = ' ';
    }
  }
  return line;
}

int main(int argc, char *argv[])
{
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  //ifstream input("input1.txt");
  //ofstream output("output1.txt");

  int inbox = 0;
  string line, tmp;
  map<string, int> m;
  
  while(getline(input, line))
  {
    if(line.substr(0, 4).compare("Dear") == 0)
    {
      if(inbox == 0)
      {
        inbox++;
        continue;
      }
      else
      {
        inbox++;
        bool isTrue = false;
        for(const auto &pair : m)
        {
          if(pair.second > 1)
          {
            isTrue = true;
            break;
          }
        }

        if(isTrue)
        {
          output << "True" << endl;
          for (const auto &pair : m)
          {
            output << pair.first << ": " << pair.second << endl;
          }
        }
        else
        {
          output << "False" << endl;
        }
      }
      m.clear();
    }

  if(line.substr(0, 4).compare("Dear") == 0)
  {
    continue;  
  } 
    
  line = clearString(line);
  stringstream ss;
  ss << line;

  while(ss >> tmp)
  {
    if (m.find(tmp) == m.end())
    {
      m.insert(make_pair(tmp, 1));
    }
    else
    {
      m[tmp]++;
    }
  }
}
  
  bool isTrue = false;
  for(const auto &pair : m)
  {
    if(pair.second > 1)
    {
      isTrue = true;
      break;
    }
  }
  
  if(isTrue)
  {
    output << "True" << endl;
    for(const auto &pair : m)
    {
      output << pair.first << ": " << pair.second << endl;
    }
    return 0;
  }
  output << "False" << endl;
}
