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
extern YYSTYPE yylval;
