// Rui Ribeiro - 83562

#ifndef __GR8_POSTNODE_H__
#define __GR8_POSTNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

    /**
     * Class for describing post nodes.
     */
    class post_node: public cdk::basic_node {
    	cdk::expression_node *_argument;

    public:
        inline post_node(int lineno, cdk::expression_node *argument) :
        	basic_node(lineno), _argument(argument) {
        }

    public:
        cdk::expression_node *argument() {
        	return _argument;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_post_node(this, level);
        }

    };

} // gr8

#endif
