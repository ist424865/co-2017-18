#ifndef __SIMPLE_LLVM_IR_WRITER_H__
#define __SIMPLE_LLVM_IR_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>

namespace simple {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class llvm_ir_writer: public basic_ast_visitor {
    cdk::symbol_table<simple::symbol> &_symtab;
    llvm::Module *_module;
    std::map<std::string, llvm::Value*> _named_values;
    llvm::IRBuilder<> _builder;

    llvm::Type *_voidTy;
    llvm::IntegerType *_integerTy;
    llvm::PointerType *_stringTy;

    llvm::Value *_child = nullptr;
    llvm::Function *_function = nullptr;  // current function

  public:
    llvm_ir_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<simple::symbol> &symtab, llvm::Module *module) :
        basic_ast_visitor(compiler), //
        _symtab(symtab), _module(module), _builder(_module->getContext()), //
        _voidTy(llvm::Type::getVoidTy(_module->getContext())), //
        _integerTy(llvm::IntegerType::get(_module->getContext(), 32)), //
        _stringTy(llvm::PointerType::get(llvm::IntegerType::get(_module->getContext(), 8), 0)) {
    }

  public:
    ~llvm_ir_writer() {
      os().flush();
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // simple

#endif
