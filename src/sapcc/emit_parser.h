#ifndef _EMIT_PARSER_H
#define _EMIT_PARSER_H

const char* errors_string =
"\n"
"static int errors = 0;\n"
"static int warnings = 0;\n"
"#include <stdarg.h>\n"
"\n"
"static void syntax_error(const char* fmt, ...) {\n"
"\n"
"    va_list args;\n"
"\n"
"    if(get_line_no() > 0)\n"
"        fprintf(stderr, \"Syntax Error: %%s:%%d:%%d \", get_fname(), get_line_no(), get_col_no());\n"
"    else\n"
"        fprintf(stderr, \"Syntax Error: \");\n"
"\n"
"    va_start(args, fmt);\n"
"    vfprintf(stderr, fmt, args);\n"
"    va_end(args);\n"
"    fprintf(stderr, \"\\n\");\n"
"\n"
"    errors++;\n"
"}\n"
"\n"
"static void syntax_error_token(Token* tok, const char* fmt, ...) {\n"
"\n"
"    va_list args;\n"
"\n"
"    fprintf(stderr, \"Syntax Error: %%s:%%d:%%d \", raw_string(tok->fname), tok->line_no, tok->col_no);\n"
"\n"
"    va_start(args, fmt);\n"
"    vfprintf(stderr, fmt, args);\n"
"    va_end(args);\n"
"    fprintf(stderr, \"\\n\");\n"
"\n"
"    errors++;\n"
"}\n"
"\n"
"static void syntax_warning(const char* fmt, ...) {\n"
"\n"
"    va_list args;\n"
"\n"
"    if(get_line_no() > 0)\n"
"        fprintf(stderr, \"Warning: %%s:%%d:%%d \", get_fname(), get_line_no(), get_col_no());\n"
"    else\n"
"        fprintf(stderr, \"Warning: \");\n"
"\n"
"    va_start(args, fmt);\n"
"    vfprintf(stderr, fmt, args);\n"
"    va_end(args);\n"
"    fprintf(stderr, \"\\n\");\n"
"\n"
"    warnings++;\n"
"}\n"
"\n"
"static void fatal_error(const char* fmt, ...) {\n"
"\n"
"    va_list args;\n"
"\n"
"    fprintf(stderr, \"Fatal Error: \");\n"
"\n"
"    va_start(args, fmt);\n"
"    vfprintf(stderr, fmt, args);\n"
"    va_end(args);\n"
"    fprintf(stderr, \"\\n\");\n"
"\n"
"    errors++;\n"
"    exit(1);\n"
"}\n"
"\n"
"int get_errors() {\n"
"    return errors;\n"
"}\n"
"\n"
"int get_wanings() {\n"
"    return warnings;\n"
"}\n"
"\n"
"\n";

const char* data_structures_string =
"\n"
"typedef struct {\n"
"    uint16_t len;   // length of this line\n"
"    uint16_t* line; // list of items in the line\n"
"    int score;      // score of this cache line\n"
"    int index;      // index of the last match\n"
"} CacheLine;\n"
"\n"
"typedef struct {\n"
"    int size;           // lines in the cache\n"
"    CacheLine** lines;  // the actual lines\n"
"} Cache;\n"
"\n"
"typedef struct _rule_ {\n"
"    uint16_t size;       // the non-terminal value\n"
"    uint16_t type;       // the non-terminal value\n"
"    uint16_t prec;       // rule precedence\n"
"    uint16_t num_lines;  // number of rule lines\n"
"    CacheLine** list;     // list of lines in the rule\n"
"} Rule;\n"
"\n";

/*
 * This is the code to emit for the actual parser.
 */
const char* parser_finder_string =
"\n"
"static uint16_t* find_rule(uint16_t type) {\n"
"\n"
"    uint16_t* tmp;\n"
"    int idx = 1;\n"
"\n"
"    for(uint16_t i = 0; i < parser_table[0]; i++) {\n"
"        tmp = &parser_table[idx];\n"
"        if(tmp[1] == type)\n"
"            return tmp;\n"
"        else\n"
"            idx += tmp[0];\n"
"    }\n"
"\n"
"    return NULL;\n"
"}\n"
"\n"
"static CacheLine* get_line(uint16_t* table) {\n"
"\n"
"    CacheLine* ptr = _ALLOC_T(CacheLine);\n"
"    ptr->len = table[0];\n"
"    ptr->line = _ALLOC_ARRAY(uint16_t, table[0]);\n"
"    memcpy(ptr->line, &table[1], sizeof(uint16_t)*table[0]+1);\n"
"\n"
"    return ptr;\n"
"}\n"
"\n"
"static Rule* get_rule(uint16_t type) {\n"
"\n"
"    uint16_t* tmp = find_rule(type);\n"
"    Rule* ptr;\n"
"\n"
"    if(tmp == NULL)\n"
"        return NULL;\n"
"    else {\n"
"        ptr = _DUP_MEM_ARRAY(tmp, Rule, tmp[0]);\n"
"        ptr->list = _ALLOC_ARRAY(CacheLine*, tmp[3]);\n"
"        uint16_t* index = &tmp[4];\n"
"        for(uint16_t i = 0; i < tmp[3]; i++) {\n"
"            ptr->list[i] = get_line(index);\n"
"            index += index[0]+1;\n"
"        }\n"
"    }\n"
"\n"
"    return ptr;\n"
"}\n"
"\n"
"static inline bool is_term(uint16_t type) {\n"
"    return (type >= BASE_TERM && type < BASE_NTERM)? true: false;\n"
"}\n"
"\n"
"static inline bool is_nterm(uint16_t type) {\n"
"    return (type < BASE_NTERM)? false: true;\n"
"}\n"
"\n"
"static Cache* create_cache(uint16_t type) {\n"
"\n"
"    const uint16_t* rule = find_rule(type);\n"
"    if(!rule)\n"
"        fatal_error(\"match_rule: unknown rule: %%u\\n\", type);\n"
"\n"
"    Cache* cache = _ALLOC_T(Cache);\n"
"    cache->size = rule[3];\n"
"    cache->lines = _ALLOC_ARRAY(CacheLine*, cache->size);\n"
"\n"
"    uint16_t* tpt = &rule[4];\n"
"    for(uint16_t i = 0; i < rule[3]; i++) {\n"
"        CacheLine* line = _ALLOC_T(CacheLine);\n"
"        line->score = 0;\n"
"        line->index = 0;\n"
"        line->len = tpt[0];\n"
"        line->line = _ALLOC_ARRAY(uint16_t, line->len);\n"
"        for(uint16_t j = 0; j < line->len; j++)\n"
"            line->line[j] = tpt[j+1];\n"
"        cache->lines[i] = line;\n"
"        tpt += tpt[0]+1;\n"
"    }\n"
"\n"
"    return cache;\n"
"}\n"
"\n"
"static Ast* match_rule(uint16_t type, bool final) {\n"
"\n"
"    // create the cache\n"
"    List* cache = create_cache(type);\n"
"    List* out = create_list(sizeof(AstEntry*));\n"
"\n"
"    // evaluate the rule\n"
"    int index = 1;\n"
"    int count = 0;\n"
"    ListIter* iter = init_list_iterator(cache);\n"
"\n"
"    // pass/fail\n"
"    return create_ast_node(type, out);\n"
"}\n"
"\n"
"Ast* parse() {\n"
"\n"
"    return match_rule(BASE_NTERM, true);\n"
"}\n"
"\n";

const char* parser_testing_string =
"#if 1\n"
"static void dump_line_obj(uint16_t obj) {"
"    if(is_nterm(obj))\n"
"        printf(\"%%s\", nterm_to_str(obj));\n"
"    else\n"
"        printf(\"%%u\", obj);\n"
"}\n"
"\n"
"static void dump_line(CacheLine* line) {\n"
"\n"
"    printf(\"    len:%%d \", line->len);\n"
"    printf(\"score:%%d \", line->score);\n"
"    printf(\"index:%%d [\", line->index);\n"
"    int idx = 0;\n"
"    dump_line_obj(line->line[idx++]);\n"
"    while(idx < line->len) {\n"
"        printf(\", \");\n"
"        dump_line_obj(line->line[idx++]);\n"
"    }\n"
"    printf(\"]\\n\");\n"
"}\n"
"\n"
"static void dump_cache(Cache* ptr) {\n"
"\n"
"    printf(\"line: \");\n"
"    printf(\"size:%%u\\n\", ptr->size);\n"
"    for(int i = 0; i < ptr->size; i++)\n"
"        dump_line(ptr->lines[i]);\n"
"    printf(\"\\n\");\n"
"}\n"
"\n"
"static void dump_rule(Rule* ptr) {\n"
"\n"
"    printf(\"size:%%u\\n\", ptr->size);\n"
"    printf(\"type:\"); dump_line_obj(ptr->type); printf(\"\\n\");\n"
"    printf(\"prec:%%u\\n\", ptr->prec);\n"
"    printf(\"lines:%%u\\n\", ptr->num_lines);\n"
"    for(unsigned int i = 0; i < ptr->num_lines; i++)\n"
"        dump_line(ptr->list[i]);\n"
"    printf(\"\\n\");\n"
"}\n"
"\n"
"int main() {\n"
"\n"
"    Rule* ptr = (Rule*)get_rule(1001);\n"
"    dump_rule(ptr);\n"
"\n"
"    ptr = (Rule*)get_rule(1003);\n"
"    dump_rule(ptr);\n"
"\n"
"    ptr = (Rule*)get_rule(1006);\n"
"    dump_rule(ptr);\n"
"\n"
"    ptr = (Rule*)get_rule(8012);\n"
"    printf(\"rule == NULL? %%s\\n\", ptr==NULL? \"true\":\"false\");\n"
"\n"
"    Cache* c = create_cache(1005);\n"
"    dump_cache(c);\n"
"\n"
"    return 0;\n"
"}\n"
"#endif\n"
"\n";

#endif /* _EMIT_PARSER_H */
