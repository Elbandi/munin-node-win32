#pragma once
#include "../../core/MuninNodePlugin.h"

typedef ULONGLONG (WINAPI *PROCTICKCOUNT)(VOID);

class UptimeMuninNodePlugin : public MuninNodePlugin
{
public:
  UptimeMuninNodePlugin();
  ~UptimeMuninNodePlugin();

  virtual const char *GetName() { return "uptime"; };
  virtual bool AutoConf() { return TRUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
private:
  PROCTICKCOUNT GetTickCount64;
};
