#include "Actuator.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

class ActuatorManager<int inDOF>{
    private:
        Actuator** actuatorArray;
    public:
        ActuatorManager(){}

        /**
         * @brief Set the Target to go to. This target can be any controllable time derivative of position as specified by actuator. 
         * 
         * @param Q The input vector of target states
         */
        void setTarget(Matrix<float,inDOF,1> Q);

        /**
         * @brief Gets the set Target pulled from each actuator
         * 
         * @return Matrix<float,inDOF,1> the current target set 
         */
        Matrix<float,inDOF,1> getTarget();

        /**
         * @brief Get the actuator Values
         * 
         * @return Matrix<float,inDOF,1> the current actuator values as stored by the Actuator object 
         */
        Matrix<float,inDOF,1> getValues();

        /**
         * @brief Returns if actuators have reached. Unless an index is specified, it returns if all actuators arewithin an error bound of the target
         * 
         * @param errorBound the bounds of the target to check within. 
         * @param actuatorIndex Which actuator to poll. If default (-1), chooses to check all actuators
         * @return true if the value is within +-errorBound of the target 
         * @return false if the current value is not within +-errorBound of the target
         */
        bool hasReached(float errorBound, int actuatorIndex = -1);

        /**
         * @brief runs each actuator sequentially.
         */
        void runBot();
};