/**
 * @file tok_queue.c
 * 
 * @brief This is the token queue implementation. The token queue is the 
 * public interface into the scanner and it's used by the parser to 
 * implement rule matching. 
 * 
 * NOTE: This library expects to be using garbage collection.
 * 
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-07-2024
 * @copyright Copyright (c) 2024
 */
#include "util.h"
#include "scanner.h"

extern Token* scan_token();

typedef struct _tok_queue_item_ {
    Token* tok;
    struct _tok_queue_item_* next;
} TokQueueItem;

typedef struct {
    TokQueueItem* head;
    TokQueueItem* crnt;
    TokQueueItem* tail;
} TokQueue;

static TokQueue* tqueue = NULL;

/*
 * Append a token to the end of the queue. It could be that advance_token()
 * has found the end of the queue, but it could be something else. 
 */
static void append_token(Token* tok) {

    assert(tqueue != NULL);
    assert(tok != NULL);

    TRY {
        TokQueueItem* item = _ALLOC_T(TokQueueItem);
        item->tok = copy_token(tok);
    }
    ANY_EXCEPT() {
        fprintf(stderr, "Fatal ");
        fprintf(stderr, "%s\n", EXCEPTION_MSG);
        exit(1);
    }

    if(tqueue->tail != NULL) {
        tqueue->tail->next = item;
        tqueue->tail = item;
    }
    else {
        tqueue->head = item;
        tqueue->crnt = item;
        tqueue->tail = item;
    }
}

/**
 * @brief Open a file for the scanner to read from. Files are expected to be
 * opened in a stack so that when a file is opened the input stream is 
 * switched. Files are automatically closed when the last character is read.
 * 
 * @param fname 
 */
void open_file(const char* fname) {

    if(tqueue == NULL) {
        TRY {
            // prime the token pipeline
            tqueue = _ALLOC_T(TokQueue);
            append_token(scan_token());
        }
        EXCEPT(MEMORY_ERROR) {
            fprintf(stderr, "Fatal ");
            fprintf(stderr, "%s\n", EXCEPTION_MSG);
            exit(1);
        }
    }

    // calling into the util library
    TRY {
        open_input_file(fname);
    }
    EXCEPT(FILE_ERROR) {
        fprintf(stderr, "Fatal ");
        fprintf(stderr, "%s\n", EXCEPTION_MSG);
        exit(1);
    }
}

/**
 * @brief Get the token object. This returns the current token, which is a 
 * global in the scanner. If the value of this token needs to be preserved, 
 * then the token should be copied.
 * 
 * @return Token* 
 */
Token* get_token() {

    assert(tqueue != NULL);

    if(tqueue->crnt != NULL) {
        return tqueue->crnt->tok;
    }

    // Should never happen. Will probably cause a segfault.
    return NULL;
}

/**
 * @brief Do a deep copy of the given token pointer. All memory is duplicated.
 * 
 * @param tok 
 * @return Token* 
 */
Token* copy_token(const Token* tok) {

    assert(tok != NULL);

    TRY {
        Token* ntok = _ALLOC_T(Token);
        ntok->fname = _DUP_STR(tok->fname);
        ntok->str = copy_string(tok->str);
        ntok->line_no = tok->line_no;
        ntok->col_no = tok->col_no;
        ntok->type = tok->type;
    }
    ANY_EXCEPT() {
        // any exception is a fatal error:
        fprintf(stderr, "Fatal ");
        fprintf(stderr, "%s\n", EXCEPTION_MSG);
        exit(1);
    }

    return ntok;
}

/**
 * @brief Make the next token in the stream the current token. If the token 
 * before this one was the end of the input, then nothing happens and the 
 * returned token is the end of input token. Returns the current token after
 * the advance happens.
 * 
 * @return Token* 
 */
Token* advance_token() {

    // avoid stupid programmer tricks
    assert(tqueue != NULL);
    assert(tqueue->crnt != NULL);

    if(tqueue->crnt->tok->type != END_OF_INPUT) {
        if(tqueue->crnt->next == NULL)
            append_token(scan_token());

        tqueue->crnt = tqueue->crnt->next;
    }

    return tqueue->crnt->tok;
}

/**
 * @brief Consume the token queue from the beginning to the current token.
 * This is called when a rule has been matched and there is no need to keep 
 * that section of the token stream. Returns the current token. NOTE: this
 * library routine expects to use garbage collections.
 * 
 * @return Token* 
 */
Token* consume_token() {

    assert(tqueue != NULL);
    assert(tqueue->crnt != NULL);

    tqueue->head = tqueue->crnt;

    return tqueue->crnt->tok;
}

/**
 * @brief Reset the token stream to the beginning. This is used when a rule
 * could not be matched and the token stream needs to be rewound to test the
 * next rule in a list of alternatives.
 * 
 * @return Token* 
 */
Token* reset_token() {

    assert(tqueue != NULL);
    assert(tqueue->crnt != NULL);

    tqueue->crnt = tqueue->head;

    return tqueue->crnt->tok;
}

/**
 * @brief Iterate the token queue. This is used by consumers that require raw
 * access to the token queue. That includes things like error reporting and
 * recovery. The first time that the iterator is called, the parameter needs
 * to be NULL. The current pointer in the queue is store there in order to 
 * track the location in the queue. When there are no more elements in the 
 * queue, then the return value is NULL.
 * 
 * Example:
 * void* mark = NULL;
 * for(Token* tok = iterate_tokens(&mark); 
 *            tok != NULL; 
 *            tok = iterate_tokens(&mark)) {
 *     // do stuff with tok
 * }
 *  
 * @param mark 
 * @return Token*
 */
Token* iterate_tokens(void** mark) {

    assert(tqueue != NULL);
    assert(tqueue->head != NULL);

    if(*mark == NULL) 
        *mark = tqueue->head;
    else if(((TokQueueItem*)(*mark))->next != NULL)
        *mark = ((TokQueueItem*)(*mark))->next;
    else
        return NULL;

    return ((TokQueueItem*)(*mark))->tok;
}

