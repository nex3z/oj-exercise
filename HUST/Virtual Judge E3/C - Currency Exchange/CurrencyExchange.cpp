#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_CURRENCY_NUM 101
#define MAX_EXCHANGE_POINTS_NUM 101

typedef struct ExchangeRecord {
	int from, to;
	double rate, commission;
} Exchange;

void solveE3c_CurrencyExchange();
void inputExchange(Exchange exchange[], int num);
bool bellmanford(int n, int m, Exchange exchange[], int oriCurrencyId, double oriCurrencyNum);

int main() {
	solveE3c_CurrencyExchange();
	return 0;
}

Exchange exchange[MAX_EXCHANGE_POINTS_NUM * 2];
void solveE3c_CurrencyExchange() {
	int n, m, s;
	double v;
	scanf("%d %d %d %lf", &n, &m, &s, &v);

	inputExchange(exchange, m);
	if (bellmanford(n, m, exchange, s, v)) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
}

void inputExchange(Exchange exchange[], int num) {
	for (int i = 0, j = 0; i < num; ++i) {
		scanf("%d %d %lf %lf %lf %lf", &exchange[j].from, &exchange[j].to, &exchange[j].rate, &exchange[j].commission,
			&exchange[j + 1].rate, &exchange[j + 1].commission);
		exchange[j + 1].from = exchange[j].to;
		exchange[j + 1].to = exchange[j].from;
		j += 2;
	}
}

double balance[MAX_CURRENCY_NUM];
bool bellmanford(int n, int m, Exchange exchange[], int oriCurrencyId, double oriCurrencyNum) {
	for (int i = 1; i <= n; ++i)
		balance[i] = 0;
	balance[oriCurrencyId] = oriCurrencyNum;

	double current;
	bool flag;
	for (int i = 1; i < n; ++i) {
		flag = false;
		for (int j = 0; j < m * 2; ++j) {
			current = (balance[exchange[j].from] - exchange[j].commission)*exchange[j].rate;
			if (balance[exchange[j].to] < current) {
				flag = true;
				balance[exchange[j].to] = current;
			}
		}
		if (flag == false)
			return false;
	}

	for (int i = 0; i < m * 2; ++i) {
		current = (balance[exchange[i].from] - exchange[i].commission)*exchange[i].rate;
		if (balance[exchange[i].to] < current)
			return true;
	}
	return false;
}