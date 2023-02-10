#pragma once

#include <exception>
#include <string>
using namespace std;

class bad_range : public exception
{
public:
	bad_range(string error); 

	virtual const char* what() const override;

private:
	string m_error;
};

class IntArray
{
private:
	int m_length{}; // Инициализация пустым значением.Это универсальное обозначение для различных типов переменных. В данном случае речь идет о целом числе, потому эквивалентно = 0
	int* m_data{};

public:
	// Конструкторы
	IntArray() = default;

	IntArray(int length);

	IntArray(const IntArray& a);

	// Деструктор
	~IntArray();

	// Геттеры
	int getLength() const;

	// Переопределение операторов
	int& operator[](int index);

	IntArray& operator=(const IntArray& a);

	// Методы
	void erase();
	
	// reallocate изменяет размер массива. Все существующие элементы будут уничтожены. 
	// Эта функция работает быстро.
	void reallocate(int newLength);

	// resize изменяет размер массива. Все существующие элементы будут сохранены.
	// Эта функция работает медленно.
	void resize(int newLength);

	void insertBefore(int value, int index);

	void remove(int index);

	// Пара дополнительных функций для удобства
	void insertAtBeginning(int value);
	void insertAtEnd(int value);
};
