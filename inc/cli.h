#include <map>
#include <string>
#include <memory>
#include "../inc/elements.hpp"

map<string, shared_ptr<Element>> open_elts_file(const string& file_name);
