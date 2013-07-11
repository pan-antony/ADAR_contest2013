#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <functional>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "parser.h"
#include "TCfunctions.h"


// test

using namespace std;

string wordbreak = " ,;()\n\t\r";

int main(int argc, char* argv[])
{
  clock_t start,end;
  start = clock();

  ifstream in1(argv[1]);
  ifstream in2(argv[2]);
  ofstream out(argv[3]);

  vector<net*> vNets;
  vector<module*> vModules;
  vector<lib*> vLibs;
  map<string,net*> mNets;
  map<string,module*> mModules;
  vector<module*> virtualinputs;
  vector<module*> virtualoutputs;

  parse(in1,in2,out,vNets,vModules,vLibs,mNets,mModules,virtualinputs,virtualoutputs,wordbreak);

  //==========Tung Che start==========
  int total_cost=Calculate_Delay(vModules);
  cout<<total_cost<<endl;
  //==========Tung Che end==========

  //out<<"===========================TEST==========================="<<endl;
  for(int i = 0 ; i < vNets.size() ; i++)
  {
    //out<<vNets[i]->netName<<endl;
    delete vNets[i];
  }
  for(int i = 0 ; i < vModules.size() ; i++)
  {
    //out<<vModules[i]->modulename<<endl;
    delete vModules[i];
  }
  for(int i = 0 ; i < vLibs.size() ; i++)
  {
    //out<<"======================================================"<<endl;
    //out<<vLibs[i]->name<<" : "<<vLibs[i]->type<<endl;
	//for(int j = 0 ; j < 6 ; j++)
	//{
	//  out<<"In["<<j<<"] : "<<vLibs[i]->in_bits[j]<<endl;
	//}
	//out<<"Out : "<<vLibs[i]->out_bits<<endl;
	//out<<"======================================================"<<endl;
    delete vLibs[i];
  }
  end = clock();
  printf("Total Execution Time: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);

  //system("pause");
  return 0;
}
