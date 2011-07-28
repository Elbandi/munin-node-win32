#pragma once
#include "../../core/MuninNodePlugin.h"

class IoBytesMuninNodePlugin : public MuninNodePlugin {
public:
  IoBytesMuninNodePlugin();
  ~IoBytesMuninNodePlugin();

  virtual const char *GetName() { return "iobytes"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
