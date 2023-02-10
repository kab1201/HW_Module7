#include <iostream>
#include "IntArray.h"

/*
� ������� ����� ����������� ��� ��������� ���� ��������� ������:
- � ������� ����������� ���������� length_error � out_of_range ��������. ���������� � ������������ �����. ����������� �� std::exception.
- � ������� �������� ������������ ������-���������� bad_range, ������� ����������� �� std::exception.
- � ������� ���������� ���� const char*
*/

int main()
{
	try
	{
		// ������� ������ �� 10 ���������
		IntArray array(10);

		// �������� ������ ������� �� 0 �� 9
		for (int i{ 0 }; i<10; ++i)
			array[i] = i + 1;

		// ������� ������ ������� �� 8 ���������
		array.resize(8);

		// ������� ����� 25 ����� ��������� � �������� 5
		array.insertBefore(25, 5);

		// ������ ������� � �������� 3
		array.remove(4);

		// ������� 30 � 40 � ����� � ������
		array.insertAtEnd(30);
		array.insertAtBeginning(40);

		// ������� ��� �������� ������� array
		for (int i{ 0 }; i<array.getLength(); ++i)
			std::cout << array[i] << ' ';

		std::cout << '\n';

		// ������������ ����������� �������
		IntArray array_copy{ array };
		array_copy.reallocate(8);
		array_copy = array;
		array_copy = array_copy;

		// ������� ��� �������� ������� b
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