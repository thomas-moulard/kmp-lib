#include <iostream>

void test_kamoulist();
void test_kamounum();
void test_kamoutil();
void test_kamouctrl();

int main()
{
	std::cout <<std::endl << " -------- KAMOULIST -------- " << std::endl << std::endl;
	test_kamoulist();
	
	std::cout <<std::endl << " -------- KAMOUNUM -------- " << std::endl << std::endl;
	test_kamounum();

	std::cout <<std::endl << " -------- KAMOUTIL -------- " << std::endl << std::endl;
	test_kamoutil();

	std::cout <<std::endl << " -------- KAMOUCTRL -------- " << std::endl << std::endl;
	test_kamouctrl();

#ifdef WIN32
	system("pause");
#endif
}