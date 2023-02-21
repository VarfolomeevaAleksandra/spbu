#include "ArrayList.h"

using namespace std;

ArrayList::ArrayList(const ArrayList& list)
{
	count = list.count;
	capacity = list.capacity;
	data = new int[capacity] {0};
	for (int i = 0; i < count; ++i)
	{
		data[i] = list.data[i];
	}
}


ArrayList::~ArrayList()
{
	delete[] data;
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

int ArrayList::length()
{
	return count;
}
void ArrayList::operator+= (int item)
{
	add(item);
}


void ArrayList::operator-= (int item)
{
	remove(count - 1);
}


ArrayList& ArrayList::operator= (const ArrayList& list)
{
	if (&list != this)
	{
		delete[] data;
		capacity = list.capacity;
		data = new int[capacity] {0};
		count = list.count;
		for (int i = 0; i < count; ++i)
		{
			data[i] = list.data[i];
		}
	}
	return *this;
}


ArrayList operator+ (const ArrayList& list, int item)
{
	ArrayList result(list);
	result.add(item);
	return result;
}


ArrayList operator+ (int item, const ArrayList& list)
{
	ArrayList result(list);
	result.add(0, item);
	return result;
}


ArrayList operator+ (const ArrayList& list1, const ArrayList& list2)
{
	ArrayList result(list1);
	for (int i = 0; i < list2.count; ++i)
	{
		result += list2.data[i];
	}
	return result;
}


ArrayList operator- (const ArrayList& list, int item)
{
	ArrayList result(list);
	int c = -1;
	for (int i = result.count - 1; i >= 0; --i)
	{
		if (result.data[i] == item)
		{
			c = i;
		}
	}
	if (c >= 0)
	{
		result.remove(c);
	}
	return result;
}


ArrayList operator- (int item, const ArrayList& list)
{
	ArrayList result(list);
	if (result.indexOf(item) >= 0)
	{
		result.remove(result.indexOf(item));
	}
	return result;
}


std::ostream& operator<<(std::ostream& stream, const ArrayList& list)
{
	stream << "[" << list.count << "/" << list.capacity << "]  {";
	if (list.count != 0)
	{
		for (int i = 0; i < list.count - 1; ++i)
		{
			stream << list.data[i] << ", ";
		}
		stream << list.data[list.count - 1] << "}" << std::endl;
	}
	else
	{
		stream << "0}" << std::endl;
	}
	return stream;
}