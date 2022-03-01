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