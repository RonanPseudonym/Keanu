#include "err.h"

class Lexer {
    private:
        std::string increment[10] = {"chad", "based", "feet", "redpilled", "poggers", "chungus", "keanu", "elon", "musk", "harambe"};
        std::string decrement[7] = {"virgin", "cringe", "bluepilled", "woman", "tiktok", "sus", "l"};
        int valid_ints[6] = {34, 41, 42, 69, 420, 666};

        void new_token(TType type, int line) {
            tokens.push_back(Token(type, line));
            current = "";
        }

    public:
        std::vector<Token> tokens;
        std::string current;

        int line = 1;

        Lexer(std::string data) {
            data += '\n';
            for (int i = 0; i < data.size(); i ++) {
                if (data[i] == '\n' || std::isspace(data[i])) {
                    if (contains(increment, current)) { // This monstrosity is very not great, but ehhhh whatever
                        new_token(TType::INCREMENT, line);
                    } else if (contains(decrement, current)) {
                        new_token(TType::DECREMENT, line);
                    } else if (current == "ratio") {
                        new_token(TType::RATIO, line);
                    } else if (current == "oh lawd") {
                        new_token(TType::OH_LAWD, line);
                    } else if (current == "comin") {
                        new_token(TType::COMIN, line);
                    } else if (current == "gimme some") {
                        new_token(TType::GIMME_SOME, line);
                    } else if (current == "new shit") {
                        new_token(TType::NEW_SHIT, line);
                    } else if (current == "space man") {
                        new_token(TType::SPACE_MAN, line);
                    } else if (current == "fr") {
                        new_token(TType::FR, line);
                    } else if (current == "and") {
                        new_token(TType::AND, line);
                    } else if (current == "less based than") {
                        new_token(TType::LESS_BASED_THAN, line);
                    } else if (current == "more based than") {
                        new_token(TType::MORE_BASED_THAN, line);
                    } else if (current == "wakanda forever") {
                        new_token(TType::WAKANDA_FOREVER, line);
                    } else if (current == "aight imma head out") {
                        new_token(TType::AIGHT_IMMA_HEAD_OUT, line);
                    } else if (current == "nvm") {
                        new_token(TType::NVM, line);
                    } else if (current == "as based as") {
                        new_token(TType::AS_BASED_AS, line);
                    } else if (current == "ded") {
                        new_token(TType::DED, line);
                    } else if (current == "floop") {
                        new_token(TType::FLOOP, line);
                    } else if (current == "mmm whatcha say") {
                        new_token(TType::MMM_WHATCHA_SAY, line);
                    } else if (current == "soooo random") {
                        new_token(TType::IM_SO_RANDOM, line);
                    } else if (current == "is") {
                        new_token(TType::IS, line);
                    } else if (is_numeric(current) && current.size() > 0) {
                        std::stringstream num_str(current);

                        int n = 0;
                        num_str >> n;

                        if (contains(valid_ints, n)) {
                            tokens.push_back(Token(TType::NUMBER, line, n));
                            current = "";
                        } else {
                            err("wtf " + std::to_string(n) + " isnt a real number", Token(TType::NUMBER, line, n));
                        }
                    } else if (is_all_upper(current)) {
                        tokens.push_back(Token(TType::VAR, line, current));
                        current = "";
                    } else {
                        current += data[i];
                    }

                    if (data[i] == '\n') {
                        new_token(TType::NEWLINE, line);
                        line ++;
                    }
                } else {
                    current += data[i];
                }
            }
        }
};