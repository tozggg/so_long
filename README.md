# so_long
[subject](https://github.com/tozggg/so_long/blob/master/subject.pdf)  
MiniLibX 라이브러리를 이용해서 2d게임 만들기  
<br>
<img width="50%" src="https://user-images.githubusercontent.com/65519376/202486713-2f4df96d-1ef8-426c-8afb-eb121eb14428.gif"/>
<br>
<br>
## Details
### MiniLibx

```c
#include <mlx.h>

// 소프트웨어와 디스플레이 연결, mlx_ptr 리턴
void *mlx_init();

// 윈도우 관리 함수
//새창열기, win_ptr 리턴
void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
//창 삭제
int mlx_destroy_window(void *mlx_ptr, void *win_ptr);

// 이미지 관련 함수
//경로의 xpm파일 이미지불러오기, img_ptr 리턴
void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
//이미지 윈도우의 좌표에 위치
int *mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

// 스트링, 픽셀 관련 함수
int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *str);
int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);

// 이벤트 관련 함수
//이벤트 루프
int mlx_loop(void *mlx_ptr);
//이벤트 핸들러(특정 키 입력)
int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
//아무 이벤트도 일어나지 않을시 핸들러 함수 호출?
int mlx_loop_hook(void *mlx_ptr, int (*funct)(), void *param);

// 윈도우 검은창으로
int mlx_clear_window(void *mlx_ptr, void *win_ptr);
```

### 허용함수

```c
open
close
read
write
malloc
free
perror
strerror
exit
```

### 제약조건

- MiniLibX 사용
- 창 최소화, 창 전환 가능
- 지도 ⇒ 벽=1, 빈공간=0, 수집품=C, 출구=E, 시작지점=P
- 쉘에 움직인 횟수 출력
- 상하좌우 이동 ⇒ WASD
- 창닫기 ⇒ esc, x버튼

### 보너스

- 적 추가
- 스프라이트에 움직임
- 화면상에 움직인 횟수 출력

---

### checklist

#### Mandatory

- make, 리링크, 컴파일 옵션 확인
- 맵 관련
    - 다른 (크기의) 맵 실행
    - 맵 오류시 error출력하고 종료
        - 직사각형
        - 벽으로 둘러쌓여있을때
        - 요소들의 개수 ( P=1 E=1 C≥1 )
- 디스플레이 관련
    - 맵이 제대로 디스플레이 되는지
    - 창은 프로그램 실행동안 열려있어야 함
    - 창을 최소화 해도 창의 내용은 일관성
- 이벤트 관련
    - 빨간 x클릭시 종료
    - esc키가 종료
    - WASD 테스트
- 플레이어 관련
    - 플레이어가 지도상에 위치한 곳에 있는지, WASD 테스트
- 벽, 스프라이트 관련
    - 플레이어가 벽을 통과할 수 없다
    - 수집품이 잘 배치되어 있으며 플레이어가 위를 지나갈 수 있다.
    - exit가 배치되어 있으며 플레이어는 모든 수집품을 얻은후에 통과 가능
    - 벽면을 제외한 모든곳을 움직일수 있다.
- 카운팅
    - 쉘에는 움직은 횟수를 세는 카운터 존재
- 픽셀 관련 함수를 사용하지 않고 이미지 함수를 사용했는지

#### Bonus

- 적과의 접촉시 패배 ⇒ 구현 x
- 스프라이트 애니메이션 존재
- 이동 카운터를 화면에 표기
