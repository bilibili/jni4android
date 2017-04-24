%require "2.4"

%{
#include "j4a__yy.h"
#include "j4a_object.h"
#include "j4a_string.h"
#include "j4a_string_pool.h"
#include "ast.hpp"
%}

%code requires {
#include "j4a__yy.h"
#include "ast__forward.hpp"
}

%token              T_PACKAGE
%token              T_IMPORT

%token <num_int>    T_BOOLEAN
%token <num_int>    T_BYTE
%token <num_int>    T_FLOAT
%token <num_int>    T_DOUBLE
%token <num_int>    T_CHAR
%token <num_int>    T_SHORT
%token <num_int>    T_INT
%token <num_int>    T_LONG
%token <num_int>    T_VOID

%token <num_int>    T_PRIVATE
%token <num_int>    T_PROTECTED
%token <num_int>    T_PUBLIC

%token <num_int>    T_ABSTRACT
%token <num_int>    T_FINAL
%token <num_int>    T_STATIC

%token <num_int>    T_CLASS
%token <num_int>    T_INTERFACE

%token <string>     T_INTEGER_LITERAL
%token <string>     T_ID
%token              T_EOF       0   "end of file"

%union {
    int                     num_int;

    const j4a::string       *string;
    class int_set           *int_set;

    ast::Annotation           *annotation;
    ast::Annotations          *annotations;
    ast::Argument             *argument;
    ast::ArgumentList         *argument_list;
    ast::Class                *clazz;
    ast::CompilationUnit      *compilation_unit;
    ast::Identifier           *identifier;
    ast::ImportList           *import_list;
    ast::Field                *field;
    ast::MemberList           *member_list;
    ast::Method               *method;
    ast::ModifierSet          *modifier_set;
    ast::Identifier           *qualified_identifier;
    ast::Type                 *type;
}

%type <annotation>            annotation
%type <annotations>           annotations
%type <argument>              argument
%type <argument_list>         argument_list
%type <clazz>                 class
%type <clazz>                 class_head
%type <identifier>            class_identifier
%type <compilation_unit>      compilation_unit
%type <compilation_unit>      compilation_unit_head
%type <identifier>            identifier
%type <qualified_identifier>  import
%type <import_list>           import_list
%type <field>                 field
%type <member_list>           member_list
%type <method>                method
%type <num_int>               modifier
%type <modifier_set>          modifier_set
%type <qualified_identifier>  package
%type <type>                  primitive_type
%type <qualified_identifier>  qualified_identifier
%type <type>                  reference_type
%type <type>                  type
%type <num_int>               t_class_or_interface

%start compilation_unit

%%

annotation:
      '@' T_ID
      {
          BISON_LOGF("annotation: %s\n", $2->c_str());
          $$ = ast::Annotation::create(*$2);
      }
    | '@' T_ID '(' T_INTEGER_LITERAL ')'
      {
          BISON_LOGF("annotation: %s(%s)\n", $2->c_str(), $4->c_str());
          $$ = ast::Annotation::create(*$2);
          $$->set_value(*$4);
      }
;

annotations:
      {
          BISON_LOGF("annotations: NULL\n");
          $$ = ast::Annotations::create();
      }
    | annotations
      annotation
      {
          BISON_LOGF("annotations: ++\n");
          $$ = $1;
          $$->insert($2);
      }
;

argument:
      type T_ID
      {
          BISON_LOGF("argument: %s %s\n", $1->get_name().c_str(), $2->c_str());
          $$ = ast::Argument::create(*$2);
          $$->set_type($1);
      }
;

argument_list:
      {
          BISON_LOGF("argument_list: NULL\n");
          $$ = ast::ArgumentList::create();
      }
    | argument
      {
          BISON_LOGF("argument_list: << %s %s\n", $1->get_type()->get_name().c_str(), $1->get_name().c_str());
          $$ = ast::ArgumentList::create();
          $$->push_back($1);
      }
    | argument_list ','
      argument
      {
          BISON_LOGF("argument_list: << , %s %s\n", $3->get_type()->get_name().c_str(), $3->get_name().c_str());
          $$ = $1;
          $$->push_back($3);
      }
;

t_class_or_interface:
      T_CLASS     {$$ = $1;}
    | T_INTERFACE {$$ = $1;}

class_identifier:
      reference_type {$$ = ast::ClassIdentifier::make_ptr($1).detach();}

class_head:
      annotations
      modifier_set
      t_class_or_interface
      class_identifier
      '{' {
          BISON_LOGF("class\n");

          $4->set_prefix(ast::Context::instance()->get_local_namespace()->get_identifier());
          ast::Context::instance()->get_local_namespace()->add_class_identifier($4);

          $$ = ast::Class::create($4);
          if ($3 == T_INTERFACE)
              $$->set_is_interface(true);

          $$->set_annotations($1);
          $$->set_modifier_set($2);
          $$->get_local_namespace()->set_identifier($4);
          ast::Context::instance()->push_local_namespace($$->get_local_namespace());
      }

class:
      class_head
      member_list
      '}' {
          BISON_LOGF("class_body\n");
          $$ = $1;
          $$->set_member_list($2);

          ast::Context::instance()->pop_local_namespace();
      }
;

compilation_unit_head:
      package
      import_list {
          BISON_LOGF("compilation_unit_head:\n");
          $$ = ast::CompilationUnit::create();
          $$->set_package($1);
          $$->set_import_list($2);

          $$->get_local_namespace()->set_identifier($1);
          $$->get_local_namespace()->add_class_identifiers($2->begin(), $2->end());
          $$->get_local_namespace()->add_package_identifier($1);

          ast::Context::instance()->push_local_namespace($$->get_local_namespace());
      }


compilation_unit:
      compilation_unit_head
      class
      T_EOF {
          BISON_LOGF("compilation_unit_body:\n");
          $$ = $1;
          $$->set_clazz($2);

          ast::Context::instance()->pop_local_namespace();

          printf("----------\n");
          $$->debug_print(0);
          printf("----------\n");
          $$->build();
      }
;

field:
      annotations
      modifier_set type T_ID ';'
      {
          BISON_LOGF("method:\n");
          $$ = ast::Field::create(*$4);
          $$->set_annotations($1);
          $$->set_modifier_set($2);
          $$->set_type($3);
      }
;

method:
      annotations
      modifier_set type T_ID '(' argument_list ')' ';'
      {
          BISON_LOGF("method:\n");
          $$ = ast::Method::create(*$4);
          $$->set_annotations($1);
          $$->set_modifier_set($2);
          $$->set_type($3);
          $$->set_argument_list($6);
      }
    | annotations
      modifier_set T_ID '(' argument_list ')' ';'
      {
          BISON_LOGF("method:\n");
          $$ = ast::Constructor::create(*$3);
          $$->set_annotations($1);
          $$->set_modifier_set($2);
          $$->set_type(ast::ReferenceType::create($$->get_name()));
          $$->set_argument_list($5);
      }
;

member_list:
      {
          BISON_LOGF("member_list: NULL\n");
          $$ = ast::MemberList::create();
      }
    | member_list
      class
      {
          BISON_LOGF("member_list: + class: %s\n", $2->get_name().c_str());
          $$ = $1;
          $$->push_back($2);
      }
    | member_list
      field
      {
          BISON_LOGF("member_list: + field: %s\n", $2->get_name().c_str());
          $$ = $1;
          $$->push_back($2);
      }
    | member_list
      method
      {
          BISON_LOGF("member_list: + method: %s\n", $2->get_name().c_str());
          $$ = $1;
          $$->push_back($2);
      }
;

modifier:
      T_ABSTRACT          {BISON_LOGF("modifier: T_ABSTRACT\n");  $$ = T_ABSTRACT;}
    | T_FINAL             {BISON_LOGF("modifier: T_FINAL\n");     $$ = T_FINAL;}
    | T_PRIVATE           {BISON_LOGF("modifier: T_PRIVATE\n");   $$ = T_PRIVATE;}
    | T_PROTECTED         {BISON_LOGF("modifier: T_PROTECTED\n"); $$ = T_PROTECTED;}
    | T_PUBLIC            {BISON_LOGF("modifier: T_PUBLIC\n");    $$ = T_PUBLIC;}
    | T_STATIC            {BISON_LOGF("modifier: T_STATIC\n");    $$ = T_STATIC;}
;

modifier_set:
      {
          BISON_LOGF("modifier_set: NULL\n");
          $$ = ast::ModifierSet::create();
      }
    | modifier_set
      modifier
      {
          BISON_LOGF("modifier_set: ++\n");
          $$ = $1;
          $$->insert_token($2);
      }
;

package:
      T_PACKAGE qualified_identifier ';' {$$ = $2;}
;

identifier:
      T_ID {$$ = ast::Identifier::create(*$1);}
;

qualified_identifier:
      identifier {
          $$ = $1;
      }
    | qualified_identifier '.' identifier {
          $$ = $3;
          $$->set_prefix($1);
      }
;

import:
      T_IMPORT qualified_identifier ';' {$$ = $2;}
;

import_list:
      {
          BISON_LOGF("import_list: NULL\n");
          $$ = ast::ImportList::create();
      }
    | import_list
      import
      {
          BISON_LOGF("import_list: ++\n");
          $$ = $1;
          $$->push_back($2);
      }
;

primitive_type:
      primitive_type '[' ']' {
        $$ = $1;
        $$->set_is_array(true);
        BISON_LOGF("primitive_type: %s[]\n", $$->get_name().c_str());
      }
    | T_BOOLEAN {
        $$ = ast::BooleanType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_BYTE {
        $$ = ast::ByteType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_FLOAT {
        $$ = ast::FloatType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_DOUBLE {
        $$ = ast::DoubleType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_CHAR {
        $$ = ast::CharType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_SHORT {
        $$ = ast::ShortType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_INT {
        $$ = ast::IntType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_LONG {
        $$ = ast::LongType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
    | T_VOID {
        $$ = ast::VoidType::create();
        BISON_LOGF("primitive_type: %s\n", $$->get_name().c_str()); }
;

reference_type:
      reference_type '[' ']' {
        $$ = $1;
        $$->set_is_array(true);
        BISON_LOGF("reference_type: %s[]\n", $$->get_name().c_str());
      }
    | qualified_identifier {
        $$ = ast::ReferenceType::create($1);
        BISON_LOGF("reference_type: %s\n", $$->get_name().c_str());
    }
;

type:
    primitive_type { $$ = $1; }
  | reference_type { $$ = $1; }

%%
