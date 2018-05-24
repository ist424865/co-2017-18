#ifndef __CDK13_AST_DOUBLE_H__
#define __CDK13_AST_DOUBLE_H__

#include <cdk/ast/literal_node.h>

namespace cdk {

  /**
   * Class for describing syntactic tree leaves for holding double
   * precision values.
   */
  class double_node: public virtual literal_node<double> {
  public:
    double_node(int lineno, double d) :
        literal_node<double>(lineno, d) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_double_node(this, level);
    }

  };

} // cdk

#endif
