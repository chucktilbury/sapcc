#ifndef _EMITTERS_H
#define _EMITTERS_H

#include "util.h"
extern CmdLine cmd;

void init_emitters();
void emit_scanner_h();
void emit_parser_c();
void emit_parser_h();
void emit_ast_c();
void emit_ast_h();
void emit_visitor_c();
void emit_visitor_h();
void emit_all();

#endif /* _EMITTERS_H */
