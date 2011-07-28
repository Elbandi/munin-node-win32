#pragma once
#include "../../core/MuninNodePlugin.h"

class CpuMuninNodePlugin : public MuninNodePlugin {
public:
  CpuMuninNodePlugin();
  ~CpuMuninNodePlugin();

  virtual const char *GetName() { return "cpu"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
