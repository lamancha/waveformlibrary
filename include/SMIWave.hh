#ifndef __SMIWAVE_HH__
#define __SMIWAVE_HH__

#include<vector>
#include<string>
#include<map>
#include<cstdio>
#include<ostream>

class WaveInfo {
public:
  WaveInfo() : Q(0), A(0), T(0), ToT(0), isDigital(false) {}
  WaveInfo(double _Q, double _A, double _T, double _ToT, bool _isDigital) 
    : Q(_Q), A(_A), T(_T), ToT(_ToT), isDigital(_isDigital) {}

  friend std::ostream& operator<< (std::ostream &out, WaveInfo &Info);

  double              Q;         // charge  [coulomb]
  double              A;         // amplitude [Volt]
  double              T;         // starting time [ns]
  double              ToT;       // time over threshold [ns]
  bool                isDigital; // is a digital pulse
};

class WaveForm : public WaveInfo {
public:
  WaveForm() : V(1024,0.0), t(1024,0.0) {
    for(size_t i=0; i<t.size(); i++) t[i] = i*0.2; // [ns] 1 bin = 200 ps
  }

  inline WaveInfo getInfo() const {return WaveInfo(Q,A,T,ToT,isDigital);}
  inline void setTimeBins(double _t){
    for(size_t i=0; i<t.size(); i++) t[i] = i*_t;}
  inline void shiftTime(double _t){
    for(size_t i=0; i<t.size(); i++) t[i] = t[i] + _t;}

  inline void resizeWave(size_t _s) {V.resize(_s); t.resize(_s);}

  std::vector<double> V;         // voltage [Volt]
  std::vector<double> t;         // time    [ns]
};

#endif