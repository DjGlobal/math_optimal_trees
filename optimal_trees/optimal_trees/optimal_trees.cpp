#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include "nodes.h"
#include "Stack algorithm.h"
#include "pseudo_trees.h"

#include <fstream>
#include <map>


using namespace std;

vector<node> buildNodesFromMap(map<char, size_t>);
map<char, string> codeChars(node*);

int main()
{
	setlocale(0, "");
	cout << "������� ��� �����" << endl;
	string filename;
	cin >> filename;
	ifstream in(filename);
	map<char, size_t> chars;

	// ������ ����
	if (!in.is_open())
		cout << "�� �� ������ ������� ����" << endl;

	while (!in.eof())
	{
		char c;
		in.get(c);
		if (!in.eof())
			++chars[c];
	}
	in.close();

	vector<node> nodes = buildNodesFromMap(chars);
	vector<node*> pointers = makePointersVector(nodes);
	t_nodes arr = { nodes.size(), pointers };
	// ��� 1. ������ ������������ ��� �������� �������
	node* parents = new node[nodes.size() - 1];
	const bool HuTucker_or_GarsiaWachs = 0; // 0 � �������� ���������, 1 � �������� ������ � �����
	node* pseudo_root = buildPseudoTree(HuTucker_or_GarsiaWachs, arr, nodes, parents);
	// ��� 2. �������� ��������
	node* root = buildTree(nodes, parents);

	map<char, string> coded = codeChars(root);

	cout << "������� ��� �����, ���� �������� ����� �����������" << endl;
	cin >> filename;
	ofstream out(filename);
	//
	out.close();

	//cout << "������� ��� �����, � ������� ���� ��������� �������������� �����" << endl;
	//cin >> filename;
	//ofstream out(filename);
	////
	//out.close();

    return 0;
}


void codeChar(node* curr, map<char, string>& codedChars, string route) {
	
	if (curr->left) {
		string route_left = route;
		string route_right = route;
		route_left.push_back('0');
		route_right.push_back('1');
		codeChar(curr->left, codedChars, route_left);
		codeChar(curr->right, codedChars, route_right);
	} else
		codedChars[curr->sign] = route;
}

map<char, string> codeChars(node* curr) {
	map<char, string> codedChars;
	string route_left = "0";
	string route_right = "1";
	codeChar(curr->left, codedChars, route_left);
	codeChar(curr->right, codedChars, route_right);
	return codedChars;
}

vector<node> buildNodesFromMap(map<char, size_t> chars) {
	vector<node> r;
	auto it = chars.begin();
	size_t i = 0;
	for (auto it = chars.begin(); it != chars.end(); ++it, ++i) {
		r.push_back({ i, it->first, it->second });
	}
	return r;
}