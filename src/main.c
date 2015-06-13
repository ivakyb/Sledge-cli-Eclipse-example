
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <Sledge/cli/cli.h>


int main(void)
{
	char in[100], response[300];  // строковые буфферы входной и ответной строки
	int8_t rv;  // return value - результат обработки команды

	puts(CLI_GREETING);  // вывести приветственное сообщение
	fflush(stdout);  // Опустошить буффер. Некоторые реализации stdlib кешируют поток и задерживают вывод.

	main2();

	do{
		gets(in);  // ввод команды с консоли
		rv = cli_command( response, sizeof(response), in, NULL );  // обработка команды
		puts(response);  // вывести ответ в консоль
		fflush(stdout);  // см.выше
	}while( rv!=1 ); // команда "exit" вернет 1 и цикл прекратится

	return EXIT_SUCCESS;
}

int main2(void)
{
	char in[] = "hello",
		 response[300];  // буфферы чтения записи

	cli_command( response, sizeof(response), in, NULL/*опции*/ );  // обработка команды
	puts(response);  // вывести ответ в консоль
	fflush(stdout);  // см.выше

	return EXIT_SUCCESS;
}
