#include <json.h>
#include <json_parser.h>
#include <json_tokenizer.h>
#include <string>

json::json() { m_type = json_type::JNULL; }

json::json(const std::string &value) {
  m_type = json_type::JSTRING;
  m_value = value;
}

json::json(bool value) {
  m_type = json_type::JBOOLEAN;
  m_value = value ? "true" : "false";
}

json::json(int value) {
  m_type = json_type::JNUMBER;
  m_value = std::to_string(value);
}

json::json(float value) {
  m_type = json_type::JNUMBER;
  m_value = std::to_string(value);
}

json::json(double value) {
  m_type = json_type::JNUMBER;
  m_value = std::to_string(value);
}

json::json(const std::map<std::string, json> &properties) {
  m_type = json_type::JOBJECT;
  m_properties = properties;
}

json::json(const std::vector<json> &elements) {
  m_type = json_type::JARRAY;
  m_elements = elements;
}

json::json(json_type type) { m_type = type; }

void json::set_type(json_type type) {
  m_type = type;
  switch (type) {
  case json_type::JARRAY:
    m_properties.clear();
    m_value = "";
    break;
  case json_type::JOBJECT:
    m_elements.clear();
    m_value = "";
  case json_type::JBOOLEAN:
    m_elements.clear();
    m_properties.clear();
    m_value = "false";
    break;
  case json_type::JNUMBER:
    m_elements.clear();
    m_properties.clear();
    m_value = "0";
    break;
  case json_type::JNULL:
  case json_type::JSTRING:
    m_elements.clear();
    m_properties.clear();
    m_value = "";
    break;
  }
}

json_type json::get_type() const { return m_type; }

void json::set_value(const std::string &value) {
  m_type = json_type::JSTRING;
  m_elements.clear();
  m_properties.clear();
  m_value = value;
}

void json::set_value(bool value) {
  m_type = json_type::JBOOLEAN;
  m_elements.clear();
  m_properties.clear();
  m_value = value ? "true" : "false";
}

void json::set_value(int value) {
  m_type = json_type::JNUMBER;
  m_elements.clear();
  m_properties.clear();
  m_value = std::to_string(value);
}

void json::set_value(float value) {
  m_type = json_type::JNUMBER;
  m_elements.clear();
  m_properties.clear();
  m_value = std::to_string(value);
}

void json::set_value(double value) {
  m_type = json_type::JNUMBER;
  m_elements.clear();
  m_properties.clear();
  m_value = std::to_string(value);
}

void json::add_property(const std::string &key, const json &value) {
  m_properties[key] = value;
}

bool json::has_property(const std::string &key) const {
  return m_properties.find(key) != m_properties.cend();
}

json json::remove_property(const std::string &key) {
  if (has_property(key)) {
    json property = m_properties[key];
    m_properties.erase(key);
    return property;
  } else {
    return json();
  }
}

json json::get_property(const std::string &key) const {
  return m_properties.find(key)->second;
}

void json::add_element(const json &element) { m_elements.push_back(element); }

json json::remove_element(size_t index) {
  json element = m_elements[index];
  m_elements.erase(m_elements.cbegin() + index);
  return element;
}

json json::get_element(size_t index) const { return m_elements[index]; }

size_t json::get_size() const {
  return m_properties.size() + m_elements.size() + m_value.size();
}

template <> std::string json::as<std::string>() const { return m_value; }

template <> bool json::as<bool>() const {
  if (m_type == json_type::JOBJECT ||
      (m_type == json_type::JARRAY && m_elements.size() > 0) ||
      (m_type == json_type::JSTRING && m_value.size() > 0) ||
      (m_type == json_type::JNUMBER && m_value.size() > 0 &&
       m_value != std::to_string(0) && m_value != std::to_string(0.0) &&
       m_value[0] != '-') ||
      m_value == "true") {
    return true;
  }
  return false;
}

template <> int json::as<int>() const { return std::stoi(m_value); }

template <> float json::as<float>() const { return std::stof(m_value); }

template <> double json::as<double>() const { return std::stod(m_value); }

std::string json::to_string() const {
  if (m_type == json_type::JBOOLEAN) {
    return m_value;
  } else if (m_type == json_type::JNUMBER) {
    return m_value;
  } else if (m_type == json_type::JSTRING) {
    return "\"" + m_value + "\"";
  } else if (m_type == json_type::JOBJECT) {
    std::string str = "{";
    for (const auto &property : m_properties) {
      str += "\"" + property.first + "\"" + ":" + property.second.to_string();
      if (property.first != m_properties.crbegin()->first)
        str += ",";
    }
    return str + "}";
  } else if (m_type == json_type::JARRAY) {
    std::string str = "[";
    size_t length = m_elements.size();
    for (size_t i = 0; i < length; ++i) {
      str += m_elements[i].to_string();
      if (i != length - 1)
        str += ",";
    }
    return str + "]";
  }
  return "null";
}

json json::parse(std::istream &input) {
  json_tokenizer tokenizer;
  return json_parser::parse(tokenizer.tokenize(input));
}
