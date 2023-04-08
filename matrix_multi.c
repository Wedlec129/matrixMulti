#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <pthread.h>
int matrix_determinant();
int size;
int need_size;
void* take_matrix(char* string, int b, int c)
{
	int counter = 0;
	int** int_matrix = (int**)malloc(c * sizeof(int*));
	for(int i = 0; i < c; i++){
		int_matrix[i] = (int*)malloc(b * sizeof(int));
		for(int j = 0; j < b; j++){
			if(string[counter] == '\t'){
				counter++;
			}
			int_matrix[i][j] = (string[counter] - 48);
				//printf("%s\n", string);
			counter++;
		}
	}
	for(int i = 0; i < c; i++){
		for(int j = 0; j < b; j++){
			printf("%d ", int_matrix[i][j]);
		}
	printf("\n");
	}
	return int_matrix;
}

int matrix_detect(FILE* file)
{
	int flag = 0; //FLAG
	
	fseek(file, 0, SEEK_END);
	int razmer = ftell(file);
	fseek(file, 0, SEEK_SET);
	if(razmer == 0){
		printf("Файл пустой!\n");
		return 0;
	}
	else{
		char* string = (char*) malloc(razmer);
		fgets(string, razmer, file);
		int a = 0, b = 1;
		int c = 1;
		for(int i = 0; i < strlen(string); i++){ 
			if(((int)string[i] >= 48 && (int)string[i] <= 57) || (string[i] == '\t')){
				a++;
				if(i == strlen(string) - 1){
					if(string[i] == '\t'){
						return 0;
					}
					if(a != b){
						return 0;
					}
				}
				if((string[i] == '\t') && (c == 1)){
					c++;
					b = a - 1;
					a = 0;
				}
				else if((string[i] == '\t') && (c != 0) && (i != strlen(string) - 1)){
					if(a - 1!= b){
						return 0;
					}
					else{
						b = a - 1;
						a = 0;
						}
					c++;
				}
				else if((string[i] != '\t') && (c == 1)){
					b++;
				}
			}
			else{
				return 0;
			}
		}
		flag++;
		if(c == 1){
			b--;
		}
		if(c != b){
			return 0;
		}
		printf("Matrix size: %dx%d\n", c, b);
		size = c;
		int** int_matrix = take_matrix(string, b, c);
		int determ = matrix_determinant(int_matrix, c);
		printf("determ is = %d\n", determ);
	}
	return flag;
}
void* resize_matrix(int **matrix, int count_a, int count_b)
{
	//printf("\ncount %d|", count);
	//size++;
	int** rezult_matrix = (int**)malloc((size) * sizeof(int*));
	int a = 0;
	int b = 0;
	for(int i = 0; i < size; i++){
		if(i == count_a){
			a++;
		}
		b = 0;
		rezult_matrix[i] = (int*)malloc((size) * sizeof(int));
		for(int j = 0; j < size; j++){
			if(j == count_b){
				b++;
			}
			rezult_matrix[i][j] = matrix[i + a][j + b];
		}
	}
	printf("\n");
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%d ", rezult_matrix[i][j]);	
		}
		printf("\n");
	}
	//printf("yes1\n");
	return rezult_matrix;
}

int matrix_determinant(int **matrix)
{
	//printf("size %d", size);
	int determ = 0;
	int help_count;
	int need_size = 0;
	//int size_counter = 0;
	if(size == 1){
		return (matrix[0][0]);
	}
	if(size == 2){
		//printf("\nif size 2: determ = %d\n", matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
		return("%d", matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	}
	else{
		//int newmatrix[size - 1][size - 1];
		size--;
		for(int i = 0; i < size + 1; i++){
			//printf("\nno\n");
			//printf("\n|%d|",matrix[0][i]);
			if(i % 2 != 0){
				help_count = -1;
			}
			else{
				help_count = 1;
			}
			//printf("|%d|\n", help_count);
			determ += help_count * matrix[0][i] * matrix_determinant(resize_matrix(matrix, 0, i));
			//printf("determ %d is %d\n", i, determ);
			//size--;
		}
		size++;
	}
	return determ;
}
int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("arg error!");
		return 0;
	}
	FILE* file = fopen(argv[1], "r");
	if(file == NULL){
		printf("FILE error!\n");
		return 0;
	}
	printf("\nSTART PROGRAMM...\n\n");
	if(matrix_detect(file) == 1){
		printf("DONE!\n");
	}
	else{
		printf("Matrix not volid!\nwe can't find the determinant!\nSORRY:(\n");
		return 0;
	}
}
