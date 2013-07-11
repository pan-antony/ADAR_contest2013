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
#include "module_net.h"

using namespace std;

string assignbreak = "abcdefghijklmnopqrstuvwxyz0123456789=; ";

struct net;
struct module;

void parse(ifstream& in1,ifstream& in2,ofstream& out,vector<net*> &vNets,vector<module*> &vModules,vector<lib*> &vLibs,map<string,net*> &mNets,map<string,module*> &mModules,vector<module*> &virtualinputs,vector<module*> &virtualoutputs,string wordbreak)
{
  string str;
  string strfirst,temp_strfirst;
  bool endline = true;
  bool filebegin = false;
  bool manywirebits = false;
  int wirebits = 0;
  int m_nets = 0;
  int ignorelines = 0;
  int numinputs = 0;
  int numoutputs = 0;
  int module_count = 0;
  module* premodule = 0;
  while(!in1.eof())
  {
    getline(in1,str);
	bool firstline = false;
	//cout<<str<<endl;
	if(endline)
	{
	  strfirst = strcut(str,wordbreak);
	  temp_strfirst = strfirst;
	  if(!filebegin && strfirst != "module")
	    continue;
	  else
	    filebegin = true;
	  firstline = true;
	}
	else
	  strfirst = temp_strfirst;
	endline = false;
	for(int i = 0 ; i < str.length() ; i++)
	{
	  //out<<str[i]<<endl;
	  if(str[i] == ';')
	  {
		//cout<<"PASS"<<endl;
		endline = true;
		break;
	  }
	}
	//out<<strfirst<<endl;
	if(strfirst == "module" || strfirst == "input" || strfirst == "output")
	{
	  out<<str<<endl;
	  if(strfirst == "input" || strfirst == "output")
	  {
	    ignorelines++;
		if(strfirst == "input")
		  numinputs++;
		else if(strfirst == "output")
		  numoutputs++;
	  }
	}
	else if(strfirst == "wire" && ignorelines > 0)
	{
	  //out<<"Ignore"<<endl;
	  out<<str<<endl;
	  if(firstline)
	    strerase(str,wordbreak);
	  strfirst = strcut(str,wordbreak);
	  int Nettype = -1;
	  if(numinputs > 0)
	  {
		//cout<<"Input ";
		Nettype = 0;
		numinputs--;
	  }
	  else if(numoutputs > 0)
	  {
		//cout<<"Output ";
		Nettype = 1;
		numoutputs--;
	  }
	  if(strfirst[0] == '[' || (!firstline && manywirebits))
	  {
	    manywirebits = true;
	    int bits;
	    if(firstline)
		{
	      strerase(strfirst,"[");
		  bits = strtoint(strfirst)+1;
		  wirebits = bits;
		  //cout<<"wire with "<<bits<<" bits"<<endl;
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		else if(!firstline && manywirebits)
		{
		  bits = wirebits;
		}
		while(strfirst != "")
		{
		  //cout<<strfirst<<", ";
		  net* newnet = new net(strfirst,Nettype,bits);
		  vNets.push_back(newnet);
		  mNets[strfirst] = newnet;
		  for(int i = 0 ; i < bits ; i++)
		  {
		    module* newmodule;
			if(Nettype == 0)
			  newmodule = new module(strfirst+"["+inttostr(i)+"]","Input",true);
			else if(Nettype == 1)
			  newmodule = new module(strfirst+"["+inttostr(i)+"]","Output",true);
			vModules.push_back(newmodule);
			if(Nettype == 0)
			  mNets[strfirst]->set_module_info(i,newmodule,true);
			else if(Nettype == 1)
			  mNets[strfirst]->set_module_info(i,newmodule,false);
		  }
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		//cout<<endl;
	  }
	  else
	  {
	    manywirebits = false;
	    //cout<<"wire with "<<1<<" bits"<<endl;
		strfirst = strcut(str,wordbreak);
		while(strfirst != "")
		{
		  //cout<<strfirst<<", ";
		  net* newnet = new net(strfirst,Nettype,1);
		  vNets.push_back(newnet);
		  mNets[strfirst] = newnet;
		  module* newmodule;
		  if(Nettype == 0)
		    newmodule = new module(strfirst,"Input",true);
		  else if(Nettype == 1)
		    newmodule = new module(strfirst,"Output",true);
		  vModules.push_back(newmodule);
		  if(Nettype == 0)
			mNets[strfirst]->set_module_info(0,newmodule,true);
		  else if(Nettype == 1)
			mNets[strfirst]->set_module_info(0,newmodule,false);
		  
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		//cout<<endl;
	  }
	  ignorelines--;
	}
	else if(strfirst == "wire" && ignorelines <= 0)
	{
	  if(firstline)
	    strerase(str,wordbreak);
	  strfirst = strcut(str,wordbreak);
	  //cout<<"Normal ";
	  if(strfirst[0] == '[' || (!firstline && manywirebits))
	  {
	    manywirebits = true;
	    int bits;
	    if(firstline)
		{
	      strerase(strfirst,"[");
		  bits = strtoint(strfirst)+1;
		  wirebits = bits;
		  //cout<<"wire with "<<bits<<" bits"<<endl;
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		else if(!firstline && manywirebits)
		{
		  bits = wirebits;
		}
	    while(strfirst != "")
		{
		  //cout<<strfirst<<", ";
		  net* newnet = new net(strfirst,2,bits);
		  vNets.push_back(newnet);
		  mNets[strfirst] = newnet;
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		//cout<<endl;
	  }
	  else
	  {
	    manywirebits = false;
	    //cout<<"wire with "<<1<<" bits"<<endl;
		strfirst = strcut(str,wordbreak);
		while(strfirst != "")
		{
		  //cout<<strfirst<<", ";
		  net* newnet = new net(strfirst,2,1);
		  vNets.push_back(newnet);
		  mNets[strfirst] = newnet;
		  strerase(str,wordbreak);
		  strfirst = strcut(str,wordbreak);
		}
		//cout<<endl;
	  }
	}
	else if(strfirst == "buf" || strfirst == "not" || strfirst == "and" || strfirst == "nand" || strfirst == "or" || strfirst == "nor" || strfirst == "xor" || strfirst == "xnor")
	{
	  //cout<<str<<endl;
	  string moduletype = strfirst;
	  string modulename = "";
	  if(firstline)
	  {
   	    strerase(str,wordbreak+"[]");
	    if(str[0] == '(')
	    {
	      strfirst = "noname"+inttostr(module_count);
	    }
	    else
	    {
	      strfirst = strcut(str,wordbreak+"[]");
		  strerase(str,wordbreak+"[]");
	    }
	  }
	  
	  module* newmodule;
	  
	  int count;
	  if(firstline)
	  {
	    newmodule = new module(strfirst,moduletype);
		vModules.push_back(newmodule);
		premodule = newmodule;
		//cout<<moduletype<<" with ";
		module_count++;
	    count = 0;
		m_nets = 0;
	  }
	  else
	  {
	    newmodule = premodule;
	    count = ++m_nets;
	  }
	  //strfirst = strcut(str,wordbreak+"[]");
	  while(str != "" && str != " " && str != "  " && str != ";")
	  {
	    if(count == 0)
		{
		  //cout<<"output wire: ";
		}
		else if(count == 1)
		{
		  //cout<<", and intput wires: ";
		}
	    strfirst = strcut(str,wordbreak+"[]");
		if(strfirst == "" || strfirst == " ")
		  break;
		if(count == 0 || count == 1)
		{
		  //cout<<strfirst;
		}
		else
		{
		  //cout<<", "<<strfirst;
		}
	    strerase(str,wordbreak+"[]");
	    string temp = strcut(str,wordbreak+"[]");
		int bit = 0;
	    if(temp[0] == '0' || temp[0] == '1' || temp[0] == '2' || temp[0] == '3' || temp[0] == '4' || temp[0] == '5' || temp[0] == '6' || temp[0] == '7' || temp[0] == '8' || temp[0] == '9')
	    {
	      bit = strtoint(temp);
		  //cout<<"["<<bit<<"]";
		  strerase(str,wordbreak+"[]");
	    }
		if(count == 0)
		{
		  //cout<<"TEST1-1"<<endl;
		  mNets[strfirst]->set_module_info(bit,newmodule,true);
		  //cout<<"TEST1-2"<<endl;
		}
		else if(strfirst[0] != '1' && strfirst[0] != '2' && strfirst[0] != '3' && strfirst[0] != '4' && strfirst[0] != '5' && strfirst[0] != '6' && strfirst[0] != '7' && strfirst[0] != '8' && strfirst[0] != '9')
		{
		  //cout<<"TEST2-1 : "<<newmodule<<", "<<newmodule->modulename<<endl;
		  mNets[strfirst]->set_module_info(bit,newmodule,false);
		  //cout<<"TEST2-2 : "<<newmodule<<endl;
		}
		else
		{
		  //cout<<"TEST3-1 : "<<newmodule<<", "<<newmodule->modulename<<", "<<strfirst<<endl;
		  newmodule->InputNets.push_back(strfirst);
		  //cout<<"TEST3-2 : "<<newmodule<<endl;
		}
		count++;
	  }
	  //cout<<endl;
	}
	else if(strfirst == "endmodule")
	  break;
  }
  while(!in2.eof())
  {
    getline(in2,str);
	string strfirst = strcut(str,wordbreak);
	if(strfirst == "module")
	{
	  strerase(str,wordbreak);
	  strfirst = strcut(str,wordbreak);
	  lib* newlib = new lib();
	  newlib->name = strfirst;
	  int in_count = 0;
	  int out_count = 0;
	  getline(in2,str);
	  strfirst = strcut(str,wordbreak);
	  while(strfirst != "endmodule")
	  {
	    strerase(str,wordbreak);
	    if(strfirst == "input")
		{
		  strfirst = strcut(str,wordbreak);
		  strerase(strfirst,"[");
		  int bits = strtoint(strfirst)+1;
		  newlib->in_bits[in_count++] = bits;
		}
		else if(strfirst == "output")
		{
		  strfirst = strcut(str,wordbreak);
		  strerase(strfirst,"[");
		  int bits = strtoint(strfirst)+1;
		  newlib->out_bits = bits;
		}
		else if(strfirst == "assign")
		{
		  string lib_type = "";
		  while(str!="" && strcut(str,assignbreak)!="")
		  {
		    lib_type += strcut(str,assignbreak);
            strerase(str,assignbreak);
		  }
		  newlib->type = lib_type;
		}
		
		getline(in2,str);
	    strfirst = strcut(str,wordbreak);
	  }
	  vLibs.push_back(newlib);
	}
  }
  
  int pre_bits = -1;
  for(int i = 0 ; i < vNets.size() ; i++)
  {
    if(vNets[i]->Nettype == 2)
	{
	  if(vNets[i]->bits != pre_bits)
	  {
	    if(pre_bits != -1)
		  out<<";"<<endl;
	    pre_bits = vNets[i]->bits;
		out<<"  wire ";
		if(pre_bits > 1)
		  out<<"["<<pre_bits-1<<":0]";
	  }
	  else
	    out<<", ";
	  out<<vNets[i]->netName;
	}
  }
  out<<";"<<endl;
  for(int i = 0 ; i < vModules.size() ; i++)
  {
    if(!vModules[i]->isVirtual)
	{
    /*out<<vModules[i]->modulename<<" has inputs from ";
	for(int j = 0 ; j < vModules[i]->Inputs.size() ; j++)
	{
	  if(vModules[i]->Inputs[j])
	  {
	    if(j==0)
	      out<<vModules[i]->Inputs[j]->modulename;
	    else
	      out<<", "<<vModules[i]->Inputs[j]->modulename;
	  }
	}
	out<<" & outputs to ";
	for(int j = 0 ; j < vModules[i]->Outputs.size() ; j++)
	{
	  if(j==0)
	    out<<vModules[i]->Outputs[j]->modulename;
	  else
	    out<<", "<<vModules[i]->Outputs[j]->modulename;
	}
	out<<endl;
	*/
	out<<"  "<<vModules[i]->nodeType<<" "<<vModules[i]->modulename<<" (";
	out<<vModules[i]->OutputNet;
	for(int j = 0 ; j < vModules[i]->InputNets.size() ; j++)
	{
	  out<<", "<<vModules[i]->InputNets[j];
	}
	out<<");"<<endl;
	}
	else
	{
	  //cout<<"Virtual module "<<vModules[i]->nodeType<<": "<<vModules[i]->modulename<<endl;
	  //out<<"Virtual module "<<vModules[i]->nodeType<<": "<<vModules[i]->modulename<<endl;
	}
  }
  
  out<<"endmodule"<<endl;
}
