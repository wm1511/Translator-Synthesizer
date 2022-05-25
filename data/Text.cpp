#include "Text.h"

void translator::Text::lower()
{
    _strlwr_s(this->_text.data(), strnlen_s(this->_text.data(), this->_text.length()) + 1);
}

std::string& translator::Text::getText()
{
    return this->_text;
}

void translator::Text::setText(const std::string& text)
{
    this->_text = text;
}
