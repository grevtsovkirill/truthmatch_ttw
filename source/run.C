#include <string.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>


void run(){
  gROOT->Reset();
  gROOT->ProcessLine(".L TruthMatchW.C");
  gROOT->ProcessLine("TruthMatchW a");
  gROOT->ProcessLine("a.Loop()");
}   
 
