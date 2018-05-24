#ifndef __GR8_SEMANTICS_FUNCTION_ENTER_H__
#define __GR8_SEMANTICS_FUNCTION_ENTER_H__

#include <iostream>
#include <cdk/ast/basic_node.h>
#include "targets/basic_ast_visitor.h"

namespace gr8 {

  //!
  //! Traverse function and count declared variables
  //!
  class function_enter: public basic_ast_visitor {
    int _counter;

  public:
    function_enter(std::shared_ptr<cdk::compiler> compiler) :
      basic_ast_visitor(compiler), _counter(0) {
    }

  public:
    ~function_enter() {
      os().flush();
    }

  public:
    int counter() {
      return _counter;
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };
  

} // gr8

#endif
