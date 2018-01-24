/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

#include "init_msm8974.h"

using android::base::GetProperty;
using android::init::property_set;

void set_rild_libpath(char const *variant)
{
    std::string libpath("/system/vendor/lib/libsec-ril.");
    libpath += variant;
    libpath += ".so";

    property_override("rild.libpath", libpath.c_str());
}

void cdma_properties(char const *operator_alpha,
        char const *operator_numeric,
        char const *default_network,
        char const *rild_lib_variant)
{
    /* Dynamic CDMA Properties */
    property_set("ro.cdma.home.operator.alpha", operator_alpha);
    property_set("ro.cdma.home.operator.numeric", operator_numeric);
    property_set("ro.telephony.default_network", default_network);
    set_rild_libpath(rild_lib_variant);

    /* Static CDMA Properties */
    property_set("ril.subscription.types", "NV,RUIM");
    property_set("ro.telephony.default_cdma_sub", "0");
    property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_properties(char const *rild_lib_variant)
{
    set_rild_libpath(rild_lib_variant);

    property_set("ro.telephony.default_network", "9");
    property_set("telephony.lteOnGsmDevice", "1");
}

void init_target_properties()
{
    std::string platform = GetProperty("ro.board.platform", "");
    if (platform != ANDROID_TARGET)
        return;

    std::string bootloader = GetProperty("ro.bootloader", "");

    if (bootloader.find("G900AZ") == 0) {
        /* hlteaio - Cricket MVNO */
        property_override("ro.build.fingerprint", "samsung/hltetu/hlteaio:5.0/LRX21T/G900AZTUS3BQD1:user/release-keys");
        property_override("ro.build.description", "hltetu-user 5.0 LRX21T G900AZTUS3BQD1 release-keys");
        property_override("ro.product.model", "SM-G900AZ");
        property_override("ro.product.device", "hlteaio");
        gsm_properties("gsm");
    } else if (bootloader.find("G900F") == 0) {
        /* hltexx */
        property_override("ro.build.fingerprint", "samsung/hltexx/hlte:6.0.1/MMB29M/G900FXXS1CQI4:user/release-keys");
        property_override("ro.build.description", "hltexx-user 6.0.1 MMB29M G900FXXS1CQI4 release-keys");
        property_override("ro.product.model", "SM-G900F");
        property_override("ro.product.device", "hlte");
        gsm_properties("gsm");
    } else if (bootloader.find("G900M") == 0) {
        /* hlteub */
        property_override("ro.build.fingerprint", "samsung/hlteub/hlte:6.0.1/MMB29M/G900MUBS1CQD1:user/release-keys");
        property_override("ro.build.description", "hlteub-user 6.0.1 MMB29M G900MUBS1CQD1 release-keys");
        property_override("ro.product.model", "SM-G900M");
        property_override("ro.product.device", "hlte");
        gsm_properties("gsm");
    } else if (bootloader.find("G900R4") == 0) {
        /* hlteusc */
        property_override("ro.build.fingerprint", "samsung/hlteusc/hlteusc:6.0.1/MMB29M/G900R4VXS2CQC2:user/release-keys");
        property_override("ro.build.description", "hlteusc-user 6.0.1 MMB29M G900R4VXS2CQC2 release-keys");
        property_override("ro.product.model", "SM-G900R4");
        property_override("ro.product.device", "hlteusc");
        cdma_properties("U.S. Cellular", "311220", "10", "usc");
    } else if (bootloader.find("G900R7") == 0) {
        /* hlteacg - CSpire variant */
        property_override("ro.build.fingerprint", "samsung/hlteacg/hlteacg:6.0.1/MMB29M/G900R7WWU3CPL1:user/release-keys");
        property_override("ro.build.description", "hlteacg-user 6.0.1 MMB29M G900R7WWU3CPL1 release-keys");
        property_override("ro.product.model", "SM-G900R7");
        property_override("ro.product.device", "hlteacg");
        cdma_properties("Default", "310000", "10", "usc");
    } else if (bootloader.find("G900T") == 0) {
        /* hltetmo */
        property_override("ro.build.fingerprint", "samsung/hltetmo/hltetmo:6.0.1/MMB29M/G900TUVU1GQC2:user/release-keys");
        property_override("ro.build.description", "hltetmo-user 6.0.1 MMB29M G900TUVU1GQC2 release-keys");
        property_override("ro.product.model", "SM-G900T");
        property_override("ro.product.device", "hltetmo");
        gsm_properties("gsm");
    } else if (bootloader.find("G900V") == 0) {
        /* hltevzw - SM-G900V - Verizon */
        property_override("ro.build.fingerprint", "Verizon/hltevzw/hltevzw:6.0.1/MMB29M/G900VVRU2DQH2:user/release-keys");
        property_override("ro.build.description", "hltevzw-user 6.0.1 MMB29M G900VVRU2DQH2 release-keys");
        property_override("ro.product.model", "SM-G900V");
        property_override("ro.product.device", "hltevzw");
        property_set("ro.telephony.get_imsi_from_sim", "true");
        cdma_properties("Verizon", "311480", "10", "vzw");
    } else if (bootloader.find("G900W8") == 0) {
        /* hltecan */
        property_override("ro.build.fingerprint", "samsung/hltevl/hltecan:6.0.1/MMB29M/G900W8VLU1DQB2:user/release-keys");
        property_override("ro.build.description", "hltevl-user 6.0.1 MMB29M G900W8VLU1DQB2 release-keys");
        property_override("ro.product.model", "SM-G900W8");
        property_override("ro.product.device", "hltecan");
        gsm_properties("gsm");
    } else if (bootloader.find("S902L") == 0) {
        /* hltetfnvzw - SM-S902L - TracFone Verizon MVNO */
        property_override("ro.build.fingerprint", "samsung/hltetfnvzw/hltetfnvzw:4.4.2/KOT49H/S902LUDUAOD3:user/release-keys");
        property_override("ro.build.description", "hltetfnvzw-user 4.4.2 KOT49H S902LUDUAOD3 release-keys");
        property_override("ro.product.model", "SM-S902L");
        property_override("ro.product.device", "hltetfnvzw");
        property_set("ro.telephony.get_imsi_from_sim", "true");
        cdma_properties("TracFone", "310000", "10", "vzw");
    } else {
        gsm_properties("gsm");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
        << device <<  " device" << std::endl;
}