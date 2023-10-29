#ifndef _EMIT_PARSER_H
#define _EMIT_PARSER_H

/*
 * This is the code to emit for the actual parser.
 */
const char* parser_finder_string =
    "#include <stdint.h>\n" \
    "#include \"util.h\"\n" \
    "\n" \
    "typedef struct {\n" \
    "    uint16_t len;    // length of this line\n" \
    "    uint16_t* line;  // list of items in the line\n" \
    "} RuleLine;\n" \
    "\n" \
    "typedef struct _rule_ {\n" \
    "    uint16_t size;       // the non-terminal value\n" \
    "    uint16_t type;       // the non-terminal value\n" \
    "    uint16_t num_lines;  // number of rule lines\n" \
    "    RuleLine** list;     // list of lines in the rule\n" \
    "} Rule;\n" \
    "\n" \
    "uint16_t* find_rule(uint16_t type) {\n" \
    "\n" \
    "    uint16_t* tmp;\n" \
    "    int idx = 1;\n" \
    "\n" \
    "    for(uint16_t i = 0; i < parser_table[0]; i++) {\n" \
    "        tmp = &parser_table[idx];\n" \
    "        if(tmp[1] == type)\n" \
    "            return tmp;\n" \
    "        else\n" \
    "            idx += tmp[0];\n" \
    "    }\n" \
    "\n" \
    "    return NULL;\n" \
    "}\n" \
    "\n" \
    "RuleLine* get_line(uint16_t* table) {\n" \
    "\n" \
    "    RuleLine* ptr = _ALLOC_T(RuleLine);\n" \
    "    ptr->len = table[0];\n" \
    "    ptr->line = _ALLOC_ARRAY(uint16_t, table[0]);\n" \
    "    memcpy(ptr->line, &table[1], sizeof(unsigned int)*table[0]+1);\n" \
    "\n" \
    "    return ptr;\n" \
    "}\n" \
    "\n" \
    "Rule* get_rule(uint16_t type) {\n" \
    "\n" \
    "    uint16_t* tmp = find_rule(type);\n" \
    "    Rule* ptr;\n" \
    "\n" \
    "    if(tmp == NULL)\n" \
    "        return NULL;\n" \
    "    else {\n" \
    "        ptr = _DUP_MEM_ARRAY(tmp, Rule, tmp[0]);\n" \
    "        ptr->list = _ALLOC_ARRAY(RuleLine*, tmp[2]); //malloc(sizeof(uint16_t*)*tmp[2]);\n" \
    "        uint16_t* index = &tmp[3];\n" \
    "        for(uint16_t i = 0; i < tmp[2]; i++) {\n" \
    "            ptr->list[i] = get_line(index);\n" \
    "            index += index[0]+1;\n" \
    "        }\n" \
    "    }\n" \
    "\n" \
    "    return ptr;\n" \
    "}\n" \
    "\n";

const char* parser_testing_string =
    "#if 1\n" \
    "// build string:\n" \
    "// gcc -Wall -Wextra -Wpedantic -o t simple_parser.c -I../src/util -L../bin -lutil -lgc\n" \
    "void dump_line(RuleLine* line) {\n" \
    "\n" \
    "    printf(\"    len: %%d\\n\", line->len);\n" \
    "    int idx = 0;\n" \
    "    printf(\"    %%u\", line->line[idx++]);\n" \
    "    while(idx < line->len) {\n" \
    "        printf(\", \");\n" \
    "        printf(\"%%u\", line->line[idx++]);\n" \
    "    }\n" \
    "    printf(\"\\n\");\n" \
    "}\n" \
    "\n" \
    "void dump_rule(Rule* ptr) {\n" \
    "\n" \
    "    printf(\"size: %%u\\n\", ptr->size);\n" \
    "    printf(\"type: %%u\\n\", ptr->type);\n" \
    "    printf(\"lines: %%u\\n\", ptr->num_lines);\n" \
    "    for(unsigned int i = 0; i < ptr->num_lines; i++)\n" \
    "        dump_line(ptr->list[i]);\n" \
    "    printf(\"\\n\");\n" \
    "}\n" \
    "\n" \
    "int main() {\n" \
    "\n" \
    "    Rule* ptr = (Rule*)get_rule(_nterm_switch_clause);\n" \
    "    dump_rule(ptr);\n" \
    "\n" \
    "    ptr = (Rule*)get_rule(_nterm_func_content_elem);\n" \
    "    dump_rule(ptr);\n" \
    "\n" \
    "    ptr = (Rule*)get_rule(_nterm_entry_definition);\n" \
    "    dump_rule(ptr);\n" \
    "\n" \
    "    ptr = (Rule*)get_rule(8012);\n" \
    "    printf(\"rule == NULL? %%s\\n\", ptr==NULL? \"true\":\"false\");\n" \
    "\n" \
    "    return 0;\n" \
    "}\n" \
    "#endif\n" \
    "\n";

#endif /* _EMIT_PARSER_H */
