#include "GestureVisualizer.h"
#include "gestures.h"
#include <iostream>

GestureVisualizer::GestureVisualizer()
{
}

void GestureVisualizer::show_static(Hand_discrete hd)
{
    if (!(hd == this->previousStaticGesture))
    {
        if (hd.l_hand || hd.r_hand)
        {
            if (hd.l_hand)
            {
                printf("Left: (%d %d %d) (%d %d %d %d %d) ", hd.l_roll, hd.l_yaw, hd.l_pitch, hd.l_pinky, hd.l_ring, hd.l_middle, hd.l_index, hd.l_thumb);
            }

            if (hd.r_hand)
            {
                printf("Right: (%d %d %d) (%d %d %d %d %d) ", hd.r_roll, hd.r_yaw, hd.r_pitch, hd.r_thumb, hd.r_index, hd.r_middle, hd.r_ring, hd.r_pinky);
            }
            printf("\n");
        }
    }
    this->previousStaticGesture = hd;
}
