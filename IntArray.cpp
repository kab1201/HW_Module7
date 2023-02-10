#include "IntArray.h"

// Класс bad_range
bad_range::bad_range(string error) : m_error(error) {};

const char* bad_range::what() const
{
	return m_error.c_str();
}

// Класс IntArray	
IntArray::IntArray(int length) : m_length(length)
{
	if (length < 0) throw length_error("The length of the array must be a positive number!");

	if (length > 0)
		m_data = new int[length]{};
};

IntArray::IntArray(const IntArray& a)
{
	// Установим размер нового массива соответствующим образом
	reallocate(a.getLength());

	// Затем скопируем элементы
	for (int index{ 0 }; index < m_length; ++index)
		m_data[index] = a.m_data[index];
}

// Деструктор
IntArray::~IntArray()
{
	delete[] m_data;
};

// Геттеры
int IntArray::getLength() const { return m_length; }

// Переопределение операторов
int& IntArray::operator[](int index)
{
	if (!(index >= 0 && index < m_length)) throw out_of_range{ "Out of range array! Operator[]" };
	return m_data[index];
}

IntArray& IntArray::operator=(const IntArray& a)
{
	// Проверим на самоназначение
	if (&a == this)
		return *this;

	// Установим размер нового массива соответствующим образом
	reallocate(a.getLength());

	// Затем скопируем элементы
	for (int index{ 0 }; index < m_length; ++index)
		m_data[index] = a.m_data[index];

	return *this;
}

// Методы
void IntArray::erase()
{
	delete[] m_data;

	// Нам нужно убедиться, что мы установили m_data в nullptr, 
	// иначе он будет оставлять указатель на деаллоцированную память!
	m_data = nullptr;
	m_length = 0;
}

void IntArray::reallocate(int newLength)
{
	// Удаляем все существующие элементы
	erase();

	// Если наш массив теперь будет пуст, то return.
	if (newLength <= 0)
		return;

	// Затем мы должны выделить новые элементы
	m_data = new int[newLength]{};
	m_length = newLength;
}

void IntArray::resize(int newLength)
{
	// Если массив уже имеет нужную длину, то все готово.
	if (newLength == m_length)
		return;

	// Если мы изменяем размер до пустого массива, сделайте это и return
	if (newLength <= 0)
	{
		erase();
		return;
	}

	// Теперь мы можем предположить, что newLength - это как минимум 1 элемент.
	// Этот алгоритм работает следующим образом: Сначала мы выделяем новый массив.
	// Затем мы копируем элементы из существующего массива в новый массив.
	// После этого мы можем уничтожить старый массив и сделать так,
	// чтобы m_data указывала на новый массив.

	// Сначала мы должны выделить новый массив
	int* data{ new int[newLength] };

	// Затем нужно определить, сколько элементов нужно скопировать из существующего массива в новый массив.
	// Мы хотим скопировать столько элементов, сколько есть в меньшем из двух массивов.
	if (m_length > 0)
	{
		int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

		// Теперь копируем элементы один за одним
		for (int index{ 0 }; index < elementsToCopy; ++index)
			data[index] = m_data[index];
	}

	// Теперь мы можем удалить старый массив, поскольку он нам больше не нужен
	delete[] m_data;

	// И можно использовать новый массив вместо этого! Обратите внимание, что это просто заставляет m_data
	// указывать на тот же адрес, что и новый массив, который мы динамически выделили.
	// Поскольку данные были выделены динамически, они не будут уничтожены, когда выйдут из области видимости.
	m_data = data;
	m_length = newLength;
}

void IntArray::insertBefore(int value, int index)
{
	// Проверим правильность значения нашего индекса
	if (!(index >= 0 && index <= m_length)) throw bad_range("Out of range array! Method insertBefore");

	// Сначала создадим новый массив на один элемент больше, чем старый массив
	int* data{ new int[m_length + 1] };

	// Скопируем все элементы до индекса index
	for (int before{ 0 }; before < index; ++before)
		data[before] = m_data[before];

	// Вставим наш новый элемент в новый массив
	data[index] = value;

	// Скопируем все элементы после вставленного элемента
	for (int after{ index }; after < m_length; ++after)
		data[after + 1] = m_data[after];

	// Наконец, удалим старый массив и используем вместо него новый массив
	delete[] m_data;
	m_data = data;
	++m_length;
}

void IntArray::remove(int index)
{
	// Проверим правильность значения нашего индекса
	if (!(index >= 0 && index < m_length)) throw "Out of range array! Method remove";

	// Если это последний оставшийся элемент в массиве, установим массив в пустое состояние и выйдем из системы
	if (m_length == 1)
	{
		erase();
		return;
	}

	// Сначала создадим новый массив на один элемент меньше, чем старый массив
	int* data{ new int[m_length - 1] };

	// Скопируем все элементы до индекса index
	for (int before{ 0 }; before < index; ++before)
		data[before] = m_data[before];

	// Скопируем все элементы после удаленного элемента
	for (int after{ index + 1 }; after < m_length; ++after)
		data[after - 1] = m_data[after];

	// Наконец, удалим старый массив и используем вместо него новый массив
	delete[] m_data;
	m_data = data;
	--m_length;
}

// Пара дополнительных функций для удобства
void IntArray::insertAtBeginning(int value) { insertBefore(value, 0); }
void IntArray::insertAtEnd(int value) { insertBefore(value, m_length); }
