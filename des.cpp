#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <array>
#include <utility>      
#include <stdarg.h>
#include<memory.h>
using namespace std;
template<typename T>
class Descartes {
public:
	Descartes(int count,T *elem);
	Descartes();
	int get_size();
	int get_relationship(int f, int s);
	void add_elems(T const& f, T const& s);
	void delete_elems(T const& f, T const& s);
	bool is_relationship(T const& f, T const& s);
	Descartes<T> operator+(Descartes<T> &right);
	Descartes<T> operator~();
private:
	T ele[64] = { 0 };
	int _size = 0;
	int size = 64;
	bool is_ele_exist(T const& elem);
	int get_ele_pos(T const& elem);
protected:
	char des[64][64];
};
template<typename T>
Descartes<T>::Descartes(int count,T *elem)
{
	memset(des, 0, sizeof(des));
	if(count)memcpy(ele, elem, count);
}
template<typename T>
Descartes<T>::Descartes()
{
	memset(des, 0, sizeof(des));
}
template<typename T>
int Descartes<T>::get_size()
{
	return _size;
}
template<typename T>
int Descartes<T>::get_relationship(int f, int s)
{
	return des[f][s];
}
template<typename T>
void Descartes<T>::add_elems(T const& f, T const& s)
{
	if (!is_ele_exist(f)&&_size<size) {
			ele[_size++] = f;
	}
	if (!is_ele_exist(s) && _size < size) {
			ele[_size++] = s;
	}
	int fpos = get_ele_pos(f), spos = get_ele_pos(s);
	if(fpos!=-1&&spos!=-1)
	{
		des[fpos][spos] = 1;
	}
}

template<typename T>
void Descartes<T>::delete_elems(T const& f, T const& s)
{
	if (!is_ele_exist(f) && _size < size) {
			ele[_size++] = f;
	}
	
	if (!is_ele_exist(s) &&_size < size) {
		ele[_size++] = s;
	}
	int fpos = get_ele_pos(f), spos = get_ele_pos(s);
	if (fpos != -1 && spos != -1)
	{
		des[fpos][spos] = 0;
	}
}

template<typename T>
bool Descartes<T>::is_relationship(T const& f, T const& s)
{
	int fpos = get_ele_pos(f), spos = get_ele_pos(s);
	if (fpos != -1 && spos != -1)
	{
		return des[fpos][spos] ? true : false;
	}
	return false;
}

template<typename T>
Descartes<T> Descartes<T>::operator+(Descartes<T> &right)
{
	if (this->get_size() == right.get_size()) {
		Descartes<T> sum = Descartes(_size,ele);
		for (int l = 0; l < _size; l++) {
			for (int r = 0; r < _size; r++) {
				if (des[l][r]) {
					for (int ll = 0; ll < _size; ll++) {
						if (right.des[r][ll]) {
							sum.des[l][ll] = 1;
							break;
						}
					}
					break;
				}
			}
		}
		return sum;
	}
	else {
		return Descartes<T>();
	}
}

template<typename T>
Descartes<T> Descartes<T>::operator~()
{
	Descartes<T> result = Descartes();
	memcpy(result.ele, ele, _size);
	for (int f = 0; f < this->_size; f++) {
		for (int s = 0; s < this->_size; s++) {
			if (this->des[f][s])result.des[s][f] = 1;
		}
	}
	return result;
}

template<typename T>
bool Descartes<T>::is_ele_exist(T const& elem)
{
	for (int i = 0; i < _size; i++)
		if (ele[i] == elem)return true;
	return false;
}

template<typename T>
int Descartes<T>::get_ele_pos(T const& elem)
{
	for (int i = 0; i < _size; i++)
		if (ele[i] == elem)return i;
	return -1;
}
