# Othello


## Rule

* 게임 시작
  * 8 * 8 보드 중앙 4칸에 검은 돌 두개와 흰 돌 두개를 교차하여 놓는다.
  * 두명의 플레이어는 각각 흰색과 검은색 중 하나를 선택한다.
  * 자신의 차례에 한 번씩 돌을 놓을 수 있다.

* 게임 진행
  * 자신이 돌을 놓고자 하는 칸과 이미 자신의 돌이 있는 칸 사이에(가로, 세로, 대각) 상대의 돌이 있는 경우에만 돌을 놓을 수 있다.
  * 자신의 돌을 놓게 된 경우, 사이에 끼어있는 상대의 돌은 모두 자신의 색깔이 된다.
 
* 패스
  * 자신의 차례에 돌을 놓을 수 있는 자리가 하나도 없을 경우, 상대 차례로 넘어간다.
  * 단, 자신의 차례에 돌을 놓을 수 있는 자리가 하나라도 있는 경우 상대 차례로 넘기는 것은 불가능하다.

* 게임 종료
  * 양쪽 모두 더 이상 놓을 곳이 없게 되면 게임이 종료된다.
  * 보드 위에 자신의 돌이 더 많은 사람이 승리한다.


## Menu

* 싱글 모드
  * 혼자 플레이하여 컴퓨터와 대결할 수 있음(컴퓨터는 놓을 수 있는 위치 중 랜덤으로 돌을 놓음)
* 멀티 모드
  * 둘이서 번갈아가면서 플레이 가능
* 맵 변경
  * 게임을 플레이하기 전 장애물을 설치하여 돌을 놓지 못하는 곳을 만들 수 있음
  * 장애물의 갯수는 정할 수 있으며, 장애물의 위치는 랜덤으로 정해짐
* 종료
  * 게임을 종료함


## 플레이 방법

1. 게임을 실행한 후 장애물 설정(3)에서 원하는 장애물의 갯수를 입력한다(기본값 0).
2. 싱글모드 혹은 멀티모드로 들어간다.
     멀티모드 플레이 시 방을 개설할 사람이 서버(선공), 그리고 참여할 사람이 클라이언트(후공)가 된다. 클라이언트로 참여 시 서버의 IP주소가 필요하다.
3. 본인의 차례에 돌을 놓고자 하는 위치의 좌표를 입력하여 돌을 놓는다 ex) E5


## 기능

* 장애물은 빨간색 X로, 돌을 놓을 수 있는 위치는 파란색 ※표시가 되어있다.
* 돌을 놓을 자리가 없어 패스할 경우 자동으로 상대 턴으로 넘어가고 패스 메시지가 출력된다.
* 보드 밑에는 흑과 백의 돌 갯수가 출력되어 각자의 돌 갯수를 확인할 수 있다.
* 두 명 모두 패스하였을 경우 혹은 보드가 꽉 차서 게임이 종료되면 종료 메시지가 출력되고 승자를 알려준다.

## 인게임

![image](https://user-images.githubusercontent.com/101162453/158518275-670e6f3b-b667-4a08-9958-4f92aa87494d.png)
* 처음 실행화면 

![image](https://user-images.githubusercontent.com/101162453/158518422-efb0a171-5c5c-4d34-8862-a89a4fed86ab.png)
* 싱글 모드 선택 시 선/후공 선택 가능

![image](https://user-images.githubusercontent.com/101162453/158518554-893c5da9-9c88-4bfa-8db7-235d707e3b20.png)
* 실제 플레이 시작 시 화면. 본인 차례에 파란색 ※표시가 된 부분에 돌을 놓을 수 있다

![image](https://user-images.githubusercontent.com/101162453/158519566-23b4400b-966d-468d-bce6-098ba9fc6b94.png)
* 장애물 설정 시 화면. 원하는 장애물의 수를 입력하여 맵을 바꿀 수 있다

![image](https://user-images.githubusercontent.com/101162453/158519807-e321fe14-1617-404e-88c6-eafdb8d58953.png)
* 장애물을 만든 후 플레이하면 빨간색 X표가 된 부분이 생기며 이 곳에는 돌을 놓을 수 없다


### 멀티 모드 플레이시

![image](https://user-images.githubusercontent.com/101162453/158520473-c7cd041c-fd0d-46e2-bcd7-c8ec81b3590c.png)
* 플레이어 1 화면: 멀티 모드의 '1. 선공(서버)' 를 선택하여 방을 개설한다.
*선공자(서버)의 장애물의 개수가 적용되어 방이 만들어지기 때문에 방을 만들기 전 장애물의 개수를 고르면 된다

![image](https://user-images.githubusercontent.com/101162453/158520823-d48f500d-c470-4522-800c-e354b828298c.png)
* 플레이어 2 화면: 멀티 모드의 '2. 후공(클라이언트)' 를 선택한 후 플레이어 1의 IP주소를 입력하면 게임이 시작된다
