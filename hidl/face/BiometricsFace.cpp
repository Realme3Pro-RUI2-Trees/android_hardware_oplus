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

#define LOG_TAG "android.hardware.biometrics.face@1.0-service.oplus"

#include "BiometricsFace.h"
#include "BiometricsFaceClientCallbackEx.h"

namespace android::hardware::biometrics::face::implementation {
using android::hardware::biometrics::face::V1_0::FaceError;
using android::hardware::biometrics::face::V1_0::OptionalUint64;

// Arbitrary value.
constexpr uint64_t kDeviceId = 123;
// Arbitrary value.
constexpr uint64_t kAuthenticatorId = 987;
// Not locked out.
constexpr uint64_t kLockoutDuration = 0;

BiometricsFace::BiometricsFace() /*: mRandom(std::mt19937::default_seed)*/ {
    mOplusBiometricsFace = IOplusBiometricsFace::getService();
    mOplusBiometricsFaceCallback = new BiometricsFaceClientCallbackEx();

    mOplusBiometricsFace->setHalCallback(mOplusBiometricsFaceCallback);
}

// Methods from IBiometricsFace follow.
Return<void> BiometricsFace::setCallback(const sp<IBiometricsFaceClientCallback>& clientCallback,
                                         setCallback_cb _hidl_cb) {
    mClientCallback = clientCallback;
    _hidl_cb({Status::OK, kDeviceId});
    return Void();
}

Return<Status> BiometricsFace::setActiveUser(int32_t userId, const hidl_string& storePath) {
    if (userId < 0 || storePath.empty() || std::string(storePath).find("/data") != 0) {
        return Status::ILLEGAL_ARGUMENT;
    }
    mUserId = userId;
    mClientCallback->onLockoutChanged(kLockoutDuration);
     return mOplusBiometricsFace->setActiveUser(userId, storePath);
}

Return<void> BiometricsFace::generateChallenge(uint32_t challengeTimeoutSec,
                                               generateChallenge_cb _hidl_cb) {
     return mOplusBiometricsFace->generateChallenge(challengeTimeoutSec, _hidl_cb);
}

Return<Status> BiometricsFace::enroll(const hidl_vec<uint8_t>& hat, uint32_t timeoutSec,
                                      const hidl_vec<Feature>& disabledFeatures) {
    // hat can never be valid in this implementation.
     return mOplusBiometricsFace->enroll(hat, timeoutSec, disabledFeatures);
}

Return<Status> BiometricsFace::revokeChallenge() {
    return mOplusBiometricsFace->revokeChallenge();
}

Return<Status> BiometricsFace::setFeature(Feature feature, bool enabled,
                                          const hidl_vec<uint8_t>& hat,
                                          uint32_t faceId) {
     return mOplusBiometricsFace->setFeature(feature, enabled, hat, faceId);
}

Return<void> BiometricsFace::getFeature(Feature feature, uint32_t faceId,
                                        getFeature_cb _hidl_cb) {
    // hat can never be valid in this implementation.
    _hidl_cb({Status::ILLEGAL_ARGUMENT, false});                                        
     return mOplusBiometricsFace->getFeature(feature, faceId, _hidl_cb);
}

Return<void> BiometricsFace::getAuthenticatorId(getAuthenticatorId_cb _hidl_cb) {
     _hidl_cb({Status::OK, kAuthenticatorId});
     return mOplusBiometricsFace->getAuthenticatorId(_hidl_cb);
}

Return<Status> BiometricsFace::cancel() {
     return mOplusBiometricsFace->cancel();
}

Return<Status> BiometricsFace::enumerate() {
     return mOplusBiometricsFace->enumerate();
}

Return<Status> BiometricsFace::remove(uint32_t faceId) {
     return mOplusBiometricsFace->remove(faceId);
}

Return<Status> BiometricsFace::authenticate(uint64_t operationId) {
     return mOplusBiometricsFace->authenticate(operationId);
}

Return<Status> BiometricsFace::userActivity() {
    return mOplusBiometricsFace->userActivity();
}

Return<Status> BiometricsFace::resetLockout(const hidl_vec<uint8_t>& hat) {
    return mOplusBiometricsFace->resetLockout(hat);
}

}  // namespace android::hardware::biometrics::face::implementation
