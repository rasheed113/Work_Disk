#ifndef WORK_DISK_PROFILE_MODEL_H
#define WORK_DISK_PROFILE_MODEL_H

#include <string>

namespace work_disk::account {

class Profile {
public:
    Profile() = default;

    Profile(
        std::string accountId,
        std::string profileId,
        std::string displayName,
        std::string gender,
        std::string mobileContactNumber,
        std::string bio,
        std::string workBusinessDescription
    );

    const std::string& accountId() const;
    const std::string& profileId() const;
    const std::string& displayName() const;
    const std::string& gender() const;
    const std::string& mobileContactNumber() const;
    const std::string& bio() const;
    const std::string& workBusinessDescription() const;

    bool exists() const;

    void setDisplayName(std::string displayName);
    void setGender(std::string gender);
    void setMobileContactNumber(std::string mobileContactNumber);
    void setBio(std::string bio);
    void setWorkBusinessDescription(std::string workBusinessDescription);

private:
    std::string accountId_;
    std::string profileId_;
    std::string displayName_;
    std::string gender_;
    std::string mobileContactNumber_;
    std::string bio_;
    std::string workBusinessDescription_;
};

} // namespace work_disk::account

#endif
