#include "../inc/component.hpp"
#include <map>
#include <memory>
#include <string>

// map<std::string, shared_ptr<Component>> open_components_file(const string& file_name) {
// 	map<string, shared_ptr<Component>> components;

// 	FILE* file = fopen(file_name.c_str(), "r");

// 	if (file == NULL) {
// 		components["error"] = make_shared<Text>();
// 		components["error"]->set_text("error during file opening");
// 	}
// 	else {
// 		char c;
// 		string component_name, component_type, component_content;
// 		while (!set_str_from_file(file, &component_type, ':') && !set_str_from_file(file, &component_name, '{') && !set_str_from_file(file, &component_content, '}')) {
// 			cout << "Type : " << component_type << " Name : " << component_name << " Content : " << component_content << "\n";
// 			if (component_type == "Text") {
// 				components[component_name] = make_shared<Text>();
// 			}
// 			component_name.erase();
// 			component_type.erase();
// 			component_content.erase();
// 		}
// 		fclose(file);
	// }

// 	return components;
// }
