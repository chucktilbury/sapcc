/**
 * @file scanner.c
 * 
 * @brief This is the implemetation of the default example scanner. It 
 * implements scanning for keywords that are defined in the grammar and 
 * also default constructed tokens that are literal numbers and literal
 * strings. Also symbols and operators such as "!=" and "==". It is 
 * designed to be easy to change to match different requirements. The 
 * scanner that is implemented here is intended to scan the tokens as they
 * are defined for the Simple programming language. See the header file for
 * more information. 
 * 
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-07-2024
 * @copyright Copyright (c) 2024
 */
#include "util.h"

