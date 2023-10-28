#include<bits/stdc++.h>
using namespace std;

bool done[5]={0};
int process=5,resources=3;
int processArr[5],available[3];
int maxArr[5][3],allocate[5][3],extraNeed[5][3];
int safeSerial[5];
int work[3];

void calculateNeedMat(){

 for (int i = 0 ; i < process ; i++){
		for (int j = 0 ; j < resources ; j++){
           extraNeed[i][j]=maxArr[i][j]-allocate[i][j];
		}
 }

}

bool safeState(){

   calculateNeedMat();
	int safeSerial[process];
	int work[resources];
	for (int i = 0; i < resources ; i++)
		work[i] = available[i];

	int coun = 0;
	while (coun < process)
	{
		bool found = false;
		for (int p = 0; p < process; p++)
		{
			if (done[p] == 0)
			{
				int j;
				for (j = 0; j < resources; j++)
					if (extraNeed[p][j] > work[j])
						break;
				if (j == resources)
				{
					for (int k = 0 ; k < resources ; k++)
						work[k] += allocate[p][k];
					safeSerial[coun++] = p;

					done[p] = 1;

					cout<<p<<" process completed\n";

					found = true;
				}
			}
		}

		if (found == false)
		{
			cout << "||NOT SAFE STATE||";
			return false;
		}
	}

	cout << "SAFE STATE\n";
	cout<<"SAFE sequence is: \n";

	for (int i = 0; i < process ; i++)
		cout << safeSerial[i] << "\n";

	return true;
}

int main(){

 freopen("input.txt","r",stdin);

 for(int i=0;i<process;i++){
    cin>> processArr[i];
 }
 for(int i=0;i<resources;i++){
    cin>> available[i];
 }

 for(int i=0;i<process;i++){
    for(int j=0;j<resources;j++){
        cin>>maxArr[i][j];
    }
 }
 for(int i=0;i<process;i++){
    for(int j=0;j<resources;j++){
        cin>>allocate[i][j];
    }
 }

  bool ans = safeState();

}
