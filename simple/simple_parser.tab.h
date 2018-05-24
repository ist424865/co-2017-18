#define tINTEGER 257
#define tIDENTIFIER 258
#define tSTRING 259
#define tWHILE 260
#define tIF 261
#define tPRINT 262
#define tREAD 263
#define tBEGIN 264
#define tEND 265
#define tIFX 266
#define tELSE 267
#define tGE 268
#define tLE 269
#define tEQ 270
#define tNE 271
#define tUNARY 272
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
