#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/llvm_ir_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void simple::llvm_ir_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
void simple::llvm_ir_writer::do_double_node(cdk::double_node * const node, int lvl) {
  // EMPTY
}
void simple::llvm_ir_writer::do_not_node(cdk::not_node * const node, int lvl) {
  // EMPTY
}
void simple::llvm_ir_writer::do_and_node(cdk::and_node * const node, int lvl) {
  // EMPTY
}
void simple::llvm_ir_writer::do_or_node(cdk::or_node * const node, int lvl) {
  // EMPTY
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl);
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _child = llvm::ConstantInt::get(_integerTy, node->value());
}

void simple::llvm_ir_writer::do_string_node(cdk::string_node * const node, int lvl) {
  llvm::Constant *fun_prints = _module->getOrInsertFunction("prints", _voidTy, _stringTy, nullptr);
  llvm::Constant *fun_println = _module->getOrInsertFunction("println", _voidTy, nullptr);

  llvm::Value *argument = _builder.CreateGlobalString(node->value(), "string");

  // Strings in Simple are always written:
  _builder.CreateCall(fun_prints, argument);
  _builder.CreateCall(fun_println); // print a newline
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  llvm::Value *argument = _child;
  _child = _builder.CreateNeg(argument, "neg");
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateAdd(L, R, "add");
}
void simple::llvm_ir_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateSub(L, R, "sub");
}
void simple::llvm_ir_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateMul(L, R, "mul");
}
void simple::llvm_ir_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateSDiv(L, R, "sdiv");
}
void simple::llvm_ir_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateSRem(L, R, "srem");
}
void simple::llvm_ir_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpSLT(L, R, "lt");
}
void simple::llvm_ir_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpSLE(L, R, "le");
}
void simple::llvm_ir_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpSGE(L, R, "ge");
}
void simple::llvm_ir_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpSGT(L, R, "gt");
}
void simple::llvm_ir_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpNE(L, R, "ne");
}
void simple::llvm_ir_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  llvm::Value *L = _child;
  node->right()->accept(this, lvl);
  llvm::Value *R = _child;
  _child = _builder.CreateICmpEQ(L, R, "eq");
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  llvm::Value *variable = _named_values[node->name()];
  _child = variable;
}

void simple::llvm_ir_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  _child = _builder.CreateLoad(_child);
}

void simple::llvm_ir_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->rvalue()->accept(this, lvl);
  llvm::Value *rhs = _child;

  llvm::GlobalVariable *lhs;
  if (new_symbol() == nullptr) {
    node->lvalue()->accept(this, lvl);
    lhs = llvm::cast<llvm::GlobalVariable>(_child);
  } else {
    // force zero as initial value
    llvm::Constant *init = llvm::cast<llvm::Constant>(llvm::ConstantInt::get(_integerTy, 0));

    // put in the known values table
    const std::string &id = new_symbol()->name();
    _named_values[id] = lhs = new llvm::GlobalVariable(*_module, _integerTy, false, llvm::GlobalVariable::WeakAnyLinkage, init);
    reset_new_symbol();
  }

  //DAVID: FIXME
  _child = _builder.CreateStore(rhs, lhs); // store the value at address
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_program_node(simple::program_node * const node, int lvl) {
  // Note that Simple doesn't have functions. Thus, it doesn't need
  // a function node. However, it must start in the main function.
  // The ProgramNode (representing the whole program) doubles as a
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  // this means that "lli" will not be able to run the program (it needs "main")
  // -- it would not work, anyway, since auxiliary functions are defined by libRTS
  llvm::FunctionType *FT = llvm::FunctionType::get(_integerTy, false);
  _function = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "_main", _module);

  llvm::BasicBlock *BB = llvm::BasicBlock::Create(_module->getContext(), "entry", _function);
  _builder.SetInsertPoint(BB);

  node->statements()->accept(this, lvl);

  // end the main function
  _builder.CreateRet(llvm::ConstantInt::get(_integerTy, 0));

  //MANUAL: Validate the generated code, checking for consistency.
  //MANUAL: verifyFunction(*F);
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_evaluation_node(simple::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
}

void simple::llvm_ir_writer::do_print_node(simple::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  llvm::Constant *fun_printi = _module->getOrInsertFunction("printi", _voidTy, _integerTy, nullptr);
  llvm::Constant *fun_println = _module->getOrInsertFunction("println", _voidTy, nullptr);

  node->argument()->accept(this, lvl); // determine the value to print
  llvm::Value *argument = _child;
  _builder.CreateCall(fun_printi, argument);
  _builder.CreateCall(fun_println); // print a newline
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_read_node(simple::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  llvm::Constant *fun_readi = _module->getOrInsertFunction("readi", _integerTy, _voidTy, nullptr);
  node->argument()->accept(this, lvl);  // left value (identifier)
  llvm::Value *lhs = _child;
  llvm::Value *rhs = _builder.CreateCall(fun_readi);
  _builder.CreateStore(rhs, lhs);
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_while_node(simple::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  llvm::BasicBlock *entry = llvm::BasicBlock::Create(_module->getContext(), "while_entry", _function);
  llvm::BasicBlock *body = llvm::BasicBlock::Create(_module->getContext(), "while_body", _function);
  llvm::BasicBlock *end = llvm::BasicBlock::Create(_module->getContext(), "while_end", _function);

  // this is a pseudo-hack to avoid explicit insertion point definition in the parent
  _builder.CreateBr(entry);

  _builder.SetInsertPoint(entry);
  node->condition()->accept(this, lvl);
  llvm::Value *condition = _child;
  _builder.CreateCondBr(condition, body, end);

  _builder.SetInsertPoint(body);
  node->block()->accept(this, lvl + 2);
  _builder.CreateBr(entry);

  // insert after the end
  _builder.SetInsertPoint(end);
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_if_node(simple::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  //llvm::BasicBlock *entry = llvm::BasicBlock::Create(_module->getContext(), "if_then_entry", _function);
  llvm::BasicBlock *block_then = llvm::BasicBlock::Create(_module->getContext(), "if_then_true_block", _function);
  llvm::BasicBlock *end = llvm::BasicBlock::Create(_module->getContext(), "if_then_end", _function);

  //_builder.SetInsertPoint(entry);
  node->condition()->accept(this, lvl);
  llvm::Value *condition = _child;
  _builder.CreateCondBr(condition, block_then, end);

  _builder.SetInsertPoint(block_then);
  node->block()->accept(this, lvl);
  _builder.CreateBr(end);

  // insert after the end
  _builder.SetInsertPoint(end);
}

//---------------------------------------------------------------------------

void simple::llvm_ir_writer::do_if_else_node(simple::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  //llvm::BasicBlock *entry = llvm::BasicBlock::Create(_module->getContext(), "if_then_else_entry", _function);
  llvm::BasicBlock *block_then = llvm::BasicBlock::Create(_module->getContext(), "if_then_else_true_block", _function);
  llvm::BasicBlock *block_else = llvm::BasicBlock::Create(_module->getContext(), "if_then_else_false_block", _function);
  llvm::BasicBlock *end = llvm::BasicBlock::Create(_module->getContext(), "if_then_else_end", _function);

  //_builder.SetInsertPoint(entry);
  node->condition()->accept(this, lvl);
  llvm::Value *condition = _child;
  _builder.CreateCondBr(condition, block_then, block_else);

  _builder.SetInsertPoint(block_then);
  node->thenblock()->accept(this, lvl + 2);
  _builder.CreateBr(end);

  _builder.SetInsertPoint(block_else);
  node->elseblock()->accept(this, lvl + 2);
  _builder.CreateBr(end);

  // insert after the end
  _builder.SetInsertPoint(end);
}
