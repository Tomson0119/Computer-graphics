#include <Windows.h> 를 추가해서 Sleep 함수를 사용했습니다.
#include <cmath> 를 추가해서 pow 함수를 사용했습니다.

Node 라는 이름의 구조체를 정의하고 x,y,z 멤버 그리고 연결하여 다음 주소를 가리키는
next 노트포인터를 정의하였습니다. 생성자로는 x y z를 유저로부터 입력받아
실제 노드의 멤버들에 적용되도록 하였습니다.
print_node 함수를 구현하여 각 세개의 값을 출력하는 기능을 추가하였습니다.

List 클래스에 head와 tail을 정의하고 최대 길이(10)와 현재 리스트 길이를 변수로 지정했습니다.
그리고 head_index 와 tail_index 변수를 추가하여 콘솔창에 출력되는 리스트의 인덱스를
자유롭게 변경할 수 있게끔 하였습니다.

클래스 객체가 소멸할 때 reset_list 함수로 리스트를 초기화하고 head와 tail을 소멸시켰습니다.

main 함수에서 list 를 선언하고 10을 최대길이로 잡았습니다.
while 문에서 리스트 출력과 커맨드에 따른 작업을 수행하도록 하였습니다.

제가 print_list 함수를 구현한 방법은 노드를 추가 삭제할 때마다 head_index, tail_index
값을 재설정하고, 출력할 때에 반영되도록 한것입니다.
for 문을 돌면서 9에서부터 0까지 인덱스를 출력하면서, 인덱스가 head_index <= index <= tail_index
가 성립하는 경우에 리스트 값을 뒤에서부터 앞으로(tail -> head)로 출력하도록 했습니다.
그를 위해서 getIndex(int index) 함수를 통해 그에 해당하는 노드를 next로 하나씩 움직이면서
nullptr인 경우를 제외하고 출력하도록 했습니다.

그리고 저는 실제 리스트의 연결 관계를 출력하는 함수 print_link를 만들어서
노드 간의 연결상태를 참고하였습니다.

유저로부터 + x y z 를 입력받을 시 x y z를 입력받은 새로운 노드를 만들고 add_last 함수에
그 노드를 추가하는 식으로 구현하였습니다.

add_last 함수에서는 리스트의 길이가 이미 최대길이일 경우에는 아무것도 하지 않도록 하였고,
0 이상의 인덱스에 자리가 비어있는 경우에는 add_first를 불러와서 먼저 앞자리에 넣도록 했습니다.
일반적인 경우에는 head 가 비어있으면 head 와 tail에 새 노드를 넣어주고,
하나 이상의 노드가 존재하면 tail의 끝에 추가하는 식으로 구현하였습니다.
이 함수는 뒷자리에 넣는 상황을 다루기 때문에 tail_index의 값을 리스트 길이 - 1로 정하였습니다.
일반적으로 tail_index는 데이터가 추가될 때마다 하나씩 늘어나게 설정됩니다.

add_first 함수도 add_last와 비슷하게 구현하였습니다. 다른 점은 데이터를 head 앞에
넣어주는 것과 head_index 값을 설정하는 방법입니다.
head_index는 보통 0이나 노드를 pop 해서 앞부분이 비어있을 때는 새로운 노드를 추가 시
head_index 값이 1씩 감소하므로 그에 맞게 구현하였습니다.
tail_index 값도 꾸준히 증가하므로 마찬가지로 리스트 길이 - 1로 정하였습니다.

pop_first 함수에서는 먼저 head 값이 없으면 그냥 널포인터를 리턴하도록 하였고
그렇지 않은 경우 head를 대상으로 지정해서 리턴하도록 했습니다.
만약 리스트가 비워지면 head_index와 tail_index를 초기화할 필요가 있어 그렇게 하였습니다.
일반적인 경우 앞부분이 비워지므로 head_index를 1씩 추가하도록 하였습니다.
이 함수는 Node 포인터를 리턴하도록 구현하였지만 void로 구현해도 상관은 없었습니다.
하지만 pop된 데이터를 나중에 사용하거나 확인하는 용도가 있을 것 같아 그렇게 하였습니다.

pop_last 함수도 비슷하게 구현하였는데, tail을 재지정하는 과정에서 getIndex 함수를 사용하였습니다.

getLength() 함수를 이용해 간단하게 length 값을 출력하도록 하였습니다.
main 함수에서는 while 루프에서 system("cls")로 콘솔창을 지우도록 했기 때문에
출력 값이 보이지 않는 문제가 생겨서 Sleep(1000) 으로 잠시 멈추도록 하였습니다.

reset_list 함수에서는 current와 removeNode 를 같이 사용하여 head부터 tail까지
removeNode가 해당 current를 받고 delete를 통해 제거를 해주는 과정을 거쳤습니다.
리스트의 길이가 0이 될때까지 진행하도록 하였고, head와 tail도 초기화해주었습니다.

get_longest_point, get_shortest_point 함수를 만들어서 최대, 최소값을 찾아
그 값을 리턴하도록 구현하였습니다. 원점에서 자표까지의 길이를 구하기 위해
get_distance 함수를 만들고 pow 함수를 이용해 각 좌표값의 제곱값을 더해서 구하였습니다.

sort_by_distance 함수를 만들어서 정렬을 하였습니다. 저는 간단한 bubble sort 방식을 사용하였습니다.
current와 after 노드를 임시로 사용해서 근접한 노드끼리 서로의 좌표길이를 비교해서
해당 노드의 데이터 값을 바꾸는 방식을 사용했습니다.
swap_data 함수를 만들어서 각각의 노드의 좌표값들을 교환하도록 하였습니다.
정렬을 완료하면 head_index 와 tail_index 값도 초기화해서 아랫부분부터 채워지도록 하였습니다.



