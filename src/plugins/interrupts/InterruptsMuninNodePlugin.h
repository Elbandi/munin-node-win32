#pragma once
#include "../../core/MuninNodePlugin.h"

class InterruptsMuninNodePlugin : public MuninNodePlugin {
public:
  InterruptsMuninNodePlugin();
  ~InterruptsMuninNodePlugin();

  virtual const char *GetName() { return "interrupts"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
