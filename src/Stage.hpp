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

void makeStage()
#endif //SNAKE_STAGE_HPP
