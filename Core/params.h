#define WALL_BASE_FR  800  //前壁右センサ
#define WALL_BASE_FL  800  //前壁左センサ
#define WALL_BASE_R   400  //右壁センサ
#define WALL_BASE_L   400  //左壁センサ
#define WALL_BASE 600     //中心時両壁センサ値
#define WALL_CUT 300

#define dt 0.001f //s
#define REDUCTION_RATIO (float)(40.0/13.0)
#define MOUSE_WEIGHT 0.098f //kg
#define WHEEL_DIAMETER 0.0238f //0.0245m
#define CSoF 1.2 //coefficient of static friction
#define STATIC_FRICTION (MOUSE_WEIGHT*9.806*CSoF)
#define ENC_RES_HALF 8192
#define ENC_RES_MAX 16384
#define MPP ((float)(WHEEL_DIAMETER*M_PI)/ENC_RES_MAX)

#define COUNTER 840
#define Ke 4820 //min^-1/V
#define Rm 1.07 //Ω
#define Km (1.98/1000.0) //N*m/A
#define DT 0.001

#define MAZE_SIZE_X 16
#define MAZE_SIZE_Y 16
#define GOAL_X 7    //7
#define GOAL_Y 7    //7
#define START_NODE 15
#define GOAL_NODE 224    //229
#define MAP_SIZE_X 15    //15
#define MAP_SIZE_Y 15   //15

#define STRAIGHT_P 0.00155f //0.3  0.34  0.34 0.4 0.42 0.42
#define STRAIGHT_D 0.05f    //0.32  0.28  0.25 0.21 0.2 0.15
#define DIAGONAL_STRAIGHT_P 0.06f
#define DIAGONAL_STRAIGHT_D 0.25f

const float VKp = 50.0f;
const float VKi = 50.0f;
const float VKd = 0;
const float WKp = 85.0f; //90
const float WKi = 1200.0f;
const float WKd = 0;

const float ReductionRation = (float)40.0f/13.0f;        
const float RotationConst = 4820.0f;     //[rpm/V]
const float RotationConstRadian = (float)(RotationConst*2.0f*M_PI)/60.0f;      //[(rad/s)/V]
const float TorqueConst = 0.505f;         //[mNm/AZ]
const float MotorResistance =  1.07f;    //[Ω]
const float Mass = 105.0f;                //[g]：機体重量
const float Inertia = 0.056595;            //[g・m2] 56494 g mm2
const float TierMass = 5.6f;             //[g]
const float TierRadius = 11.9f;          //[mm]
const float TierInertia = (float)(TierMass*TierRadius*TierRadius)/2.0f;          //[g・mm2]
const float TreadWidth = 67.0f;          //[mm] 65

const int16_t Sensor_table[7][2] = {
    {325, 150},
    {355, 130},
    {515, 110},
    {670, 90},
    {920, 70},
    {1420, 50},
    {1550, 30}
};

const int16_t Front_Sensor_table_r[7][2] = {
    {1020, 180},
    {1400, 150},
    {2000, 120},
    {2750, 100},
    {3110, 90},
    {3360, 70},
    {3480, 55}
};

const int16_t Front_Sensor_table_l[7][2] = {
    {1140, 180},
    {1550, 150},
    {2400, 120},
    {3180, 100},
    {3300, 90},
    {3480, 70},
    {3550, 55}
};

//----方向転換用定数----
#define DIR_TURN_R90  0x01  //右90度回転
#define DIR_TURN_L90  0xff  //左90度回転
#define DIR_TURN_180  0x02  //180度回転