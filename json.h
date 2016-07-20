/***************************************************************************
*            json.h
*
*  Tue January 05 01:23:48 2016
*  Copyright  2016  lk
*  <user@host>
****************************************************************************/
/*
* json.h
*
* Copyright (C) 2016 - lk
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED

#include <stdio.h>

#include "types.h"
#include "utils.h"
#ifdef __cplusplus
extern "C"
{
#endif
typedef enum json_type_e
{
	JSON_ARRAY,
	JSON_OBJECT,
	JSON_PAIR,
	JSON_ID,
	JSON_STRING,
	JSON_INT,
	JSON_DOUBLE,
	JSON_BOOL,
	JSON_NULL,
	JSON_ERROR
}json_type_t;


#define WORD_STRING 257
#define WORD_INT    258
#define WORD_ID    259
#define WORD_DOUBLE 260

typedef struct json_word_s {
	int wtype;
	int val_len;
	union
	{
		const char* string_val;//may not end with '\0',length is val_len;
		int         int_val;
		double      double_val;
	};

}json_word_t;

typedef struct json_value_pair_s
{
	struct json_value_s* json_key;
	struct json_value_s* json_val;
}json_value_pair_t;

typedef struct json_value_list_s
{
	DEF_LIST_HEADER_TYPE(json_value_s);
}json_value_list_t;

typedef struct json_value_s
{
	DEF_LIST_HEADER_TYPE(json_value_s);
	json_type_t json_type;
	union
	{
		int               bool_val;
		int               int_val;
		double            double_val;
		char*             string_val;
		json_value_pair_t pair_val;
		json_value_list_t list_val;
	};
}json_value_t;

typedef void(*print_json_callback)(const char* json_string);

typedef struct json_document_s
{
	const char* file_path;
	const char* json;
	FILE*       file;
	int         json_len;
	const char* cur_pos;
	json_word_t cur_word;
	json_word_t lookup;
	json_value_t json_error;
	pool_t*      memery_pool;
	bool_t       malloc_fast;
	bool_t       quote_key;
	bool_t       double_quote;
	print_json_callback   print_callback;
}json_document_t;



int json_init_document_empty(json_document_t* json_doc,print_json_callback print_back);
int json_init_document_file(json_document_t* json_doc, const char* file_path, print_json_callback print_back);
int json_init_document_string(json_document_t* json_doc, const char* string_json, print_json_callback print_back);
int json_destory_document(json_document_t* json_doc);
void json_set_dobule_quote(json_document_t* json_doc,bool_t bdquote);
void json_set_quote_key(json_document_t* json_doc, bool_t bquote_key);

json_value_t* json_parse_root(json_document_t* json_doc);
json_value_t* json_parse_root_pool(json_document_t* json_doc, pool_t* pool);

bool_t        json_is_array(json_value_t* json_val);
bool_t        json_is_object(json_value_t* json_val);
bool_t        json_is_string(json_value_t* json_val);
bool_t        json_is_int(json_value_t* json_val);
bool_t		  json_object_haskey(json_value_t* json_val, const char* key);

int           json_as_int(json_value_t* json_val);
const char*   json_as_string(json_value_t* json_val);
const char*   json_pair_getkey_str(json_value_t* json_val);
json_value_t* json_pair_getkey(json_value_t* json_val);
json_value_t* json_pair_getval(json_value_t* json_val);
unsigned int  json_child_count(json_value_t* json_val);
json_value_t* json_child_get(json_value_t* json_val, unsigned int index);
json_value_t* json_object_get(json_value_t* json_val, const char* key);
json_value_t* json_child_first(json_value_t* json_val);
json_value_t* json_child_next(json_value_t* json_val, json_value_t* json_child);

bool_t        json_print_node(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_int(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_double(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_key(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_bool(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_null(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_string(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_array(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_object(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);
bool_t        json_print_pair(json_document_t* json_doc,json_value_t* json_val, print_json_callback print_back);

json_word_t*  word_next(json_document_t* json_doc);
json_word_t*  word_lookup(json_document_t* json_doc);

json_value_t* json_set_int_word(json_value_t* json_val, json_word_t* json_word);
json_value_t* json_set_double_word(json_value_t* json_val, json_word_t* json_word);
json_value_t* json_set_id_word(json_value_t* json_val, json_word_t* json_word, pool_t* pool);
json_value_t* json_set_string_word(json_value_t* json_val, json_word_t* json_word, pool_t* pool);
json_value_t* json_set_pair(json_value_t* json_pair, json_value_t* json_key, json_value_t* json_val);
json_value_t* json_list_push(json_value_t* json_list, json_value_t* json_val);

json_value_t* json_new_value(json_type_t json_type, pool_t* pool);
json_value_t* json_parse_pair(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_object(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_array(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_id(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_string(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_int(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_double(json_document_t* json_doc, pool_t* pool);
json_value_t* json_parse_value(json_document_t* json_doc, pool_t* pool);

json_value_t* json_create_value(json_document_t* json_doc, json_type_t json_type);
json_value_t* json_create_object(json_document_t* json_doc);
json_value_t* json_create_array(json_document_t* json_doc);
json_value_t* json_create_id(json_document_t* json_doc,const char* str_val);
json_value_t* json_create_string(json_document_t* json_doc, const char* str_val);
json_value_t* json_create_int(json_document_t* json_doc, int int_val);
json_value_t* json_create_double(json_document_t* json_doc, double double_val);

bool_t        json_add_val2obj(json_document_t* json_doc, json_value_t* obj, json_value_t* key, json_value_t* val);
bool_t        json_add_val2arr(json_value_t* arr, json_value_t* val);
#ifdef __cplusplus
}
#endif
#endif // JSON_H_INCLUDED
