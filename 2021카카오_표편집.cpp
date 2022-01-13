#include <iostream>
#include <vector>
#include <stack>
#define pci pair<char,int>
using namespace std;


typedef struct Row {
	int num = 0; // ���ȣ
	int init_num = 0; // �ʱ� ��ȣ -> ���߿� ���� �� ���
	Row* next = NULL; // ���� ��
	Row* prev = NULL; // ���� ��
};

typedef struct removed_row {	
	Row* removed_row;
	Row* removed_up;
	Row* removed_down;
};

Row* head; // head
Row* tail; // tail
Row* cur; // ���� ��
Row* latest_remove; // ���� �ֱٿ� ������ ��
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
		if (i == k) { // ���� �� ����
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
			case 'D': // ������ �̵�
				for (int i = 0; i < cmd.second; i++) {
					cur = cur->next;
				}
				break;			

			case 'U': // ���� �̵�
				for (int i = 0; i < cmd.second; i++) {
					cur = cur->prev;
				}				
				break;

			case 'C': // ����
			{
				removed_row rmr; // ������ �ֵ�

				if (cur == head) { // head�� ������ ���					
					rmr.removed_down = head->next;
					rmr.removed_row = head;
					rmr.removed_up = NULL;
					head = cur->next;
					cur = head;
				}
				else if (cur == tail) { // tail�� ������ ���
					rmr.removed_up = tail->prev; // ������ �� �� ĭ ������ tail�� prev
					rmr.removed_row = tail;					
					rmr.removed_down = NULL;
					tail = cur->prev;		
					tail->next = NULL;
					cur = tail;
				}

				else { // �� �ܿ�
					cur->prev->next = cur->next; // ���� ������ ������ ������ ��������
					cur->next->prev = cur->prev; // ���� ������ ������ ������ ��������					
					rmr.removed_up = cur->prev;
					rmr.removed_down = cur->next;					
					rmr.removed_row = cur;
					cur = cur->next;
				}				
				stk.push(rmr);				
				renumbering(); // ��ȣ ��ο�

				break;
			}

			case 'Z': // �ǵ�����							
				removed_row rmr = stk.top();
				stk.pop();
		
				if (rmr.removed_up == NULL) { // ������� up�� ���� -> head�� �����Ȱ�
					head->prev = rmr.removed_row;
					rmr.removed_row->next = head;
					head = rmr.removed_row;

				}
				else if (rmr.removed_down == NULL) { // ������� down�� ���� -> tail �� ������
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
				renumbering(); // ��ȣ ��ο�						
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
	int n = 8; // �ʱ� �� ����
	int k = 2; // ó���� ���õ� ���� ��ġ(���ȣ)
	vector<string> cmd = { "D 12","C","U 3","C","D 4","C","U 2","Z","Z" }; // Ŀ�ǵ�	
	vector<pci> my_cmd = get_cmd(cmd);
	make_init(n,k);
	solve(my_cmd);
	string result = get_result(n);		
	cout << result << endl;
}