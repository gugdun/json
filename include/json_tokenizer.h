#ifndef _JSON_TOKENIZER_H
#define _JSON_TOKENIZER_H

#include <json_token.h>
#include <istream>
#include <queue>

class json_tokenizer {
public:
  std::queue<json_token> &tokenize(std::istream &input);
private:
  std::queue<json_token> m_tokens;
};

#endif // _JSON_TOKENIZER_H
