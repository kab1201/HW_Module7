#include <iostream>
#include "IntArray.h"

/*
В учебных целях реализовала три различных типа перехвата ошибок:
- с помощью стандартных исключений length_error и out_of_range напрямую. Определены в заголовочном файле. Наследуются от std::exception.
- с помощью создания собственного класса-исключения bad_range, который наследуется от std::exception.
- с помощью исключения типа const char*
*/

int main()
{
	try
	{
		// Объявим массив из 10 элементов
		IntArray array(10);

		// Заполним массив числами от 0 до 9
		for (int i{ 0 }; i<10; ++i)
			array[i] = i + 1;

		// Изменим размер массива до 8 элементов
		array.resize(8);

		// Вставим число 25 перед элементом с индексом 5
		array.insertBefore(25, 5);

		// Удалим элемент с индексом 3
		array.remove(4);

		// Добавим 30 и 40 в конец и начало
		array.insertAtEnd(30);
		array.insertAtBeginning(40);

		// Выведем все элементы массива array
		for (int i{ 0 }; i<array.getLength(); ++i)
			std::cout << array[i] << ' ';

		std::cout << '\n';

		// Протестируем копирование массива
		IntArray array_copy{ array };
		array_copy.reallocate(8);
		array_copy = array;
		array_copy = array_copy;

		// Выведем все элементы массива b
		for (int i{ 0 }; i<array_copy.getLength(); ++i)
			std::cout << array_copy[i] << ' ';

		std::cout << '\n';
	}
	catch (out_of_range& e)
	{
		cerr << e.what();
	}
	catch (bad_range& e)
	{
		cerr << e.what();
	}
	catch (const char* err)
	{
		cerr << err;
	}
	catch (exception& e)
	{
		cerr << e.what();
	}

	return 0;
}
