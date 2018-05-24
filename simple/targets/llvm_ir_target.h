#ifndef __SIMPLE_LLVM_IR_TARGET_H__
#define __SIMPLE_LLVM_IR_TARGET_H__

#include <cdk/basic_target.h>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include <cdk/compiler.h>

#include <llvm/IR/Module.h>

#include "targets/llvm_ir_writer.h"
#include "targets/symbol.h"

namespace simple {

  class llvm_ir_target: public cdk::basic_target {
    static llvm_ir_target _self;

  private:
    llvm_ir_target() :
        cdk::basic_target("ll") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      // this symbol table will be used to check identifiers
      // during code generation
      cdk::symbol_table<simple::symbol> symtab;

      llvm::LLVMContext &context = llvm::getGlobalContext();
      llvm::Module *module = new llvm::Module("this module", context);

      llvm_ir_writer writer(compiler, symtab, module);
      compiler->ast()->accept(&writer, 0);

      module->dump();
      //module->print(compiler->ostream(), nullptr);
      delete module;

      return true;
    }

  };

} // simple

#endif
