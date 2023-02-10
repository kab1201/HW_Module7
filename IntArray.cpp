#include "IntArray.h"

// ����� bad_range
bad_range::bad_range(string error) : m_error(error) {};

const char* bad_range::what() const
{
	return m_error.c_str();
}

// ����� IntArray	
IntArray::IntArray(int length) : m_length(length)
{
	if (length < 0) throw length_error("The length of the array must be a positive number!");

	if (length > 0)
		m_data = new int[length]{};
};

IntArray::IntArray(const IntArray& a)
{
	// ��������� ������ ������ ������� ��������������� �������
	reallocate(a.getLength());

	// ����� ��������� ��������
	for (int index{ 0 }; index < m_length; ++index)
		m_data[index] = a.m_data[index];
}

// ����������
IntArray::~IntArray()
{
	delete[] m_data;
};

// �������
int IntArray::getLength() const { return m_length; }

// ��������������� ����������
int& IntArray::operator[](int index)
{
	if (!(index >= 0 && index < m_length)) throw out_of_range{ "Out of range array! Operator[]" };
	return m_data[index];
}

IntArray& IntArray::operator=(const IntArray& a)
{
	// �������� �� ��������������
	if (&a == this)
		return *this;

	// ��������� ������ ������ ������� ��������������� �������
	reallocate(a.getLength());

	// ����� ��������� ��������
	for (int index{ 0 }; index < m_length; ++index)
		m_data[index] = a.m_data[index];

	return *this;
}

// ������
void IntArray::erase()
{
	delete[] m_data;

	// ��� ����� ���������, ��� �� ���������� m_data � nullptr, 
	// ����� �� ����� ��������� ��������� �� ���������������� ������!
	m_data = nullptr;
	m_length = 0;
}

void IntArray::reallocate(int newLength)
{
	// ������� ��� ������������ ��������
	erase();

	// ���� ��� ������ ������ ����� ����, �� return.
	if (newLength <= 0)
		return;

	// ����� �� ������ �������� ����� ��������
	m_data = new int[newLength]{};
	m_length = newLength;
}

void IntArray::resize(int newLength)
{
	// ���� ������ ��� ����� ������ �����, �� ��� ������.
	if (newLength == m_length)
		return;

	// ���� �� �������� ������ �� ������� �������, �������� ��� � return
	if (newLength <= 0)
	{
		erase();
		return;
	}

	// ������ �� ����� ������������, ��� newLength - ��� ��� ������� 1 �������.
	// ���� �������� �������� ��������� �������: ������� �� �������� ����� ������.
	// ����� �� �������� �������� �� ������������� ������� � ����� ������.
	// ����� ����� �� ����� ���������� ������ ������ � ������� ���,
	// ����� m_data ��������� �� ����� ������.

	// ������� �� ������ �������� ����� ������
	int* data{ new int[newLength] };

	// ����� ����� ����������, ������� ��������� ����� ����������� �� ������������� ������� � ����� ������.
	// �� ����� ����������� ������� ���������, ������� ���� � ������� �� ���� ��������.
	if (m_length > 0)
	{
		int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

		// ������ �������� �������� ���� �� �����
		for (int index{ 0 }; index < elementsToCopy; ++index)
			data[index] = m_data[index];
	}

	// ������ �� ����� ������� ������ ������, ��������� �� ��� ������ �� �����
	delete[] m_data;

	// � ����� ������������ ����� ������ ������ �����! �������� ��������, ��� ��� ������ ���������� m_data
	// ��������� �� ��� �� �����, ��� � ����� ������, ������� �� ����������� ��������.
	// ��������� ������ ���� �������� �����������, ��� �� ����� ����������, ����� ������ �� ������� ���������.
	m_data = data;
	m_length = newLength;
}

void IntArray::insertBefore(int value, int index)
{
	// �������� ������������ �������� ������ �������
	if (!(index >= 0 && index <= m_length)) throw bad_range("Out of range array! Method insertBefore");

	// ������� �������� ����� ������ �� ���� ������� ������, ��� ������ ������
	int* data{ new int[m_length + 1] };

	// ��������� ��� �������� �� ������� index
	for (int before{ 0 }; before < index; ++before)
		data[before] = m_data[before];

	// ������� ��� ����� ������� � ����� ������
	data[index] = value;

	// ��������� ��� �������� ����� ������������ ��������
	for (int after{ index }; after < m_length; ++after)
		data[after + 1] = m_data[after];

	// �������, ������ ������ ������ � ���������� ������ ���� ����� ������
	delete[] m_data;
	m_data = data;
	++m_length;
}

void IntArray::remove(int index)
{
	// �������� ������������ �������� ������ �������
	if (!(index >= 0 && index < m_length)) throw "Out of range array! Method remove";

	// ���� ��� ��������� ���������� ������� � �������, ��������� ������ � ������ ��������� � ������ �� �������
	if (m_length == 1)
	{
		erase();
		return;
	}

	// ������� �������� ����� ������ �� ���� ������� ������, ��� ������ ������
	int* data{ new int[m_length - 1] };

	// ��������� ��� �������� �� ������� index
	for (int before{ 0 }; before < index; ++before)
		data[before] = m_data[before];

	// ��������� ��� �������� ����� ���������� ��������
	for (int after{ index + 1 }; after < m_length; ++after)
		data[after - 1] = m_data[after];

	// �������, ������ ������ ������ � ���������� ������ ���� ����� ������
	delete[] m_data;
	m_data = data;
	--m_length;
}

// ���� �������������� ������� ��� ��������
void IntArray::insertAtBeginning(int value) { insertBefore(value, 0); }
void IntArray::insertAtEnd(int value) { insertBefore(value, m_length); }
