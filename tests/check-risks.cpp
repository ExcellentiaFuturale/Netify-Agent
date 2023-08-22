// Netify Agent Test Suite
// Copyright (C) 2022 eGloo Incorporated
// <http://www.egloo.ca>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "nd-ndpi.hpp"
#include "nd-risks.hpp"

int main(int argc, char *argv[]) {
  int rc = 0;

  cout << "Testing Netify Agent Risks..." << endl;

  ndpi_global_init();

  cout << endl
       << "nDPI risks count: " << NDPI_MAX_RISK << endl;
  cout << "Netify Agent risks count: " << ND_RISK_MAX
       << endl
       << endl;

  for (uint16_t id = 0; id < NDPI_MAX_RISK; id++) {
    auto it = nd_ndpi_risks.find(id);
    if (it != nd_ndpi_risks.end()) continue;

    ndpi_risk_enum rid = (ndpi_risk_enum)id;

    ndpi_risk_info const *const risk_info =
        ndpi_risk2severity(rid);
    if (risk_info == NULL) {
      rc = 1;
      cout << "ID# " << id
           << " (ndpi_risk2severity: UNKNOWN/ERROR)"
           << endl;
      continue;
    }

    rc = 1;
    cout << "ID# " << id << " ("
         << ndpi_risk2str(risk_info->risk) << ")" << endl;
  }

  if (rc != 0) cout << endl;
  cout << "Test result: " << ((rc == 0) ? "PASS" : "FAIL")
       << endl
       << endl;

  return rc;
}
