// Rui Ribeiro - 83562

#ifndef __GR8_SWEEPINGNODE_H__
#define __GR8_SWEEPINGNODE_H__

#include <cdk/ast/basic_node.h>

namespace gr8 {

    /**
     * Class for describing sweeping-from-to-by-do nodes.
     */
    class sweeping_node: public cdk::basic_node {
        cdk::lvalue_node *_iterator;
    	cdk::expression_node *_from;
    	cdk::expression_node *_to;
    	cdk::expression_node *_by;
    	block_node *_block;

    public:
        inline sweeping_node(int lineno, cdk::lvalue_node *iterator, cdk::expression_node *from, cdk::expression_node *to, cdk::expression_node *by, block_node *block) :
                basic_node(lineno), _iterator(iterator), _from(from), _to(to), _by(by), _block(block) {
        }
        inline sweeping_node(int lineno, cdk::lvalue_node *iterator, cdk::expression_node *from, cdk::expression_node *to, block_node *block) :
                basic_node(lineno), _iterator(iterator), _from(from), _to(to), _by(new cdk::integer_node(lineno, 1)), _block(block) {
        }

    public:
        cdk::lvalue_node *iterator() {
            return _iterator;
        }
        cdk::expression_node *from() {
            return _from;
        }
        cdk::expression_node *to() {
            return _to;
        }
        cdk::expression_node *by() {
            return _by;
        }
        block_node *block() {
            return _block;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_sweeping_node(this, level);
        }

    };

} // gr8

#endif
