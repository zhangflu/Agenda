#ifndef PATH_HPP
#define PATH_HPP

class Path {
 public:
  /**
   * user.csv path
   */
  static char *enc_userPath;
  static char *dec_userPath;
  /**
   * meeting.csv path
   */
  static char *enc_meetingPath;
  static char *dec_meetingPath;
};

char *Path::enc_meetingPath = "meetings.csv";
char *Path::enc_userPath = "users.csv";
char *Path::dec_meetingPath = "t_meetings.csv";
char *Path::dec_userPath = "t_users.csv";

#endif
