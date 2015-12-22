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
#define XBO_NEWLINE				0xFFFFFFFE		// \n

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
	{ XBO_POUND, "#" },
	{ XBO_NEWLINE, "\n" }
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
#define XOP_ANDADN		0x10000018		//	&&
#define XOP_OROR		0x10000019		//	||

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
	{ XOP_MOVEBITR, ">>" },
	{ XOP_ANDADN, "&&" },
	{ XOP_OROR, "||" }
};

//KEY WORD
#define XKEY				0x20000000
#define XKEY_AUTO			0x20000001		// auto
#define XKEY_BREAK 			0x20000002		// break 
#define XKEY_CASE			0x20000003		// case	
#define XKEY_CHAR			0x20000004		// char	
#define XKEY_CONST			0x20000005		// const	
#define XKEY_CONTINUE		0x20000006		// continue
#define XKEY_DEFAULT		0x20000007		// default
#define XKEY_DO				0x20000008		// do
#define XKEY_WHILE			0x20000009		// while
#define XKEY_DOUBLE			0x2000000a		// double	
#define XKEY_ELSE			0x2000000b		// else	
#define XKEY_ENUM 			0x2000000c		// enum 	
#define XKEY_EXTERN			0x2000000d		// extern	
#define XKEY_FLOAT			0x2000000e		// float
#define XKEY_FOR			0x2000000f		// for	
#define XKEY_GOTO			0x20000010		// goto	
#define XKEY_IF				0x20000011		// if¡¡
#define XKEY_INT			0x20000012		// int
#define XKEY_LONG			0x20000013		// long	
#define XKEY_REGISTER		0x20000014		// register
#define XKEY_RETURN			0x20000015		// return	
#define XKEY_SHORT			0x20000016		// short	
#define XKEY_SIGNED			0x20000017		// signed	
#define XKEY_SIZEOF			0x20000018		// sizeof	
#define XKEY_STATIC			0x20000019		// static
#define XKEY_STRUCT			0x2000001a		// struct	
#define XKEY_SWITCH			0x2000001b		// switch	
#define XKEY_TYPEDEF		0x2000001c		// typedef
#define XKEY_UNION			0x2000001d		// union	
#define XKEY_UNSIGNED		0x2000001e		// unsigned
#define XKEY_VOID			0x2000001f		// void
#define XKEY_VOLATILE		0x20000020		// volatile
#define XKEY_DOT3			0x20000021		//	...
#define XKEY_INCLUDE		0x20000022		// include 


static key_word XKEY_list[] = {
	{ XKEY_AUTO, "auto" },
	{ XKEY_BREAK, "break" },
	{ XKEY_CASE, "case" },
	{ XKEY_CHAR, "char" },
	{ XKEY_CONST, "const" },
	{ XKEY_CONTINUE, "continue" },
	{ XKEY_DEFAULT, "default" },
	{ XKEY_DO, "do" },
	{ XKEY_WHILE, "while" },
	{ XKEY_DOUBLE, "double" },
	{ XKEY_ELSE, "else" },
	{ XKEY_ENUM, "enum" },
	{ XKEY_EXTERN, "extern" },
	{ XKEY_FLOAT, "float" },
	{ XKEY_FOR, "for" },
	{ XKEY_GOTO, "goto" },
	{ XKEY_IF , "if" },
	{ XKEY_INT, "int" },
	{ XKEY_LONG, "long" },
	{ XKEY_REGISTER, "register" },
	{ XKEY_RETURN, "return" },
	{ XKEY_SHORT, "short" },
	{ XKEY_SIGNED, "signed" },
	{ XKEY_SIZEOF, "sizeof" },
	{ XKEY_STATIC, "static" },
	{ XKEY_STRUCT, "struct" },
	{ XKEY_SWITCH, "switch" },
	{ XKEY_TYPEDEF, "typedef" },
	{ XKEY_UNION, "union" },
	{ XKEY_UNSIGNED, "unsigned" },
	{ XKEY_VOID, "void" },
	{ XKEY_VOLATILE, "volatile" },
	{ XKEY_DOT3, "..." },
	{ XKEY_INCLUDE, "include"}
};

//constant
#define XCON		0x30000000
#define XCON_CHAR	0x30000001
#define XCON_INT	0x30000002
#define XCON_FLOAT	0x30000003
#define XCON_STRING	0x30000004
#define XCON_SCINUM	0x30000005
#define XCON_HEX	0x30000006

//idenfine
#define XIDEN		0x40000000

//error
#define XLEX_ERROR	0xffffffff

#endif // !LEX_WORD_LIST_H
