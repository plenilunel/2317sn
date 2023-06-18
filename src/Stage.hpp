//
// Created by Administrator on 6/15/2023.
//

#ifndef SNAKE_STAGE_HPP
#define SNAKE_STAGE_HPP

struct Stage{
    static void stage2(int **map, int height, int width)
    {
        for (int i = height/3; i <= height - height/2; i++)
            map[i][width/3] = BlockType::Wall;

        for (int i = width/3; i <= width - width/2; i++)
            map[height - height/2][i] = BlockType::Wall;
    }

    static void stage4(int **map, int height, int width)
    {
        // ㄱ, ㄴ 벽
        int stage2_x_point = height / 2;
        int stage2_y_point = width / 2;

        if(height % 2 == 0) {
            stage2_x_point--;
        }
        if(width % 2 == 0) {
            stage2_y_point--;
        }

        //ㄴ 모양 벽 생성
        for(int i=stage2_x_point; i<stage2_x_point+10; i++){
            map[i][9] = BlockType::Wall;
        }
        for(int i=9; i<20; i++){
            map[stage2_x_point+9][i] = BlockType::Wall;
        }

        //ㄱ 모양 벽 생성
        for(int i=stage2_x_point; i>stage2_x_point-10; i--){
            map[i][width-9] = BlockType::Wall;
        }
        for(int i=width-9; i>width-20; i--){
            map[stage2_x_point-9][i] = BlockType::Wall;
        }
    }

    static void stage3(int **map, int height, int width)
    {
        int middle_y = height/2;
        int middle_x = width/2;
        //세로 벽을 만드는 반복문
        for (int i = 1; i < height; i++)
            map[i][middle_x] = BlockType::Wall;

        //가로 벽을 만드는 반복문
        for (int i = 1; i < width; i++)
            map[middle_y][i] = BlockType::Wall;

        //배열 중앙의 값은 Corner이어야 한다.
        map[middle_y][middle_x] = BlockType::Conner;

        map[0][middle_x] = BlockType::Conner;
        map[height-1][middle_x] = BlockType::Conner;
        map[middle_y][0] = BlockType::Conner;
        map[middle_y][width-1] = BlockType::Conner;
    }

    static void stage1(int **map, int height, int width)
    {
        int middle_y = height/2;
        int middle_x = width/2;

        int left_wall_pivot_x = height/4 + height/8;
        int left_wall_pivot_y = width/3 + width/6;

        for(int i = 0; i <= left_wall_pivot_x; i++)
            map[left_wall_pivot_y][i] = BlockType::Wall;

        for(int i = 3; i < left_wall_pivot_y; i++)
            map[i][left_wall_pivot_x] = BlockType::Wall;

        for(int i = middle_y; i < left_wall_pivot_y; i++)
            map[i][middle_x] = BlockType::Wall;

        for(int i = middle_x; i > left_wall_pivot_x; i--)
            map[middle_y][i] = BlockType::Wall;

        int right_wall_pivot = height - height / 4 + height / 8;

        for(int i = width-1; i >= right_wall_pivot; i--)
            map[left_wall_pivot_y][i] = BlockType::Wall;

        for(int i = height-right_wall_pivot; i < left_wall_pivot_y; i++)
            map[i][right_wall_pivot] = BlockType::Wall;
    }
};

#endif //SNAKE_STAGE_HPP
