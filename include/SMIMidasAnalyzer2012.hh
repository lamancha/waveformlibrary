#ifndef __SMIMIDASANALYZER2012_H__
#define __SMIMIDASANALYZER2012_H__

#ifdef __HAVEMIDAS

#include"SMIWaveformAnalyzer.hh"
// stdlib includes
#include<string>
#include<fstream>
#include<vector>
#include<map>

#include"SMIMidasAnalyzerDataTypes.hh"

class TMidasEvent;

class SMIMidasAnalyzer2012 : public SMIWaveformAnalyzer{
public:
  SMIMidasAnalyzer2012() : subevents(0), srad(5), ADCNum(0),timeDiff(10.0) {}
  SMIMidasAnalyzer2012(std::string configfile) : subevents(0), srad(5), ADCNum(0),timeDiff(10.0) 
  {readConfigFile(configfile);}

  virtual bool loop(size_t start, size_t num, processBase &func);
  bool readConfigFile(std::string configfile);
  bool loadEvent(size_t num);
  bool prepareMidasEvent(TMidasEvent &event);

  inline void purgeEvents(size_t num) {if(rawMidasEvent.size()>num) 
      rawMidasEvent.erase(rawMidasEvent.begin(),rawMidasEvent.begin()+num);};
private:
  int matchEvents();

  V1742::sheader  *decodeEventHeader(void *ptr, size_t size);
  V1742::sgheader *decodeGroupHeader(void *ptr, size_t size);
  std::map<std::string,std::string> midasChannelBanks;
  std::vector<std::map<int,V1742::rawEvent> > rawMidasEvent;
  std::vector<std::map<int,V1742::rawEvent> > unmatchedMidasEvent;

  size_t subevents;
  size_t srad;
  size_t ADCNum;
  double timeDiff;

};

#endif

#endif
