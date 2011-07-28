#pragma once
#include "../../core/MuninNodePlugin.h"
#include "SMARTMuninNodePlugin.h"

class HDMuninNodePlugin : public MuninNodePlugin {
private:
	bool enabled;
public:
  HDMuninNodePlugin();
  virtual ~HDMuninNodePlugin();

  virtual const char *GetName() { return "hdd"; };
  virtual bool AutoConf() { return enabled; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
