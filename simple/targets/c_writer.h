#ifndef __SIMPLE_SEMANTICS_C_WRITER_H__
#define __SIMPLE_SEMANTICS_C_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace simple {

  /**
   * Traverse the syntax tree and generate the corresponding C code.
   */
  class c_writer: public basic_ast_visitor {
    cdk::symbol_table<simple::symbol> &_symtab;

  public:
    c_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<simple::symbol> &symtab) :
        basic_ast_visitor(compiler), _symtab(symtab) {
    }

  public:
    ~c_writer() {
      os().flush();
    }

  protected:
    void processUnaryExpression(cdk::unary_expression_node * const node, int lvl, const char *tag);
    void do_binary_expression_node(cdk::binary_expression_node * const node, int lvl, const char *op);

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // simple

#endif
