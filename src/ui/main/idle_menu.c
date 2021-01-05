/*******************************************************************************
*    NEM Wallet
*    (c) 2020 Ledger
*    (c) 2020 FDS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/
#include "idle_menu.h"
#include <os_io_seproxyhal.h>
#include <ux.h>
#include "glyphs.h"
#include "global.h"

void settings_hash_signing_change(unsigned int enabled);
const char* settings_submenu_getter(unsigned int idx);
void settings_submenu_selector(unsigned int idx);

// ------------------------------------------------------------------------- //
//                                  MENUS                                    //
// ------------------------------------------------------------------------- //

//////////////////////////////////////////////////////////////////////////////////////
UX_FLOW_DEF_VALID(
  settings_hash_signing_enable_step,
  pbb,
  settings_hash_signing_change(1),
  {
    &C_icon_validate_14,
    "Enable hash",
    "signing?",
  });

UX_FLOW_DEF_VALID(
  settings_hash_signing_disable_step,
  pb,
  settings_hash_signing_change(0),
  {
    &C_icon_crossmark,
    "Disable",
  });

UX_FLOW_DEF_VALID(
  settings_hash_signing_go_back_step,
  pb,
  ux_menulist_init(0, settings_submenu_getter, settings_submenu_selector),
  {
    &C_icon_back_x,
    "Back",
  });

UX_DEF(settings_hash_signing_flow,
  &settings_hash_signing_enable_step,
  &settings_hash_signing_disable_step,
  &settings_hash_signing_go_back_step
);

void settings_hash_signing(void) {
     ux_flow_init(0, settings_hash_signing_flow, NULL);
}

void settings_hash_signing_change(unsigned int enabled) {
    nvm_write((void*)&N_nem_pstate.hashSigning, &enabled, 1);
    display_idle_menu();
}

//////////////////////////////////////////////////////////////////////////////////////
// Settings menu:

const char* const settings_submenu_getter_values[] = {
  "Hash signing",
  "Back",
};

const char* settings_submenu_getter(unsigned int idx) {
  if (idx < ARRAYLEN(settings_submenu_getter_values)) {
    return settings_submenu_getter_values[idx];
  }
  return NULL;
}

void settings_submenu_selector(unsigned int idx) {
  switch(idx) {
    case 0:
      settings_hash_signing();
      break;
    default:
      display_idle_menu();
  }
}

//////////////////////////////////////////////////////////////////////////////////////
UX_STEP_NOCB(
        ux_idle_flow_1_step,
        pnn,
        {
            &C_icon_NEM,
            "Welcome to",
            "NEM Wallet",
        });

UX_FLOW_DEF_VALID(
        ux_idle_flow_2_step,
        pb,
        ux_menulist_init(0, settings_submenu_getter, settings_submenu_selector),
        {
             &C_icon_coggle,
            "Settings",
        });

UX_STEP_NOCB(
        ux_idle_flow_3_step,
        bn,
        {
            "Version",
            APPVERSION,
        });

UX_STEP_VALID(
        ux_idle_flow_4_step,
        pb,
        os_sched_exit(-1),
        {
            &C_icon_dashboard_x,
            "Quit",
        });

const ux_flow_step_t * const ux_idle_flow [] = {
        &ux_idle_flow_1_step,
        &ux_idle_flow_2_step,
        &ux_idle_flow_3_step,
        &ux_idle_flow_4_step,
        FLOW_END_STEP,
};

void display_idle_menu() {
    if(G_ux.stack_count == 0) {
        ux_stack_push();
    }
    ux_flow_init(0, ux_idle_flow, NULL);
}
