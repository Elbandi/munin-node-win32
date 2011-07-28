#pragma once
#include "../../core/MuninNodePlugin.h"

class SwapMuninNodePlugin : public MuninNodePlugin {
public:
  SwapMuninNodePlugin();
  ~SwapMuninNodePlugin();

  virtual const char *GetName() { return "swap"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
