// #include <cstdio>
// #include <memory>
// #include <map>
// #include <string>
// #include <iostream>
// #include <unistd.h>
// #include "../inc/elements.hpp"
// #include "../inc/functions.h"

// map<string, shared_ptr<Element>> open_elts_file(const string& file_name) {
// 	map<string, shared_ptr<Element>> elements;

// 	FILE* file = fopen(file_name.c_str(), "r");

// 	if (file == NULL) {
// 		elements["error"] = make_shared<Text>();
// 		// elements["error"]->set_text("error during file opening");
// 	}
// 	else {
// 		char c;
// 		string elt_name, elt_type, elt_content;
// 		while (!set_str_from_file(file, &elt_type, ':') && !set_str_from_file(file, &elt_name, '{') && !set_str_from_file(file, &elt_content, '}')) {
// 			cout << "Type : " << elt_type << " Name : " << elt_name << " Content : " << elt_content << "\n";
// 			if (elt_type == "Text") {
// 				elements[elt_name] = make_shared<Text>();
// 			}
// 			elt_name.erase();
// 			elt_type.erase();
// 			elt_content.erase();
// 		}
// 		fclose(file);
//     }

// 	return elements;
// }
