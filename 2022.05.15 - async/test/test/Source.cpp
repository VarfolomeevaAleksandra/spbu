#include <iostream>
#include <future>
using namespace std;
int sum = 0; // sum Ц глобальна€ переменна€
void f_sum()
{
	for (int i = 0; i < 1'000'000; i++)
		sum++;
}

int main()
{
	future <void> f1 = async(f_sum);
	//future <void> f2 = async(f_sum);
	//f1.get();
	//f2.get();
	cout << "Sum: " << sum << endl;
	// результаты неверные: 1183228 1067769 1077076
	// и различаютс€ при разных запусках программы
	return 0;
}