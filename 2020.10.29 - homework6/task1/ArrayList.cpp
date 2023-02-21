#include "ArrayList.h"

using namespace std;

ArrayList::ArrayList(const ArrayList& list)
{
	count = list.count;
	capacity = list.capacity;
	str = list.str;
	for (int i = 0; i < count; ++i)
	{
		data[i] = list.data[i];
	}
}


ArrayList::~ArrayList()
{
	delete[] data;
	if (str != nullptr)
	{
		delete[] str;
	}
}

void ArrayList::expand()
{
	ArrayList temp(2 * capacity);
	for (int i = 0; i < count; ++i)
	{
		temp.data[i] = data[i];
	}
	capacity *= 2;
	delete[] data;
	data = temp.data;
}

bool ArrayList::add(int element)
{
	if (count == capacity)
	{
		expand();
	}
	data[count++] = element;
	return true;
}

int ArrayList::numLength(int number)
{
	int result = 1;
	while (number > 9)
	{
		number /= 10;
		result++;
	}
	return result;
}

void ArrayList::addToStr(int& index, char symbol)
{
	str[index] = symbol;
	++index;
}

void ArrayList::addToStr(int& index, int number)
{
	int length = numLength(number);
	for (int i = 0; i < length; ++i)
	{
		int digit = number % 10;
		str[index + length - 1 - i] = '0' + digit;
		number /= 10;
	}
	index += length;
}


bool ArrayList::errors(int index)
{
	if ((index > count) or (index < 0)) return false;
	else return true;
}


bool ArrayList::add(int index, int element)
{
	if (errors(index) == true)
	{
		for (int i = count; i > index; --i)
		{
			data[i] = data[i - 1];
		}
		data[index] = element;
		count++;
		if (count == capacity)
		{
			expand();
		}
		return errors(index);
	}
	else return errors(index);
}

bool ArrayList::addAll(ArrayList& list)
{
	for (int i = count; i < count + list.count; ++i)
	{
		add(list.data[i - count]);
	}
	count += list.count;
	return true;
}

bool ArrayList::addAll(int index, ArrayList& list)
{
	if (errors(index) == true)
	{
		for (int i = index; i < index + list.count; ++i)
		{
			add(i, list.data[i - count]);
		}
		count += list.count;
		return errors(index);
	}
	else return errors(index);
}


void ArrayList::clear()
{
	for (int i = 0; i < count; ++i)
	{
		data[i] = 0;
	}
	count = 0;
}


bool ArrayList::contains(int element)
{
	int result = 0;
	for (int i = 0; i < count; ++i)
	{
		if (data[i] == element)
		{
			++result;
			break;
		}
	}
	return(result == 0 ? false : true);
}


int ArrayList::get(int index)
{
	return(errors(index) == false ? -1 : data[index]);
}

bool ArrayList::set(int index, int element)
{
	data[index] = element;
	return errors(index);
}

int ArrayList::indexOf(int element)
{
	int result = -1;
	for (int i = 0; i < count; ++i)
	{
		if (data[i] = element)
		{
			result = i;
			break;
		}
	}
	return result;
}

bool ArrayList::isEmpty()
{
	return(count == 0 ? true : false);
}


bool ArrayList::remove(int index)
{
	if (errors(index) == true)
	{
		for (int i = index; i < count - 1; ++i)
		{
			data[i] = data[i + 1];
		}
		data[count - 1] = 0;
		return errors(index);
	}
	else return errors(index);
}


bool ArrayList::swap(int index1, int index2)
{
	if (errors(index1) == errors(index2) == true)
	{
		int c = 0;
		c = data[index1];
		data[index1] = data[index2];
		data[index2] = c;
		return errors(index1);
	}
	return false;
}

char* ArrayList::toString()
{
	int len = 0;
	int j = 0;

	for (int i = 0; i < count; ++i)
	{
		len += numLength(data[i]);
	}
	len = len + 5 + (count - 1);
	str = new char[len];
	addToStr(j, '[');
	addToStr(j, count);
	addToStr(j, '/');
	addToStr(j, capacity);
	addToStr(j, '] ');
	addToStr(j, '{');
	for (int i = 0; i < count - 1; ++i)
	{
		addToStr(j, data[i]);
		addToStr(j, ',');
		addToStr(j, ' ');
	}
	addToStr(j, data[count]);
	addToStr(j, '}');
	addToStr(j, '\0');
	return str;
}
int ArrayList::length()
{
	return count;
}