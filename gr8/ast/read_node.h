// $Id: read_node.h,v 1.3 2018/04/13 01:51:48 ist424865 Exp $ -*- c++ -*-
#ifndef __GR8_READNODE_H__
#define __GR8_READNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // gr8

#endif
