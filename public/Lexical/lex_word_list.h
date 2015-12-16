#ifndef LEX_WORD_LIST_H
#define LEX_WORD_LIST_H

#include "xin_structs.h"

//½ç·û
#define XBO						0x00000000
#define XBO_OPENPA				0x00000001		//	(
#define XBO_CLOSEPA				0x00000002		//	)
#define XBO_OPENBR				0x00000003		//	[
#define XBO_CLOSEBR				0x00000004		//	]
#define XBO_BEGIN				0x00000005		//	{
#define XBO_END					0x00000006		//	}
#define XBO_COMMA				0x00000007		//	,
#define XBO_SEMICOLON			0x00000008		//	;
#define XBO_COLON				0x00000009		//	:
#define XBO_POUND				0x0000000a		//	#

static key_word XBO_list[] = {
	{ XBO_OPENPA, "(" },
	{ XBO_CLOSEPA, ")" },
	{ XBO_OPENBR, "[" },
	{ XBO_CLOSEBR, "]" },
	{ XBO_BEGIN, "{" },
	{ XBO_END, "}" },
	{ XBO_COMMA, "," },
	{ XBO_SEMICOLON, ";" },
	{ XBO_COLON, ":" },
	{ XBO_POUND, "#" }
};

//ÔËËã·û
#define XOP				0x10000000		//	
#define XOP_PLUS		0x10000001		//	+
#define XOP_MINUS		0x10000002		//	-
#define XOP_STAR		0x10000003		//	*
#define XOP_DIVIDE		0x10000004		//	/
#define XOP_MOD			0x10000005		//	%
#define XOP_EQ			0x10000006		//	==
#define XOP_NEQ			0x10000007		//	!=
#define XOP_LT			0x10000008		//	<
#define XOP_LEQ			0x10000009		//	<=
#define XOP_GT			0x1000000a		//	>
#define XOP_GEQ			0x1000000b		//	>=
#define XOP_ASSIGN		0x1000000c		//	=	
#define XOP_POINTTO		0x1000000d		//	->
#define XOP_DOT			0x1000000e		//	.
#define XOP_AND			0x1000000f		//	&
#define XOP_XOR			0x10000010		//	^
#define XOP_NOTBIT		0x10000011		//	~
#define XOP_OR			0x10000012		//	|
#define XOP_INC			0x10000013		//	++
#define XOP_DEC			0x10000014		//	--
#define XOP_YES			0x10000015		//	?
#define XOP_MOVEBITL	0x10000016		//	<<
#define XOP_MOVEBITR	0x10000016		//	>>
#define XOP_NOT			0x10000017		//	!
//#define XOP_ANDADN		0x10000018		//	&&

static key_word XOP_list[] = {
	{ XOP_PLUS, "+" },
	{ XOP_MINUS, "-" },
	{ XOP_STAR, "*" },
	{ XOP_DIVIDE, "/" },
	{ XOP_MOD, "%" },
	{ XOP_EQ, "==" },
	{ XOP_NEQ, "!=" },
	{ XOP_LT, "<" },
	{ XOP_LEQ, "<=" },
	{ XOP_GT, ">" },
	{ XOP_GEQ, ">=" },
	{ XOP_ASSIGN, "=" },
	{ XOP_POINTTO, "->" },
	{ XOP_DOT, "." },
	{ XOP_AND, "&" },
	{ XOP_XOR, "^" },
	{ XOP_NOTBIT, "~" },
	{ XOP_OR, "|" },
	{ XOP_INC, "++" },
	{ XOP_DEC, "--" },
	{ XOP_YES, "?"},
	{ XOP_MOVEBITL,"<<"},
	{ XOP_MOVEBITR, ">>" }
};

//KEY WORD
#define XKEY 					0x20000000
#define XKEY_CHAR				0x20000001		//	char
#define XKEY_UNSIGNED			0x20000002 		//	unsigned
#define XKEY_SHORT				0x20000003 		//	short
#define XKEY_INT				0x20000004 		//	int
#define XKEY_FLOAT				0x20000005 		//	float
#define XKEY_VOID 				0x20000006 		//	void
#define XKEY_STRUCT 			0x20000007 		//	struct
#define XKEY_IF					0x20000008 		//	if
#define XKEY_ELSE				0x20000009 		//	else
#define XKEY_FOR				0x2000000a 		//	for
#define XKEY_CONTINUE			0x2000000b 		//	continue
#define XKEY_BREAK				0x2000000c 		//	break
#define XKEY_RETURN				0x2000000d 		//	return 
#define XKEY_SIZEOF				0x2000000e 		//	sizeof
#define XKEY_CDECL				0x2000000f 		//	__cdecl
#define XKEY_STDCALL			0x20000010 		//	__stdcall
#define XKEY_PACK				0x20000011 		//	__pack
#define XKEY_GOTO				0x20000012 		//	goto
#define XKEY_DEFINE				0x20000013 		//	define
#define XKEY_INCLUDE			0x20000014 		//	include
#define XKEY_DOT3				0x20000015		//	...
#define XKEY_SWITCH				0x20000016		//	switch
#define XKEY_CASE				0x20000017		//	case


static key_word XKEY_list[] = {
	{ XKEY_CHAR, "char" },
	{ XKEY_UNSIGNED, "unsigned" },
	{ XKEY_SHORT, "short" },
	{ XKEY_INT, "int" },
	{ XKEY_FLOAT, "float" },
	{ XKEY_VOID, "void" },
	{ XKEY_STRUCT, "struct" },
	{ XKEY_IF, "if" },
	{ XKEY_ELSE, "else" },
	{ XKEY_FOR, "for" },
	{ XKEY_CONTINUE, "continue" },
	{ XKEY_BREAK, "break" },
	{ XKEY_RETURN, "return " },
	{ XKEY_SIZEOF, "sizeof" },
	{ XKEY_CDECL, "__cdecl" },
	{ XKEY_STDCALL, "__stdcall" },
	{ XKEY_PACK, "__pack" },
	{ XKEY_GOTO, "goto" },
	{ XKEY_DEFINE, "define" },
	{ XKEY_INCLUDE, "include" },
	{ XKEY_DOT3, "..." },
	{ XKEY_SWITCH,"switch"},
	{ XKEY_CASE,"case"}
};

//constant
#define XCON		0x30000000
#define XCON_CHAR	0x30000001
#define XCON_INT	0x30000002
#define XCON_FLOAT	0x30000003
#define XCON_STRING	0x30000004

//idenfine
#define XIDEN		0x40000000

//error
#define XLEX_ERROR	0xffffffff

#endif // !LEX_WORD_LIST_H
