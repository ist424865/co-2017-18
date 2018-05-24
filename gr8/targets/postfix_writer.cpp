#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/function_enter.h"
#include "ast/all.h"  // all.h is automatically generated

int local;
basic_type::type parent  = 0;

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

void gr8::postfix_writer::reverse_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (int i = node->size() - 1; i >= 0; i--) {
    node->node(i)->accept(this, lvl);
  }
}

void gr8::postfix_writer::do_block_node(gr8::block_node *const node, int lvl) {
  _symtab.push();
  if (node->declarations() != nullptr)
    node->declarations()->accept(this, lvl);
  if (node->instructions() != nullptr)
    node->instructions()->accept(this, lvl);
  _symtab.pop();
}
//---------------------------------------------------------------------------

void gr8::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.INT(node->value()); // push an integer
}

void gr8::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.DOUBLE(node->value()); // push a double
}

void gr8::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

void gr8::postfix_writer::do_null_node(gr8::null_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.INT(0); 
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identity_node(gr8::identity_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.DUP32();
    int lbl1, lbl2;
    _pf.INT(0);
    _pf.GE();
    _pf.JZ(mklbl(lbl1 = ++_lbl));
    // Positive or zero
    _pf.JMP(mklbl(lbl2 = ++_lbl));
    _pf.LABEL(mklbl(lbl1));
    // Negative
    _pf.NEG();
    _pf.LABEL(mklbl(lbl1 = lbl2));
  }
  else {
    _pf.DUP64();
    int lbl1, lbl2;
    _pf.DOUBLE(0);
    _pf.GE();
    _pf.JZ(mklbl(lbl1 = ++_lbl));
    // Positive or zero
    _pf.JMP(mklbl(lbl2 = ++_lbl));
    _pf.LABEL(mklbl(lbl1));
    // Negative
    _pf.DNEG();
    _pf.LABEL(mklbl(lbl1 = lbl2));
  }
}
void gr8::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.NEG(); // 2-complement
  }
  else {
    _pf.DNEG(); // 2-complement
  }
}
void gr8::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.INT(0);
  _pf.EQ();
}
void gr8::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.AND();
}
void gr8::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.OR();
}

//---------------------------------------------------------------------------
void gr8::postfix_writer::convert_to_double(cdk::binary_expression_node * node, int lvl) {
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_INT) {
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    _pf.I2D();
  }
  else if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    node->left()->accept(this, lvl);
    _pf.I2D();
    node->right()->accept(this, lvl);
  }
  else {
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
  }

}
void gr8::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  convert_to_double(node, lvl);

  if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DADD();
  }
  else if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.ADD();
  }
  else if (node->type()->name() == basic_type::TYPE_POINTER) {
    _pf.INT(4);
    _pf.MUL();
    _pf.ADD();
  }
}
void gr8::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  convert_to_double(node, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DSUB();
  }
  else if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.SUB();
  }
}
void gr8::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  convert_to_double(node, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DMUL();
  }
  else if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.MUL();
  }
}
void gr8::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  convert_to_double(node, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DDIV();
  }
  else if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.DIV();
  }
}
void gr8::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void gr8::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
 
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.D2I();  
  }
  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.D2I();  
  }
  _pf.LT();
}
void gr8::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
}
void gr8::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
}
void gr8::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.D2I();  
  }
  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.D2I();  
  }
  _pf.GT();
}
void gr8::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
}
void gr8::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  convert_to_double(node, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->name()); 

  if (symbol->offset() == 0) {
    _pf.ADDR(node->name());
  }
  else {
    _pf.LOCAL(symbol->offset());
  }
}

void gr8::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  if (node->lvalue()->type()->name() == basic_type::TYPE_INT) {
    _pf.LDINT();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.LDDOUBLE();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_STRING) {
    _pf.LDINT();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.LDINT();
  }
}

void gr8::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->rvalue()->accept(this, lvl); // determine the new value
  if (node->lvalue()->type()->name() == basic_type::TYPE_INT) {
    _pf.DUP32();
    node->lvalue()->accept(this, lvl);
    _pf.STINT();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE) {
    if (node->rvalue()->type()->name() == basic_type::TYPE_INT) {
      _pf.I2D();
    }
    _pf.DUP64();
    node->lvalue()->accept(this, lvl);
    _pf.STDOUBLE();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_STRING) {
    _pf.DUP32();
    node->lvalue()->accept(this, lvl);
    _pf.STINT();
  }
  else if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.DUP32();
    node->lvalue()->accept(this, lvl);
    _pf.STINT();
  }
}

//---------------------------------------------------------------------------

/* void gr8::postfix_writer::do_program_node(gr8::program_node * const node, int lvl) {
  // Note that Simple didn't have functions. Thus, it didn't need
  // a function node. However, it had to start in the main function.
  // program_node (representing the whole program) doubled as a
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");
  _pf.ENTER(0);  // Simple didn't implement local variables

  node->statements()->accept(this, lvl);

  // end the main function
  _pf.INT(0);
  _pf.STFVAL32();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("printi");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");
}*/

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.TRASH(8); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
  } else {
    std::cerr << "EVALUATION ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_read_node(gr8::read_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  /*if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("readi");
    _pf.LDFVAL32();
  } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("readd");
    _pf.LDFVAL64();
  } else if (node->type()->name() == basic_type::TYPE_UNSPEC) {
    _pf.CALL("readi");
    _pf.LDFVAL32();
  } else {
    std::cerr << "READ ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }*/
  
  // node->argument()->accept(this, lvl);
  //_pf.STINT();
}

//---------------------------------------------------------------------------

/*void gr8::postfix_writer::do_while_node(gr8::while_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
}*/

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_node(gr8::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_function_definition_node(gr8::function_definition_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  parent = node->type()->name();
  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("readd");
  _pf.EXTERN("printi");
  _pf.EXTERN("printd");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");

  function_enter *fe = new function_enter(_compiler);

  node->accept(fe, lvl);

  int count = fe->counter();

  if (*node->identifier() == "covfefe") {
    _pf.TEXT();
    _pf.ALIGN();
    _pf.GLOBAL("_main", _pf.FUNC());
    _pf.LABEL("_main");
    _pf.ENTER(count);

    //if (node->arguments() != nullptr) 
    //  node->arguments()->accept(this, lvl); 
    _symtab.push();

    local = 0;
    node->body()->accept(this, lvl + 2);
  
    // end the main function
    //_pf.INT(0);
    //_pf.STFVAL32();
    _symtab.pop();
    _pf.LEAVE();
    _pf.RET();


  }

  else {
    _pf.TEXT();
    _pf.ALIGN();

    _pf.GLOBAL(*node->identifier(), _pf.FUNC());
    _pf.LABEL(*node->identifier());

    _pf.ENTER(count); 

    local = 8;
    _symtab.push();
    if (node->arguments() != nullptr) 
      //reverse_sequence_node(node->arguments(), lvl + 2); 
      node->arguments()->accept(this, lvl + 2);
    local = 0;
    node->body()->accept(this, lvl + 2);

    _symtab.pop();
    _pf.LEAVE();
    _pf.RET();
    
  }
}


void gr8::postfix_writer::do_function_invocation_node(gr8::function_invocation_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier());

  if (node->arguments() != nullptr) {
    for (int i = node->arguments()->size() - 1; i >=0 ; i--) {
       node->arguments()->node(i)->accept(this, lvl + 4);
       basic_type::type call_type = dynamic_cast<cdk::typed_node*>(node->arguments()->node(i))->type()->name();
       if (symbol->types().at(i) == basic_type::TYPE_DOUBLE && call_type == basic_type::TYPE_INT) {
         _pf.I2D();
       } // INT in DOUBLE
    }
  }
  _pf.CALL(*node->identifier());

  if (node->type()->name() == basic_type::TYPE_VOID) {}
  else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.LDFVAL64();
  } else {
    _pf.LDFVAL32();
  }
  

}
void gr8::postfix_writer::do_function_declaration_node(gr8::function_declaration_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier());

  _pf.EXTERN(*node->identifier());

  _symtab.push();
  if (node->arguments() != nullptr) 
      node->arguments()->accept(this, lvl + 2);

  _symtab.pop();
}
void gr8::postfix_writer::do_variable_declaration_node(gr8::variable_declaration_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;  
  
  if (lvl != 0) {
    
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(*node->identifier()); 
   
    if (local > 0) { 
      symbol->offset() = local; 
      if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_STRING || node->type()->name() == basic_type::TYPE_POINTER) { 
        local += 4;
      }
      else {
        local += 8;
      }
    }
    else { 
      if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_STRING || node->type()->name() == basic_type::TYPE_POINTER) {
        local -= 4;
      }
      else {
        local -= 8;
      }
      symbol->offset() = local; 
    }
    if (node->initial() != nullptr) {
      if (node->initial()->type()->name() == basic_type::TYPE_DOUBLE) {
        node->initial()->accept(this, lvl);
        _pf.LOCAL(symbol->offset());  
        _pf.STDOUBLE();
        _pf.DUP64();
      }
      else {
        node->initial()->accept(this, lvl);
        _pf.LOCAL(symbol->offset());  
        _pf.STINT();
        _pf.DUP32();
      }
    }
    else {
       /*if (node->initial()->type()->name() == basic_type::TYPE_DOUBLE) {
	_pf.DOUBLE(0);
        _pf.LOCAL(symbol->offset());  
        _pf.STDOUBLE();
      }
      else {
	_pf.INT(0);
        _pf.LOCAL(symbol->offset());  
        _pf.STINT();
      }*/
    }
  }

  else {
    if (node->initial() != nullptr) {
      if (node->type()->name() == basic_type::TYPE_INT) {
        _pf.DATA();
        _pf.ALIGN();
        _pf.GLOBAL(*node->identifier(), _pf.OBJ());
        _pf.LABEL(*node->identifier());
        _pf.SINT(dynamic_cast<cdk::integer_node*>(node->initial())->value());
      }
      else if (node->initial()->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.DATA();
        _pf.ALIGN();
        _pf.GLOBAL(*node->identifier(), _pf.OBJ());
        _pf.LABEL(*node->identifier());
        if (node->initial()->type()->name() == basic_type::TYPE_INT) {
          _pf.SDOUBLE(dynamic_cast<cdk::integer_node*>(node->initial())->value());
        }
        else {
 	  _pf.SDOUBLE(dynamic_cast<cdk::double_node*>(node->initial())->value());
	}
      }
      else if (node->initial()->type()->name() == basic_type::TYPE_STRING) {
        int lbl1;

        _pf.RODATA(); // strings are DATA readonly
        _pf.ALIGN(); // make sure we are aligned
        _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
        _pf.SSTRING(dynamic_cast<cdk::string_node*>(node->initial())->value()); // output string characters
        
	_pf.DATA();
        _pf.ALIGN();
        _pf.GLOBAL(*node->identifier(), _pf.OBJ());
        _pf.LABEL(*node->identifier());
        _pf.SADDR(mklbl(lbl1));
      }
      else if (node->initial()->type()->name() == basic_type::TYPE_POINTER) {   
	_pf.DATA();
        _pf.ALIGN();
        _pf.GLOBAL(*node->identifier(), _pf.OBJ());
        _pf.LABEL(*node->identifier());
	_pf.SINT(0);
      }
    }
    else {
      _pf.DATA();
      _pf.ALIGN();
      _pf.GLOBAL(*node->identifier(), _pf.OBJ());
      _pf.LABEL(*node->identifier());
      if (node->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.SDOUBLE(0);
      }
      else {
        _pf.SINT(0);
      }
    }
  }
  _pf.TEXT();
  _pf.ALIGN();
}
void gr8::postfix_writer::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  int lbl1, lbl2, lbl3, lbl4;

  node->from()->accept(this, lvl + 2);
  node->iterator()->accept(this, lvl + 2);
  _pf.STINT();

  _pf.LABEL(mklbl(lbl1 = ++_lbl));

  // ITERATOR IF

  if (node->by() != nullptr) {
    node->by()->accept(this, lvl + 2);
    _pf.INT(0); 
    _pf.GT(); // by > 0
    _pf.JZ(mklbl(lbl3 = ++_lbl));
    node->iterator()->accept(this, lvl + 2);
    _pf.LDINT();
    node->to()->accept(this, lvl + 2);
    _pf.LE();
    _pf.JMP(mklbl(lbl4 = ++_lbl));
    _pf.LABEL(mklbl(lbl3));
    node->iterator()->accept(this, lvl + 2);
    _pf.LDINT();
    node->to()->accept(this, lvl + 2);
    _pf.GE();
    _pf.LABEL(mklbl(lbl4));
  }
  else {
    node->iterator()->accept(this, lvl + 2);
    _pf.LDINT();
    node->to()->accept(this, lvl + 2);
    _pf.LE();
  }

  // END ITERATOR IF

  _pf.JZ(mklbl(lbl2 = ++_lbl));

  node->block()->accept(this, lvl + 2);

  node->iterator()->accept(this, lvl + 2);
  _pf.LDINT();
  _pf.DUP32();
  if (node->by() != nullptr) {
    node->by()->accept(this, lvl + 2);
  }
  else {
    _pf.INT(1);
  }
  _pf.ADD();
  node->iterator()->accept(this, lvl + 2);
  _pf.STINT();
  _pf.TRASH(4);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));

}
void gr8::postfix_writer::do_stop_node(gr8::stop_node *const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_return_node(gr8::return_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    if (parent == basic_type::TYPE_DOUBLE) { 
      _pf.I2D();
      _pf.STFVAL64();
    } 
     else
      _pf.STFVAL32();
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.STFVAL64();
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.STFVAL32();
  } else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.STFVAL32();
  } else {
    std::cerr << "RETURN ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }

}
void gr8::postfix_writer::do_again_node(gr8::again_node *const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_post_node(gr8::post_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else {
    std::cerr << "POST ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.CALL("println"); // print a newline
}
void gr8::postfix_writer::do_tweet_node(gr8::tweet_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else {
    std::cerr << "TWEET ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  //_pf.CALL("println"); // print a newline
}

void gr8::postfix_writer::do_index_node(gr8::index_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  
  node->index()->accept(this, lvl);
  if (node->pointer()->type()->subtype()->name() == basic_type::TYPE_DOUBLE)
    _pf.INT(8);
  else
    _pf.INT(4);
  _pf.MUL();
  node->pointer()->accept(this, lvl);
  _pf.ADD();
}
void gr8::postfix_writer::do_address_of_node(gr8::address_of_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
}
void gr8::postfix_writer::do_alloc_node(gr8::alloc_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  _pf.LOCAL(local); 
  if (node->type()->subtype()->name() == basic_type::TYPE_INT || node->type()->subtype()->name() == basic_type::TYPE_STRING || node->type()->subtype()->name() == basic_type::TYPE_POINTER) {
    local -= 4 * dynamic_cast<cdk::integer_node*>(node->argument())->value();
    if (lvl > 0)
      local -= 4;
  }
  else {
    local -= 8 * dynamic_cast<cdk::integer_node*>(node->argument())->value();
    if (lvl > 0)
      local -= 8;
  }
}

