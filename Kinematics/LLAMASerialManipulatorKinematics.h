#include "LLAMAKinematics.h"

enum FRAME_TYPE{FIXED, PRISMATIC, ROTARY};

struct DHtable{
    float** dhTable;
    FRAME_TYPE* frameTypes;
};

template<int inDOF, int outDOF>
class LLAMASerialManipulatorKinematics: public LLAMAKinematics<inDOF, outDOF>{
    private:
        DHTable dhTable;
        
        Matrix<float, 4, 4> rotaryJointHT(float* dhValues, float Q);
        Matrix<float, 4, 4> prismaticJointHT(float* dhValues, float Q);
        Matrix<float, 4, 4> JointHT(float* dhValues);
    public:
        /**
         * @brief FK function that calculates the forward kinematics
         * 
         * @param Q the input vector of joint values
         * @return Matrix<float,outDOF,1> X(state) given Q(joint values)
         */
        Matrix<float,outDOF,1> FK(Matrix<float, inDOF, 1> Q);

        
        /**
         * @brief IK function that calculates the inverse kinematics
         * 
         * @param X the state
         * @return Matrix<float,inDOF,1> Q(joint values) given X(state)
         */

        virtual Matrix<float,inDOF,1> IK(Matrix<float, outDOF, 1> X);
};