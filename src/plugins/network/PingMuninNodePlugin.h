#pragma once
#include "../../core/MuninNodePlugin.h"

#define PINGCOUNT 5
class PingMuninNodePlugin : public MuninNodePluginHelper {
private:
	unsigned long ipaddr;
    HANDLE hIcmpFile;
public:
  PingMuninNodePlugin(const std::string &hostName);
  virtual ~PingMuninNodePlugin();

  virtual bool AutoConf() { return hIcmpFile != INVALID_HANDLE_VALUE; };
  virtual int GetConfig(char *buffer, int len);
  virtual int GetValues(char *buffer, int len);
  virtual bool IsLoaded() { return true; };
};
