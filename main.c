// Test.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "utils.h"

void print_back(const char* json_string)
{
	printf("%s", json_string);
}

int main()
{


	json_document_t json_doc;

	json_init_document_string(&json_doc, "{name:\"likai\",\"age\":123,test:[1,2,3],word:[{he:1,name:[3,3]}]}", print_back);
	json_value_t* json_root = json_parse_root(&json_doc);

	printf("%d\n",json_is_object(json_root));
	
	printf("%d\n", json_object_haskey(json_root, "test"));

	printf("%d\n", json_object_haskey(json_root, "name1"));

	json_value_t* json_name = json_object_get(json_root, "name");

	const char* name = json_as_string(json_name);
	printf("%s\n", name);

	json_value_t* age = json_object_get(json_root, "age");

	int iage = json_as_int(age);

	printf("%d\n", iage);


	json_value_t* json_test = json_object_get(json_root, "test");

	json_value_t* json_child = json_child_first(json_test);

	while(json_child != NULL)
	{
		int child_i = json_as_int(json_child);
		printf("%d\n", child_i);
		json_child = json_child_next(json_test,json_child);
	}
	printf("\n");

	json_print_node(json_root, print_back);
	printf("\n");
	json_destory_document(&json_doc);	
	system("pause");
	return 0;
}