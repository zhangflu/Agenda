#ifndef PATH_HPP
#define PATH_HPP

class Path {
 public:
  /**
   * user.csv path
   */
  static const char *userPath;
  static const char *s_userPath;
  /**
   * meeting.csv path
   */
  static const char *meetingPath;
  static const char *s_meetingPath;
};

const char *Path::meetingPath = "tmeetings.csv";
const char *Path::userPath = "tusers.csv";
const char *Path::s_meetingPath = "meetings.csv";
const char *Path::s_userPath = "users.csv";

#endif
