
class Actuator{
    private:
    public:
        /**
         * @brief Set the Target
         * 
         * @param setTarget the value for the actuator to reach
         */
        virtual void setTarget(float setTarget);

        /**
         * @brief Get the Target
         * 
         * @return float the target the actuator means to achieve
         */
        virtual float getTarget();

        /**
         * @brief Get the current actuator Value
         * 
         * @return float the current actuator value
         */
        virtual float getValue();

        /**
         * @brief if the actuator value is within +-errorBound of the target
         * 
         * @param errorBound the error bound
         * @return true if the current value is within +- errorBound of the target
         * @return false id the current value is not within +-errorBound of the target
         */
        virtual bool hasReached(float errorBound);

        /**
         * @brief runs the actuator.
         * 
         */
        virtual void runBot();
};