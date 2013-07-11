#ifndef _MODULENET_H_
#define _MODULENET_H_

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
#include "functions.h"

using namespace std;

struct net;

struct module
{
    string modulename;
	int numInput;
    int numOutput;
	int value;
	bool isVirtual;
	bool visit;//add
	int best_gain;//add
	string best_lib;//add
    string nodeType;
	vector<module*> Inputs;
	vector<module*> Outputs;
	vector<string> InputNets;
	string OutputNet;
	module()
	{
	  modulename = "";
	  nodeType = "";
	  value = 0;
	  isVirtual = false;
	  visit = false;//add
	  best_gain=0;//add
	  best_lib="";//add
	  numInput = numOutput = 0;
	  OutputNet = "";
	}
	module(string mname, string type, bool isv = false)
	{
	  modulename = mname;
	  nodeType = type;
	  value = 0;
	  isVirtual = isv;
	  visit = false;//add
	  best_gain=0;//add
	  best_lib=type;//add
	  numInput = numOutput = 0;
	  OutputNet = "";
	}
	void set_value(int v)
	{
	  value = v;
	}
};

struct net
{
    string netName;
	bool *has_in;
	int numOutmodules;
	int Nettype; //0 for input, 1 for output, 2 for others
	int bits;
	module** Inmodule;
    vector<module*> *Outmodules;
	net()
	{
	  //has_in = false;
	  netName = "";
	  bits = Nettype = numOutmodules = 0;
	}
	net(string netname, int type, int bit)
	{
	  //has_in = false;
	  netName = netname;
	  Nettype = type;
	  bits = bit;
	  if(bits != 0)
	  {
	    has_in = new bool[bits];
		for(int i = 0 ; i < bits ; i++)
		  has_in[i] = false;
		Inmodule = new module*[bits];
	    Outmodules = new vector<module*>[bits];
	  }
	}
	void set_module_info(int bit, module* m, bool in_or_out)
	{
	  //cout<<"TEST_SMI 0-1"<<endl;
	  string wire_info = netName;
	  //cout<<"TEST_SMI 0-2"<<endl;
	  if(bits > 1)
	    wire_info = wire_info + "[" + inttostr(bit) + "]";
	  //cout<<"TEST_SMI 0-3"<<endl;
	  if(in_or_out)
	  {
	    Inmodule[bit] = m;
		Inmodule[bit]->OutputNet = wire_info;
		has_in[bit] = true;
		for(int i = 0 ; i < Outmodules[bit].size() ; i++)
		{
		  Inmodule[bit]->Outputs.push_back(Outmodules[bit][i]);
		  Outmodules[bit][i]->Inputs.push_back(Inmodule[bit]);
		}
	  }
	  else
	  {
	    //cout<<"TEST_SMI 1-1"<<endl;
	    m->InputNets.push_back(wire_info);
		//cout<<"TEST_SMI 1-2"<<endl;
		//if(has_in && Nettype != 0 && Nettype != 1)
		if(has_in[bit])
		{
		  //cout<<endl<<"TEST1"<<endl;
		  Inmodule[bit]->Outputs.push_back(m);
		  //cout<<"TEST2"<<endl;
	      m->Inputs.push_back(Inmodule[bit]);
		  //cout<<"TEST3"<<endl;
		}
		//cout<<"TEST_SMI 1-3"<<endl;
		Outmodules[bit].push_back(m);
		//cout<<"TEST_SMI 1-4"<<endl;
		numOutmodules++;
	  }
	}
	~net()
	{
	  if(bits != 0)
	  {
	    delete[] has_in;
	    delete[] Inmodule;
	    delete[] Outmodules;
	  }
	}
};

struct lib
{
  string type;
  string name;
  int in_bits[6];
  int out_bits;
  lib()
  {
    type = "";
	name = "";
	for(int i = 0 ; i < 6 ; i++)
	{
	  in_bits[i] = 0;
	}
	out_bits = 0;
  }
};

#endif /* _MODULENET_H_ */
