#ifndef __CDK13_AST_UNARYEXPRESSION_H__
#define __CDK13_AST_UNARYEXPRESSION_H__

#include <cdk/ast/expression_node.h>

namespace cdk {

  /** Class for describing unary operators. */
  class unary_expression_node: public expression_node {
    expression_node *_argument;

  public:
    unary_expression_node(int lineno, expression_node *arg) :
        expression_node(lineno), _argument(arg) {
    }

    expression_node *argument() {
      return _argument;
    }

  };

} // cdk

#endif
