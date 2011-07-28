#pragma once
#include "../../core/MuninNodePlugin.h"

class DiskMuninNodePlugin : public MuninNodePlugin {
  WCHAR drives[32][4];
  bool enabled;
public:
  DiskMuninNodePlugin();
  virtual ~DiskMuninNodePlugin();

  virtual const char *GetName() { return "df"; };
  virtual bool AutoConf() { return enabled; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
  virtual bool IsThreadSafe() { return true; };
};
