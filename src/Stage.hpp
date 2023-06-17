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
    //0 ~ 69 (width)
    //0 ~ 46 (height)
    // 1, 2 좌표에 벽 만들기
    exam_map[1][2] = BlockType::Wall;
    //1,3 좌표에 벽 만들기
    exam_map[1][3] = BlockType::Wall;

    // 원래 동적으로 맵 사이즈 정하려 했는데 그냥 저 사이즈가 max라고 생각 하고 안쪽에서 벽을 만들어 주시면 됩니다.
    //

}

void makeStage()
#endif //SNAKE_STAGE_HPP
