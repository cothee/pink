#ifndef PINK_PB_CONN_H_
#define PINK_PB_CONN_H_

#include "status.h"
#include "csapp.h"
#include "pink_define.h"
#include "pink_util.h"
#include "pink_conn.h"
#include "xdebug.h"
#include <google/protobuf/message.h>
#include <map>

class PbConn: public PinkConn
{
public:
  PbConn(int fd);
  ~PbConn();
  /*
   * Set the fd to nonblock && set the flag_ the the fd flag
   */
  bool SetNonblock();
  void InitPara();

  ReadStatus GetRequest();
  WriteStatus SendReply();

  int flags() { 
    return flags_; 
  };

  virtual int DealMessage() = 0;


  /*
   * The Variable need by read the buf,
   * We allocate the memory when we start the server
   */
  int header_len_;
  char* rbuf_;
  int32_t cur_pos_;
  int32_t rbuf_len_;

  ConnStatus connStatus_;

  google::protobuf::Message *res_;

  char* wbuf_;
  int32_t wbuf_len_;
  int32_t wbuf_pos_;

private:

  int flags_;

  Status BuildObuf();
};

#endif
