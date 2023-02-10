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
	int m_length{}; //������������� ������ ���������.��� ������������� ����������� ��� ��������� ����� ����������. � ������ ������ ���� ���� � ����� �����, ������ ������������ = 0
	int* m_data{};

public:
	// ������������
	IntArray() = default;

	IntArray(int length);

	IntArray(const IntArray& a);

	// ����������
	~IntArray();

	// �������
	int getLength() const;

	// ��������������� ����������
	int& operator[](int index);

	IntArray& operator=(const IntArray& a);

	// ������
	void erase();
	
	// reallocate �������� ������ �������. ��� ������������ �������� ����� ����������. 
	// ��� ������� �������� ������.
	void reallocate(int newLength);

	// resize �������� ������ �������. ��� ������������ �������� ����� ���������.
	// ��� ������� �������� ��������.
	void resize(int newLength);

	void insertBefore(int value, int index);

	void remove(int index);

	// ���� �������������� ������� ��� ��������
	void insertAtBeginning(int value);
	void insertAtEnd(int value);
};