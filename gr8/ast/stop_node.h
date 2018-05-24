// Rui Ribeiro - 83562

#ifndef __GR8_STOPNODE_H__
#define __GR8_STOPNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

    /**
     * Class for describing stop nodes.
     */
    class stop_node: public cdk::basic_node {
    	int _cycle;

    public:
    	inline stop_node(int lineno) :
			basic_node(lineno), _cycle(1) {
    	}
        inline stop_node(int lineno, int cycle) :
        	basic_node(lineno), _cycle(cycle) {
        }

    public:
        int cycle() {
        	return _cycle;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_stop_node(this, level);
        }

    };

} // gr8

#endif
