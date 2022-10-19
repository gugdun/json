#ifndef _JSON_PARSER_H
#define _JSON_PARSER_H

#include <json.h>
#include <json_token.h>
#include <queue>

class json_parser {
public:
  static json parse(std::queue<json_token> &tokens);
};

#endif // _JSON_PARSER_H
