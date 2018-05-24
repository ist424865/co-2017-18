// Rui Ribeiro - 83562

#ifndef __GR8_PROJECTFUNCTIONDECLARATIONNODE_H__
#define __GR8_PROJECTFUNCTIONDECLARATIONNODE_H__

#include <cdk/ast/typed_node.h>
#include <string>

namespace gr8 {

    /**
     * Class for describing function declaration nodes.
     */
    class function_declaration_node: public cdk::typed_node {
    	int _reach;
        std::string *_identifier;
        cdk::sequence_node *_arguments;

    public:
        inline function_declaration_node(int lineno, int reach, std::string *identifier) :
        	cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _arguments(nullptr) {
        }
        inline function_declaration_node(int lineno, int reach, std::string *identifier, cdk::sequence_node *arguments) :
			cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _arguments(arguments) {
        }

    public:
        int reach() {
            return _reach;
        }
        std::string *identifier() {
            return _identifier;
        }
        cdk::sequence_node *arguments() {
            return _arguments;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_function_declaration_node(this, level);
        }

    };

} // gr8

#endif
