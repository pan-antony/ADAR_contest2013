#include "functions.h"

using namespace std;

string inttostr(int i)
{
  string s;
  stringstream ss(s);
  ss << i;
  return ss.str();
}

int strtoint(string str)
{
  bool neg = false;
  int slen = str.length();
  int start = 0;
  vector<int> temp;
  //int sum = 0;
  double sum = 0;
  if(slen > 0)
  {
    if(str[0] == '-')
	{
	  neg = true;
	  start++;
	}
	for(int i = start ; i < slen ; i++)
	{
	  if(str[i] == '1')
	  {
	    temp.push_back(1);
	  }
	  else if(str[i] == '2')
	  {
	    temp.push_back(2);
	  }
	  else if(str[i] == '3')
	  {
	    temp.push_back(3);
	  }
	  else if(str[i] == '4')
	  {
	    temp.push_back(4);
	  }
	  else if(str[i] == '5')
	  {
	    temp.push_back(5);
	  }
	  else if(str[i] == '6')
	  {
	    temp.push_back(6);
	  }
	  else if(str[i] == '7')
	  {
	    temp.push_back(7);
	  }
	  else if(str[i] == '8')
	  {
	    temp.push_back(8);
	  }
	  else if(str[i] == '9')
	  {
	    temp.push_back(9);
	  }
	  else if(str[i] == '0')
	  {
	    temp.push_back(0);
	  }
	  else
	    break;
	}
	double size = temp.size()-1;
	for(int i = 0 ; i < temp.size() ; i++)
	{
      sum += temp[i]*pow(10.0,size-i);
	  //cout<<sum<<endl;
	}
	//cout<<endl;
	//sum /= 10;
	if(neg)
	  sum = sum*-1;
	return (int)sum;
  }
  else
    return 0;
}

void strerase(string &mainstr, string cutdstr)
{
  int numFindstr = cutdstr.length();
  int posLeft = 0;
  int posRight = 0;
  bool findfirst = false;
  for(int i = 0 ; i < mainstr.length() ; i++)
  {
    bool pass = true;
	for(int j = 0 ; j < cutdstr.length() ; j++)
	{
      if(mainstr[i] == cutdstr[j])
	  {
	    pass = false;
	    break;
	  }
	}
	if(!findfirst && !pass)
	{
	  continue;
	}
	else if(!findfirst && pass)
	{
	  findfirst = true;
	  continue;
	}
	else if(findfirst && !pass)
	{
	  posRight = i;;
	  break;
	}
  }
  mainstr.erase(0,posRight);
  if(mainstr[0] == ',');
    mainstr.erase(0,1);
}

string strcut(string mainstr, string cutdstr)
{
  int numFindstr = cutdstr.length();
  int posLeft = 0;
  int posRight = 0;
  bool findL = false;
  bool findR = false;
  for(int i = 0 ; i < mainstr.length() ; i++)
  {
    if(!findL)
	{
	  bool pass = true;
	  for(int j = 0 ; j < cutdstr.length() ; j++)
	  {
        if(mainstr[i] == cutdstr[j])
	    {
		  pass = false;
	      break;
	    }
	  }
	  if(pass)
	  {
	    posLeft = i;
		posRight++;
		findL =  true;
	  }
	}
	else if(!findR)
	{
	  bool pass = true;
	  for(int j = 0 ; j < cutdstr.length() ; j++)
	  {
        if(mainstr[i] == cutdstr[j])
	    {
		  pass = false;
	      break;
	    }
	  }
	  if(pass)
	  {
	    posRight++;
	  }
	  else
	    findR =  true;
	}
	else
	  break;
  }
  string result = mainstr.substr(posLeft,posRight);
  return result;
}

