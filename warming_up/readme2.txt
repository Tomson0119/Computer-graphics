파일 입출력 함수를 이용하기 위해서 헤더에 <fstream> 을 추가하였습니다.
reaFile() 함수를 따로 만들어서 구현하였는데, 이에 특별한 이유는 없습니다.

먼저 inFile 이라는 이름의 파일입력 객체를 생성하고 "data.txt"를 받아와서
변수 letter에 문자를 하나씩 담아 확인하였습니다.

첫번째로 기본 라이브러리에서 지원하는 isdigit( int n ) 함수를 이용하여
문자가 숫자인지 아닌지 판별하였습니다. 0이 아닌 수를 리턴하면 숫자이기 때문에
그 경우에는 number_count 를 하나씩 증가시켰습니다.

두번째로 역시 기본 라이브러리에서 지원하는 isalpha( int n ) 함수를 이용하였습니다.
0이 아닌 값을 리턴하면 알파벳임으로 그 경우 alphabet_count 를 증가시켰습니다.
그리고 inFile.eof() (end of file) 이 true로 나오면 while 문을 빠져나오게 하여
마지막으로 alphabet_count 와 number_count 를 출력하도록 구현하였습니다. 
