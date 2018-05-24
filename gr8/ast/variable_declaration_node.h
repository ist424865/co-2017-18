// Rui Ribeiro - 83562

#ifndef __GR8_DECLARATIONNODE_H__
#define __GR8_DECLARATIONNODE_H__

#include <cdk/ast/typed_node.h>
#include <string>

namespace gr8 {

    /**
     * Class for describing variable declaration nodes.
     */
    class variable_declaration_node: public cdk::typed_node {
    	// 0 - private, 1 - public, 2 - use
        int _reach;
        std::string *_identifier;
        cdk::expression_node *_initial;

    public:
        inline variable_declaration_node(int lineno, int reach, std::string *identifier, cdk::expression_node *initial) :
            cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _initial(initial) {
        }
        inline variable_declaration_node(int lineno, int reach, std::string *identifier) :
        	cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _initial(nullptr) {
        }

    public:
        int reach() {
            return _reach;
        }
        std::string *identifier() {
            return _identifier;
        }

        cdk::expression_node *initial() {
            return _initial;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_variable_declaration_node(this, level);
        }

    };

} // gr8

#endif
