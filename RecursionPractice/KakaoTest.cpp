/*
문제 설명

카카오 프렌즈 컬러링북

출판사의 편집자인 어피치는 네오에게 컬러링북에 들어갈 원화를 그려달라고 부탁하여 여러 장의 그림을 받았다.
여러 장의 그림을 난이도 순으로 컬러링북에 넣고 싶었던 어피치는
영역이 많으면 색칠하기가 까다로워 어려워진다는 사실을 발견하고 그림의 난이도를 영역의 수로 정의하였다.
(영역이란 상하좌우로 연결된 같은 색상의 공간을 의미한다.)

그림에 몇 개의 영역이 있는지와 가장 큰 영역의 넓이는 얼마인지 계산하는 프로그램을 작성해보자.

입력 형식
입력은 그림의 크기를 나타내는 m과 n,
그리고 그림을 나타내는 m × n 크기의 2차원 배열 picture로 주어진다.
제한조건은 아래와 같다.

1 <= m, n <= 100
picture의 원소는 0 이상 2^31 - 1 이하의 임의의 값이다.
picture의 원소 중 값이 0인 경우는 색칠하지 않는 영역을 뜻한다.

출력 형식
리턴 타입은 원소가 두 개인 정수 배열이다.
그림에 몇 개의 영역이 있는지와 가장 큰 영역은 몇 칸으로 이루어져 있는지를 리턴한다.
*/

#include <iostream>
#include <vector>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int number_of_area;
int max_size_of_one_area;
int tempSize;
void FloodCheck(int r, int c, int value, int m, int n, vector<vector<int>>& picture)
{
	if (r < 0 || c < 0 || r > m - 1 || c > n - 1 || picture[r][c] == 0)
	{
		return;
	}
	if (picture[r][c] == value)
	{
		tempSize++;
		picture[r][c] = 0;
		FloodCheck(r - 1, c, value, m, n, picture);
		FloodCheck(r + 1, c, value, m, n, picture);
		FloodCheck(r, c - 1, value, m, n, picture);
		FloodCheck(r, c + 1, value, m, n, picture);
	}
}
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	number_of_area = 0;
	max_size_of_one_area = 0;
	int value = 0;
	for (int r = 0; r < m; r++)
	{
		for (int c = 0; c < n; c++)
		{
			if (picture[r][c] != 0)
			{
				value = picture[r][c];
				number_of_area++;
				tempSize = 0;
				FloodCheck(r, c, value, m, n, picture);
				if (max_size_of_one_area < tempSize)
				{
					max_size_of_one_area = tempSize;
				}
			}
		}
	}
	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}
int main()
{
	vector<vector<int>> picture;
	picture.push_back({ 1, 1, 1, 0 });
	picture.push_back({ 1, 1, 1, 0 });
	picture.push_back({ 0, 0, 0, 1 });
	picture.push_back({ 0, 0, 0, 1 });
	picture.push_back({ 0, 0, 0, 1 });
	picture.push_back({ 0, 0, 0, 1 });

	/*picture.push_back({ 1, 1, 0, 1 });
	picture.push_back({ 0, 1, 1, 1 });
	picture.push_back({ 0, 1, 1, 0 });
	picture.push_back({ 1, 1, 0, 0 });
	picture.push_back({ 0, 0, 0, 0 });
	picture.push_back({ 0, 0, 0, 0 });*/

	vector<int> answer(2);
	answer = solution(6, 4, picture);
	cout << answer[0] << ", " << answer[1] << endl;
	system("pause");
	return 0;
}
