#include <json_token.h>

std::string json_token::to_string() {
  switch (type) {
  case TSTRING:
    return "string (" + value + ")";
  case TBOOLEAN:
    return "boolean (" + value + ")";
  case TNUMBER:
    return "number (" + value + ")";
  case TNULL:
    return "null";
  case TBRACE_CLOSE:
    return "}";
  case TBRACE_OPEN:
    return "{";
  case TBRACKET_OPEN:
    return "[";
  case TBRACKET_CLOSE:
    return "]";
  case TCOMMA:
    return ",";
  case TCOLON:
    return ":";
  }
}
