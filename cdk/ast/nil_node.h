#ifndef __CDK13_AST_NIL_H__
#define __CDK13_AST_NIL_H__

#include <cdk/ast/basic_node.h>

namespace cdk {

  /**
   * Class for describing empty nodes (leaves).
   * The only data recorded by this type of node is the node's
   * attribute (i.e., the mnemonic) and the source code line
   * number.
   */
  class nil_node: public basic_node {
  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */
    nil_node(int lineno) :
        basic_node(lineno) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_nil_node(this, level);
    }

  };

} // cdk

#endif
