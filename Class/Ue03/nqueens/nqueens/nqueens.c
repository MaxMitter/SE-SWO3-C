#define bool  int
#define false 0
#define true  1
#define MAX_N 100

void place_queen(int col[], int i, int n) {
	int j;
	for (j = 1; j <= n; j++) {
		if (queen_fits(col, i, j)) {
			col[i] = j;
			if (i == n)
				print_solution(col, n);
			else /*i < n*/
				place_queen(col, i + 1, n);
			col[i] = 0;
		} /*if*/
	} /*for*/
} /*place_queen*/


bool queen_fits(int col[], int i, int j) {
	int k;
	for (k = 1; k < i; k++) {
		if (( col[k] == j ) ||
			  (k+col[k] == i+j) ||
			  (k-col[k] == i-j))
		return false;
	} /*for*/
	return true;
} /* queen_fits */

static int solution_num = 0;
void print_solution(int col[], int n) {
	solution_num++;
	printf("solution %d\n", solution_num);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (col[i] == j)
				printf("D");
			else
				printf("- ");
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	int cols[MAX_N + 1];
	int n = 8;

	place_queen(cols, 1, n);

	return 0;
}
