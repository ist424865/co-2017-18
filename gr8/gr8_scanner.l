%option c++ prefix="gr8_scanner_" outfile="gr8_scanner.cpp"
%option stack noyywrap yylineno 8bit 
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <stack>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "gr8_parser.tab.h"

namespace {
	std::stack<int> identation;
	int idt_count;
	bool isFirst;
}

#define YY_USER_INIT {\
	identation.push(0);\
}

// don't change this
#define yyerror LexerError
%}

FLOAT \.[0-9]+([eE][+-]?[0-9]+)?|[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?|[0-9]+([eE][+-]?[0-9]+)
BASE7  0[0-6]+
BASE10 0|[1-9][0-9]*

%x X_STRING X_COMMENT X_IDENTATION X_SPECIAL
%%

					   { set_debug(1); }

"!!".*$                ; /* ignore comments */

"<<"				   yy_push_state(X_COMMENT);
<X_COMMENT>"<<"		   yy_push_state(X_COMMENT);
<X_COMMENT>">>"        yy_pop_state();
<X_COMMENT>.|\n        ; /* ignore comments */

"small"                return tSMALL;
"huge"                 return tHUGE;
"news"                 return tNEWS;
"fake"                 return tFAKE;
"initially"            return tINITIALLY;
"null"				   return tNULL;

"plus"                 return tPLUS;
"minus"                return tMINUS;
"times"                return tTIMES;
"over"                 return tOVER;
"modulus"              return tMODULUS;
"not"                  return tNOT;
"and"                  return tAND;
"or"                   return tOR;
"assign"               return tASSIGN;
"to"                   return tTO;
"cell"                 return tCELL;
"at"                   return tAT;
"above"                return tABOVE;
"below"                return tBELOW;
"equals"               return tEQUALS;
"input"                return tINPUT;

"use"                  return tUSE;
"public"               return tPUBLIC;
"define"               return tDEFINE;
"procedure"            return tPROCEDURE;
"function"             return tFUNCTION;
"on"                   return tON;
"as"                   return tAS;
"do"                   return tDO;
"uses"                 return tUSES;
"for"                  return tFOR;
"return"			   return tRETURN;

"if"                   return tIF; 
"then"                 return tTHEN;
"elsif"	       	       return tELSIF;	   
"else"                 return tELSE; 
"stop"				   return tSTOP;
"read"                 return tREAD; 
"again"				   return tAGAIN;
"post"                 return tPOST;
"tweet"                return tTWEET;
"sweeping"             return tSWEEPING;
"from"                 return tFROM;
"by"                   return tBY;
"objects"			   return tOBJECTS;
"?"					   return tINTERROG;

[A-Za-z][A-Za-z0-9-]*  yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                     yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"           yy_pop_state(); return tSTRING;
<X_STRING>~			   yy_push_state(X_SPECIAL);

<X_SPECIAL>t           *yylval.s += '\t'; yy_pop_state();
<X_SPECIAL>n           *yylval.s += '\n'; yy_pop_state();
<X_SPECIAL>r           *yylval.s += '\r'; yy_pop_state();
<X_SPECIAL>\"          *yylval.s += '"'; yy_pop_state();
<X_SPECIAL>~           *yylval.s += '~'; yy_pop_state();
<X_SPECIAL>[0-6]{1,3}  if (strtol(yytext, nullptr, 7) > 255) yyerror("Overflow"); *yylval.s += (char) strtol(yytext, nullptr, 7); yy_pop_state();
<X_SPECIAL>.|\n|\0	   yyerror("Invalid use of ~");

<X_STRING>\n|\0        yyerror("Invalid character in string");
<X_STRING>.            *yylval.s += yytext;

{FLOAT}                yylval.f = strtof(yytext, nullptr); if (errno == ERANGE) yyerror("Overflow"); return tFLOAT;

{BASE7}                yylval.i = strtol(yytext, nullptr, 7); if (errno == ERANGE) yyerror("Overflow"); return tINTEGER;

{BASE10}               yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tINTEGER;

"..."\n				   ; /* continue */				   		   

[(),]       		   return *yytext;

\n				       idt_count = 0; isFirst = true; yy_push_state(X_IDENTATION); /* identation */	
<X_IDENTATION>" "	   idt_count++; /* increment */
<X_IDENTATION>\t       idt_count += 8 - (idt_count % 8); /* increment the modulus of 8 */
<X_IDENTATION>\n       yyless(yyleng - 1); yy_pop_state(); /* ignore empty line */
<X_IDENTATION>.		   {
					   		if (idt_count > identation.top()) {
					       		identation.push(idt_count); 
					   	   		yyless(yyleng - 1);
					       		yy_pop_state();
					       		return '{'; /* new identation */	
					   		}
					   		else if (idt_count == identation.top()) {
					       		yyless(yyleng - 1);
					       		yy_pop_state();/* same identation */
					       		return ';';
					   		}   
					   		else {
					   			yyless(yyleng - 1);
					   	   		if (isFirst) {
					   	   			isFirst = false;
					   	   			return ';';
					   	   		}

					   			identation.pop();
					   			if (idt_count == identation.top()) {
					   				yy_pop_state();
					   				return '}'; 
					   			}
					   			else if (idt_count < identation.top()) {
					   				return '}';
					   			}
					   			else {
					   				yyerror("Bad identation"); /* wrong identation */
					   			}
					 		} 
					   } 
					 
<<EOF>>				   {	
							if (identation.size() > 1) {
								if (isFirst) {
									isFirst = false;
									return ';';
								}	
								identation.pop();
								return '}';
							}
							else {
								yyterminate();
							}
					   }
[ \t]+                 ; /* ignore whitespaces */

.                      yyerror("Unknown character");

%%
