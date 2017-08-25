//理解回调函数
#include<iostream>
#include<time.h>
#include<windows.h>  
using namespace std;

void pressure(int i) {
	cout << endl << "自行车跑气了，气压："<<i << endl;
}
void stop() {
	cout <<endl<< "自行车没有气了！！" << endl;
}
class Bicycle {
private:
	int press;
public:
	Bicycle(int _press) { press = _press; }
	void run(void(*pressEvent)(int), void(*stopEvent)()) {
		srand((unsigned)time(NULL));
		cout << "自行车开动了！" << endl;
		while (true) {
			cout << "跑。";
			Sleep(100);
			if (rand() % 8 == 0) {
				press = press - 1;
				pressEvent(press);
				if (press <= 0) {
					stopEvent();
					break;
				}
			}
		}
	}
};
int main_2_1() {
	Bicycle bike= Bicycle(5);
	bike.run(pressure, stop);
	return 0;
}
