#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define N 5

int main(int argc, char** argv)
{
	FILE* fptr = NULL;

	fptr = fopen("hello.bin", "w");
	assert(fptr);

	for (int i = 0; i<N; i++) {
		int n = i+65;
		fwrite(&n, sizeof(int), 1, fptr);
	}

	fclose(fptr);

	fptr = fopen("hello.bin","rb");
	assert(fptr);

	printf("\nReverseOrder\n");
	fseek(fptr, -sizeof(int), SEEK_END);
	
	for (int i = 0; i<N;i++) {
		int n;
		fread(&n, sizeof(int), 1, fptr);
		printf("{%c}\n",n);
		fseek(fptr, -2*sizeof(int),SEEK_CUR);
	}
	fseek(fptr, sizeof(int),SEEK_SET);
	for (int i=0;i<N;i++){
		int n;
		fread(&n, sizeof(int), 1, fptr);
		printf("{%c}\n",n);
	}
	
	fclose(fptr);
	return EXIT_SUCCESS;
}
