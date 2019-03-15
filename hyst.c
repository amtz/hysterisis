#include <stdio.h>

#define MAX 10

struct pairs {
    int input;
    int output;
};

struct points {
    int count;
    struct pairs at[MAX];
};

struct hyst
{
    int hysterisis;
    int prev_idx;
    struct points points;
};

struct hyst h =
{
    .hysterisis = 2,
    .prev_idx = 0,
    .points = {
        .count = 6,
        .at = {
            {
                0, 0
            },
            {
                10, 100
            },
            {
                20, 250
            },
            {
                35, 400
            },
            {
                45, 900
            },
            {
                90, 1000
            },
        }
    }
};

int hyst_get_out(struct hyst * hyst, int input)
{
    int idx = hyst->prev_idx;

    if (input >= hyst->points.at[idx].input)
    {
        while (idx < hyst->points.count - 1)
        {
            if (input >= hyst->points.at[idx + 1].input + hyst->hysterisis / 2)
                idx++;
            else
                break;
        }
    }
    else
    {
        while (idx > 0)
        {
            if (input < hyst->points.at[idx].input - hyst->hysterisis / 2)
                idx--;
            else
                break;
        }
    }

    hyst->prev_idx = idx;

    /*printf("input=%d, idx = %d\n", input, idx);*/

    return hyst->points.at[idx].output;
}

#define A(in) do {\
        int o = hyst_get_out(&h, in);\
        printf("input %d => %d\n", in, o);\
    } while (0)

int main(int argc, char* argv[])
{
    A(1);
    A(8);
    A(9);
    A(10);
    A(11);
    A(12);
    A(19);
    A(20);
    A(21);
    A(23);
    A(46);
    A(19);
    A(15);
    A(10);
    A(9);
    A(8);

    return 0;
}
