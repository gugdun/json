#ifndef _JSON_H
#define _JSON_H

#include <istream>
#include <map>
#include <string>
#include <vector>

enum json_type { JNULL, JBOOLEAN, JNUMBER, JSTRING, JOBJECT, JARRAY };

class json {
public:
  json();
  json(const std::string &value);
  json(bool value);
  json(int value);
  json(float value);
  json(double value);
  json(const std::map<std::string, json> &properties);
  json(const std::vector<json> &elements);
  json(json_type type);

  void set_type(json_type type);
  json_type get_type() const;

  void set_value(const std::string &value);
  void set_value(bool value);
  void set_value(int value);
  void set_value(float value);
  void set_value(double value);

  void add_property(const std::string &key, const json &value);
  bool has_property(const std::string &key) const;
  json remove_property(const std::string &key);
  json get_property(const std::string &key) const;

  void add_element(const json &element);
  json remove_element(size_t index);
  json get_element(size_t index) const;

  size_t get_size() const;

  template <typename T> T as() const;
  template <> std::string as() const;
  template <> bool as() const;
  template <> int as() const;
  template <> float as() const;
  template <> double as() const;

  std::string to_string() const;
  static json parse(std::istream &input);

private:
  json_type m_type;
  std::string m_value;
  std::map<std::string, json> m_properties;
  std::vector<json> m_elements;
};

#endif // _JSON_H
