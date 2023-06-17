//
// Created by Administrator on 6/15/2023.
//

#ifndef SNAKE_STAGE_HPP
#define SNAKE_STAGE_HPP

#define DIM_X 69
#define DIM_Y 46

//example
int exam_map[DIM_Y][DIM_X];
void stage1()
{
    //가운데 십자 벽
    
    int stage1_x_point = DIM_Y / 2; //배열 중앙 x좌표
    int stage1_y_point = DIM_X / 2; //배열 중앙 y좌표

    if(DIM_Y % 2 == 0){
        stage1_x_point--; //현재 배열의 가로가 짝수일 경우 1을 빼준다.
    }   
    if(DIM_X % 2 == 0){
        stage1_y_point--; //현재 배열의 세로가 짝수일 경우 1을 빼준다.
    }

    //세로 벽을 만드는 반복문
    for(int i=stage1_x_point-(stage1_x_point/2); i<stage1_x_point+(stage1_x_point/2); i++){
        exam_map[i][stage1_y_point] = BlockType::Wall;
    }

    //가로 벽을 만드는 반복문
    for(int i=stage1_y_point-(stage1_y_point/2); i<stage1_y_point+(stage1_y_point/2); i++){
        exam_map[stage1_x_point][i] = BlockType::Wall;
    }

    //배열 중앙의 값은 Conner이어야 한다.
    exam_map[stage1_x_point][stage1_y_point] = BlockType::Conner;
}

void stage2()
{
    // ㄱ, ㄴ 벽
    
    int stage2_x_point = DIM_Y / 2;
    int stage2_y_point = DIM_X / 2;

    if(DIM_Y % 2 == 0) {
        stage2_x_point--;
    }
    if(DIM_X % 2 == 0) {
        stage2_y_point--;
    }

    //ㄴ 모양 벽 생성
    for(int i=stage2_x_point; i<stage2_x_point+10; i++){
        exam_map[i][9] = BlockType::Wall;
    }
    for(int i=9; i<20; i++){
        exam_map[stage2_x_point+9][i] = BlockType::Wall;
    }

    //ㄱ 모양 벽 생성
    for(int i=stage2_x_point; i>stage2_x_point-10; i--){
        exam_map[i][DIM_X-9] = BlockType::Wall;
    }
    for(int i=DIM_X-9; i>DIM_X-20; i--){
        exam_map[stage2_x_point-9][i] = BlockType::Wall;
    }
}

void stage3()
{
    //4분할 벽
    
    int stage3_x_point = DIM_Y / 2;
    int stage3_y_point = DIM_X / 2;

    if(DIM_Y % 2 == 0){
        stage1_x_point--;
    }   
    if(DIM_X % 2 == 0){
        stage1_y_point--;
    }

    //세로 벽을 만드는 반복문
    for(int i=1; i<DIM_Y-1; i++){
        exam_map[i][stage3_y_point] = BlockType::Wall;
    }

    //가로 벽을 만드는 반복문
    for(int i=1; i<DIM_X-1; i++){
        exam_map[stage3_x_point][i] = BlockType::Wall;
    }

    //배열 중앙의 값은 Corner이어야 한다.
    exam_map[stage3_x_point][stage3_y_point] = BlockType::Conner;

    //
    exam_map[0][stage3_y_point] = BlockType::Conner;
    exam_map[DIM_Y-1][stage3_y_point] = BlockType::Conner;
    exam_map[stage3_x_point][0] = BlockType::Conner; 
    exam_map[stage3_x_point][DIM_X-1] = BlockType::Conner;
}
void makeStage()
#endif //SNAKE_STAGE_HPP
