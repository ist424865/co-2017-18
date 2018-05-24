#ifndef __CDK13_AST_TYPEDNODE_H__
#define __CDK13_AST_TYPEDNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/basic_type.h>

namespace cdk {

  /**
   * Typed nodes store a type description.
   */
  class typed_node: public basic_node {
  protected:
    // This must be a pointer, so that we can anchor a dynamic
    // object and be able to change/delete it afterwards.
    basic_type *_type;

  public:
    /**
     * Simple constructor.
     *
     * @param lineno the source code line number corresponding to
     * the node
     */
    typed_node(int lineno) :
        basic_node(lineno), _type(nullptr) {
    }

    basic_type *type() {
      return _type;
    }
    void type(basic_type *type) {
      _type = type;
    }

  };

} // cdk

#endif
