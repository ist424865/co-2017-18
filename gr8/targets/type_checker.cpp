// NOTES:
// FALTA input (read) no add, sub e equals

#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

basic_type::type _parentType = 0;

/**
 * Basic Nodes
 */

void gr8::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void gr8::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_null_node(gr8::null_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_POINTER)); // IS IT?
}

//---------------------------------------------------------------------------

/**
 * List of nodes
 */

void gr8::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  // DO NOTHING!
}

void gr8::type_checker::do_block_node(gr8::block_node *const node, int lvl) {
  // DO NOTHING!
}

//---------------------------------------------------------------------------

/**
 * Unary Expressions
 */

void gr8::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  
  if (node->argument()->type()->name() != basic_type::TYPE_INT && node->argument()->type()->name() != basic_type::TYPE_DOUBLE && node->argument()->type()->name() != basic_type::TYPE_UNSPEC) throw std::string("wrong type in argument of unary expression");

  if (node->argument()->type()->name() == basic_type::TYPE_INT)
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_identity_node(gr8::identity_node *const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void gr8::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void gr8::type_checker::do_address_of_node(gr8::address_of_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl);

  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype = new basic_type(node->argument()->type()->size(), node->argument()->type()->name());

}
void gr8::type_checker::do_alloc_node(gr8::alloc_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  
  if (node->argument()->type()->name() != basic_type::TYPE_INT && node->argument()->type()->name() != basic_type::TYPE_UNSPEC) throw std::string("wrong type in argument of unary expression");

  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

void gr8::type_checker::do_index_node(gr8::index_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->pointer()->accept(this, lvl);

  if (node->pointer()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("lvalue in index node must be a pointer");

  node->index()->accept(this, lvl);

  if (node->index()->type()->name() != basic_type::TYPE_INT)
    throw std::string("argument in index node must be an integer");

  node->type(node->pointer()->type()->subtype());
}

//---------------------------------------------------------------------------

/**
 * Expressions that operate only with integer and double types
 */

void gr8::type_checker::processBinaryIntegerDouble(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
    
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_UNSPEC) throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_UNSPEC) throw std::string("wrong type in right argument of binary expression");

  if (node->left()->type()->name() == basic_type::TYPE_UNSPEC)
    node->left()->type(node->right()->type()); 
  else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC)
    node->right()->type(node->left()->type()); 

  if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT) 
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

/**
 * Add operates with pointers, doubles and integers
 */

void gr8::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if ((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_INT) ||
      (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_INT))
      throw std::string("other argument with pointer argument must be int");
  else if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER) 
      throw std::string("wrong type in left argument of binary expression");
  else if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");

  if (node->left()->type()->name() == basic_type::TYPE_UNSPEC)
    node->left()->type(node->right()->type()); 
  else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC)
    node->right()->type(node->left()->type()); 

  if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT) 
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER)
    node->type(node->left()->type());
  else if (node->right()->type()->name() == basic_type::TYPE_POINTER)
    node->type(node->right()->type());
  else
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

/**
 * Sub operates with pointers, doubles and integers
 */

void gr8::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if ((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_POINTER) ||
      (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_POINTER))
      throw std::string("other argument with pointer argument must be pointer");
  else if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER) 
      throw std::string("wrong type in left argument of binary expression");
  else if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");

  if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT) 
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER)
    node->type(new basic_type(4, basic_type::TYPE_INT));
  else
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

bool gr8::type_checker::pointerComparator(basic_type *first, basic_type *second) {
  basic_type *currentOne = first;
  basic_type *currentTwo = second;

  while (currentOne != nullptr || currentTwo != nullptr) {
    if (currentOne != currentTwo) {
      return false;
    }
    currentOne = currentOne->subtype();
    currentTwo = currentTwo->subtype();
  }

  if (currentOne != currentTwo) {
    return false;
  }
  return true;
}

/**
 * Equals operates with pointers, doubles and integers
 */

void gr8::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if ((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_POINTER) ||
      (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_POINTER))
      throw std::string("other argument with pointer argument must be pointer");
  else if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER) 
      throw std::string("wrong type in left argument of binary expression");
  else if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");

  if (node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER)
    if (!pointerComparator(node->left()->type(), node->right()->type()))
      throw std::string("comparison between different type of pointers");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

/**
 * Expressions that operate with integers or integers and doubles
 */

void gr8::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryIntegerDouble(node, lvl);
}
void gr8::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryIntegerDouble(node, lvl);
}
void gr8::type_checker::do_mod_node(cdk::mod_node * const 

node, int lvl) {
  processBinaryInteger(node, lvl);
}
void gr8::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryIntegerDouble(node, lvl);
}
void gr8::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryIntegerDouble(node, lvl);
}

/**
 * Logic expressions that operate only with integer type
 */

void gr8::type_checker::processBinaryInteger(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in right argument of binary expression");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

/**
 * Logic that operate with integers
 */

void gr8::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in argument of not expression");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryInteger(node, lvl);
}
void gr8::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryInteger(node, lvl);
}

/**
 * Not in gr8 but necessary
 */

void gr8::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  // NOT USED!
}
void gr8::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  // NOT USED!
}
void gr8::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  // NOT USED!
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  } else {
    throw id;
  }
}

void gr8::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void gr8::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }

  if (node->lvalue()->type()->name() != basic_type::TYPE_INT && 
      node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE && 
      node->lvalue()->type()->name() != basic_type::TYPE_STRING &&
      node->lvalue()->type()->name() != basic_type::TYPE_POINTER) throw std::string("wrong type in left argument of assignment expression");
  
  node->rvalue()->accept(this, lvl + 2);

  if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
    if (node->rvalue()->type()->name() == basic_type::TYPE_POINTER && node->rvalue()->type()->subtype() == nullptr) {
    } // objects
    else {
      basic_type *lcurrent = node->lvalue()->type();
      basic_type *rcurrent = node->rvalue()->type();

      while (lcurrent != nullptr && rcurrent != nullptr) {
        if (lcurrent->name() != rcurrent->name()) throw std::string("wrong type in right argument of assignment expression");
        lcurrent = lcurrent->subtype();
        rcurrent = rcurrent->subtype();
      }
      if (lcurrent != nullptr || rcurrent != nullptr) throw std::string("wrong type in right argument of assignment expression");
    }
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT) {} // INT in DOUBLE
  else if (node->rvalue()->type()->name() != node->lvalue()->type()->name()) throw std::string(
      "wrong type in right argument of assignment expression");

  node->type(node->lvalue()->type());
  if (node->rvalue()->type()->name() == basic_type::TYPE_POINTER && node->rvalue()->type()->subtype() == nullptr) {
    node->rvalue()->type(node->lvalue()->type());
  } // objects
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_return_node(gr8::return_node *const node, int lvl) {
  node->argument()->accept(this, lvl);
  if (_parentType == basic_type::TYPE_DOUBLE && node->argument()->type()->name() == basic_type::TYPE_INT)
    return ;
  if (node->argument()->type()->name() != _parentType) throw std::string("wrong type in return argument of function");
}

void gr8::type_checker::do_stop_node(gr8::stop_node *const node, int lvl) {
  // ARGUMENT IS INTEGER!
}

void gr8::type_checker::do_again_node(gr8::again_node *const node, int lvl) {
  // ARGUMENT IS INTEGER!
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_post_node(gr8::post_node *const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->argument()->type()->name() != basic_type::TYPE_INT && 
           node->argument()->type()->name() != basic_type::TYPE_DOUBLE && 
           node->argument()->type()->name() != basic_type::TYPE_STRING) throw std::string("wrong type in argument of post");
}
void gr8::type_checker::do_tweet_node(gr8::tweet_node *const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT && 
      node->argument()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->argument()->type()->name() != basic_type::TYPE_STRING) throw std::string("wrong type in argument of tweet");
}

void gr8::type_checker::do_read_node(gr8::read_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_if_node(gr8::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}
void gr8::type_checker::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}
void gr8::type_checker::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  node->iterator()->accept(this, lvl + 4);
  if (node->iterator()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in iterator of sweeping");
  node->from()->accept(this, lvl + 4);
  if (node->from()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in from of sweeping");
  node->to()->accept(this, lvl + 4);
  if (node->to()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in to of sweeping");
  node->by()->accept(this, lvl + 4);
  if (node->by()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in by of sweeping");
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_function_invocation_node(gr8::function_invocation_node *const node, int lvl) {
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier());

  if (symbol == nullptr) {
    throw "undefined/undeclared function " + *node->identifier();
  }

  if (node->arguments() != nullptr) {
    for (size_t i = 0; i < node->arguments()->size(); i++) {
       node->arguments()->node(i)->accept(this, lvl + 4);
       basic_type::type call_type = dynamic_cast<cdk::typed_node*>(node->arguments()->node(i))->type()->name();
       if (symbol->types().at(i) == basic_type::TYPE_DOUBLE && (call_type == basic_type::TYPE_INT || call_type != basic_type::TYPE_DOUBLE)) {
       } // INT in DOUBLE
       else if (symbol->types().at(i) != call_type) throw std::string("different types of arguments in function invocation and definition");
    }
  }
  
  node->type(symbol->type());
}
void gr8::type_checker::do_function_definition_node(gr8::function_definition_node *const node, int lvl) {
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier());

  if (symbol == nullptr) {
    std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), *node->identifier());
    symbol->stage() = 1;
    if (node->arguments() != nullptr) {
      for (size_t i = 0; i < node->arguments()->size(); i++) {
        symbol->types().push_back(dynamic_cast<cdk::typed_node*>(node->arguments()->node(i))->type()->name());
      }
    }

    _symtab.insert(*node->identifier(), symbol);
  }
  else {
    if (symbol->stage() == 1) throw "already defined function " + *node->identifier();
    if (symbol->type()->name() != node->type()->name()) throw std::string("different types in function declaration and definition");
    if (node->arguments() != nullptr) {
      for (size_t i = 0; i < node->arguments()->size(); i++) {
        if (symbol->types().at(i) != dynamic_cast<cdk::typed_node*>(node->arguments()->node(i))->type()->name()) throw std::string("different types of arguments in function declaration and definition");
      }
    }
  }
  _parentType = node->type()->name(); 
}
void gr8::type_checker::do_function_declaration_node(gr8::function_declaration_node *const node, int lvl) {

  std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier());

  if (symbol == nullptr) {
    std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), *node->identifier());
    symbol->stage() = 0;
    if (node->arguments() != nullptr) {
      for (size_t i = 0; i < node->arguments()->size(); i++) {
        symbol->types().push_back(dynamic_cast<cdk::typed_node*>(node->arguments()->node(i))->type()->name());
      }
    }
    _symtab.insert(*node->identifier(), symbol);
  }
  else {
    throw "already declared function " + *node->identifier();
  }

}
void gr8::type_checker::do_variable_declaration_node(gr8::variable_declaration_node *const node, int lvl) {
  std::shared_ptr<gr8::symbol> symbol = _symtab.find_local(*node->identifier());

  if (symbol == nullptr) {
    std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), *node->identifier());
    _symtab.insert(*node->identifier(), symbol);
  } 
  else {
    throw "already declared variable " + *node->identifier();
  }

  _parent->set_new_symbol(symbol);  // advise parent that a symbol has been inserted

  if (node->initial() != nullptr) {
    node->initial()->accept(this, lvl + 4);
    if (node->type()->name() == basic_type::TYPE_DOUBLE && node->initial()->type()->name() == basic_type::TYPE_INT) {} // INT in DOUBLE
    else if (node->initial()->type()->name() != node->type()->name()) throw std::string("initial type is different from declared variable");
  }
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {
  // NOT USED!
}
void gr8::type_checker::do_data_node(cdk::data_node * const node, int lvl) {
  // NOT USED!
}


