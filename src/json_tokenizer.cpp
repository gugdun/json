#include <json_tokenizer.h>
#include <stdexcept>

std::queue<json_token> &json_tokenizer::tokenize(std::istream &input) {
  while (!input.eof()) {
    char c = input.get();
    if (input.eof()) break;
    if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
      continue;
    } else if (c == '[') {
      m_tokens.push(json_token(token_type::TBRACKET_OPEN));
    } else if (c == ']') {
      m_tokens.push(json_token(token_type::TBRACKET_CLOSE));
    } else if (c == '{') {
      m_tokens.push(json_token(token_type::TBRACE_OPEN));
    } else if (c == '}') {
      m_tokens.push(json_token(token_type::TBRACE_CLOSE));
    } else if (c == ':') {
      m_tokens.push(json_token(token_type::TCOLON));
    } else if (c == ',') {
      m_tokens.push(json_token(token_type::TCOMMA));
    } else if (c == 'n') {
      std::string str = "n";
      while (!input.eof() && str.length() < 4) {
        c = input.get();
        str.push_back(c);
      }
      if (str != "null") {
        throw std::runtime_error("Expected \"null\", got \"" + str + "\"");
      } else {
        m_tokens.push(json_token());
      }
    } else if (c == 't') {
      std::string str = "t";
      while (!input.eof() && str.length() < 4) {
        c = input.get();
        str.push_back(c);
      }
      if (str != "true") {
        throw std::runtime_error("Expected \"true\", got \"" + str + "\"");
      } else {
        m_tokens.push(json_token(token_type::TBOOLEAN, "true"));
      }
    } else if (c == 'f') {
      std::string str = "f";
      while (!input.eof() && str.length() < 5) {
        c = input.get();
        str.push_back(c);
      }
      if (str != "false") {
        throw std::runtime_error("Expected \"false\", got \"" + str + "\"");
      } else {
        m_tokens.push(json_token(token_type::TBOOLEAN, "false"));
      }
    } else if (c == '"') {
      std::string str;
      while (!input.eof() && (c = input.get()) != '"')
        str.push_back(c);
      if (c != '"') {
        std::string message = "Expected '\"', got '";
        message.push_back(c);
        message.push_back('\'');
        throw std::runtime_error(message);
      } else {
        m_tokens.push(json_token(token_type::TSTRING, str));
      }
    } else if (c == '-' || (c >= '0' && c <= '9')) {
      std::string str;
      do {
        str.push_back(c);
      } while (!input.eof() && ((c = input.get()) == '.' || (c >= '0' && c <= '9')));
      std::stod(str); // check format
      json_token number = json_token(token_type::TNUMBER, str);
      m_tokens.push(number);
      input.unget();
    }
  }
  return m_tokens;
}
