#include <iostream>
#include <vector>
#include <sstream>
#include <map>

template<class C, typename T>
bool contains(C&& c, T e) { return std::find(std::begin(c), std::end(c), e) != std::end(c); };

bool is_numeric(std::string str) {
   for (int i = 0; i < str.length(); i++)
      if (isdigit(str[i]) == false)
         return false; //when one non numeric value is found, return false
      return true;
}

bool is_all_upper(const std::string& word)
{
    for(auto& c: word) 
        if(!std::isupper(static_cast<unsigned char>(c))) 
            return false;
    return true;
}

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

    NEW_SHIT,
    NEWLINE
};

class Token {
    public:
        std::string content;
        int content_i;
        TType type;

        Token(TType type) {
            this -> type = type;
        }

        Token(TType type, std::string content) {
            this -> type = type;
            this -> content = content;
        }

        Token(TType type, int content) {
            this -> type = type;
            this -> content_i = content;
        }
};

class Lexer {
    private:
        std::string increment[9] = {"chad", "based", "redpilled", "poggers", "chungus", "keanu", "elon", "musk", "harambe"};
        std::string decrement[6] = {"virgin", "cringe", "bluepilled", "woman", "tiktok", "sus"};
        int valid_ints[6] = {34, 41, 42, 69, 420, 666};

        void new_token(TType type) {
            tokens.push_back(Token(type));
            current = "";
        }

    public:
        std::vector<Token> tokens;
        std::string current;

        Lexer(std::string data) {
            data += '\n';
            for (int i = 0; i < data.size(); i ++) {
                if (data[i] == '\n' || std::isspace(data[i])) {
                    if (contains(increment, current)) { // This monstrosity is very not great, but ehhhh whatever
                        new_token(TType::INCREMENT);
                    } else if (contains(decrement, current)) {
                        new_token(TType::DECREMENT);
                    } else if (current == "ratio") {
                        new_token(TType::RATIO);
                    } else if (current == "oh lawd") {
                        new_token(TType::OH_LAWD);
                    } else if (current == "comin") {
                        new_token(TType::COMIN);
                    } else if (current == "gimme some") {
                        new_token(TType::GIMME_SOME);
                    } else if (current == "new shit") {
                        new_token(TType::NEW_SHIT);
                    } else if (current == "space man") {
                        new_token(TType::SPACE_MAN);
                    } else if (current == "fr") {
                        new_token(TType::FR);
                    } else if (current == "and") {
                        new_token(TType::AND);
                    } else if (current == "less based than") {
                        new_token(TType::LESS_BASED_THAN);
                    } else if (current == "more based than") {
                        new_token(TType::MORE_BASED_THAN);
                    } else if (current == "wakanda forever") {
                        new_token(TType::WAKANDA_FOREVER);
                    } else if (current == "aight imma head out") {
                        new_token(TType::AIGHT_IMMA_HEAD_OUT);
                    } else if (current == "nvm") {
                        new_token(TType::NVM);
                    } else if (current == "as based as") {
                        new_token(TType::AS_BASED_AS);
                    } else if (current == "not as based as") {
                        new_token(TType::NOT_AS_BASED_AS);
                    } else if (current == "is") {
                        new_token(TType::IS);
                    } else if (is_numeric(current)) {
                        std::stringstream num_str(current);

                        int n = 0;
                        num_str >> n;

                        if (contains(valid_ints, n)) {
                            tokens.push_back(Token(TType::NUMBER, n));
                            current = "";
                        } else {
                            // Error here
                        }
                    } else if (is_all_upper(current)) {
                        tokens.push_back(Token(TType::VAR, current));
                        current = "";
                    } else {
                        current += data[i];
                        // Error here maybe?
                    }

                    if (data[i] == '\n') {
                        new_token(TType::NEWLINE);
                    }
                } else {
                    current += data[i];
                }
            }
        }
};

enum LayerType {
    LOOP,
    IF_BLOCK
};

class Parser {
    private:
        int find_var(std::string name) {
            auto ans = variables.find(name);

            if (ans != variables.end()) {
                return ans->second;
            }
        }

        void set(std::string var_name, int num, bool multiply, std::vector<Token> tokens, int i) {
            if (var_name != "") {
                if (tokens[i + 1].type == TType::NEWLINE || tokens[i + 1].type == TType::AND) {
                    auto ans = variables.find(var_name);

                    if (ans != variables.end()) {
                        if (!multiply) {
                            ans->second += num;
                        } else {
                            ans->second *= num;
                        }
                    }

                    i ++;
                } else {
                    // Error
                }
            } else {
                // Error
            }
        }
    public:
        std::map<std::string, int> variables;
        std::vector<LayerType> layers;

        void run(std::string data) {
            std::vector<Token> tokens = Lexer(data).tokens;
            std::string var_name = "";

            for (int i = 0; i < tokens.size(); i ++) {
                switch (tokens[i].type) {
                    case TType::OH_LAWD:
                        if (tokens[i + 1].type == TType::VAR && tokens[i + 2].type == TType::COMIN) {
                            variables.insert(
                                std::pair<std::string, int>
                                    (tokens[i + 1].content, 0));
                            i += 2;
                        } else {
                            // Error
                        }
                        break;
                    case TType::IS:
                        if (i == 0 || tokens[i - 1].type != TType::VAR) {
                            if (tokens[i + 1].type == TType::VAR && tokens[i + 3].type == TType::VAR) {
                                int o1 = find_var(tokens[i + 1].content);
                                int o2 = find_var(tokens[i + 3].content);

                                bool is_true;

                                switch (tokens[i + 2].type) {
                                    case TType::RATIO:
                                        is_true = o1 % o2 == 0;
                                        break;
                                    case TType::MORE_BASED_THAN:
                                        is_true = o1 > o2;
                                        break;
                                    case TType::LESS_BASED_THAN:
                                        is_true = o1 < o2;
                                        break;
                                    case TType::AS_BASED_AS:
                                        is_true = o1 == o2;
                                        break;
                                    case TType::NOT_AS_BASED_AS:
                                        is_true = o1 != o2;
                                        break;
                                    default:
                                        // Error
                                        break;
                                }

                                i += 3;

                                if (!is_true) {
                                    while (tokens[i].type != TType::NVM)
                                        i ++;
                                } else {
                                    layers.push_back(LayerType::IF_BLOCK);
                                }
                            } else {
                                // Error
                            }
                        } else if (tokens[i - 1].type == TType::VAR) {
                            var_name = tokens[i - 1].content;

                        } else {
                            // Error
                        }
                        break;

                    case TType::WAKANDA_FOREVER:
                        layers.push_back(LayerType::LOOP);
                        break;

                    case TType::AIGHT_IMMA_HEAD_OUT: { // May need to improve this – backpop count is a bit funky
                        int backpop_count = 1;

                        while (true) {
                            bool brk_flag = (layers.back() == LayerType::LOOP);
                            layers.pop_back();
                            backpop_count ++;

                            if (brk_flag)
                                break;
                        }

                        while (true) {
                            i ++;

                            if (tokens[i].type == TType::NVM) {
                                if (backpop_count > 0) {
                                    backpop_count --;
                                } else {
                                    break;
                                }
                            }
                        }

                        break;
                    }
                        
                    case TType::NVM:
                        if (layers.size() > 0) {
                            if (layers.back() == LayerType::IF_BLOCK) {
                                layers.pop_back();
                            } else if (layers.back() == LayerType::LOOP) { // Going backwards
                                int nvm_count = 0;

                                i --;

                                while (true) {
                                    if (tokens[i].type == TType::NVM) {
                                        nvm_count ++;
                                    }

                                    if (tokens[i].type == TType::IS && tokens[i-1].type != TType::VAR) {
                                        nvm_count --;
                                    }

                                    if (tokens[i].type == TType::WAKANDA_FOREVER && nvm_count == 0) {
                                        break;
                                    } else if (tokens[i].type == TType::WAKANDA_FOREVER) {
                                        nvm_count --;
                                    }

                                    i --;
                                }

                                i --;
                            }
                            break;
                        }

                    case TType::NUMBER:
                        set(var_name, tokens[i].content_i, false, tokens, i);
                        break;

                    case TType::INCREMENT:
                        set(var_name, 1, false, tokens, i);
                        break;

                    case TType::DECREMENT:
                        set(var_name, -1, false, tokens, i);
                        break;

                    case TType::RATIO:
                        set(var_name, 2, true, tokens, i);
                        break;

                    case TType::VAR:
                        set(var_name, find_var(tokens[i].content), false, tokens, i);
                        break;

                    case TType::GIMME_SOME:
                        if (tokens[i + 1].type == TType::VAR)
                            if (i < tokens.size() + 1) {
                                if (tokens[i + 2].type == TType::FR) {
                                    std::cout << find_var(tokens[i + 1].content);
                                    i += 2;
                                    break;
                                }
                            }

                            putchar(find_var(tokens[i + 1].content));

                        if (tokens[i + 1].type == TType::NEW_SHIT)
                            putchar('\n');
                        if (tokens[i + 1].type == TType::SPACE_MAN)
                            putchar(' ');

                        i ++;

                        break;

                    case TType::NEWLINE:
                        var_name = "";
                        break;

                    // case TType::IS:
                    //     if (tokens[i - 1].type == VAR)
                }
            }
        }
};