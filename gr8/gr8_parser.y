%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
#define PRIVATE			   0
#define PROCEDURE		   false
#define FUNCTION		   true
%}

%union {
  int                   i;	/* integer value */
  float					f;  /* float value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type	       *type;
  cdk::typed_node      *typed;
  gr8::block_node      *block;
};

%token <i> tINTEGER
%token <s> tIDENTIFIER tSTRING
%token <f> tFLOAT
%token tSMALL tHUGE tNEWS tFAKE tINITIALLY tNULL tPLUS tMINUS tTIMES tOVER tMODULUS tNOT tAND tOR 
%token tASSIGN tTO tCELL tAT tABOVE tBELOW tEQUALS tINPUT tUSE tPUBLIC tDEFINE tPROCEDURE tFUNCTION 
%token tON tAS tDO tUSES tFOR tRETURN tIF tTHEN tELSIF tELSE tSTOP tREAD tAGAIN tPOST tTWEET tSWEEPING tFROM tBY tINTERROG

%left tOR 
%left tAND
%nonassoc tNOT
%right tEQUALS
%left tABOVE tBELOW
%left tPLUS tMINUS
%left tTIMES tOVER tMODULUS
%nonassoc tINDEX tCELL
%nonassoc tUNARY tOBJECTS tINTERROG

%nonassoc tIFX
%nonassoc tELSE

%type <i> qualf
%type <s> str
%type <node> stmt decl stmt asgn condt iter
%type <typed> var funct fdecl fdef
%type <sequence> vars listd listi exprs decls vars
%type <block> block
%type <expression> expr finv
%type <lvalue> lval  
%type <type> lists listf listh type
%type file 

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file  : listd { compiler->ast($1); } 
      |       { compiler->ast(new cdk::nil_node(LINE)); }
      ;

listd : decl	   { $$ = new cdk::sequence_node(LINE, $1); }
      | listd decl { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;

decl  : var ';'  { $$ = $1; }
      | funct    { $$ = $1; }
      ;

var   : type tIDENTIFIER		                       { $$ = new gr8::variable_declaration_node(LINE, PRIVATE, $2); $$->type($1); }
      | type tIDENTIFIER '(' tINITIALLY expr ')'       { $$ = new gr8::variable_declaration_node(LINE, PRIVATE, $2, $5); $$->type($1); }
      | qualf type tIDENTIFIER                         { $$ = new gr8::variable_declaration_node(LINE, $1, $3); $$->type($2); }
      | qualf type tIDENTIFIER '(' tINITIALLY expr ')' { $$ = new gr8::variable_declaration_node(LINE, $1, $3, $6); $$->type($2); }
      ;

vars  : var          { $$ = new cdk::sequence_node(LINE, $1); }
      | vars ',' var { $$ = new cdk::sequence_node(LINE, $3, $1); }
      ;

funct : fdecl ';' { $$ = $1; }
      | fdef      { $$ = $1; }
      ; 

fdecl : qualf type tFUNCTION tIDENTIFIER                            { $$ = new gr8::function_declaration_node(LINE, $1, $4); $$->type($2); }
      | qualf tPROCEDURE tIDENTIFIER                                { $$ = new gr8::function_declaration_node(LINE, $1, $3); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | qualf type tFUNCTION tIDENTIFIER tUSES vars                 { $$ = new gr8::function_declaration_node(LINE, $1, $4, $6); $$->type($2); }
      | qualf tPROCEDURE tIDENTIFIER tUSES vars                     { $$ = new gr8::function_declaration_node(LINE, $1, $3, $5); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | type tFUNCTION tIDENTIFIER                                  { $$ = new gr8::function_declaration_node(LINE, PRIVATE, $3); $$->type($1); }
      | tPROCEDURE tIDENTIFIER                                      { $$ = new gr8::function_declaration_node(LINE, PRIVATE, $2); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | type tFUNCTION tIDENTIFIER tUSES vars                       { $$ = new gr8::function_declaration_node(LINE, PRIVATE, $3, $5); $$->type($1); }
      | tPROCEDURE tIDENTIFIER tUSES vars                           { $$ = new gr8::function_declaration_node(LINE, PRIVATE, $2, $4); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      ;

fdef  : tDEFINE qualf type tFUNCTION tIDENTIFIER tAS block          { $$ = new gr8::function_definition_node(LINE, $2, $5, $7); $$->type($3); }
      | tDEFINE qualf tPROCEDURE tIDENTIFIER tAS block              { $$ = new gr8::function_definition_node(LINE, $2, $4, $6); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | tDEFINE qualf type tFUNCTION tIDENTIFIER tON vars tAS block { $$ = new gr8::function_definition_node(LINE, $2, $5, $7, $9); $$->type($3); }
      | tDEFINE qualf tPROCEDURE tIDENTIFIER tON vars tAS block     { $$ = new gr8::function_definition_node(LINE, $2, $4, $6, $8); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | tDEFINE type tFUNCTION tIDENTIFIER tAS block                { $$ = new gr8::function_definition_node(LINE, PRIVATE, $4, $6); $$->type($2); }
      | tDEFINE tPROCEDURE tIDENTIFIER tAS block                    { $$ = new gr8::function_definition_node(LINE, PRIVATE, $3, $5); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      | tDEFINE type tFUNCTION tIDENTIFIER tON vars tAS block       { $$ = new gr8::function_definition_node(LINE, PRIVATE, $4, $6, $8); $$->type($2); }
      | tDEFINE tPROCEDURE tIDENTIFIER tON vars tAS block           { $$ = new gr8::function_definition_node(LINE, PRIVATE, $3, $5, $7); $$->type(new basic_type(4, basic_type::TYPE_VOID)); }
      ;

finv  : tUSE exprs tFOR tIDENTIFIER { $$ = new gr8::function_invocation_node(LINE, $4 ,$2); }
      | tDO tIDENTIFIER             { $$ = new gr8::function_invocation_node(LINE, $2); }
      ;

lists : tSMALL		 { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(4, basic_type::TYPE_INT); }
      | lists tSMALL { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $1; }
      ;

listh : tHUGE	    { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(8, basic_type::TYPE_DOUBLE); }
      | listh tHUGE { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $1;}
      ;

listf : tFAKE 	  	{ $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(4, basic_type::TYPE_STRING); }
      | listf tFAKE { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $1; }
      ;

type  : tSMALL      { $$ = new basic_type(4, basic_type::TYPE_INT); }
      | lists tFAKE { $$ = $1; }
      | tHUGE 		{ $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
      | listh tFAKE { $$ = $1; }
      | tNEWS 		{ $$ = new basic_type(4, basic_type::TYPE_STRING); }
      | listf tNEWS { $$ = $1; }
      ;

decls : decl       { $$ = new cdk::sequence_node(LINE, $1); }
      | decls decl { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;

listi : stmt       { $$ = new cdk::sequence_node(LINE, $1); }
      | listi stmt { $$ = new cdk::sequence_node(LINE, $2, $1); }   
      ;

block : '{' decls '}'       { $$ = new gr8::block_node(LINE, $2, nullptr); }
      | '{' listi '}'       { $$ = new gr8::block_node(LINE, nullptr, $2); }
      | '{' decls listi '}' { $$ = new gr8::block_node(LINE, $2, $3); }
      | '{' '}'             { $$ = new gr8::block_node(LINE, nullptr, nullptr); }
      ;

stmt  : expr ';'            { $$ = new gr8::evaluation_node(LINE, $1); }
      | asgn ';'		    { $$ = $1; }
      | tTWEET expr ';'		{ $$ = new gr8::tweet_node(LINE, $2); }
      | tPOST expr ';'		{ $$ = new gr8::post_node(LINE, $2); }
      | tAGAIN ';'			{ $$ = new gr8::again_node(LINE); }
      | tAGAIN tINTEGER ';' { $$ = new gr8::again_node(LINE, $2); }
      | tSTOP ';'			{ $$ = new gr8::stop_node(LINE); }
      | tSTOP tINTEGER ';'  { $$ = new gr8::stop_node(LINE, $2); }
      | tRETURN ';'			{ $$ = new gr8::return_node(LINE, nullptr); }
      | tRETURN expr ';'    { $$ = new gr8::return_node(LINE, $2); }
      | tIF condt				{ $$ = $2; }
      | iter				{ $$ = $1; }
      | block				{ $$ = $1; }
      ;

asgn  : tASSIGN expr tTO lval { $$ = new cdk::assignment_node(LINE, $4, $2); }
      ;

condt : expr tTHEN block %prec tIFX  { $$ = new gr8::if_node(LINE, $1, $3); }
      | expr tTHEN block tELSE block { $$ = new gr8::if_else_node(LINE, $1, $3, $5); }
      | expr tTHEN block tELSIF condt { $$ = new gr8::if_else_node(LINE, $1, $3, $5); }
      ;

iter  : tSWEEPING lval tFROM expr tTO expr tDO block          { $$ = new gr8::sweeping_node(LINE, $2, $4, $6, $8); }
      | tSWEEPING lval tFROM expr tTO expr tBY expr tDO block { $$ = new gr8::sweeping_node(LINE, $2, $4, $6, $8, $10); }
      ;

exprs : expr           { $$ = new cdk::sequence_node(LINE, $1); }
      | exprs ',' expr { $$ = new cdk::sequence_node(LINE, $3, $1); }
      ;

qualf : tPUBLIC { $$ = 1; }
	  | tUSE    { $$ = 2; }
	  ;

expr : tINTEGER                         { $$ = new cdk::integer_node(LINE, $1); }
     | tFLOAT                           { $$ = new cdk::double_node(LINE, $1); }
     | str                              { $$ = new cdk::string_node(LINE, $1); }
     | '(' expr ')'                     { $$ = $2; }
     | tPLUS expr %prec tUNARY          { $$ = new gr8::identity_node(LINE, $2); }
     | tMINUS expr %prec tUNARY         { $$ = new cdk::neg_node(LINE, $2); }
     | lval tINTERROG   	        { $$ = new gr8::address_of_node(LINE, $1); }
     | expr tOBJECTS  		        { $$ = new gr8::alloc_node(LINE, $1); }
     | expr tPLUS expr	                { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr tMINUS expr	                { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr tTIMES expr	                { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr tOVER expr	                { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr tMODULUS expr	        { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr tBELOW expr	                { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr tABOVE expr	                { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tEQUALS expr	        { $$ = new cdk::eq_node(LINE, $1, $3); }
     | tNOT expr                        { $$ = new cdk::not_node(LINE, $2); }
     | expr tAND expr	                { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr tOR expr                    { $$ = new cdk::or_node(LINE, $1, $3); }
     | finv                             { $$ = $1; }
     | lval %prec tINDEX                { $$ = new cdk::rvalue_node(LINE, $1); }
     | tNULL				{ $$ = new gr8::null_node(LINE); }
     | tINPUT                           { $$ = new gr8::read_node(LINE); }
     ;

str  : tSTRING                          { $$ = new std::string(*$1); }
     | str tSTRING                      { *$$ = *$1 + *$2; }
     ;

lval : tIDENTIFIER                      { $$ = new cdk::identifier_node(LINE, $1); }
     | tCELL expr tAT lval %prec tINDEX { $$ = new gr8::index_node(LINE, new cdk::rvalue_node(LINE, $4), $2); }
     | tCELL expr tAT '(' expr ')' %prec tINDEX { $$ = new gr8::index_node(LINE, $5, $2); } 
     ;

%%
