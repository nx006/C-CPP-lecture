#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 정렬 양식을 출력하는 매크로
#define SHOWLINE printf("Num. %-15s %-15s %s\n", "Name", "Tel", "Email"); puts("------------------------------------------");
// 문자열 크기
#define STRING_SIZE 256

/*******
* 메뉴 선택지 상수
* 이 enum을 참조하는 함수:
*	printMenu(), selectMenu
********/
enum { Insert = 1, Delete, Search, PrintAll, Save, Exit };

/*******
* struct : MEMBER
* description
*	이름, 전화번호, 이메일 주소, order 로 이루어진 구조체
*	이중 연결 리스트이나, 원형 연결 리스트는 아니다.
*	즉 head->prev = NULL이고, last->next = NULL이 저장되어야 한다.
********/
typedef struct _MEMBER {
	struct _MEMBER* next; ///> 다음 노드 저장
	struct _MEMBER* prev; ///> 이전 노드 저장
	char name[STRING_SIZE]; ///> 이름
	char telephoneNumber[STRING_SIZE]; ///> 전화번호
	char emailAddress[STRING_SIZE]; ///> 이메일 주소
	int order; ///> 멤버의 순서이자 번호. 생성 순서대로 번호를 부여받는다.
} MEMBER;

void printMenu();
void selectMenu(MEMBER*, int);
int getMenuSelection();
void initializeHead(MEMBER* head);
void printAllData(MEMBER*);
void printMember(const MEMBER*);
void insert(MEMBER*);
void appendMember(MEMBER* list, const char* name, const char* telephoneNumber, const char* emailAddress, int order);
MEMBER* findMember(MEMBER* list, const char* name);
void search(MEMBER* head);
void deleteAllData(MEMBER* head);
void deleteTargetMember(MEMBER*);
void deleteMember(MEMBER* head);
void resetOrder(MEMBER*, int);
void save(MEMBER* head);


int main(void)
{
	int menuSelection = 0; ///> 메뉴 선택지
	MEMBER* head = malloc(sizeof(MEMBER)); ///> 주소록의 head노드
	initializeHead(head); // head노드를 기본값으로 초기화한다.

	while (menuSelection != Exit) { // menuSelection이 EXIT이면 반복문을 탈출한다
		printMenu();
		menuSelection = getMenuSelection();
		selectMenu(head, menuSelection);
	}

	deleteAllData(head);
	return 0;
}

/*********
* function : printMenu
* purpose : 메뉴 목록을 출력한다.
**********/
void printMenu()
{
	puts("-- Telephone Book Menu --");
	printf("%d. Insert\n", Insert);
	printf("%d. Delete\n", Delete);
	printf("%d. Search\n", Search);
	printf("%d. Print All\n", PrintAll);
	printf("%d. Save\n", Save);
	printf("%d. Exit\n", Exit);
}

/********
* function : selectMenu
* purpose : selection에 대응하는 메뉴 기능을 실행시킨다.
* parameters
*	MEMBER* head : 주소록의 헤더 노드
*	int selection : 메뉴 선택
* description :
*	selection에 대응하는 기능(함수)를 실행한다.
*	만약 selection에 대응하는 메뉴가 없을 경우, 에러 메시지를 출력한다.
*	Exit을 선택한 경우, 굿바이 메시지를 출력하고 반복문을 종료한다.
*	selection 목록은 enum 참고
* note :
*	EXIT을 선택한 경우에도 함수 자체가 프로그램을 종료하진 않는다. 메인 함수에서 종료해주어야 한다.
*	EXIT을 선택한 경우에도 주소록의 메모리를 해제하지는 않는다. 메인 함수에서 해제해주어야 한다.
********/
void selectMenu(MEMBER* head, int selection)
{
	switch (selection) {
	case Insert:
		insert(head);
		break;
	case Delete:
		deleteMember(head);
		break;
	case Search:
		search(head);
		break;
	case PrintAll:
		printAllData(head);
		break;
	case Save:
		save(head);
		break;
	case Exit:
		puts("Exit, thanks you!");
		return;
	default:
		puts("Thou selected wrong menu");
	}
}

/*********
* function : getMenuSelection
* purpose : menuSelection을 입력받고 반환한다.
* description :
*	안내 메시지를 출력하고, 정수 값을 입력받고 이를 반환한다.
*	입력버퍼를 자체적으로 비운다. 즉 '\n'(엔터) 를 입력 버퍼에서 제거하는 기능이 포함되어 있다.
* note :
*	자체적으로 올바른 메뉴가 선택되었는 지 확인하는 기능은 없다.
*********/
int getMenuSelection()
{
	int menuSelection = 0;
	printf("Choose your item: ");
	scanf_s("%d", &menuSelection);

	while (getchar() != '\n');
	// clear the stdin buffer

	return menuSelection;
}

/*********
* function : initializeHead
* purpose : head 노드를 초기화한다.
* parameters : 주소록의 head node
* description:
*	head 노드가 처음 생성되었을 때, head노드를 초기화하는 함수이다.
*	prev와 next 포인터를 NULL로 초기화한다.
*	order = -1
*	name, emailAddress, telephoneNumber을 각각 HEAD NAME, HEAD ADDRESS, 000-000-0000으로 초기화한다.
**********/
void initializeHead(MEMBER* head)
{
	head->prev = NULL;
	head->next = NULL;
	head->order = -1;
	strcpy_s(head->name, sizeof(head->name), "HEAD NAME");
	strcpy_s(head->emailAddress, sizeof(head->emailAddress), "HEAD ADDRESS");
	strcpy_s(head->telephoneNumber, sizeof(head->telephoneNumber), "000-000-0000");
}

/********
* function : appendMember
* purpose : 주소록에 멤버를 추가한다.
* parameters
*	MEMBER* head : 주소록의 헤드 노드
*	const char* name, telephoneNumber, emailAddress
*	const int order
* description :
*	주소록 리스트의 맨 끝에 새 멤버 노드를 추가한다.
*	만약 새 노드 생성에 실패할 경우, 에러 메시지를 출력한 후 함수를 종료한다.
*	노드 생성에 성공할 경우, 매개변수로 받은 name, telephoneNumber, emailAddress, order 값을 갖는 멤버가 추가된다.
*	추가된 멤버의 next 포인터는 NULL이고, prev는 바로 직전 노드를 참조한다.
*	바로 직전 노드의 next 포인터를 추가된 노드를 참조한다.
* note :
*	새 노드 생성에 실패해도 예외를 던지지 않는다. 에러 메시지만 출력한다.
*********/
void appendMember(MEMBER* head, const char* name, const char* telephoneNumber, const char* emailAddress, const int order)
{
	MEMBER* newMember = malloc(sizeof(MEMBER));

	if (newMember == NULL) {
		puts("ERROR : node creation failed");
		return;
	}
	newMember->prev = NULL;
	newMember->next = NULL;

	// 데이터 취합부
	strcpy_s(newMember->name, sizeof(newMember->name), name);
	strcpy_s(newMember->telephoneNumber, sizeof(newMember->telephoneNumber), telephoneNumber);
	strcpy_s(newMember->emailAddress, sizeof(newMember->emailAddress), emailAddress);
	newMember->order = order;

	// head node의 다음이 없을 경우, 즉 추가된 노드가 첫 노드일 경우
	if (head->next == NULL) {
		newMember->prev = head;
		newMember->next = NULL;

		head->next = newMember;
		head->prev = NULL;
	}
	else {
		MEMBER* cur = head; ///> cur은 head부터 끝헤드까지 탐색한다.
		while (cur->next != NULL) {
			cur = cur->next;
		}

		// 주소록 끝에 newMember를 연결한다.
		cur->next = newMember;
		newMember->prev = cur;
	}
}

/*********
* function : findMember
* purpose : name에 부합하는 멤버를 찾고 이를 반환한다.
* parameters
*	MEMBER* head : 주소록의 헤드 노드
*	const char* name : 찾으려는 멤버의 이름
* return : 찾으려는 멤버 구조체 노드
* description
*	head에 연결된 리스트 중에서 name이 일치하는 멤버를 찾아 반환한다.
*	만약 일치하는 name이 없다면, NULL을 반환한다.
**********/
MEMBER* findMember(MEMBER* head, const char* name)
{
	MEMBER* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		if (strcmp(cur->name, name) == 0) {
			return cur;
		}
	}

	return NULL;
}

/********
* function : search
* purpose : menu- search 기능 구현, 이름을 입력받고 일치하는 멤버를 주소록에서 찾아 정보를 출력한다.
* parameters
*	head : 주소록의 헤드 노드
* description :
*	안내 메지지를 출력하고, 찾으려는 대상의 이름을 입력받는다.
*	findMember()함수를 통해 대상이 되는 멤버를 찾는다. 이를 targetMember로 받는다.
*	만약 targetMember가 NULL이면, 에러 메시지를 출력하고 프로그램을 종료한다.
*	만약 targetMember가 존재하면, 출력 양식에 맞추어 targetMember의 정보를 출력한다.
*	출력 시 printMember() 함수, SHOWLINE 매크로 사용
*********/
void search(MEMBER* head)
{
	puts("[SEARCH]");
	char targetName[STRING_SIZE];
	printf("Input Name to Search: ");
	gets_s(targetName, sizeof(targetName));

	MEMBER* targetMember = findMember(head, targetName);
	if (targetMember == NULL) {
		printf("Error: No data found for Name “%s”\n", targetName);
		return;
	}
	else {
		SHOWLINE;
		printMember(targetMember);
	}
}

/********
* function : deleteAllData
* purpose : head노드에 연결된 주소록의 모든 노드 메모리를 해제한다.
* parameters : 주소록의 헤드 노드
* description
*	head노드에 연결된 주소록의 모든 노드 메모리를 해제한다.
*	주로 주소록이 필요 없을 때나, 프로그램을 종료할 때 사용한다.
* note
*	deleteMember, deleteTargetMember와는 역할이 다르다. 주소록의 모든 데이터를 삭제한다.
*	head 노드를 포함해서 삭제한다. 따로 head노드를 해제하려 하지 말 것
*********/
void deleteAllData(MEMBER* head)
{
	MEMBER* cur = head; 
	MEMBER* next = NULL; ///> cur을  free()로 해제하기에, 임시로 다음 노드를 가리킬 next 포인터가 필요하다.
	while (cur != NULL) {
		next = cur->next; // cur을 해제하기 전, 임시로 next를 cur->next 노드로 저장한다.
		free(cur);
		cur = next;
	}
}
/******
* function : deleteMember
* purpose : menu-2. delete의 기능 구현, 이름을 입력받고 해당 이름에 일치하는 멤버 노드를 주소록에서 삭제한다.
* parameters : 주소록의 헤드 노드
* description
*	안내 메시지를 출력 후 이름을 입력받는다.
*	만약 이름에 일치하는 멤버가 주소록에 없으면 안내문을 출력한다.
*	만약 이름에 일치하는 멤버가 주소록에 있으면 deleteTargetMember를 통해 해당 멤버 노드를 삭제한다.
*******/
void deleteMember(MEMBER* head)
{
	puts("[DELETE]");

	char targetName[STRING_SIZE];
	printf("Input Name to Delete: ");
	gets_s(targetName, sizeof(targetName));

	MEMBER* targetMember = findMember(head, targetName);
	if (targetMember == NULL) {
		printf("Data for Name “%s” is not exist\n", targetName);
	}
	else {
		deleteTargetMember(targetMember);
		resetOrder(head, 1);
	}
}
/********
* function : resetOrder
* purpose : MEMBER 구조체의 order(순서)를 오름차순으로 재정렬한다.
* parameters
*	MEMBER* head : 주소록 리스트의 헤드
*	const int startNumber : 시작 순서, 이 숫자를 시작으로 오름차순 정렬한다.
* description
*	startNum을 기준으로, head노드에 연결되어 있는 연결 리스트의 order을 오름차순 정렬한다.
*	주로 노드가 삭제되었을 때 등 순번에 대한 재정렬이 필요한 경우 사용한다.
*********/
void resetOrder(MEMBER* head, int startNumber)
{
	MEMBER* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		cur->order = startNumber;
		startNumber++;
	}
}

/********
* function : save
* purpose : 주소록을 파일로 저장한다.
* parameters
*	MEMBER* head : 주소록의 헤드 노드
* description
*	파일 이름을 입력받고, fileName 파일에 주소록을 저장한다.
*	이때 저장 양식은 SHOWLINE 양식을 따르지 않고, 따로 정렬한다.
*	콘솔의 글자수와 파일의 글자수는 일부 차이가 있어, SHOWLINE 양식보다 더 크게 정렬함.
*	파일을 여는 데 실패했을 경우, 에러 메시지를 출력하고 반환한다.
* note
*	파일 저장 양식의 유동성을 확보하기 위해 .txt를 붙이지 않는다. 입력자가 직접 "fileName.txt"로 입력해야 한다.
*********/
void save(MEMBER* head)
{
	puts("[Save to File]");

	char fileName[STRING_SIZE] = ""; ///> 파일 이름
	printf("Input file name to save: ");
	gets_s(fileName, sizeof(fileName));

	FILE* bookFile = 0;
	fopen_s(&bookFile, fileName, "wt");

	if (bookFile == NULL) {
		printf("ERROR: %s open failed\n", fileName);
		return;
	}

	// 정렬 양식에 맞추어 입력하기 위해, fprintf 함수 이용한다.
	fprintf(bookFile, "Num. % -20s % -20s %s\n", "Name", "Tel", "Email");
	MEMBER* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		fprintf(bookFile, "[%d]    %-20s %-20s %s\n", \
			cur->order, \
			cur->name, \
			cur->telephoneNumber, \
			cur->emailAddress);
	}

	fclose(bookFile);
	printf("Telephone Book “%s” is saved\n", fileName);
}

/*******
* function : deleteTargetMember
* purpose : target에 해당하는 멤버 노드를 주소록에서 삭제한다.
* parameters
*	MEMBER* target : 지우려는 대상 멤버
* description
*	target의 prev(이전) 노드와 next(이후) 노드를 적절히 연결한 후, free()함수를 통해 target을 해제한다.
*	만약 target이 마지막 노드일 시, prev 노드가 끝임을 나타내기 위해 prev->next = NULL로 설정한다.
* note
*	매개변수가 head노드가 아닌 target노드다.
*	이 함수에는 target이 헤드 노드인지를 검사하는 기능이 없다.
********/
void deleteTargetMember(MEMBER* target)
{
	// 만약 target이 마지막 노드라면, prev->next를 NULL로 설정한다.
	if (target->next == NULL) {
		target->prev->next = NULL;
	}

	// 만약 target이 중간에 있는 노드라면, target의 prev와 next 노드를 서로 연결한다.
	else {
		target->prev->next = target->next;
		target->next->prev = target->prev;
	}

	free(target);
}

/********
* function : printAllData
* purpose : 주소록의 모든 멤버를 양식에 맞추어 출력한다.
* parameters
*	MEMBER* head : 주소록의 헤드 노드
* description
*	안내문을 추력한 후, 양식에 맞추어 모든 멤버를 출력한다.
*	출력 양식은 SHOWLINE 매크로에 맞추어 출력하며, 출력 시 printMember() 함수를 사용해 각 멤버를 출력한다.
*********/
void printAllData(MEMBER* head)
{
	puts("[Print All Data]");
	
	SHOWLINE;
	MEMBER* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
		printMember(cur);
	}

	printf("\n");
}

/*******
* function : printMember
* purpose : 단일 member의 정보를 출력 양식에 맞추어 출력한다.
* parameters
*	MEMBER* member : 출력할 대상 멤버의 노드
* description
*	대상 멤버를 출력 양식에 맞추어 출력한다.
*	이때 출력 양식은 SHOWLINE 매크로의 양식을 따른다.
*	만약 member가 존재하지 않으면 에러 메시지를 출력하고 return 한다.
* note
*	SHOWLINE 매크로가 수정되면 이 함수의 출력 양식도 같이 수정되어야 한다.
*	parameter가 head노드가 아니다! 이 함수에는 member가 헤드 노드인지 검사하는 기능이 없다.
********/
void printMember(const MEMBER* member)
{
	if (member == NULL) {
		puts("ERROR : no data for such member");
		return;
	}
	printf("[%d]  %-15s %-15s %s\n", \
		member->order,\
		member->name, \
		member->telephoneNumber, \
		member->emailAddress);
}

/*******
* function : insert
* purpose : menu-1. insert의 구현, 멤버의 정보를 입력받고 주소록에 추가한다.
* parameters :
*	MEMBER* head : 주소록의 헤드 노드
* description :
*	안내문을 출력하며, 이름, 전화번호, 이메일 주소 순으로 입력받는다.
*	memberOrder은 기본적으로 1에서부터 순차적으로 부여하기 위한 변수이지만,
*	resetOrder() 함수를 사용해서 새로 추가할 때마다 모든 주소록의 order를 재부여하는 기능이 있다.
*	appendMember() 함수를 사용해서 입력받는 데이터에 부합되는 멤버를 주소록에 추가한다.
* 
*	주소록의 크기를 10으로 제한한다.
*	즉 order가 10보다 크면 주소록을 추가하지 않는다.
* note :
*	STRING_SIZE 보다 큰 바이트 크기의 문자열이 입력되었을 시 이에 대한 에러를 처리하지 않는다.
********/
void insert(MEMBER* head)
{
	char name[STRING_SIZE];
	char telephoneNumber[STRING_SIZE];
	char emailAddress[STRING_SIZE];
	static int memberOrder = 1; ///> memberOrder의 순서를 부여하기 위한 변수, 초기화되지 않고, 함수가 호출될 때마다 증가한다.

	printf("[INSERT]\n");
	printf("Input Name: ");
	gets_s(name, sizeof(name));
	printf("Input Tel. Number: ");
	gets_s(telephoneNumber, sizeof(telephoneNumber));
	printf("Input Email Address: ");
	gets_s(emailAddress, sizeof(emailAddress));

	appendMember(head, name, telephoneNumber, emailAddress, memberOrder);
	resetOrder(head, 1);

	// 주소록의 크기를 제한하는 기능
	// 마지막 멤버의 order가 10보다 크면 해당 멤버를 삭제하고, 안내 메시지를 출력한다.
	int maxMemberOrder = 10;
	MEMBER* cur = head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	if (cur->order > maxMemberOrder) {
		printf("Telephone book can save maximum %d members\n", maxMemberOrder);
		deleteTargetMember(cur);
	}
}
