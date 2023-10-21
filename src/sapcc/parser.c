
#include "parser.h"
#include "errors.h"
#include "logger.h"

#define PLEVEL 10
static Parser* parser_state;

static Rule* create_rule() {

    Rule* ptr  = _ALLOC_T(Rule);
    ptr->match = create_string(NULL);
    ptr->list  = create_str_list();

    return ptr;
}

static void destroy_rule(Rule* ptr) {

    if(ptr != NULL) {
        destroy_string(ptr->match);
        destroy_str_list(ptr->list);
        _FREE(ptr);
    }
}

/*
 * Rule list functions simplify casting.
 */
static void add_rule_list(RuleList* ptr, Rule* val) {

    add_ptr_list((PtrList*)ptr, (void*)val);
}

static RuleListIter* init_rule_list_iter(RuleList* ptr) {

    return init_ptr_list_iter((PtrList*)ptr);
}

static Rule* iterate_rule_list(RuleListIter* iter) {

    return (Rule*)iterate_ptr_list((PtrListIter*)iter);
}

static RuleList* create_rule_list() {

    RuleList* ptr = (RuleList*)create_ptr_list();
    return ptr;
}

static void destroy_rule_list(RuleList* ptr) {

    Rule* tmp;
    RuleListIter* rli = init_rule_list_iter(ptr);
    while(NULL != (tmp = iterate_rule_list(rli)))
        destroy_rule(tmp);

    destroy_ptr_list((PtrList*)ptr);
}

/*
 * Non Terminal functions.
 */
static NonTerminal* create_nonterminal() {

    NonTerminal* ptr = _ALLOC_T(NonTerminal);

    ptr->name       = create_string(NULL);
    ptr->pre_match  = create_string(NULL);
    ptr->post_match = create_string(NULL);
    ptr->list       = create_rule_list();
    ptr->ref        = 0;
    ptr->val        = 0;

    return ptr;
}

static void destroy_nonterminal(NonTerminal* ptr) {

    if(ptr != NULL) {
        destroy_string(ptr->name);
        destroy_string(ptr->pre_match);
        destroy_string(ptr->post_match);
        destroy_rule_list(ptr->list);
        _FREE(ptr);
    }
}

/*
 * Non Terminal list functions simplify casting.
 */
static void add_nterm_list(NonTermList* ptr, NonTerminal* val) {

    add_ptr_list((PtrList*)ptr, (void*)val);
}

static NonTermListIter* init_nterm_list_iter(NonTermList* ptr) {

    return init_ptr_list_iter((PtrList*)ptr);
}

static NonTerminal* iterate_nterm_list(NonTermListIter* iter) {

    return (NonTerminal*)iterate_ptr_list(iter);
}

static NonTermList* create_nterm_list() {

    NonTermList* ptr = (NonTermList*)create_ptr_list();
    return ptr;
}

static void destroy_nterm_list(NonTermList* ptr) {

    NonTerminal* tmp;
    NonTermListIter* ntli = init_nterm_list_iter(ptr);
    while(NULL != (tmp = iterate_nterm_list(ntli)))
        destroy_nonterminal(tmp);

    destroy_ptr_list((PtrList*)ptr);
}

/*
 * Terminal list functions simplify casting.
 */
static Terminal* create_terminal() {

    Terminal* ptr = _ALLOC_T(Terminal);
    ptr->name     = create_string(NULL);
    ptr->keep     = false;
    ptr->ref      = 0;
    ptr->val      = 0;

    return ptr;
}

static void destroy_terminal(Terminal* term) {

    if(term != NULL) {
        destroy_string(term->name);
        _FREE(term);
    }
}

static void add_term_list(TermList* ptr, Terminal* val) {

    add_ptr_list((PtrList*)ptr, (void*)val);
}

static TermListIter* init_term_list_iter(TermList* ptr) {

    return init_ptr_list_iter(ptr);
}

static Terminal* iterate_term_list(TermListIter* iter) {

    return (Terminal*)iterate_ptr_list(iter);
}

static TermList* create_term_list() {

    TermList* ptr = (TermList*)create_ptr_list();
    return ptr;
}

static void destroy_term_list(TermList* ptr) {

    assert(ptr != NULL);

    Terminal* tmp;
    TermListIter* tli = init_term_list_iter(ptr);
    while(NULL != (tmp = iterate_term_list(tli)))
        destroy_terminal(tmp);

    destroy_ptr_list((PtrList*)ptr);
}

static int parse_header() {

    int retv = 0;

    if(scan_block() > 0) {
        add_str_list(parser_state->headers, copy_string(get_token()->str));
    }
    else
        retv++;

    return retv;
}

static int parse_source() {

    int retv = 0;

    if(scan_block() > 0) {
        add_str_list(parser_state->sources, copy_string(get_token()->str));
    }
    else
        retv++;

    return retv;
}

/*
 * When this is entered, the "%tokens" token has already been read. It is
 * followed by a '{' and a series of string that give the names of terminal
 * symbols. If it has a '@' appended to it, then "keep" is set. At the end of
 * the symbols, the '}' character appears and is consumed. If there is
 * something other than these, then a syntax error occurs.
 */
static int parse_tokens() {

    Token* tok = get_token();
    int value  = 500;

    if(tok->type != OBRACE) {
        syntax_error("expected a '{' but got a %s", tok_type_to_str(tok->type));
        return 1;
    }
    else
        consume_token();

    while(true) {
        tok = get_token();
        if(tok->type == SYMBOL) {
            Terminal* term = create_terminal();
            if(strrchr(raw_string(tok->str), '@')) {
                truncate_string(tok->str, len_string(tok->str) - 1);
                term->keep = true;
            }
            term->name = copy_string(tok->str);
            term->ref  = 0;
            term->val  = value++;
            add_term_list(parser_state->terminals, term);
            consume_token();
        }
        else if(tok->type == CBRACE) {
            consume_token();
            return 0;
        }
        else {
            syntax_error("expected a terminal SYMBOL or a '}', but got a %s", tok_type_to_str(tok->type));
            consume_token();
            return 1;
        }
    }

    return 0;
}

/*
 * When this is entered, a ':' has been read for a rule line.
 */
static int parse_rule(NonTerminal* nterm) {

    consume_token(); // consume the COLON
    Rule* rule = create_rule();

    while(true) {
        Token* tok = get_token();
        if(tok->type == SYMBOL) {
            add_str_list(rule->list, copy_string(tok->str));
            consume_token();
        }
        else if(tok->type == OBRACE) {
            scan_block();
            tok = get_token();
            if(tok->type != BLOCK) {
                syntax_error("expected a code BLOCK, but got a %s", tok_type_to_str(tok->type));
                consume_token();
                return 1;
            }
            else
                rule->match = copy_string(tok->str);

            consume_token(); // consume the block
            add_rule_list(nterm->list, rule);
            return 0;
        }
        else {
            syntax_error("expected a rule SYMBOL or a code BLOCK, but got a %s", tok_type_to_str(tok->type));
            consume_token();
            return 1;
        }
    }

    return 0;
}

/*
 * When this is entered, the non-terminal name and it's block have been read.
 * The next thing is a list of rules that is preceeded with a ':' and ends with
 * a block of code.
 */
static int parse_rules(NonTerminal* nterm) {

    Token* tok;

    while(true) {
        tok = get_token();
        if(tok->type == COLON) {
            if(parse_rule(nterm))
                return 1;
        }
        else if(tok->type == SEMI) {
            consume_token(); // consume the semicolon

            scan_block();
            tok = get_token();
            if(tok->type != BLOCK) {
                syntax_error("expected a code BLOCK, but got a %s", tok_type_to_str(tok->type));
                consume_token();
                return 1;
            }
            else
                nterm->post_match = copy_string(tok->str);

            consume_token(); // consume the block
            return 0;
        }
        else {
            syntax_error("expected a ':' or a ';', but got a %s", tok_type_to_str(tok->type));
            consume_token();
            return 1;
        }
    }

    return 0;
}

/*
 * When this is entered, the "%grammer" token has already been read and
 * consumed. The next token is a '{'. After that, the nonterminal and the rest
 * of the syntax:
 *
 * nonterminal { // block of C code }
 *    : rule { // block of C code }
 *    ...
 *    ; { block of C code }
 *
 * ...
 *
 * The %grammar block is ended with a '}' token.
 */
static int parse_grammar() {

    Token* tok = get_token();
    int value  = 1000;

    if(tok->type != OBRACE) {
        syntax_error("expected a '{' but got a %s", tok_type_to_str(tok->type));
        return 1;
    }
    else
        consume_token();

    while(true) {
        tok = get_token();
        if(tok->type == SYMBOL) {
            NonTerminal* ptr = create_nonterminal();
            ptr->name        = copy_string(tok->str);
            consume_token();

            scan_block();
            tok = get_token();
            if(tok->type != BLOCK) {
                syntax_error("expected a code BLOCK, but got a %s", tok_type_to_str(tok->type));
                consume_token();
                return 1;
            }
            else
                ptr->pre_match = copy_string(tok->str);

            consume_token();
            // get the rule list, including the closure.
            if(parse_rules(ptr)) {
                return 1;
            }

            ptr->ref = 0;
            ptr->val = value++;

            // add it to the list
            add_nterm_list(parser_state->non_terminals, ptr);
        }
        else if(tok->type == CBRACE) {
            consume_token();
            return 0;
        }
        else {
            syntax_error("expected a non-terminal SYMBOL or a '}', but got a %s", tok_type_to_str(tok->type));
            consume_token();
            return 1;
        }
    }

    return 0;
}

static void dump_terminal(Terminal* term) {

    printf("\t%-20s", raw_string(term->name));
    printf("keep:%-7s", term->keep ? "true " : "false");
    printf("value:%-6d", term->val);
    printf("references:%d\n", term->ref);
}

static void dump_rules(NonTerminal* nterm) {

    Rule* rule;
    RuleListIter* rli = init_rule_list_iter(nterm->list);
    while(NULL != (rule = iterate_rule_list(rli))) {
        printf("\t: ");
        Str* s;
        StrListIter* sli = init_str_list_iter(rule->list);
        while(NULL != (s = iterate_str_list(sli))) {
            printf("%s ", raw_string(s));
        }
        printf("%s\n", raw_string(rule->match));
    }
}

static void dump_nonterminal(NonTerminal* nterm) {

    printf("%s\t", raw_string(nterm->name));
    printf("value:%d\t", nterm->val);
    printf("references:%d\n", nterm->ref);
    printf("\tpre-match: %s\n", raw_string(nterm->pre_match));
    printf("\tpost-match: %s\n", raw_string(nterm->post_match));
    dump_rules(nterm);
    printf("\n");
}

void dump_parser() {

    printf("dump the parser\n");

    Str* str;
    StrListIter* sli;

    sli = init_str_list_iter(parser_state->headers);
    printf("HEADERS:\n");
    while(NULL != (str = iterate_str_list(sli)))
        printf("%s\n", raw_string(str));

    sli = init_str_list_iter(parser_state->sources);
    printf("\nSOURCES:\n");
    while(NULL != (str = iterate_str_list(sli)))
        printf("%s\n", raw_string(str));

    Terminal* term;
    TermListIter* tli = init_term_list_iter(parser_state->terminals);
    printf("\nTERMINALS:\n");
    while(NULL != (term = iterate_term_list(tli)))
        dump_terminal(term);

    NonTerminal* nterm;
    NonTermListIter* ntli = init_nterm_list_iter(parser_state->non_terminals);
    printf("\nNON-TERMINALS:\n");
    while(NULL != (nterm = iterate_nterm_list(ntli)))
        dump_nonterminal(nterm);
}

/*
 * Verify that there are no terminals and non-terminals with the same name.
 */
static void check_duplicates() {

    LOG(PLEVEL, "ENTER: check duplicates");

    Terminal* term;
    TermListIter* tli = init_term_list_iter(parser_state->terminals);
    while(NULL != (term = iterate_term_list(tli))) {
        NonTerminal* nterm;
        NonTermListIter* ntli = init_nterm_list_iter(parser_state->non_terminals);
        while(NULL != (nterm = iterate_nterm_list(ntli))) {
            if(!comp_string(term->name, nterm->name)) {
                fprintf(stderr, "Syntax Error: terminal and non-terminal have the same name: %s", raw_string(term->name));
                return;
            }
        }
    }

    LOG(PLEVEL, "LEAVE: check duplicates");
}

static void increment_reference(Str* str) {

    LOG(PLEVEL, "ENTER: increment references: %s", raw_string(str));

    // Iterate the terminals and the non-terminals and publish a warning if
    // they are not referenced.
    Terminal* term;
    TermListIter* tli = init_term_list_iter(parser_state->terminals);
    while(NULL != (term = iterate_term_list(tli))) {
        if(!comp_string(term->name, str)) {
            term->ref++;
            LOG(PLEVEL, "LEAVE: increment references: %s", raw_string(term->name));
            return;
        }
    }

    NonTerminal* nterm;
    NonTermListIter* ntli = init_nterm_list_iter(parser_state->non_terminals);
    while(NULL != (nterm = iterate_nterm_list(ntli))) {
        if(!comp_string(nterm->name, str)) {
            nterm->ref++;
            LOG(PLEVEL, "LEAVE: increment references: %s", raw_string(nterm->name));
            return;
        }
    }

    LOG(PLEVEL, "LEAVE: increment references");
}

/*
 * Update the reference numbers.
 */
static void update_references() {

    LOG(PLEVEL, "ENTER: update references");

    // iterate the rules and update the terminal and non-terminal references
    NonTerminal* nterm;
    NonTermListIter* ntli = init_nterm_list_iter(parser_state->non_terminals);
    while(NULL != (nterm = iterate_nterm_list(ntli))) {
        Rule* rule;
        RuleListIter* rli = init_rule_list_iter(nterm->list);
        while(NULL != (rule = iterate_rule_list(rli))) {
            Str* str;
            StrListIter* sli = init_str_list_iter(rule->list);
            while(NULL != (str = iterate_str_list(sli))) {
                increment_reference(str);
            }
        }
    }
    LOG(PLEVEL, "ENTER: update references");
}

/*
 * Verify that all of the terminals and non-terminals are referenced in the
 * grammar.
 */
static void check_references() {

    LOG(PLEVEL, "ENTER: check references");

    // Iterate the terminals and the non-terminals and publish a warning if
    // they are not referenced.
    Terminal* term;
    TermListIter* tli = init_term_list_iter(parser_state->terminals);
    while(NULL != (term = iterate_term_list(tli))) {
        if(term->ref == 0)
            warning("terminal symbol \"%s\" has no references in grammar", raw_string(term->name));
    }

    NonTerminal* nterm;
    NonTermListIter* ntli = init_nterm_list_iter(parser_state->non_terminals);
    // first non-terminal in the list never has references
    iterate_nterm_list(ntli);
    while(NULL != (nterm = iterate_nterm_list(ntli))) {
        if(nterm->ref == 0)
            warning("non-terminal symbol \"%s\" has no references in grammar", raw_string(nterm->name));
    }
    LOG(PLEVEL, "ENTER: check references");
}

/*
 * Public Interface
 */
void init_parser() {

    parser_state = _ALLOC_T(Parser);

    init_scanner(get_cmd_raw(cmd, "file"));

    parser_state->terminals     = create_term_list();
    parser_state->non_terminals = create_nterm_list();
    parser_state->headers       = create_str_list();
    parser_state->sources       = create_str_list();
}

void destroy_parser() {

    destroy_term_list(parser_state->terminals);
    destroy_nterm_list(parser_state->non_terminals);
    destroy_str_list(parser_state->headers);
    destroy_str_list(parser_state->sources);
    _FREE(parser_state);
}

Parser* parser() {

    Token* tok;
    int errors = 0;

    tok = get_token();
    while(tok->type != END_OF_INPUT) {
        switch(tok->type) {
            case GRAMMAR:
                consume_token();
                errors += parse_grammar();
                break;
            case TOKENS:
                consume_token();
                errors += parse_tokens();
                break;
            case SOURCE:
                consume_token();
                errors += parse_source();
                consume_token();
                break;
            case HEADER:
                consume_token();
                errors += parse_header();
                consume_token();
                break;
            case END_OF_INPUT:
                // do nothing...
                break;
            default:
                syntax_error("expected a directive but got a %s", tok_type_to_str(tok->type));
                consume_token();
                errors++;
                break;
        }

        if(errors > 10)
            return NULL;
        tok = get_token();
    }

    check_duplicates();
    update_references();
    check_references();
    return parser_state;
}

int get_num_term() {
    return len_list(parser_state->terminals);
}

int get_num_nterm() {
    return len_list(parser_state->non_terminals);
}

TermList* get_term_list() {
    return parser_state->terminals;
}

NonTermList* get_nterm_list() {
    return parser_state->non_terminals;
}
