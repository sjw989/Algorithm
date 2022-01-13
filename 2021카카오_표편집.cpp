#include <iostream>
#include <vector>
#include <stack>
#define pci pair<char,int>
using namespace std;


typedef struct Row {
	int num = 0; // 행번호
	int init_num = 0; // 초기 번호 -> 나중에 비교할 때 사용
	Row* next = NULL; // 다음 행
	Row* prev = NULL; // 이전 행
};

typedef struct removed_row {	
	Row* removed_row;
	Row* removed_up;
	Row* removed_down;
};

Row* head; // head
Row* tail; // tail
Row* cur; // 현재 행
Row* latest_remove; // 가장 최근에 삭제된 행
stack<removed_row> stk;


vector<pci> get_cmd(vector<string> cmd) {
	vector<pci> my_cmd;

	for (int i = 0; i < cmd.size(); i++) {		
		if (cmd[i].size() < 2) { // 
			my_cmd.push_back(make_pair(cmd[i][0], 0));
		}
		else {
			my_cmd.push_back(make_pair(cmd[i][0], cmd[i][2]- '0'));
		}		
	}		
	return my_cmd;
	
}

void make_init(int n, int k) {
	for (int i = 0; i < n; i++) {
		Row* row = new Row;				
		row->num = i;
		row->init_num = i;
		if (i == 0) { // head			
			head = row;		
			tail = row;						
		}
		else { // tail			
			row->prev = tail;
			tail->next = row;
			tail = row;
		}		
		if (i == k) { // 시작 행 저장
			cur = row;
		}					
	}
}

void renumbering() {
	Row* row = head;
	int i = 0;
	while (row->next != NULL) {
		row->num = i;
		i++;
		row = row->next;
	}
	tail->num = i;	
}

// pair<char,int> 
void solve(vector<pci> my_cmd) {
	for (pci cmd : my_cmd) {				
		switch (cmd.first) {
			case 'D': // 밑으로 이동
				for (int i = 0; i < cmd.second; i++) {
					cur = cur->next;
				}
				break;			

			case 'U': // 위로 이동
				for (int i = 0; i < cmd.second; i++) {
					cur = cur->prev;
				}				
				break;

			case 'C': // 삭제
			{
				removed_row rmr; // 삭제된 애들

				if (cur == head) { // head가 삭제된 경우					
					rmr.removed_down = head->next;
					rmr.removed_row = head;
					rmr.removed_up = NULL;
					head = cur->next;
					cur = head;
				}
				else if (cur == tail) { // tail이 삭제된 경우
					rmr.removed_up = tail->prev; // 삭제된 행 한 칸 위에는 tail의 prev
					rmr.removed_row = tail;					
					rmr.removed_down = NULL;
					tail = cur->prev;		
					tail->next = NULL;
					cur = tail;
				}

				else { // 그 외에
					cur->prev->next = cur->next; // 현재 이전의 다음을 현재의 다음으로
					cur->next->prev = cur->prev; // 현재 다음의 이전을 현재의 이전으로					
					rmr.removed_up = cur->prev;
					rmr.removed_down = cur->next;					
					rmr.removed_row = cur;
					cur = cur->next;
				}				
				stk.push(rmr);				
				renumbering(); // 번호 재부여

				break;
			}

			case 'Z': // 되돌리기							
				removed_row rmr = stk.top();
				stk.pop();
		
				if (rmr.removed_up == NULL) { // 삭제당시 up이 없다 -> head가 삭제된것
					head->prev = rmr.removed_row;
					rmr.removed_row->next = head;
					head = rmr.removed_row;

				}
				else if (rmr.removed_down == NULL) { // 삭제당시 down이 없다 -> tail 이 삭제됨
					tail->next = rmr.removed_row;
					rmr.removed_row->prev = tail;					
					tail = rmr.removed_row;
					tail->next = NULL;
					cout << "tail : " << tail->num << " " << tail->init_num << endl;
				}
				else {
					rmr.removed_up->next = rmr.removed_row;
					rmr.removed_row->prev = rmr.removed_up;
					rmr.removed_row->next = rmr.removed_down;
					rmr.removed_down->prev = rmr.removed_row;
				}							
				renumbering(); // 번호 재부여						
				break;
		}			

		
		Row* test = new Row;
		test = head;
		while (test->next != NULL) {
			if (test == cur) {
				cout << "c" << " ";
			}
			cout << test->num << " " << test->init_num << endl;
			test = test->next;
		}
		if (cur == tail) {
			cout << "c" << " ";
		}
		cout << tail->num << " " << tail->init_num << endl;
		cout << endl;
	}
}


string get_result(int n) {	
	string result;
	return result;
}

int main() {	
	int n = 8; // 초기 행 개수
	int k = 2; // 처음에 선택된 행의 위치(행번호)
	vector<string> cmd = { "D 12","C","U 3","C","D 4","C","U 2","Z","Z" }; // 커맨드	
	vector<pci> my_cmd = get_cmd(cmd);
	make_init(n,k);
	solve(my_cmd);
	string result = get_result(n);		
	cout << result << endl;
}