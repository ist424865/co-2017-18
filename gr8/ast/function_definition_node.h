// Rui Ribeiro - 83562

#ifndef __GR8_PROJECTFUNCTIONDEFINITIONNODE_H__
#define __GR8_PROJECTFUNCTIONDEFINITIONNODE_H__

#include <cdk/ast/typed_node.h>
#include <string>

namespace gr8 {

    /**
     * Class for describing function declaration nodes.
     */
    class function_definition_node: public cdk::typed_node {
        int _reach;
        std::string *_identifier;
        cdk::sequence_node *_arguments;
        block_node *_body;

    public:
        inline function_definition_node(int lineno, int reach, std::string *identifier, block_node *body) :
        	cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _arguments(nullptr), _body(body) {
        }
        inline function_definition_node(int lineno, int reach, std::string *identifier, cdk::sequence_node *arguments, block_node *body) :
			cdk::typed_node(lineno), _reach(reach), _identifier(identifier), _arguments(arguments), _body(body) {
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
        block_node *body() {
            return _body;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_function_definition_node(this, level);
        }

    };

} // gr8

#endif
