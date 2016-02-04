#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bson.h>

/*
*   Current tokens for MongoDB :
*       - special characters : . || ( || ) || { || } ||  " || ' || ,
*       - logical operators :( $or || $and || $nor ) ==> logic_oper()
*       - reserves_keyWords :
*                1 - functions(reserved_words) : (find_token , update_token , use_token , db_token , remove_token) ==> db_functions()
*                        use : ==> use_function()
*                2 - symbols :
*                        - the identifiers || strings !!
*       - Numbers : number_token ==> number()
*/


















// Declare the structure of our LinkedList 
typedef struct list_bson
{
	char key[20];
	char value[20];
	struct list * next ;
}bson_list;







// Declare the structure of our LinkedList 
typedef struct list
{
	char key[20];
	char value[20];
	struct list * next ;
}find_list;

// Declare the head of the LinkedList 
find_list * head;

// Those varibales will help to save the current key and it's value , in order to pass it as parameters to insetToList function ! 
char Aux_key[20] ;
char Aux_value[20] ;
//char Aux_value_int ;

find_list * create_node(char key[20] , char  value[20])
{
	find_list * curr = (find_list * )malloc(sizeof(find_list)) ;
	strcpy(curr->key , key) ;
	strcpy(curr->value , value);
	curr->next = NULL ;
	return curr ;

}


void insertToList(char key[20] , char  value[20])
{
         
	find_list * prec = (find_list * )malloc(sizeof(find_list)) ;
	if(head == NULL)
		{
			head = (find_list * )malloc(sizeof(find_list)) ;
			strcpy(head->key , key) ;
			strcpy(head->value , value);
			head->next = NULL ;
		}
	else
	{
		find_list * curr = (find_list * )malloc(sizeof(find_list));	
	        curr = head;		
		while(curr->next != NULL)
		{	
			curr = curr->next;
		}

		curr->next  = create_node(key , value);
	}	


}


void explore_list(find_list * hd)
{   
   if(hd == NULL )
  {
	printf(" Your LinkedList is Empty \n");
  }
  else
  {
	find_list * curr = (find_list * )malloc(sizeof(find_list)) ;
	curr =  hd ;
	while(curr != NULL)
	{	printf("In Loop ");
		//printf("%s :: %s\n",curr->key,curr->value);
		curr = curr->next ;
	}
  }
}







int getListLength()
{
	find_list * curr = (find_list * ) malloc(sizeof(find_list));
	curr = head ;
	int length = 0 ;
	
	while(curr != NULL)
	{
		length++;
		curr = curr->next ;
	}
	return length ;
}


























typedef enum{
    db_token , find_token , insert_token ,update_token , use_token , remove_token, collection_idf_token , dot_token , opened_bracket_token , closed_bracket_token , comma_token , opened_brace_token
    , closed_brace_token , quotation_marks_token , apostrophe_token , colon_token , number_token , id_token , string_token , opened_box_brackets , closed_box_brackets , eq_token , gte_token , gt_token , lt_token , lte_token ,
         or_token , nor_token , ne_token , in_token , nin_token , not_token , show_token , dbs_token
}Tokens;




typedef enum{

    special_char_error , id_missing, opened_box_brackets_missing ,  closed_box_brackets_missing , colon_missing , closed_bracket_missing
    , opened_brace_missing , closed_brace_missing , db_keyWord_missing ,  dot_missing , opened_bracket_missing , undefined_function , comma_missing , $in_Or_$nin_missing
    ,invalid_number , dbs_token_missing

}error_tokens;






typedef struct
{
    Tokens keyWordToken ; char keyWord[8];
}KeyWords ;

find_list * update_lst ;
int cdts_length ;
char  * query;
char current_char ;
int  current_index ;
int query_length ;
char  current_word[15] ;
Tokens current_token ;
char * json ;
int jsonLength ;
FILE * dataBases_store ;
/** Some flags to know wich function used in the query
    if insert = 1 : we the fct use the insert function , if = 0 the query use another fct thant insert
**/
int insert , find , update , delete , use , show ;

/** variables to stock the db name  , and the collection name **/
char *  db_name ;
char  collection_name[15];


KeyWords key_Words[18] =
{{db_token , "db"} , {find_token , "find"} , {show_token , "show"} , {dbs_token , "dbs"} , {insert_token , "insert"} , {update_token , "update"} , {use_token , "use"} , {remove_token , "remove"} , {or_token , "$or"}, {nor_token , "$nor"} , {gt_token ,"$gt"},{gte_token ,"$gte"}
,{lt_token ,"$lt"},{lte_token ,"$lte"} ,{ne_token ,"$ne"} , {in_token , "$in" } ,  {nin_token , "$nin" } , {not_token , "$not"}};


 void print_token(Tokens token)
{
 switch( token )
 {
    case db_token:
        printf("db_token\n");
        break ;
    case show_token:
        printf("show_token\n");
        break ;
    case dbs_token:
        printf("dbs_token\n");
        break ;
    case remove_token :
	printf("remove_token\n");	
    case use_token:
        printf("use_token\n");
        break ;
    case find_token:
        printf("find_token\n");
        break ;
    case insert_token:
        printf("insert_token\n");
        break ;
    case update_token:
        printf("update_token\n") ;
        break ;
     case number_token :
        printf("number_token\n");
        break ;
      case  comma_token:
        printf("comma_token\n");
        break ;
    case quotation_marks_token :
        printf("quotation_marks_token\n");
        break ;
    case apostrophe_token :
        printf("apostrophe_token\n");
        break ;
    case opened_bracket_token:
        printf("opened_bracket_token\n");
        break ;
    case closed_bracket_token:
        printf("closed_bracket_token\n");
        break ;
    case opened_brace_token:
        printf("opened_brace_token\n");
        break ;
    case closed_brace_token:
        printf("closed_brace_token\n");
        break ;
    case dot_token:
        printf("dot_token\n");
        break ;
    case colon_token :
        printf("colon_token\n");
        break ;
    case id_token :
        printf("id_token\n");
        break ;
    case string_token:
        printf("string_token\n");
        break ;
    case opened_box_brackets :
        printf("opened_box_brackets\n");
        break ;
    case closed_box_brackets :
        printf("closed_box_brackets\n");
        break ;
    case gte_token :
        printf("gte_token\n");
        break;
    case gt_token :
        printf("gt_token\n");
        break;
    case lt_token :
        printf("lt_token\n");
        break ;
    case lte_token :
        printf("lte_token\n");
        break ;
    case eq_token :
        printf("eq_token\n");
        break ;
    case or_token :
        printf("or_token\n");
        break ;
    case nor_token:
        printf("nor_token\n");
        break ;
    case ne_token :
        printf("ne_token\n");
        break ;
    case in_token :
        printf("in_token\n");
        break ;
    case nin_token :
        printf("nin_token\n");
        break ;
    case not_token :
        printf("not_token\n");
        break ;

}
}

Tokens look_for_token(Tokens key_word)
{
switch( key_word )
{
    case db_token:
        print_token(db_token);
        return db_token ;
    case show_token:
        print_token(show_token);
        return show_token ;
     case dbs_token:
        print_token(dbs_token);
        return dbs_token ;
    case use_token:
        print_token(use_token);
        return use_token ;
    case find_token:
        print_token(find_token);
        return find_token ;
    case insert_token:
        print_token(insert_token);
        return insert_token ;
    case update_token:
        print_token(update_token);
        return update_token ;
   case remove_token :
	print_token(remove_token);
	return remove_token ;	
    case number_token :
        print_token(number_token);
        return number_token ;
    case  comma_token:
        print_token(comma_token);
        return comma_token ;
    case quotation_marks_token :
        print_token(quotation_marks_token);
        return quotation_marks_token ;
    case apostrophe_token :
        print_token(apostrophe_token);
        return apostrophe_token ;
    case opened_bracket_token:
        print_token(opened_bracket_token);
        return opened_bracket_token ;
    case closed_bracket_token:
        print_token(closed_bracket_token);
        return closed_bracket_token ;
    case opened_brace_token:
        print_token(opened_brace_token);
        return opened_brace_token ;
    case closed_brace_token:
        print_token(closed_brace_token);
        return closed_brace_token ;
    case dot_token:
        print_token(dot_token);
        return dot_token ;
    case colon_token :
        print_token(colon_token);
        return colon_token ;
     case id_token :
        print_token(id_token);
        return id_token ;
     case string_token :
        print_token(string_token);
        return string_token ;
     case opened_box_brackets :
        print_token(opened_box_brackets);
        return opened_box_brackets ;
     case closed_box_brackets :
        print_token(closed_box_brackets);
        return closed_box_brackets ;
    case gte_token :
        print_token(gte_token);
        return gte_token ;
    case gt_token :
        print_token(gt_token);
        return gt_token ;
    case lt_token :
        print_token(lt_token);
        return lt_token ;
    case lte_token :
        print_token(lte_token);
        return lte_token ;
    case eq_token :
        print_token(eq_token);
        return eq_token ;
    case or_token :
        print_token(or_token);
        return or_token ;
    case nor_token:
        print_token(nor_token);
        return nor_token ;
    case ne_token :
        print_token(ne_token);
        return ne_token ;
    case in_token :
        print_token(in_token);
        return in_token ;
    case nin_token :
        print_token(nin_token);
        return nin_token ;
    case not_token :
        print_token(not_token);
        return not_token ;


}
}


void print_error_token(error_tokens key_word)
{
switch (key_word)
{
case opened_brace_missing :
    printf("opened_brace_missing\n");
    break ;
case invalid_number :
    printf("invalid_number");
    break ;
case closed_brace_missing :
    printf("closed_brace_missing\n");
    break ;
case special_char_error :
    printf("special_char_error\n");
    break ;
case dbs_token_missing :
    printf("dbs_token_missing\n");
    break ;
case id_missing :
    printf("id_missing\n");
    break ;
case opened_box_brackets_missing :
    printf("opened_box_brackets_missing\n");
    break ;
case closed_box_brackets_missing :
    printf("closed_box_brackets_missing\n");
    break ;
case opened_bracket_missing :
    printf("opened_bracket_missing\n");
    break ;
case closed_bracket_missing :
    printf("closed_bracket_missing\n");
    break ;
case colon_missing :
    printf("colon_missing\n");
    break ;
case dot_missing :
    printf("dot_missing\n");
    break ;
case undefined_function :
    printf("undefined_function\n");
    break ;
case comma_missing :
    printf("comma_missing\n");
    break ;
case $in_Or_$nin_missing:
        printf("$in Or $nin operator is missing");


}
}





Tokens isKeyWord()
{
int i = 0 ;

while( i < 19)
{
if(strcmp(current_word ,key_Words[i].keyWord) == 0)
{
    return look_for_token(key_Words[i].keyWordToken);
}
else
    i++ ;
}
    return look_for_token(id_token);
}


Tokens special_char_function()
{
switch (current_char)
{
    case  ',':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(comma_token);
    case  ':':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(colon_token);
    case '"' :
    {
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        int i = 0 ; // as index
        while(1)
        {
            if(current_char == 34)
            {
                if(json != NULL && json[0] != '\0' )
                    {
                        current_word[i] = current_char ;
                        i++ ;
                        json[jsonLength] = current_char;
                        jsonLength++ ;
                    }
                current_index++;
                current_char = query[current_index];
                current_word[i-1] = '\0';
                return look_for_token(string_token);
             }
            else
            {
                if(json != NULL && json[0] != '\0' )
                    {
                        current_word[i] = current_char ;
                        i++ ;
                        json[jsonLength] = current_char;
                        jsonLength++ ;
                    }
                current_index++;
                current_char = query[current_index];
            }

        }
     }

    case '\'' :
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(apostrophe_token);
    case '(':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(opened_bracket_token);
    case ')':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(closed_bracket_token);
    case '{':
        if(json != NULL && json[0] != '\0' && strcmp(json , "{") != 0)
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(opened_brace_token);
    case '}':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(closed_brace_token);
    case '.':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(dot_token);
    case '[':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(opened_box_brackets);
    case ']':
        if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_index++;
        current_char = query[current_index];
        return look_for_token(closed_box_brackets);

}
}

Tokens numbrer_function()
{
	int i = 0 ;
if(json != NULL && json[0] != '\0' )
        {   current_word[i] = current_char ;
		i++ ;
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
    current_index++ ;
    current_char = query[current_index];
while(current_char >= 48 && current_char <= 57)
{
    if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }

     	
     current_word[i] = current_char ;
     i++ ;
    current_index++ ;
    current_char = query[current_index];
}       current_word[i] = '\0' ;
if( current_char == ' ' || current_char == ',' || current_char == '}')
{    return look_for_token(number_token);
}
/** Error Case **/
else
{
    print_error_token(invalid_number);
    exit(1);
}
}


Tokens string_function()
{

    int i = 0 ;
    while(current_char == '$' ||current_char >= 97 && current_char <= 122 || current_char >= 65 && current_char <= 90 || current_char >= 48 && current_char <= 57 || current_char == '_')
    {   if(json != NULL && json[0] != '\0' )
        {
            json[jsonLength] = current_char;
            jsonLength++ ;
        }
        current_word[i] = current_char ;
        current_index++ ;
        current_char = query[current_index];
        i++ ;
    }
    current_word[i] = '\0';
    return isKeyWord();
}

Tokens read_char()
{
while(current_char == ' ' || current_char == '\t')
{
    current_index++;
    current_char = query[current_index];
}
if( current_char == '$' || current_char >= 97 && current_char <= 122 || current_char >= 65 && current_char <= 90)
{
    return string_function();

}
if(current_char >= 48 && current_char <= 57)
{
    return numbrer_function();
}
/*
if(current_char == 36)
{
    ligical_oper_function();
}*/
if(  current_char == '[' || current_char == ']' ||current_char == ':' || current_char == '.' || current_char == ',' || current_char == '{' || current_char == '}' || current_char == '(' || current_char == ')' || current_char == '"' || current_char == '\'')
{
    return special_char_function();
}

}

void  verify_token(Tokens expected_token , error_tokens error)
{
if( current_token == expected_token)
{
    current_token = read_char();
}
else
{
    print_error_token(error);
    exit(1);
}
}




/** <leaf-inter> ::= , <leaf-value-list> | epsilon **/

void leaf_inter()
{
switch(current_token)
{
    case comma_token :
        current_token = read_char();
        leaf_value_list();
        break ;
     case closed_box_brackets :
        break ;

}
}

/** <leaf-value-list> ::= <leaf-value> <leaf-inter> **/
void leaf_value_list()
{
    leaf_value();
    leaf_inter();
}

/** <array> ::= [ <leaf-value-list> ] **/
void array()
{
    verify_token(opened_box_brackets , opened_box_brackets_missing);
    leaf_value_list();
    verify_token(closed_box_brackets , closed_box_brackets_missing);
}

/** <key> ::= <id-token> **/

void key()
{

    verify_token(id_token , id_missing);

}




/** <array-operator> ::= <in-operator> |  <nin-operator>  **/
void array_operator()
{
switch(current_token)
{
    case in_token :
        current_token = read_char();
        break ;
    case nin_token :
        current_token = read_char();
        break ;
}
}








/** <attributs-inter> ::= , <attributs-list> | epsilon **/

void attributs_inter()
{
switch(current_token)
{
    case comma_token :
        current_token = read_char();
        attributs_list();
        break ;
    case closed_brace_token:
        break ;
}
}


/** <attributs> ::= <key> : <leaf-value> **/
void attributs()
{
    key();
    verify_token(colon_token , colon_missing);
    leaf_value();
}



/** <attributs-list> ::= <attributs> <attributs-inter> **/
void attributs_list()
{
    attributs();
    attributs_inter();

}






/** <document> ::=  <attributs-list> } **/
void document()
{
    attributs_list();
    verify_token(closed_brace_token , closed_brace_missing);
}

/** <operator-inter> ::= , <key> : { <operator-list> | epsilon  **/

void operator_inter()
{
switch(current_token)
{
    case comma_token :
        current_token = read_char();
        key();
        verify_token(colon_token , colon_missing);
        verify_token(opened_brace_token , closed_brace_missing);
        operator_list();
        break ;
    case closed_brace_token:
        break ;
    default :
        printf("Error on operator_inter !");
        exit(1);
}
}

/** <value-operator> ::= <gt-operator> |
                     <gte-operator> |
                     <lt-operator> |
                     <lte-operator> |
                     <eq-operator> |
                     <ne-operator> |
                     <type-operator> |
                     <size-operator> |
                     <regex-operator> |
                     <exists-operator> **/

void value_operator()
{
switch(current_token)
{
    case gt_token :
        current_token = read_char();
        break ;
    case gte_token:
        current_token = read_char();
        break ;
    case lt_token :
        current_token = read_char();
        break ;
    case lte_token :
        current_token = read_char();
        break ;
    case eq_token:
        current_token = read_char();
        break ;
}

}


/** <operators> ::= <value-operator> : <leaf-value> } | <array-operator> : [ <leaf-value-list> ] } | <not-operator> : <operator> } |  <elemmatch-operator> : <expression> } **/
void operators()
{
switch(current_token)
{
    case gt_token: /** <value-operator> case **/
        {
            value_operator();
            verify_token(colon_token , colon_missing);
            leaf_value();
            verify_token(closed_brace_token , closed_brace_missing);
            break ;
         }
      case lt_token: /** <value-operator> case **/
        {
            value_operator();
            verify_token(colon_token , colon_missing);
            leaf_value();
            verify_token(closed_brace_token , closed_brace_missing);
            break ;
         }
     case in_token: /** <array-operator> : [ <leaf-value-list> ]  **/
        array_operator();
        verify_token(colon_token , colon_missing);
        verify_token(opened_box_brackets , opened_box_brackets_missing);
        leaf_value_list();
        verify_token(closed_box_brackets , closed_box_brackets_missing);
        break ;
    case nin_token: /** <array-operator> : [ <leaf-value-list> ]  **/
        array_operator();
        verify_token(colon_token , colon_missing);
        verify_token(opened_box_brackets , opened_box_brackets_missing);
        leaf_value_list();
        verify_token(closed_box_brackets , closed_box_brackets_missing);
        break ;
     case not_token :              /** <not-operator> : <operators>  **/
        current_token = read_char();
        verify_token(colon_token , colon_missing);
        operators();
        break ;
     default :
        printf("Oops , Error : Invalid Operator !");
        exit(1);

}

}
/** <operator-list> ::=  { <operators> <operator-inter> **/
void operator_list()
{
    operators();
    operator_inter();
}


/** <operator-object> ::=  <operator-list>   **/
void operator_object()
{
    operator_list();
}


/** <aux> ::= <operator-object> || <document> **/
void aux()
{ //print_token(current_token);
switch (current_token)
{
    case id_token:
        document();
        break ;
    case gt_token:
        if(insert == 1 )
        {
            printf("Oops , Error operation $gt not permitted !");
            exit(1);
        }
        operator_object();
        break ;
    case lt_token:
                if(insert == 1 )
        {
            printf("Oops , Error : operation $lt not permitted !");
            exit(1);
        }

        operator_object();
        break ;
     case in_token:
        if(insert == 1 )
        {
            printf("Oops , Error operation $gt not permitted !");
        }
        operator_object();
        break ;
    default :
    	//printf("*****> %s\n",current_word);
    	//current_token = read_char();
    	//printf("*****> %s\n",current_word);
    	//print_token(current_token);
        printf(" Aux Error.\n");
        exit(1);
}

}















/**<comment-clause> ::=  <comment-operator> : <string> }

<text-clause> ::=  <text-operator> : { <search-operator> : <string> } } |
                   <text-operator> : { <search-operator> : <string> , <language-operator> : <language> } } **/

/** <expression-inter> ::= , <expression-list> | epsilon **/
void expression_list();

void expression_inter()
{
switch(current_token)
{
    case comma_token:
        current_token = read_char();
        expression_list();
        break ;
    case closed_box_brackets:
        break ;
     default:
            printf("Oops , Error : Logical Expreesion Error .");
            break ;
}
}


/** <expression-list> ::= <request> <expression-inter> **/
void expression_list()
{
    request();
    expression_inter();
}

/** <logic-operator> ::= <or-operator> | <nor-operator> **/
void logic_operator()
{
switch(current_token)
{
    case or_token :
        current_token = read_char();
        break ;
    case nor_token :
        current_token = read_char();
        break ;
    default :
        printf("Unreconized Logical Operator");
        exit(1);
}
}

/** <expression-logic-clause> ::=  <logic-operator> : [ <expression-list> ]  **/

void expression_logic_clause()
{
    logic_operator();
    verify_token(colon_token , colon_missing);
    verify_token(opened_box_brackets , opened_box_brackets_missing);
    expression_list();
    verify_token(closed_box_brackets , closed_box_brackets_missing);

}

/** <leaf-clause> ::= <key> :  <value> **/
void leaf_clause()
{
    verify_token(colon_token , colon_missing);
    value();
}

/** <leaf-value> ::= <string-token> | <number-token> | <array> | <date> | <boolean> | <date> | <min-key> | <max-key> | <null> | <regex> | <function> | <binary> | <document> |  **/
void leaf_value()
{
switch(current_token)
{
    case string_token :
	 if(find == 1 || update == 1 || delete == 1 )
	{	
		strcpy(Aux_value , current_word);
		insertToList(Aux_key , Aux_value);		
	}   
        current_token = read_char();
        break ;
    case number_token :
	 if(find == 1 || update == 1 || delete == 1 )
	{	
		strcpy(Aux_value , current_word);
		insertToList(Aux_key , Aux_value);
	} 
	
	 current_token = read_char();
	
               break ;
    case opened_box_brackets :
        array();
        break ;
        case opened_brace_token :
        current_token = read_char();
        document();
        break ;
}
}



/** <value> ::= { <aux> | <leaf-value> **/
void  value()
{
switch (current_token)
{
    case string_token : /** <string >**/
        leaf_value();
        break ;
     case number_token : /** <number> **/
        leaf_value();
        break ;
     case opened_box_brackets : /** <array> **/
        leaf_value();
        break ;
    case opened_brace_token : /** <document>  || <operator-object> **/
       // printf("---->%s\n",current_word);
       //  print_token(current_token);
        current_token = read_char();
       // printf("----->%s\n",current_word);
        aux();
        break ;
}
}



/** <clause> ::= <expression-logic-clause> | <leaf-clause> |  <text-clause> |  <comment-clause>  **/
void clause()
{
    switch (current_token)
    {
        case id_token:
       
            if(find==1 || delete == 1 || update == 1 )
            {
            	strcpy(Aux_key , current_word);	
	    }
            current_token = read_char();
            leaf_clause();
            break ;
        case or_token:
            if(insert == 1)
            {
                printf("Oops , Error : Operation $or not permitted !");
                exit(1);
            }
             expression_logic_clause();
             break ;
        case nor_token:
            if(insert == 1)
            {
                printf("Oops , Error : Operation $nor not permitted !");
                exit(1);
            }
             expression_logic_clause();
             break ;
        default :
            printf("Error clause \n");
            exit(1);
    }
}


/** <clause-inter> ::=  , <clause-list> | epsilon **/

void  clause_inter()
{
int spy ;
switch(current_token)
{
    case comma_token :
        /** To add the first " of a key => looking for json format **/
        spy = jsonLength ;
        json[jsonLength] = '"';
        jsonLength++ ;
        current_token = read_char();
        /** To add the second  " of a key => looking for json format **/
        if(current_token == id_token)
            {   strcpy(Aux_key , current_word);
                json[jsonLength] = '"';
                jsonLength++ ;
            }
        else
        {
            int i ;
            for(i = spy ; i < jsonLength ; i++)
            {
                json[i] = json[i+1];
            }
        }
        clause_list();
    case closed_brace_token : /** epsilon case **/
            break ;
}

}


/** <clause-list> ::= <clause>  <clause-inter> **/
void clause_list()
{
    clause();
    clause_inter();
}


/** <request> ::= { <clause-list> } || epsilon  **/
void request()
{
int spy ;
switch(current_token)
{
case opened_brace_token :
    
    // Get the json 
    spy = jsonLength ;
    json[jsonLength] = '"';
    jsonLength++ ;
    current_token = read_char();
    if(current_token == id_token)
    {
        json[jsonLength] = '"';
        jsonLength++ ;

    }
    else
    {
    int i ;
    for(i = spy ; i < jsonLength ; i++)
    {
        json[i] = json[i+1];
    }
    }

    clause_list();
    verify_token(closed_brace_token , closed_brace_missing);
    break ;

case closed_bracket_token :
    if(insert == 1)
    {
        printf("Oops , Error : no object passed to insert!\n");
        exit(1);
    }

    break ;
default :
    printf(" Oops , Error :  ' ( ' Or ' { ' is missing !");
    exit(1);
}
}
/** <setaux> ::= <clause_list> } | $set : <request> } **/


void setaux()
{
	switch(current_token)
	{
		case id_token :
			clause_list();
			break;	
	}
}

/** <set> ::=  { <setaux>  **/

void set()
{
	 verify_token(opened_brace_token , opened_brace_missing);
	 setaux();
}


/** <pars_update>  ::=  <request> , <set>**/

void pars_update()
{
	request();
	cdts_length = getListLength();
	verify_token(comma_token , comma_missing);
	set();
}






/** <function> ::= insert_token (  <request>  )   | find_token   (  <request>   )
| remove_token (  <request>  )   | update_token (  <pars_update>  ) **/


void function()
{
switch(current_token)
{
    case insert_token :
        insert = 1 ;
        current_token = read_char();
        json[jsonLength] = current_char ;
        jsonLength++ ;
        verify_token(opened_bracket_token , opened_bracket_missing);
        request();
        verify_token(closed_bracket_token , closed_bracket_missing);
        break ;
    case find_token :

        find = 1 ; /** Set the flag of the function find to 1 , in order to call that function later !**/
	head = NULL ;
        current_token = read_char();
        json[jsonLength] = current_char ;
        jsonLength++ ;
        verify_token(opened_bracket_token , opened_bracket_token);
        request();
        verify_token(closed_bracket_token , closed_bracket_missing);
        break ;
   case remove_token :
        delete = 1 ; /** Set the flag of the function find to 1 , in order to call that function later !**/
	head = NULL ;
        current_token = read_char();
        json[jsonLength] = current_char ;
        jsonLength++ ;
        verify_token(opened_bracket_token , opened_bracket_token);
        request();
        verify_token(closed_bracket_token , closed_bracket_missing);
        break ;
   case update_token :
	update = 1 ;
        current_token = read_char();
        json[jsonLength] = current_char ;
        jsonLength++ ;
        verify_token(opened_bracket_token , opened_bracket_missing);
        pars_update();
	current_token = read_char() ;
        verify_token(closed_bracket_token , closed_bracket_missing);
        break ;


	
	

    default:
        print_error_token(undefined_function);
        exit(1);
}
}



/** <db-aux> ::=   . <collection_idf> . <function> | epsilon **/

void db_aux()
{
switch(current_token)
{
    case dot_token :
        current_token = read_char();


        // Get the colection name :
        int i ;
        for(i = 0 ; i < strlen(current_word) ; i++)
        {
            collection_name[i] = current_word[i];
        }
        collection_name[strlen(current_word)] = '\0';
        
        verify_token(id_token , id_missing);
        verify_token(dot_token , dot_missing);
        function();
        break ;
     default:

      if(current_char == 0)  /** Implementing db query **/
      {
          printf("Current database : %s\n",db_name);
      }
      else
      {
        printf("Oops , Error : db error !");
        exit(1);
      }
      break ;
}
}

/** <the_query> ::= <db-token> <db-aux> || <use-token> <dbName-token> || <show-token> <dbs-token> **/
void the_query()
{
switch(current_token)
{
    case db_token:
        current_token = read_char();
        db_aux();
        break ;
    case use_token :
        current_token = read_char();
        /** Change the data base **/
        db_name = current_word ;
        verify_token(id_token , id_missing);
        /** Initial the flag use to 1 : in order to know wich function to call later **/
        use = 1 ;
        break ;
    case show_token :
        current_token = read_char();
        verify_token(dbs_token , dbs_token_missing);
          /** Initial the flag use to 1 : in order to know wich function to call later **/
        show = 1 ;
        break ;
    default :
        printf("Oops , Error : Undefinded function");
        exit(1);

}
}


/** 				Use Fucnction 			**/
void use_function()
{ 
  	dataBases_store = fopen("database" , "a");
  	struct stat info;
    char file_dir[15];
    snprintf(file_dir, sizeof(file_dir), "db/%s",db_name);
    char file_path[15];
  if( stat(file_dir , &info ) != 0 ) /** If the dir of the data base dosn't exist , if so create a new dir with the name of db_name !!**/
    {
      char db_file_path[20];
      printf("No data base found , a new one will be created with the name %s\n",db_name);
      snprintf(db_file_path, sizeof(db_file_path), "mkdir db/%s",db_name);
      system(db_file_path);
      fputs(db_name , dataBases_store);
      fclose(dataBases_store);
    }
  if( info.st_mode & S_IFDIR )  /** If the dir of the data base exists !!**/
      {
        printf( "Using %s data base ...\n", db_name );
      }

}

void show_function()
{
  /** The  database.txt file contain the name of all the data bases used or created before **/
  system("cat database.txt");
}
void json_to_bson()
{
  bson_t *b;
  bson_error_t error;
  b = bson_new_from_json (json, -1, &error);
  /** Prepare the string to contain the path of the collection file **/
  char coll_file[20];
  snprintf(coll_file, sizeof(coll_file), "db/%s/%s",db_name ,collection_name);
  FILE * collec = fopen(coll_file,"a");

  if (!b)
  {
     printf ("Error: %s\n", error.message);
  }
  else
  {
     fwrite(bson_get_data(b),b->len,1,collec);
     printf("1 Object inserted , Data Base : %s , Collection :  %s \n",db_name , collection_name);
     bson_destroy (b);
     fclose(collec);
  }
}



/** Insert into db function **/

void  insert_function()
{
  struct stat info;
  char file_dir[50];
  snprintf(file_dir, sizeof(file_dir), "db/%s/%s",db_name ,collection_name);
  char file_path[50];
  if( stat(file_dir , &info ) != 0 ) /** If the file of the collection  dosn't exist , if so , we create a new file with the name of collection_name!!**/
  {

    char db_file_path[50];
    printf("No collection found with the name %s , a new one will be created with this name \n",collection_name);
    snprintf(db_file_path, sizeof(db_file_path), "touch db/%s/%s",db_name , collection_name);
    system(db_file_path);

    /** Function that will do the conversion from the json format to the bson formaat , and save it in the collection file .**/
    json_to_bson();
  }
  else /** If the dir of the data base exists !!**/
  {
      printf("Inserting document into the collection %s ...\n",collection_name);
   /** Function that will do the conversion from the json format to the bson formaat , and save it in the collection file .**/
      json_to_bson();
  }
}
/** 			Bson To Json 		**/

void bson_to_json()
{
   bson_reader_t *reader;
   const bson_t *b;
   bson_error_t error;
   char *str;

       char coll_file_path[100] ;
       snprintf(coll_file_path, sizeof(coll_file_path), "db/%s/%s",db_name,collection_name);
      reader = bson_reader_new_from_file (coll_file_path , &error);
      while ((b = bson_reader_read (reader, NULL)))
      {
	 str = bson_as_json(b, NULL);
         fprintf(stdout, "%s\n", str);
         bson_free(str);
      }
      bson_reader_destroy (reader);
}





void delete_function()
{
  bson_t *b;
  bson_iter_t iter;
  bson_reader_t *reader;
  const bson_value_t *val;
  bson_error_t error;  
  char coll_path[100] ;
  snprintf(coll_path, sizeof(coll_path), "db/%s/%s", db_name , collection_name);
  reader = bson_reader_new_from_file (coll_path ,false );
  int flag = 0 ;
  char temp_file[20] ;
  snprintf(temp_file, sizeof(temp_file), "db/%s/%s", db_name ,"temp_file");
  FILE * file = fopen(temp_file , "w");

  int length = getListLength();  
  int testConditions = 0 ;
 while ((b = bson_reader_read (reader, NULL)))
  {
      if (bson_iter_init (&iter, b))
      {
       while (bson_iter_next (&iter))
    {
         val = bson_iter_value (&iter);
	  char * str =  bson_iter_key (&iter) ;
	  /** value : char *  **/
         if (val->value_type == BSON_TYPE_UTF8)
        {  
           char * str2 =  val->value.v_utf8.str ;
           if( cdtStringExist(str , str2) == 1)  
	   {   		
		   testConditions += 1 ;	   
	   }
	 }
	 /** value : int 	**/
          if (val->value_type  == BSON_TYPE_INT32 )
       	 {  
         	if(cdtIntExist(str ,val->value.v_int32) == 1 )
         	{      	 		
			testConditions += 1 ;
	 	}
         }
      }  
  // If the number of the conditions verified == the length of our linked list ==> We print the json !
	  if(testConditions != length)
	  { 
	     flag = 1 ; 
	      fwrite(bson_get_data(b), 1, b->len, file); 
	  }
	  testConditions = 0 ;
    }
  } 	if(flag == 1)
 	{ 
	      char cmd[50];
	      snprintf(cmd, sizeof(cmd), "rm -f  db/%s/%s ",db_name , collection_name);
	      system(cmd);
	      char cmd2[50];
              snprintf(cmd2, sizeof(cmd2), "mv %s db/%s/%s  ",temp_file,db_name,collection_name);
              system(cmd2);
 	}

} 




































int isString(char string[20])
{
	int i = 0;
	for( i = 0 ; i < strlen(string) ; i++)
	{   
		if(string[i] >= 97 &&   string[i] <= 122 || string[i] >= 65 && string[i] <= 90)
		{
					continue ;
		}
		else
		{			return 0 ;
		}
	}
	return 1 ;




}

int cdtStringExist(char key[20] , char value[20])
{
	
		find_list * curr = (find_list * )malloc(sizeof(find_list)) ;
		curr =  head ;
		while(curr != NULL)
		{	
		       if( (strcmp(key , curr->key ) == 0 ) && (strcmp( value , curr->value) == 0) )
		     		{
		       			return 1 ; // We found a match with the condition given
		       		}
			curr = curr->next ;
               }

		// We didn't found a match with the condition given
		return 0 ;
 }

int cdtIntExist(char key[20] , int value)
{
	
		find_list * curr = (find_list * )malloc(sizeof(find_list)) ;
		curr =  head ;
		while(curr != NULL)
		{	
		       if( (strcmp(key , curr->key ) == 0 ) && atoi(curr->value) == value)
		     		{
		       			return 1 ; // We found a match with the condition given
		       		}
			curr = curr->next ;
		}
				
		// We didn't found a match with the condition given
		return 0 ;
 }



void find_function()
{
 
 
  bson_t *b;
  bson_iter_t iter;
  bson_reader_t *reader;
  const bson_value_t *val;
  bson_error_t error;  
  char coll_path[100] ;
  snprintf(coll_path, sizeof(coll_path), "db/%s/%s", db_name , collection_name);
  reader = bson_reader_new_from_file (coll_path ,&error );

  int length = getListLength();  
  int testConditions = 0 ;

 while ((b = bson_reader_read (reader, NULL)))
  {
      if (bson_iter_init (&iter, b))
      {
       while (bson_iter_next (&iter))
    {
         val = bson_iter_value (&iter);
	  char * str =  bson_iter_key (&iter) ;
         
	  /** value : char *  **/
         if (val->value_type == BSON_TYPE_UTF8)
        {  
           char * str2 =  val->value.v_utf8.str ;
           if( cdtStringExist(str , str2) == 1)  
	   {   		
		   testConditions += 1 ;	   
	   }
	 }

	 /** value : int 	**/
          if (val->value_type  == BSON_TYPE_INT32 )
       	 {  
         	if(cdtIntExist(str ,val->value.v_int32) == 1 )
         	{      	 		
			testConditions += 1 ;
	 	}
         }
      }
  // If the number of the conditions verified == the length of our linked list ==> We print the json !
	  if(testConditions == length)
	  {   
	      char * json ;
              json = bson_as_json(b , NULL);
              printf("%s\n",json);
	  }
	  testConditions = 0 ;
    }
  }
}







int cdtStringUpdate(char key[20] , char value[20] , find_list * curr)
{
		       if( (strcmp(key , curr->key ) == 0 ) )
		     		{
		       			return 1 ; // We found a match with the condition given
		       		}
	
		// We didn't found a match with the condition given
		return 0 ;
 }

int cdtIntUpdate(char key[20] , int value , find_list  * curr)
{
		       if( (strcmp(key , curr->key ) == 0 ))
		     		{
		       			return 1 ; // We found a match with the condition given
		       		}
	
		// We didn't found a match with the condition given
		return 0 ;
 }




void update_bson(bson_t * b , FILE *  file)
{   				
   bson_t bson_updated = BSON_INITIALIZER ;
   bson_init(&bson_updated);  
   bson_iter_t iter ;
  const bson_value_t * val ;

  if(update_lst == NULL )
  {
	printf(" Oops , Error :   No data given t \n");
  }

  else
    {  	
       find_list * curr = (find_list * )malloc(sizeof(find_list)) ;
	   curr =  update_lst ;
   
      		if (bson_iter_init(&iter, b))
       			{   
       	 			
       				while (bson_iter_next (&iter))
         			{   
        	 			val = bson_iter_value (&iter);
	  		 			char * str =  bson_iter_key (&iter) ;
	 					 /** value : char *  **/
         				if (val->value_type == BSON_TYPE_UTF8)
        				{    curr =  update_lst ;
     	   					char * str2 =  val->value.v_utf8.str ;
     	   					while(curr != NULL)
     	   					{
           						if(   (cdtStringUpdate(str , str2 , curr ) == 1 )  && (isString(curr->value) == 1)  )
	   								{   		
		     							BSON_APPEND_UTF8(&bson_updated, str , curr->value);
	   								}
	   							else if(isString(curr->value) == 1 )
	   								{    
	   									BSON_APPEND_UTF8(&bson_updated, str , str2);
	   								}
	   							curr = curr->next ;	
	   						}	
	 					}
	 					/** value : int 	**/
         			 if (val->value_type  == BSON_TYPE_INT32 )
       	 				{     curr =  update_lst ;
       	 					while(curr != NULL)
       	 					{
			         			if( (cdtIntUpdate(str ,val->value.v_int32 , curr) == 1) && ((isString(curr->value) == 0) ))
			         			{    
									BSON_APPEND_INT32(&bson_updated, str, atoi(curr->value));
				 				}
								else if(isString(curr->value) == 0)
								{
									BSON_APPEND_INT32(&bson_updated, str, val->value.v_int32 );
								}	
								curr = curr->next ;
							}
         				}

        		    }	    
               }
                //char * json ;
           		//json = bson_as_json(&bson_updated , NULL);
				//printf("---->%s\n",json); 
           		fwrite(bson_get_data(&bson_updated), 1, bson_updated.len, file); 
           		printf("  Document met a jour ! \n");
}
}
 








void cutList()
{      	find_list * curr ;
	find_list * prec ;

	update_lst = (find_list * )malloc(sizeof(find_list));
	int flag = 0 ;
	curr = (find_list * )malloc(sizeof(find_list));
        curr = head ;
	prec = (find_list * )malloc(sizeof(find_list));
	prec = curr ;
	while(flag < cdts_length)
	{	prec = curr ;
		curr = curr->next ;
		flag++ ;
	}
	update_lst = curr ;
	prec->next = NULL ;
}




void update_function()
{

  char temp_file[50] ;
  snprintf(temp_file, sizeof(temp_file), "db/%s/%s", db_name ,"temp_file");
  FILE * file = fopen(temp_file , "w");

  cutList();

  const bson_t *b;
  bson_iter_t iter;
  bson_reader_t *reader;
  const bson_value_t *val;
  bson_error_t error;  
  char coll_path[100] ;
  snprintf(coll_path, sizeof(coll_path), "db/%s/%s", db_name , collection_name);
  reader = bson_reader_new_from_file (coll_path ,&error );


  int length = getListLength();
  int testConditions = 0 ;
    
 while ((b = bson_reader_read (reader, NULL)))
  {
  	if (bson_iter_init (&iter, b))
      {
       while (bson_iter_next (&iter))
      { 
         val = bson_iter_value (&iter);
	  char * str =  bson_iter_key (&iter) ;
         
	  /** value : char *  **/
         if (val->value_type == BSON_TYPE_UTF8)
        {  
           char * str2 =  val->value.v_utf8.str ;
           if( cdtStringExist(str , str2) == 1)  
	   {   		
		   testConditions += 1 ;	   
	   }
	 }

	 /** value : int 	**/
          if (val->value_type  == BSON_TYPE_INT32 )
       	 {  
         	if(cdtIntExist(str ,val->value.v_int32) == 1 )
         	{      	 		
			testConditions += 1 ;
	 	}
         }
      }
  // If the number of the conditions verified == the length of our linked list ==> We print the json !
	  if(testConditions == length)
	  {   
	     
			update_bson(b  , file);
	  }
	  else
	  {
	  		fwrite(bson_get_data(b), 1, b->len, file); 
	  }
	  testConditions = 0 ;
    }
  }

    char cmd[50];
	snprintf(cmd, sizeof(cmd), "rm -f  db/%s/%s ",db_name , collection_name);
	system(cmd);
	char cmd2[50];
    snprintf(cmd2, sizeof(cmd2), "mv %s db/%s/%s  ",temp_file,db_name,collection_name);
    system(cmd2);

  }



































void executeQuery()
{
    /** Execute the quety depending on the flags (insert , find , delet , update , ..)**/

    /** insert query case's **/

  if(insert == 1)
  {
    insert_function();
  }
  if(use == 1)
  {
    use_function();
  }
  if(show == 1)
  {
      show_function();
  }
  if( find == 1)
  { 
	if(head == NULL)
  	{
  		bson_to_json();
  	}
	else
	{
    		find_function();
	}

  }
  if(delete == 1 )
  {
  	if(head != NULL)
	{
		delete_function();
	}
	else
	{
		printf("Error : No Conditions given ! ");
		exit(1);
	} 
  }
  if(update == 1 )
  {
  
  	if(head != NULL)
	{
		update_function();
	}
	else
	{
		printf("Error : No Condition giver ! ");
		exit(1);
	}	
  }


}


int main(int argc , char*argv[])
{


    /**
    * query : string to store the query given from the command line .
    */
    query = (char *) malloc(200 * sizeof(char))  ;

    /** Where we save the json extracted from the user's  query **/
    json = (char *)malloc(150 * sizeof(char));
    jsonLength = 0 ;

    /** Each flag related to a function **/
    insert = 0 ; find = 0 ; update = 0 ; delete = 0 ;
    cdts_length = 0 ;
    update_lst = NULL ;
    /** Initilaize the tree to null (this tree will be used in the Executing part of finf function )**/
   

    /**A loop to get the query from the command line **/
    int i ;
    for (i=1; i<argc; i++)
    {
        strcat(query, argv[i]);
        if (argc > i+1)
            strcat(query," ");
    }
    if(argc == 1)
    {
        printf("Oops , Error : Please enter a query .\n");
        exit(1);
    }


    // "db.mycol.insert({ name : \"hatim\"})";
                                    //"db.users.insert( { age: { $gt: 18 } })"
    // db.users.find({ status: "A" })

    else
    {   //  query = "db.hey.insert({name : \"hatim\" , age : 18})" ;
        query_length = strlen(query);
        current_index = 0 ;
        /** db_name is initilized to the default data base **/
        db_name = (char *)malloc(20* sizeof(char));
        db_name = "default";
        printf("Your query is : %s\n",query);
        while(current_index < query_length)
        {
    /** No need to increment current_index again , already done by other xx_function() !! **/
            current_char = query[current_index];
            current_token = read_char();
    /** The Start of the BNF . **/
            the_query();
        }
        json[jsonLength - 1] = '\0'; /** To cut the ( remains in the last character **/
        if(strcmp(json , ")") == 0)
        {
            json = "";
        }

        if(use != 1 || show != 1)
        {
          printf("Your json is : %s\n",json);
        }
        executeQuery();
    }
   
   

return 0;

}
