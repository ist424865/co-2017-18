#ifndef __CDK13_AST_IDENTIFIER_H__
#define __CDK13_AST_IDENTIFIER_H__

#include <cdk/ast/lvalue_node.h>
#include <string>

namespace cdk {

  /**
   * Class for describing syntactic tree leaves for holding identifiers.
   */
  class identifier_node: public lvalue_node {
    std::string _name;

  public:
    identifier_node(int lineno, const char *s) :
        lvalue_node(lineno), _name(s) {
    }
    identifier_node(int lineno, const std::string &s) :
        lvalue_node(lineno), _name(s) {
    }
    identifier_node(int lineno, const std::string *s) :
        lvalue_node(lineno), _name(*s) {
    }

  public:
    const std::string &name() const {
      return _name;
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_identifier_node(this, level);
    }

  };

} // cdk

#endif
