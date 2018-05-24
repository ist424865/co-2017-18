// Rui Ribeiro - 83562

#ifndef __GR8_FUNCTIONINVOCATIONNODE_H__
#define __GR8_FUNCTIONINVOCATIONNODE_H__

#include <cdk/ast/expression_node.h>
#include <string>

namespace gr8 {

    /**
     * Class for describing function invocation nodes.
     */
    class function_invocation_node: public cdk::expression_node {
        std::string *_identifier;
        cdk::sequence_node *_arguments;

    public:
        inline function_invocation_node(int lineno, std::string *identifier, cdk::sequence_node *arguments) :
            cdk::expression_node(lineno), _identifier(identifier), _arguments(arguments) {
        }
        inline function_invocation_node(int lineno, std::string *identifier) :
            cdk::expression_node(lineno), _identifier(identifier), _arguments(nullptr) {
        }

    public:
        std::string *identifier() {
            return _identifier;
        }
        cdk::sequence_node *arguments() {
            return _arguments;
        }

        void accept(basic_ast_visitor *sp, int level) {
            sp->do_function_invocation_node(this, level);
        }

    };

} // gr8

#endif
