// Rui Ribeiro - 83562

#ifndef __GR8_ADDRESSOFNODE_H__
#define __GR8_ADDRESSOFNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace gr8 {

    /**
     * Class for describing address_of nodes.
     */
    class address_of_node: public cdk::expression_node {
    	cdk::lvalue_node *_argument;

    public:
        inline address_of_node(int lineno, cdk::lvalue_node *argument) :
			cdk::expression_node(lineno), _argument(argument) {
        }

    public:
        cdk::lvalue_node *argument() {
        	return _argument;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_address_of_node(this, level);
        }

    };

} // gr8

#endif
