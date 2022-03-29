#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

#define differentiateStep 0.001

template<int inDOF, int outDOF>
class LLAMAKinematics{
    private:
        Matrix<float, inDOF, 1>* newtonianAdditionMatrices;
    public:
        LLAMAKinematics(){
            // Matrix<float, inDOF, 1> tempZeros =  MatrixXd::Zero(inDOF, 1); 
            // for(int i = 0; i < inDOF; i++){
            //     MatrixXd tempDisp = tempZeros;
            //     newtonianAdditionMatrices[i];
            // }
        }

        /**
         * @brief FK function that calculates the forward kinematics
         * 
         * @param Q the input vector of actuator values
         * @return Matrix<float,outDOF,1> X(state) given Q(actuator values)
         */
        virtual Matrix<float,outDOF,1> FK(Matrix<float, inDOF, 1> Q);

        
        /**
         * @brief IK function that calculates the inverse kinematics
         * 
         * @param X the state
         * @return Matrix<float,inDOF,1> Q(actuator values) given X(state)
         */

        virtual Matrix<float,inDOF,1> IK(Matrix<float, outDOF, 1> X);

        // virtual Matrix<float, outDOF, inDOF> Jacobian(Matrix<float, inDOF, 1> Q){
        //     Matrix<float,outDOF,1> jacobianToReturn;
        //     Matrix<float, inDOF, 1> neutonianApproximationInput = Q;
        //     for(int i = 0; i < inDOF; i++){

        //     }
        //     jacobianToReturn << (FK())
        //     for(int i = 0; i < inDOF; i++){
        //     }
        // }

};


//global function for "decomposing" homogenous transformation matrices to 6DOF states [x, y, z, psi, theta, phi]

// //Put in LLAMAFunction namespace
// Matrix<float, 6,1> decomPose(Matrix<float, 4, 4> HTMatrix){
//     //[x; y; z] = HTMatrix(0,3)?  
//     //Find null space of (R-I), w_hat -- (unit vector of rotation axis)
//     //Find perpendicular vector, w_hat_p
//     //find angle between w_hat_p and R*w_hat_p, mag_w
//     //[psi, theta, phi] = w_hat*mag_w
// }
