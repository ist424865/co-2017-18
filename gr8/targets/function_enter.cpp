#include "targets/function_enter.h"
#include "ast/all.h"  // all.h is automatically generated

void gr8::function_enter::do_integer_node(cdk::integer_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_double_node(cdk::double_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_string_node(cdk::string_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_null_node(gr8::null_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_tweet_node(gr8::tweet_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_evaluation_node(gr8::evaluation_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_if_else_node(gr8::if_else_node *const node, int lvl) {
  node->thenblock()->accept(this, lvl);
  node->elseblock()->accept(this, lvl);
}
void gr8::function_enter::do_again_node(gr8::again_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  node->block()->accept(this, lvl);
}
void gr8::function_enter::do_return_node(gr8::return_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_alloc_node(gr8::alloc_node *const node, int lvl) {
  if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_POINTER || node->type()->name() == basic_type::TYPE_STRING)
    _counter += 4 * dynamic_cast<cdk::integer_node*>(node->argument())->value();
  else if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _counter += 8 * dynamic_cast<cdk::integer_node*>(node->argument())->value();
}
void gr8::function_enter::do_function_invocation_node(gr8::function_invocation_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_identity_node(gr8::identity_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_address_of_node(gr8::address_of_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}
void gr8::function_enter::do_block_node(gr8::block_node *const node, int lvl) {
  if (node->declarations() != nullptr)
    node->declarations()->accept(this, lvl);
  if (node->instructions() != nullptr)
    node->instructions()->accept(this, lvl);
}
void gr8::function_enter::do_post_node(gr8::post_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_variable_declaration_node(gr8::variable_declaration_node *const node, int lvl) {
  if (node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_POINTER || node->type()->name() == basic_type::TYPE_STRING)
    _counter += 4;
  else if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _counter += 8;
}
void gr8::function_enter::do_function_definition_node(gr8::function_definition_node *const node, int lvl) {
  node->body()->accept(this, lvl);
}
void gr8::function_enter::do_index_node(gr8::index_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_function_declaration_node(gr8::function_declaration_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_stop_node(gr8::stop_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_read_node(gr8::read_node *const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_neg_node(cdk::neg_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_not_node(cdk::not_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_and_node(cdk::and_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_or_node(cdk::or_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_add_node(cdk::add_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_sub_node(cdk::sub_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_mul_node(cdk::mul_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_div_node(cdk::div_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_mod_node(cdk::mod_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_lt_node(cdk::lt_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_le_node(cdk::le_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_ge_node(cdk::ge_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_gt_node(cdk::gt_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_ne_node(cdk::ne_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_eq_node(cdk::eq_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  // EMPTY
}
void gr8::function_enter::do_if_node(gr8::if_node * const node, int lvl) {
  node->block()->accept(this, lvl);
}
