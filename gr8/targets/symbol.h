#ifndef __GR8_SEMANTICS_SYMBOL_H__
#define __GR8_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>
#include <vector>

namespace gr8 {

  class symbol {
    basic_type *_type;
    std::string _name;
    
    // 0 - declared, 1 - defined
    int _functionStage = 0;
    int _offset = 0;

    // function argument types
    typedef unsigned long int btype;
    typedef std::vector<btype> stypes;
    stypes sequence_type;

  public:

    symbol(basic_type *type, const std::string &name) :
        _type(type), _name(name) {
    }

    virtual ~symbol() {
      delete _type;
    }

    basic_type *type() const {
      return _type;
    }
    const std::string &name() const {
      return _name;
    }
    int &stage() {
      return _functionStage;
    }
    stypes &types() {
      return sequence_type;
    }
    int &offset() {
      return _offset;
    }
  };

} // gr8

#endif
