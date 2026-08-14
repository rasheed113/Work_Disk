#include "profile_model.h"

#include <utility>

namespace work_disk::account {

Profile::Profile(
    std::string accountId,
    std::string profileId,
    std::string displayName,
    std::string gender,
    std::string mobileContactNumber,
    std::string bio,
    std::string workBusinessDescription
)
    : accountId_(std::move(accountId)),
      profileId_(std::move(profileId)),
      displayName_(std::move(displayName)),
      gender_(std::move(gender)),
      mobileContactNumber_(std::move(mobileContactNumber)),
      bio_(std::move(bio)),
      workBusinessDescription_(std::move(workBusinessDescription)) {}

const std::string& Profile::accountId() const {
    return accountId_;
}

const std::string& Profile::profileId() const {
    return profileId_;
}

const std::string& Profile::displayName() const {
    return displayName_;
}

const std::string& Profile::gender() const {
    return gender_;
}

const std::string& Profile::mobileContactNumber() const {
    return mobileContactNumber_;
}

const std::string& Profile::bio() const {
    return bio_;
}

const std::string& Profile::workBusinessDescription() const {
    return workBusinessDescription_;
}

bool Profile::exists() const {
    return !profileId_.empty();
}

void Profile::setDisplayName(std::string displayName) {
    displayName_ = std::move(displayName);
}

void Profile::setGender(std::string gender) {
    gender_ = std::move(gender);
}

void Profile::setMobileContactNumber(std::string mobileContactNumber) {
    mobileContactNumber_ = std::move(mobileContactNumber);
}

void Profile::setBio(std::string bio) {
    bio_ = std::move(bio);
}

void Profile::setWorkBusinessDescription(
    std::string workBusinessDescription
) {
    workBusinessDescription_ = std::move(workBusinessDescription);
}

} // namespace work_disk::account
