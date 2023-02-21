#include <iostream>
using namespace std;

int main()
{
	int x, n1, n2, n3, n4, n5, n6, a1, a2, a3, a4, a5, a6, number = 0;
	cin >> x;
	if (x >= 9) 
		{
			n1 = 9; n4 = 9; 
		}
	if (x < 9) 
		{
			n1 = x; n4 = x; 
		}
	for (a1 = 0; a1 <= n1; a1++) 
		{
			n2 = x - a1;
			for (a2 = 0; a2 <= n2; a2++) 
				{
					n3 = n2 - a2;
					for (a3 = 0; a3 <= n3; a3++)
						{
							if ((a1 + a2 + a3) == x) 
								{
									for (a4 = 0; a4 <= n4; a4++) 
										{
											n5 = x - a4;
											for (a5 = 0; a5 <= n5; a5++) 
												{
													n6 = n4 - a4;
													for (a6 = 0; a6 <= n6; a6++) 
														{
															if ((a4 + a5 + a6) == x) 
																{
																	cout << a1 << a2 << a3 << a4 << a5 << a6 << endl;
																	number++;
																}
														}
												}
										}
								}
						}
				}
		}
	cout << "vsego " << number << endl;

	return 0;
}