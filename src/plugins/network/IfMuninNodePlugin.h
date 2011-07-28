#pragma once
#include "../../core/MuninNodePlugin.h"

class IfMuninNodePlugin : public MuninNodePlugin
{
public:
  IfMuninNodePlugin();
  virtual ~IfMuninNodePlugin();

  virtual const char *GetName() { return "if"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
//private:
};
