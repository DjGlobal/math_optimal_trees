#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <queue>
#include <stack>
#include "Stack algorithm.h"

//node *T;

using namespace std;

bool isCompatible(array<node, 11>, size_t, size_t);  //����� ���� ����������� ��� i-���� ��������
array<node, 11> findAllCompatibles(array<node, 11>, size_t, size_t);

int main()
{
	array<node, 11> arr = { {
		{ 'a',8,0,0,0 },
		{ 'b',6,0,0,0 },
		{ 'c',2,0,0,0 },
		{ 'd',3,0,0,0 },
		{ 'e',4,0,0,0 },
		{ 'f',7,0,0,0 },
		{ 'g',11,0,0,0 },
		{ 'h',9,0,0,0 },
		{ 'j',8,0,0,0 },
		{ 'k',1,0,0,0 },
		{ 'l',3,0,0,0 }
	} };

	
	array<node, 11>  curr_arr = arr; //���, �� �� �� ��������

	size_t curr_size = curr_arr.size(); //������� ��� ����, �� ��� ������� 
									  //(���� ����� ��������� ��� curr_arr.size ��������� ����� �������, �� �� ����)
	///////////��� 1/////////////
	// ���� �������� ����������� ����������� ���� (A, B)
	size_t A = 0, B = 0;
	while (curr_arr.size())
	{

		for (size_t i = A; i < curr_size; i++) //������� ������� ����� ����
		{
			array<node, 11> all_compatible;
			size_t k = 0;
			for (size_t j = 0; j < curr_size; j++) //������� ������� ����� ����
			{
				if (i == j) continue;
				all_compatible = findAllCompatibles(curr_arr, i, curr_size);  //������ ����� ������� ������� �.�.�.�.
				for (k = 0; k < all_compatible.size(); k++)  //������ ����� ������� ������� �.�.�.�.
					if (!(all_compatible[k].weight > curr_arr[j].weight))
						break;
				if (k == all_compatible.size())
				{
					all_compatible = { 0 };  //�� ��� �������
					all_compatible = findAllCompatibles(curr_arr, j, curr_size);  //������ ����� ������� ������� �.�.�.�.
					for (k = 0; k < all_compatible.size(); k++)   //������ ����� ������� ������� �.�.�.�.
						if (!(all_compatible[k].weight >= curr_arr[i].weight))
							break;
					if (k == all_compatible.size())   //��� ������� ���������, ���� �������
					{
						B = j;
						break;
					}
				}
				/*if (isCompatible(arr, i, j)) {
					all_compatible[k] = arr[j];
					++k;
				}*/
			}
			if (k == all_compatible.size()) //�������� ���-�� ����� �������� ��� ����� �����
			{
				A = i;
				break;
			}
		}


		//����������� �.�.�.�., ������ ���� ��������� �����, ������ ��� �����
		curr_arr[A].weight += curr_arr[B].weight; //��� ��� ���� ������ � ���������
		curr_arr[A].level = max(curr_arr[A].level, curr_arr[B].level) + 1;
		//��� ���� �������� ������� � ��������������� ��������� �� arr
		for (size_t i = B; i < curr_size - 1; i++)
			swap(curr_arr[i], curr_arr[i + 1]);
		curr_size--;

	}
	//�� � ���� ��� ���� ��������� ���� � curr_arr �� ��������� ���� �������

	////////////��� 2///////////////////
	// �������� ��������
	stack<node> st;  //�������� ��������
	stack<node> qu;
	for (int i = 10; i < 0; i--)  //������������� ����� �� ����� �������
		qu.push(arr[i]);
	
	while (Move1(st, qu));   //����� � ��������� �� ���������
		
    return 0;
}

array<node, 11> findAllCompatibles(array<node,11> arr, size_t curr, size_t size)
{   
	array<node, 11> all_compatible;
	size_t k = 0;
	for (size_t i = 0; i < size; i++)
		if (i != curr && isCompatible(arr, curr, i))
		{
			all_compatible[k] = arr[i];
			k++;
		}
	return all_compatible;  //�� ��� ��������� ��������
}



bool isCompatible(array<node, 11> arr, size_t a, size_t b) {
	if ((a == (b + 1)) || (a == (b - 1)))
		return true;
	if (a > b) swap(a, b);
	for (size_t i = a + 1; i < b; i++)
	{
		if (!arr[i].level) return false;
	}
	return true;
}

