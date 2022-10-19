#ifndef _JSON_TOKEN_H
#define _JSON_TOKEN_H

#include <string>

enum token_type {
  TNULL,
  TBOOLEAN,
  TNUMBER,
  TSTRING,
  TBRACE_OPEN,
  TBRACE_CLOSE,
  TBRACKET_OPEN,
  TBRACKET_CLOSE,
  TCOMMA,
  TCOLON
};

struct json_token {
  std::string value;
  token_type type;
  json_token(token_type type = token_type::TNULL, std::string value = "") : type(type), value(value) {}
  std::string to_string();
};

#endif // _JSON_TOKEN_H
