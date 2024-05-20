#pragma once
#include<string>
#include<vector>
#include "Lexer.h"
#include "utils.h"


std::string translate(const std::string& arg) {
	std::vector<std::string> tokens = tokenizer(arg);
	tokens.push_back("\0");
	std::string line;
	std::string result;
	const std::vector<std::string> var_declaration = { "int", "float", "char", "string", "double", "bool", "void", "auto" };
	const std::vector<std::string> operators = { "=", "-", "+", "/", "*", "%","==", "!=", "<="
	">=", "*=", "+=", "-=", "/=", "!", "%=", ">>", "<<", ":", "::", "++", "--", "(", "[", "{", "}", "]", ")"};
	const std::vector<std::string> control_flow = { "if", "for", "while", "else"};
	const std::vector<std::string> key_words = { "cout", "cin","return"};
	std::vector<std::string> variables = { "true", "false" };
	std::vector<std::string> functions = { "printf" };
	unsigned int nesting = 0;
	unsigned int paranteses_nesting = 0;
	int lines = 0;
	bool alr_p_dec_var = false;
	unsigned int in_func_dec_stage = 0; // 1 = type declaration, 2 = identifyer, 3 = argument, 4 = instructions
	unsigned int in_var_dec_stage = 0; // 1 = type declaration, 2 = identifyer, 3 = asignation
	bool in_list = false;
	unsigned int after_cout = 0; // counts the number of printed elements
	bool after_cin = false;
	bool in_if_arg = false;
	bool commentary = false;
	bool in_control_flow_arg = false;
	bool after_control_flow = false;
	bool include_first_brace = false; // to avoid a bug
	for (int i = 0; i < tokens.size(); i++) {
		if (include_first_brace) {
			line = cpp_to_py_nesting(nesting - 1) + line;
		}
		else {
			line = cpp_to_py_nesting(nesting) + line;
		}

		if (commentary) { // commentary case
			if (tokens[i] == "\n"){
				commentary = false;
				line += "\n";
			}
			else
				line += tokens[i] + " ";
		}
		else if (in(tokens[i], var_declaration)) { // declarative keyword case
			if (tokens[i] == "void") {
				in_func_dec_stage++;
			}
			else{
				in_var_dec_stage++;
			}
		}
		else if (in(tokens[i], control_flow)) { // control flow keyword case
			after_control_flow = true;
			line += tokens[i] + " ";
		}
		else if (in(tokens[i], key_words)) { //other keyword case
			if (tokens[i] == "cout") {
				line += "print (";
				after_cout = 1;
			}
			else if (tokens[i] == "cin") {
				after_cin = true;
			}
			else if (tokens[i] == "return")
				line += "return ";
		}
		else if (in(tokens[i], variables)) { // variable case
			if (tokens[i] == "true") line += "True";
			else if (tokens[i] == "false") 
				line += "False";
			else if(!after_cin)
				 if (in(tokens[i], var_declaration) || in(tokens[i], control_flow) || in(tokens[i], key_words))
					line += "_" + tokens[i];
				else
					line += tokens[i];
		}
		else if (in(tokens[i], functions)) { //function case
			if (tokens[i] == "printf") line += "print";
			else if (in(tokens[i], var_declaration) || in(tokens[i], control_flow) || in(tokens[i], key_words))
				line += "_" + tokens[i];
			else
				line += tokens[i];
		}
		else if (in(tokens[i], operators)) { // operator case
			if (tokens[i] == "<<" && after_cout > 0 && tokens[i - 1] != "cout") {
				line += ", ";
				after_cout++;
			}
			else if (tokens[i] == ">>" && after_cin) {
				line = "";
				for (int j = 0; j < nesting; j++)
					line += "\t";
				line += "_" + tokens[i + 1] + " = input()\n";
				result += line; 
				line = "";
			}
			else if (tokens[i] == ":") {
				line += " in ";
			}
			else if (tokens[i] == "::") {
				if (i > 0 && tokens[i - 1] != "std")
					line += ".";
			}
			else if (tokens[i] == "++") {
				line += " += 1";
			}
			else if (tokens[i] == "--") {
				line += " -= 1";
			}
			else if (tokens[i] == "(") {
				paranteses_nesting++;
				if (after_control_flow){
					in_control_flow_arg = true;
				}
				else{
					line += "(";
					if (in_func_dec_stage == 2)
						in_func_dec_stage++;
					else if (in_var_dec_stage == 2) {
						in_var_dec_stage = 0;
						in_func_dec_stage = 3;
					}
				}
			}
			else if (tokens[i] == ")") {
				paranteses_nesting--;
				if (in_func_dec_stage == 3 && paranteses_nesting == 0) {
					line = "def " + line;
					in_func_dec_stage++;
					line += "):\n";
					result += line;
					nesting++;
					line = cpp_to_py_nesting(nesting);
					nesting--;
				}
				else if (after_control_flow && paranteses_nesting == 0) {
					in_control_flow_arg = false;
					line += ":\n";
				}
				else
					line += ")";
			}
			else if (tokens[i] == "{") {
				if (in_func_dec_stage == 4) {
					result += line;
					line = "";
				}
				else if (in_var_dec_stage == 3)
					line += "[";
				else{
					nesting++;
					include_first_brace = true;
				}

			}
			else if (tokens[i] == "}") {
				if (in_var_dec_stage == 3) {
					line += "]";
					in_var_dec_stage = 0;
				}
				else{
					nesting--;
					if (in_func_dec_stage == 4)
						in_func_dec_stage = 0;
				}
			}
			else if (tokens[i] == "/" && tokens[i + 1] == "/") {
				line += "#";
				i++;
				commentary = true;
			}
			else if (tokens[i] == ".") {
				line += ".";
			}
			else if (tokens[i] == "=" && in_var_dec_stage == 2){
					in_var_dec_stage++;
					line += " = ";
			}
			else {
				if(tokens[i] != "<<" && tokens[i] != ">>")
					line += " " + tokens[i] + " ";

			}

		}
		else {
			if (in_s(begin_s(tokens[i]), "0123456789") && !after_cin) {
				line += clear_number(tokens[i]);
			}
			else if(tokens[i] == ";" && !in_control_flow_arg || tokens[i] == "\0") {
				
				if (after_cout)
					line += ")";

				if (in_var_dec_stage == 2)
					line += " = None";

				in_list = false;
				after_cout = 0;
				after_cin = false;
				in_if_arg = false;
				in_control_flow_arg = false;
				after_control_flow = false;
				if(include_first_brace){
					line = cpp_to_py_nesting(nesting - 1) + line;
				}
				else {
					line = cpp_to_py_nesting(nesting) + line;
				}

				result += line + '\n';
				lines++;
				line = "";
				include_first_brace = false;
				in_var_dec_stage = 0;
			}
			else if (begin_s(tokens[i]) == '"' || begin_s(tokens[i]) == '\'') {
				line += tokens[i];
			}
			else if(tokens[i] != "\n"){
				if (in_var_dec_stage == 1) {
					if (in(tokens[i], {"&", ">", "^", "*"})) {
						
					}
					else{
					in_var_dec_stage++;
					variables.push_back(tokens[i]);
					line += "_" + tokens[i];
					}
				}
				else if (in_func_dec_stage == 1) {
					in_func_dec_stage++;
					functions.push_back(tokens[i]);
					if (in(tokens[i], var_declaration) || in(tokens[i], control_flow) || in(tokens[i], key_words))
						line += "_" + tokens[i];
					else
						line += tokens[i];
				} 
			}
		}

		//file << nesting << " levels of nesting for " << tokens[i] << '\n';

	}
	return result;
}