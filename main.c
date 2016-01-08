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

	//json_init_document_string(&json_doc, "{name:\"likai\" ,\"age\":123,test:[1,2,3],word:[{he:1,name:[3,3]}]}", print_back);
	json_init_document_file(&json_doc, "C:\\Users\\lk\\Documents\\Visual Studio 2015\\Projects\\Test\\Debug\\test.txt", print_back);
	json_value_t* json_root = json_parse_root(&json_doc);
	json_print_node(json_root, print_back);
	printf("\n");
	json_destory_document(&json_doc);	
	system("pause");
	return 0;
}