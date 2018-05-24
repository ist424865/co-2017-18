// $Id: evaluation_node.h,v 1.1 2014/05/02 22:33:16 david Exp $
#ifndef __SIMPLE_EVALUATIONNODE_H__
#define __SIMPLE_EVALUATIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace simple {

  /**
   * Class for describing evaluation nodes.
   */
  class evaluation_node: public cdk::basic_node {
    cdk::expression_node *_argument;

  public:
    inline evaluation_node(int lineno, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_evaluation_node(this, level);
    }

  };

} // simple

#endif
