# WORK_DISK ROADMAP

Last Updated: 20 July 2026

--------------------------------------------------
PROJECT STATUS
--------------------------------------------------

[✓] Project Name Selected
[✓] Brand Name Selected
[✓] Architecture Discussion Completed
[✓] File Structure Discussion Completed
[✓] Dashboard Planning Completed

--------------------------------------------------
BRAND
--------------------------------------------------

Project Name:
Work_Disk

ID Format:

RWD-A7X92KQ1
RWD-B4M81ZT6
RWD-P9R52LF8

Decision:
Random unique IDs.

--------------------------------------------------
PROJECT RULES
--------------------------------------------------

[✓] One Feature = One Folder

[✓] One Logic = One File

[✓] No Giant Files

[✓] No final/new/latest filenames

[✓] Backup Before Major Changes

[✓] Update Roadmap After Every Feature

[✓] Prefer Small Files

[✓] UI and Database Separate

[✓] Split Early, Not Late

--------------------------------------------------
PROJECT STRUCTURE
--------------------------------------------------

Work_Disk/

├── work_disk_docs/
├── work_disk_web/
└── work_disk_app/

--------------------------------------------------
DOCUMENTATION FILES
--------------------------------------------------

work_disk_docs/

PROJECT_RULES.md
ROADMAP.md
DISCUSSION_LOG.md
FEATURE_REQUESTS.md
CHANGELOG.md

--------------------------------------------------
WEB PLATFORM
--------------------------------------------------

Status: Planned

Features:

[ ] Login
[ ] Register
[ ] Dashboard
[ ] Profile
[ ] Work Entry
[ ] History
[ ] Finance
[ ] Diary
[ ] Settings
[ ] Download App
[ ] Cloud Sync
[ ] Password Recovery

--------------------------------------------------
APP PLATFORM
--------------------------------------------------

Status: Planned

Features:

[ ] Offline Mode
[ ] Local Database
[ ] Dashboard
[ ] Profile
[ ] Work Entry
[ ] History
[ ] Finance
[ ] Diary
[ ] Settings
[ ] Sync With Web

--------------------------------------------------
DASHBOARD FINAL PLAN
--------------------------------------------------

[✓] Cover Photo

[✓] Profile Photo

[✓] Name

[✓] Unique ID

[✓] Small Smart Clock

[✓] Day and Date

[✓] Gaming Style UI

[✓] Premium Fonts

[✓] Lemon Green Glow Clock

[✓] Marquee / Smart News Bar

Quick Actions:

[ ] New Entry
[ ] Diary
[ ] Finance
[ ] Settings

Cards:

[ ] Today
[ ] Week
[ ] Month
[ ] Grand Total

Card Behaviour:

Today Card
→ Today History

Week Card
→ Weekly History

Month Card
→ Monthly History

Grand Total Card
→ Full History

--------------------------------------------------
PROFILE SYSTEM
--------------------------------------------------

Required:

[ ] Full Name
[ ] Email
[ ] Mobile Number
[ ] Password

Optional:

[ ] Profile Photo
[ ] Cover Photo
[ ] Company Name
[ ] Gender
[ ] Home Address
[ ] Bio

--------------------------------------------------
WORK ENTRY SYSTEM
--------------------------------------------------

Work Type:

[ ] Machine
[ ] Press
[ ] Packing
[ ] Other

Machine Types:

[ ] Singer
[ ] Overlock
[ ] Flatlock
[ ] Other

Rate Types:

[ ] Per Piece
[ ] Per Dozen
[ ] Per 100 Pieces
[ ] Other

Smart Logic:

Per Piece
→ Enter Pieces

Per Dozen
→ Enter Dozens

Per 100
→ Enter Pieces

Auto Amount Calculation

--------------------------------------------------
DIARY SYSTEM
--------------------------------------------------

[✓] Diary Button Replaces History Button

Features:

[ ] Notes

[ ] Events

[ ] Reminders

[ ] Poetry

[ ] Personal Notes

[ ] Goals

[ ] Custom Categories

Save Options:

[ ] Save

[ ] Save as Reminder

--------------------------------------------------
FINANCE
--------------------------------------------------

[ ] Salary Tracking

[ ] Balance Tracking

[ ] Income Summary

[ ] Expense Tracking

--------------------------------------------------
DATABASE
--------------------------------------------------

Users

Entries

Finance

Diary

Settings

--------------------------------------------------
AUTHENTICATION
--------------------------------------------------

V1:

[ ] Email Login

[ ] Mobile Login

[ ] ID Login

[ ] Forget Password

Future:

[ ] Google Login

[ ] Facebook Login

[ ] X Login

--------------------------------------------------
FUTURE FEATURES
--------------------------------------------------

[ ] Notifications

[ ] Cloud Backup

[ ] Data Export

[ ] Admin Panel

[ ] Voice Notes

[ ] Web Sync

--------------------------------------------------
IMPORTANT LESSON FROM APK DIARY
--------------------------------------------------

Never Put Everything In One File.

Feature
→ Folder

Logic
→ File

Easy Maintenance
→ Easy Future

---

# Day 11 Milestone Completed

Foundation phase completed:

- Product vision established
- Project constitution established
- Engineering standards defined
- Database architecture principles documented
- Documentation structure finalized
- Backup and archive organization improved

Next phase:

Implementation will continue according to approved foundation documents.
## Day 12 — DatabaseManager Engineering

**Status:** ✅ Completed

### Objectives Completed

* DatabaseManager architecture enhanced.
* Connection status management implemented.
* SQL utility methods added.
* Transaction support implemented.
* Error handling improved.
* Successful compilation completed.
* Successful runtime verification completed.
* Stable backup created.

### Outcome

The DatabaseManager now provides a reliable and centralized database foundation for all service classes and future business logic.

## Day 13 — Service Layer Engineering

**Status:** ✅ Completed

### Objectives Completed

* Service Layer audit completed.
* UserService verified.
* SettingsService verified.
* FinanceService verified.
* DiaryService verified.
* DeviceService verified.
* WorkEntryService implemented.
* `main.cpp` updated to use Service Layer for WorkEntry operations.
* Project compiled successfully.
* Runtime verification completed.

### Outcome

The project now has a consistent architecture in which the application communicates with the database through service classes. The Service Layer foundation is complete and ready for future business logic, validation, reporting, and UI integration.

## Day 14 — Service Layer Validation & Testing

**Status:** ✅ Completed

### Objectives Completed

* Service Layer runtime validation completed.
* UserService CRUD flow verified.
* WorkEntryService CRUD flow verified.
* Test runner improved for repeatable execution.
* Dynamic user ID handling implemented.
* Hard-coded validation IDs removed.
* Compilation successful.
* Runtime verification successful.

### Outcome

The backend foundation is now more stable with reliable repeatable testing. Service architecture is verified and ready for future business logic development.


## Day 15 – Completed

### Milestone
Database Architecture Planning

### Completed
- Reviewed the existing DatabaseManager implementation.
- Identified maintainability improvements.
- Designed the long-term modular database architecture.
- Defined an implementation strategy that preserves the existing public API.
- Prepared the project for the Database Architecture Refinement phase.

### Next Milestone (Day 16)
- Create the new database module structure.
- Begin incremental refactoring.
- Maintain backward compatibility.
- Compile and validate after each major step.
- Update documentation and create a new backup.


## Day 15 – Completed

### Milestone
Database Architecture Planning

### Completed
- Reviewed the existing DatabaseManager implementation.
- Identified maintainability improvements.
- Designed the long-term modular database architecture.
- Defined an implementation strategy that preserves the existing public API.
- Prepared the project for the Database Architecture Refinement phase.

### Next Milestone (Day 16)
- Create the new database module structure.
- Begin incremental refactoring.
- Maintain backward compatibility.
- Compile and validate after each major step.
- Update documentation and create a new backup.
