# HW_Module7
В учебных целях реализовала три различных типа перехвата ошибок:
- с помощью стандартных исключений length_error и out_of_range напрямую. Определены в заголовочном файле. Наследуются от std::exception.
- с помощью создания собственного класса-исключения bad_range, который наследуется от std::exception.
- с помощью исключения типа const char*
