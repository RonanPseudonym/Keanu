#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <string>

#include "lexer.h"

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
                    err("you can't chain operators without newlines or and operators dumbass", tokens[i]);
                }
            } else {
                // err("you can't use 'is' without declaring the variable before ffs", tokens[i]);
            }
        }
    public:
        std::map<std::string, int> variables;
        std::vector<LayerType> layers;

        Parser() {
            srand(time(0));
        }

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
                            err("you can't oh lawd without a variable and a 'comin', obviously", tokens[i]);
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
                                        err("that's not an operator", tokens[i]);
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
                                err("you need two variables in 'is' statements", tokens[i]);
                            }
                        } else if (tokens[i - 1].type == TType::VAR) {
                            var_name = tokens[i - 1].content;

                        } else {
                            err("that's not how you use 'is'", tokens[i]);
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

                    case TType::DED:
                        set(var_name, 0, true, tokens, i);
                        break;

                    case TType::FLOOP:
                        set(var_name, -1, true, tokens, i);
                        break;

                    case TType::COMMUNIST:
                        if (tokens[i+1].type == TType::VAR) {
                            int nvalue = std::stoi(std::to_string(find_var(var_name)) + std::to_string(find_var(tokens[i+1].content) - 1));
                            
                            auto ans = variables.find(var_name);

                            if (ans != variables.end()) {
                                ans->second = nvalue;
                            }
                            
                            i += 2;
                        } else {
                            err("you cant be communist without a variable to communize dumbass", tokens[i]);
                        }
                        break;

                    case TType::IM_SO_RANDOM:
                        set(var_name, rand() % 100, false, tokens, i);
                        break;

                    case TType::MMM_WHATCHA_SAY:
                        std::cout << "> ";
                        set(var_name, getchar(), false, tokens, i);
                        getchar();

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