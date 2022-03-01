#include "util.h"

enum TType {
    INCREMENT,
    DECREMENT,

    RATIO,
    NUMBER,

    OH_LAWD,
    COMIN,
    GIMME_SOME,

    SPACE_MAN,
    FR,

    IS,
    AND,
    
    VAR,

    WAKANDA_FOREVER,
    NVM,
    
    MORE_BASED_THAN,
    LESS_BASED_THAN,
    AS_BASED_AS,
    NOT_AS_BASED_AS,

    AIGHT_IMMA_HEAD_OUT,

    MMM_WHATCHA_SAY,
    IM_SO_RANDOM,

    DED,
    FLOOP,

    NEW_SHIT,
    NEWLINE
};

class Token {
    public:
        std::string content;
        int content_i;
        TType type;
        int line;

        Token(TType type, int line) {
            this -> type = type;
            this -> line = line;
        }

        Token(TType type, int line, std::string content) {
            this -> type = type;
            this -> content = content;
            this -> line = line;
        }

        Token(TType type, int line, int content) {
            this -> type = type;
            this -> content_i = content;
            this -> line = line;
        }
};