#include <stdio.h>
#include <stdlib.h>

#include "error.h"

typedef struct {
	char author[AUTOR_LINE_LEN];
	char title[TITLE_LINE_LEN];
	char publishing[PUBLISHING_LINE_LEN];
	unsigned short year;
	unsigned short count_of_line;
} Order;

Order* getOrders(FILE* file_base) {
	Order* orders = calloc(ORDERS_NUMBERS, sizeof(Order));

	for (int i = 0; i < 4000; i++) {
		Order ord;

		fread(ord.author, 1, sizeof(ord.author), file_base);
		fread(ord.title, 1, sizeof(ord.title), file_base);
		fread(ord.publishing, 1, sizeof(ord.publishing), file_base);
		fread(&ord.year, 1, sizeof(ord.year), file_base);
		fread(&ord.count_of_line, 1, sizeof(ord.count_of_line), file_base);

		orders[i] = ord;

		printf("%s | %s | %s | %d | %d\n", orders[i].author, orders[i].title, orders[i].publishing, orders[i].year, orders[i].count_of_line);
	}

	return orders;
}

int main() {
	int error_code = OK;
	
	FILE* file_base = fopen("testBase1.dat", "rb");
	
	if (file_base != NULL) {
		Order* orders = getOrders(file_base);

		fclose(file_base);
		free(orders);
	} else
		printf("File testBase1.dat is not found!\n");

	return error_code;
}
