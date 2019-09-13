#include "iostream"
#include "string.h"
using namespace std;
struct Source
{
	char Sname;
	int Scount;
};
typedef struct {
	int n;
	int queue[10];
}Queue;
Queue queue ;
int length = 3, Count = 5;
int const max[5][3] = { { 7, 5, 3 }, { 3, 2, 2 }, { 9, 0, 2 }, { 2, 2, 2 }, { 4, 3, 3 } };
int allocation[5][3] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } };
int need[5][3]= { { 7, 4, 3 }, { 1, 2, 2 }, { 6, 0, 0 }, { 0, 1, 1 }, { 4, 3, 1 } };
int available[3] = { 3, 3, 2 };
int allbuff[5][3], needbuff[5][3], avabuff[3];
bool Save(int needbuff[][3], int allbuff[][3], int avabuff[]){
	int work[3], finish[5], flag, k = 0, F = 1, t = 0;
	for (int i = 0; i<Count; i++){ finish[i] = 0; }
	for (int j = 0; j<length; j++){
		work[j] = avabuff[j];
	}
	while (F){
		t = 0;
		for (int i = 0; i<Count; i++){
			if (finish[i] == 0){
				flag = 0;
				for (int j = 0; j<length; j++){
					if (needbuff[i][j]>work[j]){
						flag = 1; break;
					}
				}
				if (!flag){
					queue.queue[k++] = i;
					for (int j = 0; j<length; j++){
						work[j] += allbuff[i][j];
						finish[i] = 1;
					}
				}
			}
			else { t++; if (t == Count)return false; continue; }
		}
		for (int i = 0; i<Count; i++){
			if (finish[i] == 0){ F = 1; break; }
			else F = 0;
		}
	}
	return true;
}
bool Request(int n, int cost[]){

	for (int i = 0; i<length; i++){
		if (need[n][i]<cost[i])return false;
		if (available[i]<cost[i])return false;
	}
	for (int i = 0; i<Count; i++){
		for (int j = 0; j<length; j++){
			allbuff[i][j] = allocation[i][j];
			needbuff[i][j] = need[i][j];
		}
		avabuff[i] = available[i];
	}
	for (int i = 0; i<3; i++){
		avabuff[i] = avabuff[i] - cost[i];
		allbuff[n][i] = allbuff[n][i] + cost[i];
		needbuff[n][i] = needbuff[n][i] - cost[i];
	}
	if (Save(needbuff, allbuff, avabuff)){
		for (int i = 0; i<Count; i++){
			for (int j = 0; j<length; j++){
				allocation[i][j] = allbuff[i][j];
				need[i][j] = needbuff[i][j];
			}
			available[i] = avabuff[i];
		}
	}
	else return false;
	return true;
}

/*bool Request(int n, int cost[]){

	for (int i = 0; i<length; i++){
		if (need[n][i]<cost[i])		return false;
		if (available[i]<cost[i])	return false;
	}
	for (int i = 0; i<Count; i++){
		for (int j = 0; j<length; j++){
			allbuff[i][j] = allocation[i][j];
			needbuff[i][j] = need[i][j];
		}
		avabuff[i] = available[i];
	}
	for (int i = 0; i<3; i++){
		avabuff[i] = avabuff[i] - cost[i];
		allbuff[n][i] = allbuff[n][i] + cost[i];
		needbuff[n][i] = needbuff[n][i] - cost[i];
	}
	if (Save(needbuff, allbuff, avabuff)){
		for (int i = 0; i<Count; i++){
			for (int j = 0; j<length; j++){
				allocation[i][j] = allbuff[i][j];
				need[i][j] = needbuff[i][j];
			}
			available[i] = avabuff[i];
		}
	}
	else 
		return false;
	return true;
}
*/
int main(){
	Source All[3] = { { 'A', 10 }, { 'B', 5 }, { 'C', 7 } };
	queue.n = 5;
	int cost[3] = { 0,1,0 };
	if (Request(2, cost))
	{
		cout << "p2可以分配安全序列为：";
		for (int i = 0; i<queue.n; i++)
			cout <<queue.queue[i] << "  ";
	}
		
	else
		cout << "p2无法分配"<<endl;
	if (Request(1, cost))
	{
		cout << "p1可以分配安全序列为：";
		for (int i = 0; i<queue.n; i++)
			cout << queue.queue[i] << "  ";
	}
	else
		cout << "p1无法分配" << endl;

}
