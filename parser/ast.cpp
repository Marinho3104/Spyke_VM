#include "ast.h"

#include "code_information.h"
#include "linked_list.h"
#include "ast_helper.h"
#include "ast_nodes.h"
#include "token.h"

#include <iostream>


parser::Ast::~Ast() { 

    global_name_space->~Ast_Node_Name_Space(); free(global_name_space);

    delete name_space_control; 

    // Check if open nodes is empty    
    delete open_nodes; 

}

parser::Ast::Ast(Code_Information* __code_information, utils::Linked_List <Token*>* __tokens_collection) 
    : tokens_collection(__tokens_collection) { 

        name_space_chain = new utils::Linked_List <Name_Space*>();
        open_nodes = new utils::Linked_List <Ast_Node*>();

        name_space_control = new Name_Space_Control();

        generate_ast_nodes(); 
        
}

void parser::Ast::print(const char* __information) {

    if (0) return;

    std::cout << "\n";

    for (int _  = 0; _ < open_nodes->count + 1; _++)

        std::cout << "\t";

    std::cout << __information << std::endl;

}

void parser::Ast::generate_ast_nodes() 
    { global_name_space = Ast_Node_Name_Space::generate(this, name_space_control->name_spaces_collection->first->object); }

void parser::Ast::add_to_chain(Name_Space* __name_space) { name_space_chain->add(__name_space, 0); }

void parser::Ast::pop_from_chain() { delete name_space_chain->remove(name_space_chain->count); }


