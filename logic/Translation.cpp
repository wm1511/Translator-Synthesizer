#include "Translation.h"

void translator::Translation::translate(Dictionary& dict, Text& text)
{  
    text.lower();

    const std::regex rgx("[a-zA-ZąćęłńóśźżĄĆĘŁŃÓŚŹŻ]+");
    std::smatch smt;
    std::vector<std::string> words;
    std::string source(text.getText());
    std::string result = std::regex_replace(source, rgx, "$");
    
    while (std::regex_search(source, smt, rgx))
    {
        words.push_back(smt[0]);
        source = smt.suffix();
    }

    for (std::string& word : words)
    {
        size_t pos = result.find('$');
        result.replace(pos, 1, dict.getEquivalent(word));
    }

    text.setText(result);
}