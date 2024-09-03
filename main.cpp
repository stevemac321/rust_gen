#include <iostream>
#include <fstream>
#include <string>

// Function to ask the user for the element type
std::string askElementType() {
    std::cout << "What type of elements do you want your array to consist of in your function?\n";
    std::cout << "1.) chars\n";
    std::cout << "2.) ints\n";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "1") return "char";
    if (choice == "2") return "i32";
    return "i32";
}

// Function to list available types for selected element type
std::string askTypeOption(const std::string& element_type) {
    std::cout << "Choose the type option for the selected element type:\n";
    if (element_type == "char") {
        std::cout << "1.) String\n";
        std::cout << "2.) &str\n";
        std::cout << "3.) Vec<char>\n";
        std::cout << "4.) &[char]\n";
        std::cout << "5.) &[char; 3]\n";
        std::cout << "6.) All\n";
    } else if (element_type == "i32") {
        std::cout << "1.) Vec<i32>\n";
        std::cout << "2.) &[i32]\n";
        std::cout << "3.) &[i32; 3]\n";
        std::cout << "4.) All\n";
    }

    std::string choice;
    std::getline(std::cin, choice);
    return choice;
}

// Function to generate the Rust code for each type
void generateFunction(std::ofstream& outfile, const std::string& func_name, const std::string& param_type, bool is_char, bool include_mutable) {
    // Generate immutable version
    outfile << "fn " << func_name << "_immutable(arr: " << param_type << ") {\n";
    if (is_char && (param_type == "String" || param_type == "&str")) {
        outfile << "    for elem in arr.chars() {\n";
    } else {
        outfile << "    for elem in arr.iter() {\n";
    }
    outfile << "        println!(\"{}\", elem);\n";
    outfile << "    }\n";
    outfile << "}\n\n";

    // Generate mutable version if applicable
    if (include_mutable) {
        outfile << "fn " << func_name << "_mutable(mut arr: " << param_type << ") {\n";
        if (param_type != "&str") {
            outfile << "    let mut arr = arr;\n";
        }
        if (is_char && (param_type == "String" || param_type == "&str")) {
            outfile << "    for elem in arr.chars() {\n";
        } else {
            outfile << "    for elem in arr.iter() {\n";
        }
        outfile << "        println!(\"{}\", elem);\n";
        outfile << "    }\n";
        outfile << "}\n\n";
    }
}

// Function to generate Rust functions based on user input
void generateFunctions(const std::string& element_type, const std::string& type_option, const std::string& filename) {
    std::ofstream outfile(filename);

    if (element_type == "char") {
        if (type_option == "1" || type_option == "6") {
            generateFunction(outfile, "fn_string", "String", true, true);
        }
        if (type_option == "2" || type_option == "6") {
            generateFunction(outfile, "fn_str", "&str", true, false);
        }
        if (type_option == "3" || type_option == "6") {
            generateFunction(outfile, "fn_vec_char", "Vec<char>", true, true);
        }
        if (type_option == "4" || type_option == "6") {
            generateFunction(outfile, "fn_slice_char", "&[char]", true, false);
        }
        if (type_option == "5" || type_option == "6") {
            generateFunction(outfile, "fn_array_char", "&[char; 3]", true, false);
        }
    } else if (element_type == "i32") {
        if (type_option == "1" || type_option == "4") {
            generateFunction(outfile, "fn_vec_int", "Vec<i32>", false, true);
        }
        if (type_option == "2" || type_option == "4") {
            generateFunction(outfile, "fn_slice_int", "&[i32]", false, false);
        }
        if (type_option == "3" || type_option == "4") {
            generateFunction(outfile, "fn_array_int", "&[i32; 3]", false, false);
        }
    }

    // Generate the main function
    outfile << "fn main() {\n";
    if (element_type == "char") {
        if (type_option == "1" || type_option == "6") {
            outfile << "    let string_example = String::from(\"abc\");\n";
            outfile << "    fn_string_immutable(string_example.clone());\n";
            outfile << "    fn_string_mutable(string_example);\n";
        }
        if (type_option == "2" || type_option == "6") {
            outfile << "    let str_example: &str = \"abc\";\n";
            outfile << "    fn_str_immutable(str_example);\n";
        }
        if (type_option == "3" || type_option == "6") {
            outfile << "    let vec_char_example: Vec<char> = vec!['a', 'b', 'c'];\n";
            outfile << "    fn_vec_char_immutable(vec_char_example.clone());\n";
            outfile << "    fn_vec_char_mutable(vec_char_example);\n";
        }
        if (type_option == "4" || type_option == "6") {
            outfile << "    let slice_char_example: &[char] = &['a', 'b', 'c'];\n";
            outfile << "    fn_slice_char_immutable(slice_char_example);\n";
        }
        if (type_option == "5" || type_option == "6") {
            outfile << "    let array_char_example: [char; 3] = ['a', 'b', 'c'];\n";
            outfile << "    fn_array_char_immutable(&array_char_example);\n";
        }
    } else if (element_type == "i32") {
        if (type_option == "1" || type_option == "4") {
            outfile << "    let vec_int_example: Vec<i32> = vec![1, 2, 3];\n";
            outfile << "    fn_vec_int_immutable(vec_int_example.clone());\n";
            outfile << "    fn_vec_int_mutable(vec_int_example);\n";
        }
        if (type_option == "2" || type_option == "4") {
            outfile << "    let slice_int_example: &[i32] = &[1, 2, 3];\n";
            outfile << "    fn_slice_int_immutable(slice_int_example);\n";
        }
        if (type_option == "3" || type_option == "4") {
            outfile << "    let array_int_example: [i32; 3] = [1, 2, 3];\n";
            outfile << "    fn_array_int_immutable(&array_int_example);\n";
        }
    }
    outfile << "}\n";

    outfile.close();
}

// Main function
int main() {
    std::string element_type = askElementType();
    std::string type_option = askTypeOption(element_type);

    std::cout << "\nReview your choices:\n";
    std::cout << "Element type: " << element_type << "\n";
    std::cout << "Type option: " << type_option << "\n";

    std::cout << "\nIs this correct? (Y/N)\n";
    std::string confirmation;
    std::getline(std::cin, confirmation);

    if (confirmation == "Y" || confirmation == "y") {
        std::cout << "\nEnter the filename to save the generated Rust code:\n";
        std::string filename;
        std::getline(std::cin, filename);
        
        std::cout << "\nGenerating Rust code...\n\n";
        generateFunctions(element_type, type_option, filename);
        std::cout << "Rust code has been saved to " << filename << "\n";
    } else {
        std::cout << "Operation canceled.\n";
    }

    return 0;
}
