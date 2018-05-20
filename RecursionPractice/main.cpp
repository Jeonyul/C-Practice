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