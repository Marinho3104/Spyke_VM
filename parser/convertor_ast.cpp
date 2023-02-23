#include "convertor_ast.h"

#include "convertor_exceptions.h"
#include "ast_definitions.h"
#include "linked_list.h"
#include "ast_helper.h"
#include "byte_code.h"
#include "convertor.h"
#include "ast_nodes.h"
#include "opcodes.h"
#include <iostream>


utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast(Convertor* __convertor, Ast_Node* __ast_node) {

    utils::Linked_List <byte_code::Byte_Code*>* _byte_code = 
        new utils::Linked_List <byte_code::Byte_Code*>(0), *_temp;

    // std::cout << "Node type -> " << __ast_node->node_type << std::endl;

    switch (__ast_node->node_type)
    {
    case AST_NODE_NAME_SPACE: 

        _temp =
            get_byte_code_of_ast_node_name_space(
                __convertor, 
                (Ast_Node_Name_Space*) __ast_node
            );  

        _byte_code->join(
            _temp
        );

        delete _temp;

        break;
    
    case AST_NODE_CODE_BLOCK: 
    
        get_byte_code_of_ast_node_code_block(
            __convertor, 
            (Ast_Node_Code_Block*) __ast_node
        ); break;

    case AST_NODE_STRUCT_DECLARATION:

        get_byte_code_of_ast_node_struct_declaration(
            __convertor,
            (Ast_Node_Struct_Declaration*) __ast_node
        ); break;

    case AST_NODE_VARIABLE_DECLARATION:

        _temp =
            get_byte_code_of_ast_node_variable_declaration(
                __convertor,
                (Ast_Node_Variable_Declaration*) __ast_node
            );  

        _byte_code->join(
            _temp
        );

        delete _temp;

        break;

    case AST_NODE_FUNCTION_DECLARATION:

        get_byte_code_of_ast_node_function_declaration(
            __convertor,
            (Ast_Node_Function_Declaration*) __ast_node
        ); break;

    case AST_NODE_EXPRESSION:

        _temp =
            get_byte_code_of_ast_node_expression(
                __convertor,
                (Ast_Node_Expression*) __ast_node
            );
        
        _byte_code->join(
            _temp
        );

        delete _temp;
        
        break;

    case AST_NODE_VARIABLE:

        _byte_code->add(
            get_byte_code_of_ast_node_variable(
                __convertor,
                (Ast_Node_Variable*) __ast_node
            )
        ); break;

    case AST_NODE_FUNCTION_CALL:

        _temp =
            get_byte_code_of_ast_node_function_call(
                __convertor,
                (Ast_Node_Function_Call*) __ast_node
            );

        _byte_code->join(
            _temp
        );

        delete _temp;
        
        break;

    case AST_NODE_IMPLICIT_VALUE:

        _byte_code->add(
            get_byte_code_of_ast_node_implicit_value(
                __convertor,
                (Ast_Node_Implicit_Value*) __ast_node
            )
        ); break;

    case AST_NODE_POINTER_OPERATION:

        _temp =
            get_byte_code_of_ast_node_pointer_operations(
                __convertor,
                (Ast_Node_Pointer_Operation*) __ast_node
            );

        _byte_code->join(
            _temp
        );

        delete _temp;
        
        break;

    case AST_NODE_PARENTHESIS:

        _temp =
            get_byte_code_of_ast_node_parenthesis(
                __convertor,
                (Ast_Node_Parenthesis*) __ast_node
            );

        _byte_code->join(
            _temp
        );

        delete _temp;
        
        break;

    case AST_NODE_CONSTRUCTOR_CALL:

        _temp =
            get_byte_code_of_ast_node_constructor_call(
                __convertor,
                (Ast_Node_Constructor_Call*) __ast_node
            );

        _byte_code->join(
            _temp
        );

        delete _temp;
        
        break;

    default: break; throw Ordinary_Exception_Convertor("Unexpected Ast Node Type"); break;
    }

    return _byte_code;

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_name_space(Convertor* __convertor, Ast_Node_Name_Space* __ast_node_name_space) {

    utils::Linked_List <byte_code::Byte_Code*>* _byte_code =
        new utils::Linked_List <byte_code::Byte_Code*>(0), *_temp;

    __convertor->print("--> Get Byte Code Of Ast Node Name Space <--");

    for (int _ = 0; _ < __ast_node_name_space->declarations->count; _++) {

        _temp = get_byte_code_of_ast(
            __convertor,
            __ast_node_name_space->declarations->operator[](_)
        );

        _byte_code->join(
            _temp
        );

        delete _temp;

    }

    return _byte_code;

}

void parser::get_byte_code_of_ast_node_code_block(Convertor* __convertor, Ast_Node_Code_Block* __ast_node_code_block) {

    __convertor->print("--> Get Byte Code Of Ast Node Code Block <--");

    __convertor->set_block(
        __ast_node_code_block->code
    );

}

void parser::get_byte_code_of_ast_node_struct_declaration(Convertor* __convertor, Ast_Node_Struct_Declaration* __ast_node_struct_declaration) {

    __convertor->print("--> Get Byte Code Of Ast Node Struct Declaration <--");

    if (!__ast_node_struct_declaration->body_defined) {__convertor->print("--> Get Byte Code Of Ast Node Struct Declaration Out <--");return;}

    // std::cout << "Count -> " << __ast_node_struct_declaration->body->declarations->count << std::endl;

    for (int _ =  0; _ < __ast_node_struct_declaration->body->declarations->count; _++) {

        if (
            __ast_node_struct_declaration->body->declarations->operator[](_)->node_type == AST_NODE_FUNCTION_DECLARATION
        ) get_byte_code_of_ast_node_function_declaration(
            __convertor,
            (Ast_Node_Function_Declaration*) __ast_node_struct_declaration->body->declarations->operator[](_)
        );
        
        
        // __convertor->set_block(
        //     ((Ast_Node_Function_Declaration*) __ast_node_struct_declaration->body->declarations->operator[](_))->body->code
        // );

    }

    __convertor->print("--> Get Byte Code Of Ast Node Struct Declaration Out <--");

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_variable_declaration(Convertor* __convertor, Ast_Node_Variable_Declaration* __ast_node_variable_declaration) {

    __convertor->print("--> Get Byte Code Of Ast Node Variable Declaration <--");

    utils::Linked_List <byte_code::Byte_Code*>* _byte_code =
        new utils::Linked_List <byte_code::Byte_Code*>(0), *_temp;

    __ast_node_variable_declaration->stack_position = 
        __convertor->current_block->current_stack_size;

    _temp = get_byte_code_of_ast_node_constructor_call(
        __convertor,
        __ast_node_variable_declaration->constructor_call
    );

    _byte_code->join(
        _temp
    );

    delete _temp;

    _byte_code->add(
        byte_code::Byte_Code::generate(
            STACK_MEMORY_ALLOCATION,
            __ast_node_variable_declaration->representive_type->get_size()
        )
    );

    __convertor->current_block->current_stack_size += 
        _byte_code->last->object->argument;

    return _byte_code;

}

void parser::get_byte_code_of_ast_node_function_declaration(Convertor* __convertor, Ast_Node_Function_Declaration* __ast_node_function_declaration) {

    __convertor->print("--> Get Byte Code Of Ast Node Function Declaration <--");

    if (__ast_node_function_declaration->body_position == -1) 

        __ast_node_function_declaration->body_position =
            __convertor->add_block();

    if (!__ast_node_function_declaration->body_defined) return;

    __convertor->set_block(
        __ast_node_function_declaration->body->code,
        __ast_node_function_declaration->body_position
    );

    __convertor->blocks->operator[](__ast_node_function_declaration->body_position)->block->insert(
        byte_code::Byte_Code::generate(
            LOAD,
            __ast_node_function_declaration->representive_type->get_size()
        ), 0
    );

    for (int _ = 0; _ < __ast_node_function_declaration->parameters->count; _++)

        __convertor->blocks->operator[](__ast_node_function_declaration->body_position)->block->insert(
            byte_code::Byte_Code::generate(
                LOAD,
                __ast_node_function_declaration->representive_type->get_size()
            ), 1 + _
        );

    __convertor->print("--> Get Byte Code Of Ast Node Function Declaration Out <--");

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_expression(Convertor* __convertor, Ast_Node_Expression* __ast_node_expression) {

    __convertor->print("--> Get Byte Code Of Ast Node Expression <--");
        
    return 
        get_byte_code_of_ast(
            __convertor,
            __ast_node_expression->expression_instructions
        );

}

byte_code::Byte_Code* parser::get_byte_code_of_ast_node_variable(Convertor* __convertor, Ast_Node_Variable* __ast_node_variable) {

    __convertor->print("--> Get Byte Code Of Ast Node Variable <--");
    // std::cout << "Stack position -> " << __convertor->current_block->current_stack_size - 
    //             (__convertor->current_block->current_stack_size - __ast_node_variable->variable_declaration->stack_position) << std::endl;

    return 
        byte_code::Byte_Code::generate(
            LOAD,
            __convertor->current_block->current_stack_size - 
                (__convertor->current_block->current_stack_size - __ast_node_variable->variable_declaration->stack_position)
        );

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_function_call(Convertor* __convertor, Ast_Node_Function_Call* __ast_node_function_call) {

    __convertor->print("--> Get Byte Code Of Ast Node Function Call <--");

    utils::Linked_List <byte_code::Byte_Code*>* _byte_code = 
        new utils::Linked_List <byte_code::Byte_Code*>(0), *_temp;

    int _current_stack = __ast_node_function_call->representive_type->get_size();

    for (int _ = 0; _ < __ast_node_function_call->parameters->count; _++) {

        // std::cout << "Current stack -> " << _current_stack << std::endl;
        // std::cout << "Count param -> " << __ast_node_function_call->parameters->count << std::endl;

        if (
            __ast_node_function_call->parameters->operator[](_)
        ) {

            _temp = get_byte_code_of_ast_node_expression(
                __convertor,
                __ast_node_function_call->parameters->operator[](_)
            );

            _byte_code->join(
                _temp
            );

            _byte_code->add(
                byte_code::Byte_Code::generate(
                    LOAD,
                    -1 * _current_stack
                )
            );

            delete _temp;

        }

        _current_stack += 
            __ast_node_function_call->function_declaration->parameters_type->operator[](_)->get_size();

        

    }

    _byte_code->add(
        byte_code::Byte_Code::generate(
            CALL,
            __ast_node_function_call->function_declaration->body_position
        )
    );

    return _byte_code;  

}

byte_code::Byte_Code* parser::get_byte_code_of_ast_node_implicit_value(Convertor* __convertor, Ast_Node_Implicit_Value* __ast_node_implicit_value) {

    __convertor->print("--> Get Byte Code Of Ast Node Implicit Value <--");

    exit(1);

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_pointer_operations(Convertor* __convertor, Ast_Node_Pointer_Operation* __ast_node_pointer_operation) {

    __convertor->print("--> Get Byte Code Of Ast Node Pointer Operations <--");

    utils::Linked_List <byte_code::Byte_Code*>* _byte_code = 
        new utils::Linked_List <byte_code::Byte_Code*>(0), *_temp;

    if (!__ast_node_pointer_operation->pointer_level) return _byte_code;

    _temp = get_byte_code_of_ast(
        __convertor,
        __ast_node_pointer_operation->value
    );

    _byte_code->join(
        _temp
    );

    delete _temp;

    int _pointer_level = __ast_node_pointer_operation->pointer_level;

    char _code = 
        _pointer_level > 0 ? SET_ADDRESS_INTO_STACK : GET_ADDRESS_FROM_STACK;
    
    if (_pointer_level < 0) _pointer_level *= -1;

    for (int _ = 0; _ < _pointer_level; _++)

        _byte_code->add(
            byte_code::Byte_Code::generate(
                _code, 0
            )
        );

    return _byte_code;

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_parenthesis(Convertor* __convertor, Ast_Node_Parenthesis* __ast_node_parenthesis) {

    __convertor->print("--> Get Byte Code Of Ast Node Parenthesis <--");

    return get_byte_code_of_ast_node_expression(
        __convertor,
        __ast_node_parenthesis->expression
    );

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_constructor_call(Convertor* __convertor, Ast_Node_Constructor_Call* __ast_node_constructor_call) {

    __convertor->print("--> Get Byte Code Of Ast Node Constructor Call <--");

    return 
        get_byte_code_of_ast_node_function_call(
            __convertor,
            __ast_node_constructor_call->constructor
        );

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_accessing(Convertor*, Ast_Node_Accessing*) {

}

utils::Linked_List <byte_code::Byte_Code*>* parser::get_byte_code_of_ast_node_byte_code(Convertor*, Ast_Node_Accessing*) {

}




