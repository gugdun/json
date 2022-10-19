#include <json_token.h>
#include <json_parser.h>
#include <stdexcept>

json json_parser::parse(std::queue<json_token> &tokens) {
  json current;
  if (tokens.empty()) {
    throw std::runtime_error("Unexpected end of file");
  } else if (tokens.front().type == token_type::TNULL) {
    current.set_type(json_type::JNULL);
    tokens.pop();
  } else if (tokens.front().type == token_type::TBOOLEAN) {
    current.set_type(json_type::JBOOLEAN);
    current.set_value(tokens.front().value);
    tokens.pop();
  } else if (tokens.front().type == token_type::TNUMBER) {
    current.set_type(json_type::JNUMBER);
    current.set_value(tokens.front().value);
    tokens.pop();
  } else if (tokens.front().type == token_type::TSTRING) {
    current.set_type(json_type::JSTRING);
    current.set_value(tokens.front().value);
    tokens.pop();
  } else if (tokens.front().type == token_type::TBRACE_OPEN) {
    current.set_type(json_type::JOBJECT);
    tokens.pop();
    while (!tokens.empty() && tokens.front().type != token_type::TBRACE_CLOSE) {
      if (tokens.front().type != token_type::TSTRING) {
        throw std::runtime_error("Property name expected, found: " + tokens.front().value);
      }
      std::string key = tokens.front().value;
      tokens.pop();
      if (!tokens.empty() && tokens.front().type != token_type::TCOLON) {
        throw std::runtime_error("Expected ':', got \"" + tokens.front().value + "\"");
      } else if (tokens.empty()) {
        throw std::runtime_error("Unexpected end of file");
      }
      tokens.pop();
      if (tokens.empty()) {
        throw std::runtime_error("Unexpected end of file");
      }
      current.add_property(key, json_parser::parse(tokens));
      if (tokens.front().type == token_type::TCOMMA) {
        tokens.pop();
        if (tokens.empty() || tokens.front().type == token_type::TBRACE_CLOSE) {
          throw std::runtime_error("Comma unexpected");
        }
      }
    }
    if (tokens.empty()) {
      throw std::runtime_error("Unexpected end of file");
    } else {
      tokens.pop();
    }
  } else if (tokens.front().type == token_type::TBRACKET_OPEN) {
    current.set_type(json_type::JARRAY);
    tokens.pop();
    while (!tokens.empty() && tokens.front().type != token_type::TBRACKET_CLOSE) {
      current.add_element(json_parser::parse(tokens));
      if (tokens.front().type == token_type::TCOMMA) {
        tokens.pop();
        if (tokens.empty() || tokens.front().type == token_type::TBRACKET_CLOSE) {
          throw std::runtime_error("Comma unexpected");
        }
      }
    }
    if (tokens.empty()) {
      throw std::runtime_error("Unexpected end of file");
    } else {
      tokens.pop();
    }
  }
  
  return current;
}
