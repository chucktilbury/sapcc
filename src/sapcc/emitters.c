
#include "emitters.h"

static Str* base_name;

void init_emitters() {

    TRY{
        Str* base = get_cmd_str(cmd, "ofile");
        printf("outfile base = %p, \"%s\"\n", base, raw_string(base));
    }
    EXCEPT(LIST_ERROR) {
        Str* base = get_cmd_str(cmd, "file");
        printf("using the output name: %s\n", raw_string(base));
    }
    FINAL
}

void emit_scanner_h() {

}

void emit_parser_c() {

}

void emit_parser_h() {

}

void emit_ast_c() {

}

void emit_ast_h() {

}

void emit_visitor_c() {

}

void emit_visitor_h() {

}

void emit_all() {

    emit_scanner_h();
    emit_parser_c();
    emit_parser_h();
    emit_ast_c();
    emit_ast_h();
    emit_visitor_c();
    emit_visitor_h();
}
