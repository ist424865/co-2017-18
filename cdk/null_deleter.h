#ifndef __CDK13_NULL_DELETER_H__
#define __CDK13_NULL_DELETER_H__

namespace cdk {

  // this is a horrible way of not messing the memory up when getting a shared ptr to a
  // static object
  struct null_deleter {
    void operator()(void * const) {
    }
  };

} // cdk

#endif
