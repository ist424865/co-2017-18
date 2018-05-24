/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20150711

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "gr8_parser.y"
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#define PRIVATE			   0
#define PROCEDURE		   false
#define FUNCTION		   true
#line 16 "gr8_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 61 "gr8_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 56 "gr8_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tIDENTIFIER 258
#define tSTRING 259
#define tFLOAT 260
#define tSMALL 261
#define tHUGE 262
#define tNEWS 263
#define tFAKE 264
#define tINITIALLY 265
#define tNULL 266
#define tPLUS 267
#define tMINUS 268
#define tTIMES 269
#define tOVER 270
#define tMODULUS 271
#define tNOT 272
#define tAND 273
#define tOR 274
#define tASSIGN 275
#define tTO 276
#define tCELL 277
#define tAT 278
#define tABOVE 279
#define tBELOW 280
#define tEQUALS 281
#define tINPUT 282
#define tUSE 283
#define tPUBLIC 284
#define tDEFINE 285
#define tPROCEDURE 286
#define tFUNCTION 287
#define tON 288
#define tAS 289
#define tDO 290
#define tUSES 291
#define tFOR 292
#define tRETURN 293
#define tIF 294
#define tTHEN 295
#define tELSIF 296
#define tELSE 297
#define tSTOP 298
#define tREAD 299
#define tAGAIN 300
#define tPOST 301
#define tTWEET 302
#define tSWEEPING 303
#define tFROM 304
#define tBY 305
#define tINTERROG 306
#define tINDEX 307
#define tUNARY 308
#define tOBJECTS 309
#define tIFX 310
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   13,   13,    4,    4,    8,    8,    8,    8,
   12,   12,    9,    9,   10,   10,   10,   10,   10,   10,
   10,   10,   11,   11,   11,   11,   11,   11,   11,   11,
   19,   19,   21,   21,   23,   23,   22,   22,   24,   24,
   24,   24,   24,   24,   16,   16,   14,   14,   17,   17,
   17,   17,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    5,    6,    6,    6,    7,
    7,   15,   15,    1,    1,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,    2,    2,
   20,   20,   20,
};
static const YYINT yylen[] = {                            2,
    1,    0,    1,    2,    2,    1,    2,    6,    3,    7,
    1,    3,    2,    1,    4,    3,    6,    5,    3,    2,
    5,    4,    7,    6,    9,    8,    6,    5,    8,    7,
    4,    2,    1,    2,    1,    2,    1,    2,    1,    2,
    1,    2,    1,    2,    1,    2,    1,    2,    3,    3,
    4,    2,    2,    2,    3,    3,    2,    3,    2,    3,
    2,    3,    2,    1,    1,    4,    3,    5,    5,    8,
   10,    1,    3,    1,    1,    1,    1,    1,    3,    2,
    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    2,    3,    3,    1,    1,    1,    1,    1,    2,
    1,    4,    6,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   43,   37,   75,   74,    0,    0,    0,    0,
    3,    0,    6,    0,   14,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    5,   13,    4,   34,
   40,   44,   38,   36,   42,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   11,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   28,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   76,  101,   99,   77,   97,    0,
    0,    0,    0,   98,    0,    0,    0,    0,    0,   95,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   52,   47,   45,    0,   64,    0,    0,   65,
    0,    0,   24,    0,    0,    0,   27,   12,    0,    0,
   80,   81,    0,    0,    0,    0,   32,    0,  100,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   83,
    8,   82,   30,    0,   61,    0,   63,    0,    0,   59,
    0,   57,    0,    0,    0,   54,   50,   48,   49,   46,
    0,   53,    0,    0,   23,    0,   10,    0,    0,    0,
   79,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   62,    0,   60,   58,   56,   55,    0,   51,
   26,    0,   29,    0,  102,   31,    0,   66,    0,    0,
   25,    0,    0,    0,    0,  103,   69,   68,    0,    0,
    0,   70,    0,    0,   71,
};
static const YYINT yydgoto[] = {                          9,
   53,   88,  104,   11,  106,  147,  107,   54,   13,   14,
   15,   55,   16,  108,  125,  109,  110,  111,   90,   91,
   17,   18,   19,   56,
};
static const YYINT yysindex[] = {                       -74,
    0,    0,    0,    0,    0,    0,  -66, -228,    0,  -61,
    0,    5,    0,   12,    0,  -74, -219, -201, -212, -238,
 -185,   24, -209, -210, -174, -221,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   48, -168, -203, -158, -173,
 -145,  399, -189,   76, -119, -124, -149,  399,   20, -161,
 -113, -156, -110,    0,  102, -109,  399, -117, -134,  737,
  399,  -32,  324,    0,  399,   20, -152,  399,   20, -100,
  399,  102,  737,  399,    0,    0,    0,    0,    0,  737,
  737,  737,  737,    0,  737,  -98,  737,  -96,   35,    0,
 -141,  102,   20,  737,  737,  709,  737,  -58,  -52,  737,
  737, -230,    0,    0,    0,  112,    0,  553,  498,    0,
  363,  -31,    0,  399,   20,  -30,    0,    0,   50,  102,
    0,    0,  876, -175,  -42,  858,    0,   66,    0,  737,
  737,  737,  737,  737,  737,  737,  737,  737,  737,    0,
    0,    0,    0, -101,    0,  535,    0,  244,  122,    0,
  124,    0,  691,  763, -143,    0,    0,    0,    0,    0,
  601,    0,   20,  -29,    0,   20,    0,  -11,  -73,  737,
    0, -235, -235, -125, -125, -125,  876,  431, -159, -159,
  876, -230,    0,   20,    0,    0,    0,    0,  737,    0,
    0,   20,    0,  737,    0,    0,  858,    0, -229,  800,
    0,   81,  737,   20,  737,    0,    0,    0, -150,   20,
  737,    0,  843,   20,    0,
};
static const YYINT yyrindex[] = {                       191,
 -205, -204,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  193,    0,    0,    0,    0,
    0,    0,    0,  135,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -34,    0,    0,    0,    0,
    0,    0,  147,  -33,    0,    0,  155,    0,    0,    0,
    0,    0,    0,    0,  156,    0,    0,    0,  160,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  162,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -41,    0,    0,
    2,  164,    0,    0,  105,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  165,
    0,    0,  172,    0,    0,  -40,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  202,  254,  103,  133,  163,  413,  449,  284,  376,
  443,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -39,    0,  653,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   16,    0,  -89,   -8,    0,   31,    0,    6,    0,    0,
    0,  -17,    0,  127,    0,    0,  -28,  965,    0,  -93,
    0,    0,    0,   17,
};
#define YYTABLESIZE 1185
static const YYINT yytable[] = {                         78,
  150,  170,   78,   72,   73,   12,  152,   29,  155,    7,
    9,   71,   71,   71,   71,   10,   20,   78,  158,   36,
   64,   12,   22,   23,    7,    9,   26,   76,  194,   24,
   62,   10,   20,  132,  133,  134,   44,  113,   40,   72,
  117,   30,   96,   92,   31,   96,   83,  112,   37,   34,
  116,   35,   39,   41,  105,   33,  120,   35,   33,   35,
   96,   32,   33,   27,  143,   45,  203,  204,   12,   70,
   28,  158,   38,  140,  195,  141,  118,   41,   10,   20,
   42,   39,   41,   43,   48,   49,  165,   46,  198,   47,
  167,  130,  131,  132,  133,  134,  164,  135,  136,   50,
  160,   57,  168,  137,  138,  139,  171,  130,  131,  132,
  133,  134,   52,   51,   12,   58,  130,  131,  132,  133,
  134,  206,  135,  136,   10,   20,   65,   66,  137,  138,
  139,   68,   69,  140,  191,  114,  115,  193,   59,  210,
   60,   61,   63,   86,   67,   71,   86,   73,   36,  140,
    1,    2,    3,    4,  211,  199,   74,   44,  140,  127,
  189,   86,  129,  201,  142,  130,  131,  132,  133,  134,
  156,  135,  136,   87,  182,  208,   87,  137,  138,  139,
  185,  212,  186,  140,  196,  215,    1,    2,    3,    4,
    2,   87,    1,   20,    1,    2,    3,    4,  149,    1,
    2,    3,    4,   88,  151,   16,   88,  140,    5,    6,
    7,    8,   92,   19,   22,   92,    5,    6,   15,   21,
   18,   88,   21,   17,   25,   78,   78,   78,   78,   78,
   92,   78,   78,  207,   78,  161,   78,   78,   78,   78,
    0,    0,   84,    0,    0,   84,   76,    0,   78,  169,
   78,   72,   73,   78,    7,    9,   93,  163,  166,  192,
   84,    0,    0,   78,    0,   83,    0,   78,   96,   96,
   96,   96,   96,    0,   96,   96,    0,   96,    0,   96,
   96,   96,   96,    0,    1,    2,    3,    4,    0,    0,
    0,   96,    0,   96,   85,    0,   96,   85,    0,    0,
    0,  130,  131,  132,  133,  134,   96,  135,  136,   39,
   96,    0,   85,  137,  138,  139,  130,  131,  132,  133,
  134,    0,  135,  136,   90,    0,    0,   90,  137,  138,
  139,    0,  130,  131,  132,  133,  134,    0,  135,  136,
    0,    0,   90,  140,  137,  138,  139,  130,  131,  132,
  133,  134,    0,  135,  136,    0,    0,    0,  140,  137,
  138,  139,    0,   87,    0,   75,   75,   75,   75,   86,
   86,   86,   86,   86,  140,   86,   86,    0,   86,    0,
   86,   86,   86,   86,    0,    0,    0,    0,    0,  140,
   75,    0,   86,    0,   86,    0,    0,   86,    0,   87,
   87,   87,   87,   87,    0,   87,   87,   86,   87,    0,
   87,   87,   87,   87,    0,    0,   89,    0,    0,   89,
    0,  162,   87,    0,   87,    0,    0,   87,    0,   88,
   88,   88,   88,   88,   89,   88,   88,   87,   88,    0,
   88,   88,   88,   88,   92,   92,   63,   92,  103,   92,
    0,    0,   88,   93,   88,    0,   93,   88,    0,    0,
    0,   92,    0,   92,    0,    0,   92,   88,   84,   84,
    0,   93,    0,    0,   84,   84,   92,   84,    0,   84,
   84,   84,   84,   91,    0,    0,   91,    0,    0,   94,
    0,   84,   94,   84,    0,    0,   84,    0,    0,    0,
    0,   91,    0,    0,    0,    0,   84,   94,    0,    0,
  130,  131,  132,  133,  134,    0,  135,  136,    0,    0,
   85,   85,  137,  138,  139,    0,   85,   85,    0,   85,
    0,   85,   85,   85,   85,    0,    0,   87,  184,    0,
    0,    0,    0,   85,    0,   85,    0,    0,   85,    0,
    0,    0,  140,    0,    0,    0,   90,   90,   85,   90,
    0,   90,   90,   90,   90,    0,    0,    0,    0,    0,
    0,    0,    0,   90,    0,   90,    0,    0,   90,    0,
   75,   76,   77,   78,    1,    2,    3,    4,   90,   79,
   80,   81,   87,  183,    0,   82,    0,    0,   94,    0,
   83,    0,    0,    0,    0,   84,   95,    6,    7,    8,
    0,    0,    0,   86,    0,    0,   96,   97,    0,    0,
   63,   98,  159,   99,  100,  101,  102,    0,    0,  130,
  131,  132,  133,  134,    0,  135,  136,    0,    0,    0,
   87,  137,  138,  139,    0,    0,    0,    0,   89,   89,
    0,   89,    0,   89,   89,   89,   89,    0,    0,    1,
    2,    3,    4,    0,    0,   89,    0,   89,    0,    0,
   89,  140,    0,    0,    0,   63,    0,  157,    0,    0,
   89,    5,    6,    0,    0,   93,   93,    0,   93,    0,
   93,    0,   67,    0,    0,    0,    0,  130,  131,  132,
  133,  134,   93,  135,   93,    0,    0,   93,    0,  137,
  138,  139,    0,    0,    0,   91,   91,   93,   91,    0,
   91,    0,   94,   63,   94,  190,   94,    0,    0,    0,
    0,    0,   91,    0,   91,    0,    0,   91,   94,  140,
   94,    0,    0,   94,    0,    0,    0,   91,   87,  187,
    0,    0,    0,   94,   75,   76,   77,   78,    1,    2,
    3,    4,    0,   79,   80,   81,    0,  145,    0,   82,
    0,    0,   94,    0,   83,   67,   87,   67,    0,   84,
   95,    6,    7,    8,    0,    0,    0,   86,    0,    0,
   96,   97,    0,    0,    0,   98,    0,   99,  100,  101,
  102,  130,  131,  132,  133,  134,    0,  135,  136,   75,
   76,   77,   78,  137,  138,  139,    0,    0,   79,   80,
   81,  188,    0,    0,   82,    0,    0,   94,    0,   83,
    0,    0,    0,    0,   84,   85,    0,    0,    0,    0,
    0,    0,   86,  140,    0,   96,   97,    0,    0,    0,
   98,    0,   99,  100,  101,  102,    0,   75,   76,   77,
   78,    0,    0,    0,    0,    0,   79,   80,   81,    0,
    0,    0,   82,    0,    0,   94,    0,   83,    0,    0,
    0,    0,   84,   85,    0,    0,    0,    0,    0,    0,
   86,    0,    0,   96,   97,    0,    0,    0,   98,    0,
   99,  100,  101,  102,    0,    0,    0,    0,    0,   67,
   67,   67,   67,    0,    0,    0,    0,    0,   67,   67,
   67,    0,    0,    0,   67,    0,    0,   67,    0,   67,
    0,    0,    0,    0,   67,   67,    0,    0,    0,    0,
    0,    0,   67,    0,    0,   67,   67,    0,    0,    0,
   67,    0,   67,   67,   67,   67,    0,  130,  131,  132,
  133,  134,    0,  135,  136,   75,   76,   77,   78,  137,
  138,  139,    0,    0,   79,   80,   81,    0,    0,    0,
   82,    0,    0,    0,    0,   83,    0,    0,    0,    0,
   84,   85,    0,   75,   76,   77,   78,    0,   86,  140,
    0,    0,   79,   80,   81,    0,    0,    0,   82,    0,
    0,    0,    0,   83,    0,    0,    0,    0,   84,   85,
    0,    0,    0,    0,   89,    0,   86,    0,    0,  130,
  131,  132,  133,  134,    0,  135,  136,  119,    0,    0,
    0,  137,  138,  139,  121,  122,  123,  124,    0,  126,
    0,  128,    0,    0,    0,    0,    0,    0,  144,  126,
  146,  148,    0,    0,  153,  154,  130,  131,  132,  133,
  134,  140,  135,  136,    0,  205,    0,    0,  137,  138,
  139,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  172,  173,  174,  175,  176,  177,
  178,  179,  180,  181,    0,    0,    0,    0,  140,  130,
  131,  132,  133,  134,    0,  135,  136,    0,    0,    0,
    0,  137,  138,  139,  130,  131,  132,  133,  134,    0,
  135,  136,  214,    0,  197,    0,  137,  138,  139,    0,
    0,    0,  130,  131,  132,  133,  134,    0,    0,    0,
    0,  140,    0,  200,  137,  138,  139,    0,  202,    0,
    0,    0,    0,    0,    0,    0,  140,  148,    0,  209,
    0,    0,    0,    0,    0,  213,    0,    0,    0,    0,
    0,    0,    0,    0,  140,
};
static const YYINT yycheck[] = {                         41,
   59,   44,   44,   44,   44,    0,   59,   16,  102,   44,
   44,   44,   44,   44,   44,    0,    0,   59,  108,  258,
   49,   16,    7,    7,   59,   59,   10,  258,   40,  258,
   48,   16,   16,  269,  270,  271,  258,   66,   22,   57,
   69,  261,   41,   61,  264,   44,  277,   65,  287,  262,
   68,  264,  258,  258,   63,  261,   74,  262,  264,  264,
   59,  263,  264,   59,   93,  287,  296,  297,   63,   53,
   59,  161,  258,  309,  168,   41,   71,  287,   63,   63,
  291,  287,  287,  258,  288,  289,  115,   40,  182,  258,
   41,  267,  268,  269,  270,  271,  114,  273,  274,  258,
  109,  291,  278,  279,  280,  281,   41,  267,  268,  269,
  270,  271,  258,  287,  109,   40,  267,  268,  269,  270,
  271,   41,  273,  274,  109,  109,  288,  289,  279,  280,
  281,  288,  289,  309,  163,  288,  289,  166,  258,  290,
  265,  291,  123,   41,  258,   44,   44,  265,  258,  309,
  261,  262,  263,  264,  305,  184,  291,  258,  309,  258,
  304,   59,  259,  192,  306,  267,  268,  269,  270,  271,
   59,  273,  274,   41,  276,  204,   44,  279,  280,  281,
   59,  210,   59,  309,  258,  214,  261,  262,  263,  264,
    0,   59,    0,   59,  261,  262,  263,  264,  257,  261,
  262,  263,  264,   41,  257,   59,   44,  309,  283,  284,
  285,  286,   41,   59,   59,   44,  283,  284,   59,  286,
   59,   59,   59,   59,  286,  267,  268,  269,  270,  271,
   59,  273,  274,  203,  276,  109,  278,  279,  280,  281,
   -1,   -1,   41,   -1,   -1,   44,  258,   -1,  290,  292,
  292,  292,  292,  295,  289,  289,  289,  289,  289,  289,
   59,   -1,   -1,  305,   -1,  277,   -1,  309,  267,  268,
  269,  270,  271,   -1,  273,  274,   -1,  276,   -1,  278,
  279,  280,  281,   -1,  261,  262,  263,  264,   -1,   -1,
   -1,  290,   -1,  292,   41,   -1,  295,   44,   -1,   -1,
   -1,  267,  268,  269,  270,  271,  305,  273,  274,  286,
  309,   -1,   59,  279,  280,  281,  267,  268,  269,  270,
  271,   -1,  273,  274,   41,   -1,   -1,   44,  279,  280,
  281,   -1,  267,  268,  269,  270,  271,   -1,  273,  274,
   -1,   -1,   59,  309,  279,  280,  281,  267,  268,  269,
  270,  271,   -1,  273,  274,   -1,   -1,   -1,  309,  279,
  280,  281,   -1,   40,   -1,  261,  262,  263,  264,  267,
  268,  269,  270,  271,  309,  273,  274,   -1,  276,   -1,
  278,  279,  280,  281,   -1,   -1,   -1,   -1,   -1,  309,
  286,   -1,  290,   -1,  292,   -1,   -1,  295,   -1,  267,
  268,  269,  270,  271,   -1,  273,  274,  305,  276,   -1,
  278,  279,  280,  281,   -1,   -1,   41,   -1,   -1,   44,
   -1,   59,  290,   -1,  292,   -1,   -1,  295,   -1,  267,
  268,  269,  270,  271,   59,  273,  274,  305,  276,   -1,
  278,  279,  280,  281,  273,  274,  123,  276,  125,  278,
   -1,   -1,  290,   41,  292,   -1,   44,  295,   -1,   -1,
   -1,  290,   -1,  292,   -1,   -1,  295,  305,  267,  268,
   -1,   59,   -1,   -1,  273,  274,  305,  276,   -1,  278,
  279,  280,  281,   41,   -1,   -1,   44,   -1,   -1,   41,
   -1,  290,   44,  292,   -1,   -1,  295,   -1,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,  305,   59,   -1,   -1,
  267,  268,  269,  270,  271,   -1,  273,  274,   -1,   -1,
  267,  268,  279,  280,  281,   -1,  273,  274,   -1,  276,
   -1,  278,  279,  280,  281,   -1,   -1,   40,  295,   -1,
   -1,   -1,   -1,  290,   -1,  292,   -1,   -1,  295,   -1,
   -1,   -1,  309,   -1,   -1,   -1,  273,  274,  305,  276,
   -1,  278,  279,  280,  281,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  290,   -1,  292,   -1,   -1,  295,   -1,
  257,  258,  259,  260,  261,  262,  263,  264,  305,  266,
  267,  268,   40,   59,   -1,  272,   -1,   -1,  275,   -1,
  277,   -1,   -1,   -1,   -1,  282,  283,  284,  285,  286,
   -1,   -1,   -1,  290,   -1,   -1,  293,  294,   -1,   -1,
  123,  298,  125,  300,  301,  302,  303,   -1,   -1,  267,
  268,  269,  270,  271,   -1,  273,  274,   -1,   -1,   -1,
   40,  279,  280,  281,   -1,   -1,   -1,   -1,  273,  274,
   -1,  276,   -1,  278,  279,  280,  281,   -1,   -1,  261,
  262,  263,  264,   -1,   -1,  290,   -1,  292,   -1,   -1,
  295,  309,   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,
  305,  283,  284,   -1,   -1,  273,  274,   -1,  276,   -1,
  278,   -1,   40,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,  271,  290,  273,  292,   -1,   -1,  295,   -1,  279,
  280,  281,   -1,   -1,   -1,  273,  274,  305,  276,   -1,
  278,   -1,  274,  123,  276,  125,  278,   -1,   -1,   -1,
   -1,   -1,  290,   -1,  292,   -1,   -1,  295,  290,  309,
  292,   -1,   -1,  295,   -1,   -1,   -1,  305,   40,   59,
   -1,   -1,   -1,  305,  257,  258,  259,  260,  261,  262,
  263,  264,   -1,  266,  267,  268,   -1,   59,   -1,  272,
   -1,   -1,  275,   -1,  277,  123,   40,  125,   -1,  282,
  283,  284,  285,  286,   -1,   -1,   -1,  290,   -1,   -1,
  293,  294,   -1,   -1,   -1,  298,   -1,  300,  301,  302,
  303,  267,  268,  269,  270,  271,   -1,  273,  274,  257,
  258,  259,  260,  279,  280,  281,   -1,   -1,  266,  267,
  268,   59,   -1,   -1,  272,   -1,   -1,  275,   -1,  277,
   -1,   -1,   -1,   -1,  282,  283,   -1,   -1,   -1,   -1,
   -1,   -1,  290,  309,   -1,  293,  294,   -1,   -1,   -1,
  298,   -1,  300,  301,  302,  303,   -1,  257,  258,  259,
  260,   -1,   -1,   -1,   -1,   -1,  266,  267,  268,   -1,
   -1,   -1,  272,   -1,   -1,  275,   -1,  277,   -1,   -1,
   -1,   -1,  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,
  290,   -1,   -1,  293,  294,   -1,   -1,   -1,  298,   -1,
  300,  301,  302,  303,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,   -1,   -1,   -1,   -1,   -1,  266,  267,
  268,   -1,   -1,   -1,  272,   -1,   -1,  275,   -1,  277,
   -1,   -1,   -1,   -1,  282,  283,   -1,   -1,   -1,   -1,
   -1,   -1,  290,   -1,   -1,  293,  294,   -1,   -1,   -1,
  298,   -1,  300,  301,  302,  303,   -1,  267,  268,  269,
  270,  271,   -1,  273,  274,  257,  258,  259,  260,  279,
  280,  281,   -1,   -1,  266,  267,  268,   -1,   -1,   -1,
  272,   -1,   -1,   -1,   -1,  277,   -1,   -1,   -1,   -1,
  282,  283,   -1,  257,  258,  259,  260,   -1,  290,  309,
   -1,   -1,  266,  267,  268,   -1,   -1,   -1,  272,   -1,
   -1,   -1,   -1,  277,   -1,   -1,   -1,   -1,  282,  283,
   -1,   -1,   -1,   -1,   60,   -1,  290,   -1,   -1,  267,
  268,  269,  270,  271,   -1,  273,  274,   73,   -1,   -1,
   -1,  279,  280,  281,   80,   81,   82,   83,   -1,   85,
   -1,   87,   -1,   -1,   -1,   -1,   -1,   -1,   94,   95,
   96,   97,   -1,   -1,  100,  101,  267,  268,  269,  270,
  271,  309,  273,  274,   -1,  276,   -1,   -1,  279,  280,
  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  130,  131,  132,  133,  134,  135,
  136,  137,  138,  139,   -1,   -1,   -1,   -1,  309,  267,
  268,  269,  270,  271,   -1,  273,  274,   -1,   -1,   -1,
   -1,  279,  280,  281,  267,  268,  269,  270,  271,   -1,
  273,  274,  290,   -1,  170,   -1,  279,  280,  281,   -1,
   -1,   -1,  267,  268,  269,  270,  271,   -1,   -1,   -1,
   -1,  309,   -1,  189,  279,  280,  281,   -1,  194,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  309,  203,   -1,  205,
   -1,   -1,   -1,   -1,   -1,  211,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  309,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 310
#define YYUNDFTOKEN 337
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"tINTEGER","tIDENTIFIER","tSTRING","tFLOAT","tSMALL","tHUGE","tNEWS","tFAKE",
"tINITIALLY","tNULL","tPLUS","tMINUS","tTIMES","tOVER","tMODULUS","tNOT","tAND",
"tOR","tASSIGN","tTO","tCELL","tAT","tABOVE","tBELOW","tEQUALS","tINPUT","tUSE",
"tPUBLIC","tDEFINE","tPROCEDURE","tFUNCTION","tON","tAS","tDO","tUSES","tFOR",
"tRETURN","tIF","tTHEN","tELSIF","tELSE","tSTOP","tREAD","tAGAIN","tPOST",
"tTWEET","tSWEEPING","tFROM","tBY","tINTERROG","tINDEX","tUNARY","tOBJECTS",
"tIFX",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file : listd",
"file :",
"listd : decl",
"listd : listd decl",
"decl : var ';'",
"decl : funct",
"var : type tIDENTIFIER",
"var : type tIDENTIFIER '(' tINITIALLY expr ')'",
"var : qualf type tIDENTIFIER",
"var : qualf type tIDENTIFIER '(' tINITIALLY expr ')'",
"vars : var",
"vars : vars ',' var",
"funct : fdecl ';'",
"funct : fdef",
"fdecl : qualf type tFUNCTION tIDENTIFIER",
"fdecl : qualf tPROCEDURE tIDENTIFIER",
"fdecl : qualf type tFUNCTION tIDENTIFIER tUSES vars",
"fdecl : qualf tPROCEDURE tIDENTIFIER tUSES vars",
"fdecl : type tFUNCTION tIDENTIFIER",
"fdecl : tPROCEDURE tIDENTIFIER",
"fdecl : type tFUNCTION tIDENTIFIER tUSES vars",
"fdecl : tPROCEDURE tIDENTIFIER tUSES vars",
"fdef : tDEFINE qualf type tFUNCTION tIDENTIFIER tAS block",
"fdef : tDEFINE qualf tPROCEDURE tIDENTIFIER tAS block",
"fdef : tDEFINE qualf type tFUNCTION tIDENTIFIER tON vars tAS block",
"fdef : tDEFINE qualf tPROCEDURE tIDENTIFIER tON vars tAS block",
"fdef : tDEFINE type tFUNCTION tIDENTIFIER tAS block",
"fdef : tDEFINE tPROCEDURE tIDENTIFIER tAS block",
"fdef : tDEFINE type tFUNCTION tIDENTIFIER tON vars tAS block",
"fdef : tDEFINE tPROCEDURE tIDENTIFIER tON vars tAS block",
"finv : tUSE exprs tFOR tIDENTIFIER",
"finv : tDO tIDENTIFIER",
"lists : tSMALL",
"lists : lists tSMALL",
"listh : tHUGE",
"listh : listh tHUGE",
"listf : tFAKE",
"listf : listf tFAKE",
"type : tSMALL",
"type : lists tFAKE",
"type : tHUGE",
"type : listh tFAKE",
"type : tNEWS",
"type : listf tNEWS",
"decls : decl",
"decls : decls decl",
"listi : stmt",
"listi : listi stmt",
"block : '{' decls '}'",
"block : '{' listi '}'",
"block : '{' decls listi '}'",
"block : '{' '}'",
"stmt : expr ';'",
"stmt : asgn ';'",
"stmt : tTWEET expr ';'",
"stmt : tPOST expr ';'",
"stmt : tAGAIN ';'",
"stmt : tAGAIN tINTEGER ';'",
"stmt : tSTOP ';'",
"stmt : tSTOP tINTEGER ';'",
"stmt : tRETURN ';'",
"stmt : tRETURN expr ';'",
"stmt : tIF condt",
"stmt : iter",
"stmt : block",
"asgn : tASSIGN expr tTO lval",
"condt : expr tTHEN block",
"condt : expr tTHEN block tELSE block",
"condt : expr tTHEN block tELSIF condt",
"iter : tSWEEPING lval tFROM expr tTO expr tDO block",
"iter : tSWEEPING lval tFROM expr tTO expr tBY expr tDO block",
"exprs : expr",
"exprs : exprs ',' expr",
"qualf : tPUBLIC",
"qualf : tUSE",
"expr : tINTEGER",
"expr : tFLOAT",
"expr : str",
"expr : '(' expr ')'",
"expr : tPLUS expr",
"expr : tMINUS expr",
"expr : lval tINTERROG",
"expr : expr tOBJECTS",
"expr : expr tPLUS expr",
"expr : expr tMINUS expr",
"expr : expr tTIMES expr",
"expr : expr tOVER expr",
"expr : expr tMODULUS expr",
"expr : expr tBELOW expr",
"expr : expr tABOVE expr",
"expr : expr tEQUALS expr",
"expr : tNOT expr",
"expr : expr tAND expr",
"expr : expr tOR expr",
"expr : finv",
"expr : lval",
"expr : tNULL",
"expr : tINPUT",
"str : tSTRING",
"str : str tSTRING",
"lval : tIDENTIFIER",
"lval : tCELL expr tAT lval",
"lval : tCELL expr tAT '(' expr ')'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 65 "gr8_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence); }
break;
case 2:
#line 66 "gr8_parser.y"
	{ compiler->ast(new cdk::nil_node(LINE)); }
break;
case 3:
#line 69 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 4:
#line 70 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 5:
#line 73 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[-1].typed; }
break;
case 6:
#line 74 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].typed; }
break;
case 7:
#line 77 "gr8_parser.y"
	{ yyval.typed = new gr8::variable_declaration_node(LINE, PRIVATE, yystack.l_mark[0].s); yyval.typed->type(yystack.l_mark[-1].type); }
break;
case 8:
#line 78 "gr8_parser.y"
	{ yyval.typed = new gr8::variable_declaration_node(LINE, PRIVATE, yystack.l_mark[-4].s, yystack.l_mark[-1].expression); yyval.typed->type(yystack.l_mark[-5].type); }
break;
case 9:
#line 79 "gr8_parser.y"
	{ yyval.typed = new gr8::variable_declaration_node(LINE, yystack.l_mark[-2].i, yystack.l_mark[0].s); yyval.typed->type(yystack.l_mark[-1].type); }
break;
case 10:
#line 80 "gr8_parser.y"
	{ yyval.typed = new gr8::variable_declaration_node(LINE, yystack.l_mark[-6].i, yystack.l_mark[-4].s, yystack.l_mark[-1].expression); yyval.typed->type(yystack.l_mark[-5].type); }
break;
case 11:
#line 83 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typed); }
break;
case 12:
#line 84 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typed, yystack.l_mark[-2].sequence); }
break;
case 13:
#line 87 "gr8_parser.y"
	{ yyval.typed = yystack.l_mark[-1].typed; }
break;
case 14:
#line 88 "gr8_parser.y"
	{ yyval.typed = yystack.l_mark[0].typed; }
break;
case 15:
#line 91 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, yystack.l_mark[-3].i, yystack.l_mark[0].s); yyval.typed->type(yystack.l_mark[-2].type); }
break;
case 16:
#line 92 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, yystack.l_mark[-2].i, yystack.l_mark[0].s); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 17:
#line 93 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, yystack.l_mark[-5].i, yystack.l_mark[-2].s, yystack.l_mark[0].sequence); yyval.typed->type(yystack.l_mark[-4].type); }
break;
case 18:
#line 94 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, yystack.l_mark[-4].i, yystack.l_mark[-2].s, yystack.l_mark[0].sequence); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 19:
#line 95 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, PRIVATE, yystack.l_mark[0].s); yyval.typed->type(yystack.l_mark[-2].type); }
break;
case 20:
#line 96 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, PRIVATE, yystack.l_mark[0].s); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 21:
#line 97 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, PRIVATE, yystack.l_mark[-2].s, yystack.l_mark[0].sequence); yyval.typed->type(yystack.l_mark[-4].type); }
break;
case 22:
#line 98 "gr8_parser.y"
	{ yyval.typed = new gr8::function_declaration_node(LINE, PRIVATE, yystack.l_mark[-2].s, yystack.l_mark[0].sequence); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 23:
#line 101 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, yystack.l_mark[-5].i, yystack.l_mark[-2].s, yystack.l_mark[0].block); yyval.typed->type(yystack.l_mark[-4].type); }
break;
case 24:
#line 102 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, yystack.l_mark[-4].i, yystack.l_mark[-2].s, yystack.l_mark[0].block); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 25:
#line 103 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, yystack.l_mark[-7].i, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block); yyval.typed->type(yystack.l_mark[-6].type); }
break;
case 26:
#line 104 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, yystack.l_mark[-6].i, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 27:
#line 105 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, PRIVATE, yystack.l_mark[-2].s, yystack.l_mark[0].block); yyval.typed->type(yystack.l_mark[-4].type); }
break;
case 28:
#line 106 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, PRIVATE, yystack.l_mark[-2].s, yystack.l_mark[0].block); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 29:
#line 107 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, PRIVATE, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block); yyval.typed->type(yystack.l_mark[-6].type); }
break;
case 30:
#line 108 "gr8_parser.y"
	{ yyval.typed = new gr8::function_definition_node(LINE, PRIVATE, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block); yyval.typed->type(new basic_type(4, basic_type::TYPE_VOID)); }
break;
case 31:
#line 111 "gr8_parser.y"
	{ yyval.expression = new gr8::function_invocation_node(LINE, yystack.l_mark[0].s ,yystack.l_mark[-2].sequence); }
break;
case 32:
#line 112 "gr8_parser.y"
	{ yyval.expression = new gr8::function_invocation_node(LINE, yystack.l_mark[0].s); }
break;
case 33:
#line 115 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = new basic_type(4, basic_type::TYPE_INT); }
break;
case 34:
#line 116 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[-1].type; }
break;
case 35:
#line 119 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 36:
#line 120 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[-1].type;}
break;
case 37:
#line 123 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 38:
#line 124 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[-1].type; }
break;
case 39:
#line 127 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_INT); }
break;
case 40:
#line 128 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type; }
break;
case 41:
#line 129 "gr8_parser.y"
	{ yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE); }
break;
case 42:
#line 130 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type; }
break;
case 43:
#line 131 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_STRING); }
break;
case 44:
#line 132 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type; }
break;
case 45:
#line 135 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 46:
#line 136 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 47:
#line 139 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 48:
#line 140 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 49:
#line 143 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-1].sequence, nullptr); }
break;
case 50:
#line 144 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, nullptr, yystack.l_mark[-1].sequence); }
break;
case 51:
#line 145 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 52:
#line 146 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, nullptr, nullptr); }
break;
case 53:
#line 149 "gr8_parser.y"
	{ yyval.node = new gr8::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 54:
#line 150 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 55:
#line 151 "gr8_parser.y"
	{ yyval.node = new gr8::tweet_node(LINE, yystack.l_mark[-1].expression); }
break;
case 56:
#line 152 "gr8_parser.y"
	{ yyval.node = new gr8::post_node(LINE, yystack.l_mark[-1].expression); }
break;
case 57:
#line 153 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE); }
break;
case 58:
#line 154 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE, yystack.l_mark[-1].i); }
break;
case 59:
#line 155 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE); }
break;
case 60:
#line 156 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE, yystack.l_mark[-1].i); }
break;
case 61:
#line 157 "gr8_parser.y"
	{ yyval.node = new gr8::return_node(LINE, nullptr); }
break;
case 62:
#line 158 "gr8_parser.y"
	{ yyval.node = new gr8::return_node(LINE, yystack.l_mark[-1].expression); }
break;
case 63:
#line 159 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 64:
#line 160 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 65:
#line 161 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].block; }
break;
case 66:
#line 164 "gr8_parser.y"
	{ yyval.node = new cdk::assignment_node(LINE, yystack.l_mark[0].lvalue, yystack.l_mark[-2].expression); }
break;
case 67:
#line 167 "gr8_parser.y"
	{ yyval.node = new gr8::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].block); }
break;
case 68:
#line 168 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].block, yystack.l_mark[0].block); }
break;
case 69:
#line 169 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].block, yystack.l_mark[0].node); }
break;
case 70:
#line 172 "gr8_parser.y"
	{ yyval.node = new gr8::sweeping_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].block); }
break;
case 71:
#line 173 "gr8_parser.y"
	{ yyval.node = new gr8::sweeping_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].block); }
break;
case 72:
#line 176 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 73:
#line 177 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 74:
#line 180 "gr8_parser.y"
	{ yyval.i = 1; }
break;
case 75:
#line 181 "gr8_parser.y"
	{ yyval.i = 2; }
break;
case 76:
#line 184 "gr8_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 77:
#line 185 "gr8_parser.y"
	{ yyval.expression = new cdk::double_node(LINE, yystack.l_mark[0].f); }
break;
case 78:
#line 186 "gr8_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 79:
#line 187 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 80:
#line 188 "gr8_parser.y"
	{ yyval.expression = new gr8::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 81:
#line 189 "gr8_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 82:
#line 190 "gr8_parser.y"
	{ yyval.expression = new gr8::address_of_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 83:
#line 191 "gr8_parser.y"
	{ yyval.expression = new gr8::alloc_node(LINE, yystack.l_mark[-1].expression); }
break;
case 84:
#line 192 "gr8_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 85:
#line 193 "gr8_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 86:
#line 194 "gr8_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 87:
#line 195 "gr8_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 88:
#line 196 "gr8_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 89:
#line 197 "gr8_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 90:
#line 198 "gr8_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 91:
#line 199 "gr8_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 92:
#line 200 "gr8_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 93:
#line 201 "gr8_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 94:
#line 202 "gr8_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 95:
#line 203 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 96:
#line 204 "gr8_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 97:
#line 205 "gr8_parser.y"
	{ yyval.expression = new gr8::null_node(LINE); }
break;
case 98:
#line 206 "gr8_parser.y"
	{ yyval.expression = new gr8::read_node(LINE); }
break;
case 99:
#line 209 "gr8_parser.y"
	{ yyval.s = new std::string(*yystack.l_mark[0].s); }
break;
case 100:
#line 210 "gr8_parser.y"
	{ *yyval.s = *yystack.l_mark[-1].s + *yystack.l_mark[0].s; }
break;
case 101:
#line 213 "gr8_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); }
break;
case 102:
#line 214 "gr8_parser.y"
	{ yyval.lvalue = new gr8::index_node(LINE, new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue), yystack.l_mark[-2].expression); }
break;
case 103:
#line 215 "gr8_parser.y"
	{ yyval.lvalue = new gr8::index_node(LINE, yystack.l_mark[-1].expression, yystack.l_mark[-4].expression); }
break;
#line 1276 "gr8_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
