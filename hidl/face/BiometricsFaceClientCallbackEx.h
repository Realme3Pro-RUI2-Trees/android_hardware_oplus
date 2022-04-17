/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vendor/oplus/hardware/biometrics/face/1.0/IBiometricsFaceClientCallbackEx.h>

namespace android {
namespace hardware {
namespace biometrics {
namespace face {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::hardware::Return;
using ::vendor::oplus::hardware::biometrics::face::V1_0::IBiometricsFaceClientCallbackEx;

class BiometricsFaceClientCallbackEx : public IBiometricsFaceClientCallbackEx {
public:
    Return<void> onFaceCmd(int32_t cmdId, const hidl_vec<uint32_t>& result, uint32_t resultLen) override;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace face
}  // namespace biometrics
}  // namespace hardware
}  // namespace android
