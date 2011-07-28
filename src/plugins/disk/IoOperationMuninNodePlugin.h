#pragma once
#include "../../core/MuninNodePlugin.h"

class IoOperationMuninNodePlugin : public MuninNodePlugin {
public:
  IoOperationMuninNodePlugin();
  ~IoOperationMuninNodePlugin();

  virtual const char *GetName() { return "iooperation"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
