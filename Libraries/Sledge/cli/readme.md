Реализация интерфейса коммандной строки (англ. CLI - command line interface).

## Как с ней работать.
0. **Обеспечить зависимости**
    `string.h` - работа со строками, стандартная библиотека Си должна быть включена в проект;
    [`sledge/utils`](https://bitbucket.org/qyw/sledge-utils)

1. **Настроить**. Для этого служит файл `cliConfig.h`, который должен находиться в include-папке проекта, например, `project/config/`.
Ниже приведено его содержимое.
``` C
/// Максимальная длинна коммандной строки
#define CMDLINE_MAX_LENGTH	64
/// Максимальное число аргументов с учётом комманды
#define ARGV_MAX		8
/// Макс. длинна имени комманды
#define CMD_NAME_SIZE  10

/// Приветствие
#define CLI_GREETING 	"==========================================="NEWLINE \
                        "==== Welcome to Sledge Telnet interface ==="NEWLINE \
                        "==========================================="NEWLINE

/// Приглашение коммандной строки
#define CLI_INVITE      "> "
```

2. **Реализовать комманды**. Редактировать файл `sledge/cli/examples/cli_commands.c`, предварительно скопировав и добавив в проект.

- Первым делом включить заголовок библиотечного модуля.

``` C
#include "sledge/cli/cli.h"

```

- Во-вторых, описать функции комманд. `cli_COMMAND_FUNCTION` упрощает работу с модулем и гарантирует отсутствие ошибок. ~~Если планируете вызывать эти функции извне, что маловероятно и не очень-то логично, `static` не писать~~.

``` C
/**
 * All following functions have the same syntacsis.
 * @param[OUT] *response 	the pointer to string which will contain response
 * @param[IN]   respLen		max length of response
 * @param[IN]   argc 		arguments number
 * @param[IN]  *argv[] 		arguments
 * @param[IN]  *opts 		Options which will be passed to concrete command processor
 * @retval Error code. 0 is OK. 1 is signal to close connection. <0 - any error
 */
static cli_COMMAND_FUNCTION( cli_info );
static cli_COMMAND_FUNCTION( cli_hello );
//static cli_COMMAND_FUNCTION( cli_reset );

```

- Три. COMMANDS — это массив структур, которые обязательно должны быть отсортированы по имени комманды.
Структура `CliCommand_t` проста: имя, функция, описание. Длина имени (включая нуль-терминатор) не дожна превышать `CMD_NAME_SIZE`. Следить за этим не обязательно - компилятор предупредит.
 
Функции `cli_help()`, `cli_clear()`, `cli_exit()`, `cli_reset()` определены в `cli.c` как weak и могут быть переопределены ниже.
Функция `cli_unknown()` обрабатывает нулевой указатель на функцию. Поэтому в ответ на комманду `stats` пользователь получит сообщение "`Command not implemented yet.`"
Функция `cli_unknown()` может быть переопределена.

``` C
/// MUST be sorted in ASCENDING order.
const CliCommand_t COMMANDS[] = {
	{"?"	, cli_help,  "The same as help" },
	{"cls"  , cli_clear, "Clear the screen (VT100)" },
	{"exit" , cli_exit,  "Close connection" },
	{"hello", cli_info,  "Say hello" },
	{"HELP" , cli_help,  "Show this short help" },
	{"info",  cli_info,  "Print information about device and firmware" },
	{"reset"  cli_reset, "Reset the uC" },
	{"stats", NULL,      "Statistics" },
};

const size_t COMMANDS_COUNT = array_length(COMMANDS);

```

- Далее самое интересное - функции
``` C
/**
 * Information about firmware and device.
 */
cli_COMMAND_FUNCTION( cli_info )
{
	snprintf( response, respLen,
			"Firmware built at " __TIME__ __DATE__);
	return 0;
}

/**
 * Say hello.
 */
cli_COMMAND_FUNCTION( cli_hello )
{
    if( argc<2 ){
        strlcpy( response, "Please, enter your name"NEWLINE );
        return 0;
    }
    sprintf( response, respLen, "Hello, %s!", argv[1] );
    return 0;
}

```

Подготовительный этап завершён.

## Использование
`volatile` позволит посмотреть переменную через дебаггер. `puts` - функция запишет строку в поток stdout, в вашей программе предварительно должен быть инициализирован UART или USB.VCP и перенаправлнена (retarget) функция putc. Подробнее о [retarget](...).
``` C
void main(void)
{
    /*volatile*/ char resp[64];
    char cmdline[64] = "hello world";

    cli_command(resp, sizeof(resp), cmdline, 0);
    puts( resp );
	
	strcpy( cmdline, "reset" );
    cli_command(resp, sizeof(resp), cmdline, 0);
	
	/// НЕ РЕКОМЕНДУЕТСЯ, но возможно.
	/// Найти комманду по имени и вызвать соответствующий обработчик.
    cli_searchCommandByName("reset")->func(0,0,0,0,0);

    while(1);   /// We should never get here
}

```

### Лицензия License
BSD 4-clause or MIT with Expat


#### Статья на сайте
[sledge.com](http://localhost:4000/2015/03/31/sledge-cli-%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D1%84%D0%B5%D0%B9%D1%81-%D0%BA%D0%BE%D0%BC%D0%BC%D0%B0%D0%BD%D0%B4%D0%BD%D0%BE%D0%B9-%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B8)

#### Смотрите также
[`sledge`](https://bitbucket.org/qyw/sledge)				[sledge.com]()  
[`sledge/utils`](https://bitbucket.org/qyw/sledge-utils)	[sledge.com]()  
[`sledge/c11n`](https://bitbucket.org/qyw/sledge-c11n) 		[sledge.com]()  
