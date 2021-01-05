/*******************************************************************************
*    NEM Wallet
*    (c) 2017 Ledger
*    (c) 2020 FDS
*
*   Licensed under the Apache License, Version 2.0 (the "License");
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
#include "get_app_configuration.h"
#include <os.h>
#include "global.h"
/*
* LEDGER_MAJOR_VERSION, LEDGER_MINOR_VERSION, LEDGER_PATCH_VERSION define in Makefile
*/
void handle_app_configuration(volatile unsigned int *tx) {
    G_io_apdu_buffer[0] = N_nem_pstate.hashSigning;
    G_io_apdu_buffer[1] = LEDGER_MAJOR_VERSION;
    G_io_apdu_buffer[2] = LEDGER_MINOR_VERSION;
    G_io_apdu_buffer[3] = LEDGER_PATCH_VERSION;
    *tx = 4;
    THROW(0x9000);
}
