%tokens {
    OPAREN
    CPAREN
    ADD@
    SUB@
    POW@
    MUL@
    DIV@
    MOD@
    INT_CONST@
}

%grammar {
    expression {
        : expr_term
    }

    expr_term:1 {
        : expr_pow ADD expr_term
        : expr_pow SUB expr_term
    }

    expr_pow:3 {
        : expr_fact POW expr_pow
    }

    expr_fact:2 {
        : expr_unary MUL expr_fact
        : expr_unary DIV expr_fact
        : expr_unary MOD expr_fact
    }

    expr_unary:4 {
        : SUB expression
        : primary
    }

    primary {
        : const_expression
        : OPAREN expression CPAREN
    }

    const_expression {
        : INT_CONST
    }
}