#include "gradient.h"
//view[y][x]

path_point highest_of_(float view[VIEW_SIZE][VIEW_SIZE], path_point head){
    int y, x;
    int max_y = -6, max_x = -6;
    int rel_y = 0, rel_x = 0;
    float max = view[5][5];
    path_point temp = {head.x,head.y};
    for(y=0; y<VIEW_SIZE; y++){
        max_y = -6;
        max_x++;
        for(x=0; x<VIEW_SIZE; x++){
            max_y++;
            //printf("view[%d][%d] = %f | Relative = [%d][%d]\n", y,x, view[y][x], max_y, max_x);
            if(max < view[y][x]){
                max = view[y][x];
                rel_x = max_x;
                rel_y = max_y;
                //printf("New Max -> %f\n", max);
            }
        }
    }
        //printf("Highest height found: [%f]\n\n",max);
        temp.x += rel_y;
        temp.y += rel_x;

        return temp;
}
void leap(path_point head, path_point temp){

}

path_point find_highest_point(){
    path_point head = {50,50};
    path_point temp;
    path_point old = {25,25};
    path_point old2 = {25,25};
    float view[VIEW_SIZE][VIEW_SIZE];
    while(1){
        generate_view(view, head.y, head.x);
        //printf("Value of head -> %f\n\n", view[5][5]);

        temp = highest_of_(view, head);

        //printf("Head moved from [%d][%d] --> [%d][%d]\n\n", head.y,head.x,temp.y,temp.x);
        if(view[5][5] == -1){
            //printf("Out of bounds!\n");
            //printf("Bounced from [%d][%d] --> ",temp.y,temp.x);
                if(temp.x > old2.x){
                    temp.x = round(temp.x*0.8);
                }else{
                    temp.x = round(temp.x*1.2);
                }
                if(temp.y > old2.y){
                    temp.y = round(temp.y*0.8);
                }else{
                    temp.y = round(temp.y*1.2); 
                }
            //printf("[%d][%d]\n\n",temp.y,temp.x);
        }
        if(temp.x == head.x && temp.y == head.y){
            if(declare_peak(head.x,head.y)){
                //printf("==============================================================================================================================\n");
                //printf("peak found\n");
                //printf("==============================================================================================================================\n\n\n");
                break;
            }else{
                //printf("peak not found, possible plateau, preparing leap. . .\n\n");
                if(view[5][5] > 390){
                    //printf("head close to peak, careful leap\n");
                    //printf("Leaped from [%d][%d] --> ",temp.y,temp.x);
                    if(old.x > old2.x){
                        temp.x = round(temp.x*1.1);
                    }else if(old2.x > old.x){
                        temp.x = round(temp.x*0.9);
                    }
                    if(old.y > old2.y){
                        temp.y = round(temp.y*1.1);
                    }else if(old2.x > old.y){
                        temp.y = round(temp.y*0.9); 
                    }
                    //printf("[%d][%d]\n\n",temp.y,temp.x);
                }else{
                    //printf("Leaped from [%d][%d] --> ",temp.y,temp.x);
                    if(old.x > old2.x){
                        temp.x = round(temp.x*1.3);
                    }else if(old2.x > old.x){
                        temp.x = round(temp.x*0.7);
                    }
                    if(old.y > old2.y){
                        temp.y = round(temp.y*1.3);
                    }else if(old2.x > old.y){
                        temp.y = round(temp.y*0.7); 
                    }
                    //printf("[%d][%d]\n\n",temp.y,temp.x);
                }
            }
        }
        old2 = old;
        old = head;
        head.x = round(temp.x);
        head.y = round(temp.y);
    }
    return head;
}

